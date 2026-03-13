CC = gcc
FLAGS = -Wall -lpthread

all:
	$(CC) $(FLAGS) main_linux.c log_processor.c -o a

run: all
	./a

clean:
	rm -f a