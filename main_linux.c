
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "log_processor.h"

void* createThread(void *arg);

int main(){

    pthread_t hilo;

    pthread_create(&hilo, NULL, createThread, NULL);

    const char *filename = "access.log";

    long file_size = get_file_size(filename);
    if (file_size <= 0) {
        fprintf(stderr, "ERROR: No se existe el archivo '%s'.\n", filename);
        return 1;
    }

    proccesFile(filename);
    pthread_join(hilo, NULL);
    return 0;
}

void* createThread(void *arg){
    printf("hola desde el hilo\n");
    return NULL;
}