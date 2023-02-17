.PHONY: clean
CC=gcc
CFLAGS= -g -Wall -Wextra -gdwarf-2 -g3

exec.out: main.o parser.o lexer.o file.o
	$(CC) $(CFLAGS) -o exec.out main.o parser.o lexer.o file.o

main.o: main.c parser.h lexer.h file.h
	$(CC) -c $(CFLAGS) main.c

parser.o: parser.c parser.h lexer.h
	$(CC) -c $(CFLAGS) parser.c

lexer.o: lexer.c lexer.h file.h
	$(CC) -c $(CFLAGS) lexer.c

file.o: file.c file.h
	$(CC) -c $(CFLAGS) file.c

clean:
	rm -f exec *.o *.s
