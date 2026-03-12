
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "log_processor.h"

void* createThread(void *arg);

int main(){
    pthread_t hilos[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];

    const char *filename = "access.log";

    long file_size = get_file_size(filename);
    if (file_size <= 0) {
        fprintf(stderr, "ERROR: No se existe el archivo '%s'.\n", filename);
        return 1;
    }


    for (size_t i = 0; i < NUM_THREADS; i++)
    {
        args[i].filename = filename;
        args[i].start_byte = i * (file_size / NUM_THREADS);
        args[i].end_byte   = (i == NUM_THREADS - 1)
                                ? file_size
                                : (i + 1) * (file_size / NUM_THREADS);

        pthread_create(&hilos[i], NULL, createThread, &args[i]);
    }


    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(hilos[i], NULL);
    }

    return 0;
}

void* createThread(void *arg){
    ThreadArgs *new_thread = (ThreadArgs*)arg;
    proccesFile(new_thread);    
    return NULL;
}