
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "log_processor.h"

void* createThread(void *arg);

int main(){
    pthread_t hilo;
    const char *filename = "access.log";
    long start_byte = 0;
    long end_byte = 0;

    long file_size = get_file_size(filename);
    if (file_size <= 0) {
        fprintf(stderr, "ERROR: No se existe el archivo '%s'.\n", filename);
        return 1;
    }

    end_byte = file_size / NUM_THREADS;
    ThreadArgs *new_thread = malloc(sizeof(ThreadArgs));

    new_thread -> filename = filename;
    new_thread -> start_byte = start_byte;
    new_thread -> end_byte = end_byte;

    pthread_create(&hilo, NULL, createThread, (void*)new_thread);


    pthread_join(hilo, NULL);
    return 0;
}

void* createThread(void *arg){
    ThreadArgs *new_thread = (ThreadArgs*)arg;

    printf("Leyendo desde byte %ld hasta byte %ld\n", new_thread->start_byte, new_thread->end_byte);

    proccesFile(new_thread->filename, new_thread->start_byte, new_thread->end_byte);    
    return NULL;
}