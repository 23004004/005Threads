
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "log_processor.h"

void* createThread(void *arg);

int main(){
    pthread_t hilo;
    const char *filename = "access.log";

    long file_size = get_file_size(filename);
    if (file_size <= 0) {
        fprintf(stderr, "ERROR: No se existe el archivo '%s'.\n", filename);
        return 1;
    }

    pthread_create(&hilo, NULL, createThread, (void*)filename);


    pthread_join(hilo, NULL);
    return 0;
}

void* createThread(void *arg){
    const char *filename = (const char*)arg;
    proccesFile(filename);
    return NULL;
}