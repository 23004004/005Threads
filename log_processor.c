#include <stdio.h>
#include <stddef.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include "log_processor.h"

long get_file_size(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == 0) {
        return st.st_size;
    }
    return -1;
}

void init_table(Entry *table[]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        table[i] = NULL;
    }
}

unsigned int hash(const char *str) {
    unsigned int h = 0;

    while (*str) {
        h = (h * 31) + *str;
        str++;
    }

    return h % HASH_SIZE;
}

void insert_or_increment(Entry *table[], const char *key) {

    unsigned int index = hash(key);

    Entry *current = table[index];

    while (current) {

        if (strcmp(current->key, key) == 0) {
            current->count++;
            return;
        }

        current = current->next;
    }

    Entry *new_entry = malloc(sizeof(Entry));

    strcpy(new_entry->key, key);
    new_entry->count = 1;
    new_entry->next = table[index];

    table[index] = new_entry;
}

int count_unique(Entry *table[]) {

    int total = 0;

    for (int i = 0; i < HASH_SIZE; i++) {

        Entry *current = table[i];

        while (current) {
            total++;
            current = current->next;
        }
    }

    return total;
}

void most_visited_url(Entry *table[]) {

    char max_url[256] = "";
    int max_count = 0;

    for (int i = 0; i < HASH_SIZE; i++) {

        Entry *current = table[i];

        while (current) {

            if (current->count > max_count) {
                max_count = current->count;
                strcpy(max_url, current->key);
            }

            current = current->next;
        }
    }

    printf("URL Más Visitada: %s (%d veces)\n", max_url, max_count);
}

void proccesFile(ThreadArgs *args){

    FILE *file = fopen(args-> filename, "r");
    if (!file) {
        fprintf(stderr, "No se pudo abrir '%s'\n",
                args-> filename);
        return;
    }

    fseek(file, args-> start_byte, SEEK_SET);
    if (args-> start_byte > 0) {
        char skip[4096];
        fgets(skip, sizeof(skip), file);
    }


    char line[4096];
    args->error_count = 0;

    init_table(args-> ip_table);
    init_table(args-> url_table);

    while (ftell(file) < args-> end_byte && fgets(line, sizeof(line), file)) {

        char ip[64]     = {0};
        char method[16] = {0};
        char url[256]   = {0};
        char timestamp[64]     = {0};
        int  status     = 0;

        int parsed = sscanf(line,
            "%255s %*s %*s [%63[^]]] \"%15s %255[^\"]\" %d",
            ip, timestamp, method, url, &status);

        if (parsed != 5) continue;

        if (status >= 400 && status <= 599) {
            args->error_count++;;
        }

        insert_or_increment(args-> ip_table, ip);
        insert_or_increment(args-> url_table, url);
    }

    fclose(file);
}

void merge_table(Entry *dest[], Entry *src[]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Entry *current = src[i];
        while (current) {
            for (int j = 0; j < current->count; j++) {
                insert_or_increment(dest, current->key);
            }
            current = current->next;
        }
    }
}