
#include <stdio.h>
#include <stdlib.h>
#include "log_processor.h"

int main(){
    const char *filename = "access.log";

    long file_size = get_file_size(filename);
    if (file_size <= 0) {
        fprintf(stderr, "ERROR: No se existe el archivo '%s'.\n", filename);
        return 1;
    }

    proccesFile(filename);

    return 0;
}
