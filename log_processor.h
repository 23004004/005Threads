#ifndef LOG_PROCESSOR_H
#define LOG_PROCESSOR_H

#include <pthread.h>

#define HASH_SIZE 10007
#define NUM_THREADS   4

typedef struct Entry {
    char key[256];
    int count;
    struct Entry *next;
} Entry;

typedef struct {
    const char *filename;
    long start_byte;
    long end_byte;
    Entry *ip_table[HASH_SIZE];
    Entry *url_table[HASH_SIZE];
    int error_count;
} ThreadArgs;

long get_file_size(const char *filename);
void proccesFile(ThreadArgs *args);
#endif
