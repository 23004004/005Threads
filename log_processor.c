#include <stdio.h>
#include <stddef.h>
#include <sys/stat.h>

long get_file_size(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == 0) {
        return st.st_size;
    }
    return -1;
}

void proccesFile(const char *filename){

    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "No se pudo abrir '%s'\n",
                filename);
        return;
    }

    char line[4096];
    int error_count = 0;
    int lines_reas = 0;

    while (fgets(line, sizeof(line), file)) {

        char ip[64];
        char method[16];
        char url[256];
        char ts[64];

        int status;

        sscanf(line,
            "%255s %*s %*s [%63[^]]] \"%15s %255[^\"]\" %d",
            ip, ts, method, url, &status);

        printf("IP:%s URL:%s STATUS:%d\n", ip, url, status);
        lines_reas++;
        if (status >= 400 && status <= 599) {
            error_count++;
        }
    }

    fclose(file);

    printf("Lineas leidas: %d\n", lines_reas);
    printf("Errores HTTP: %d\n", error_count);
}