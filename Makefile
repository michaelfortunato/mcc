.PHONY: clean
CC=gcc
CFLAGS= -Wall -Wextra -g -O0

# TODO: Learn how to do this properly
TARGET_DIR = .
SOURCE_DIR = .


# exec.out: main.o parser.o lexer.o file.o
# 	$(CC) $(CFLAGS) -o exec.out main.o parser.o lexer.o file.o
# 
# main.o: main.c parser.h lexer.h file.h
# 	$(CC) -c $(CFLAGS) main.c
# 
# parser.o: parser.c parser.h lexer.h
# 	$(CC) -c $(CFLAGS) parser.c
# 
# lexer.o: lexer.c lexer.h file.h
# 	$(CC) -c $(CFLAGS) lexer.c
# 
# file.o: file.c file.h
# 	$(CC) -c $(CFLAGS) file.c

exec: main.o hashtable.o linkedlist.o
	$(CC) $(CFLAGS) -o exec main.o hashtable.o linkedlist.o
	
main.o: main.c hashtable.h linkedlist.h
	$(CC) -c $(CFLAGS) main.c -o main.o

hashtable.o: hashtable.c hashtable.h
	$(CC) -c $(CFLAGS) hashtable.c -o hashtable.o

linkedlist.o: linkedlist.c linkedlist.h
	$(CC) -c $(CFLAGS) linkedlist.c -o linkedlist.o

clean:
	rm -f exec *.o *.s

