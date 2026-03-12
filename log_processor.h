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

long get_file_size(const char *filename);
void proccesFile(const char *filename);

#endif
