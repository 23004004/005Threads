#!/bin/bash

echo "Compilando..."
gcc -Wall main_linux.c log_processor.c -o a -lpthread

if [ $? -eq 0 ]; then
    time ./a
else
    echo "Error de compilación"
fi