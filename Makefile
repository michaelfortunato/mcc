.PHONY: clean
CC=gcc
CFLAGS= -g -Wall -Wextra -gdwarf-2 -g3

exec.out: main.o lexer.o file.o
	$(CC) $(CFLAGS) -o exec.out main.o lexer.o file.o

main.o: main.c lexer.h
	$(CC) -c $(CFLAGS) main.c

lexer.o: lexer.c lexer.h file.h
	$(CC) -c $(CFLAGS) lexer.c

file.o: file.c file.h
	$(CC) -c $(CFLAGS) file.c

clean:
	rm -f exec *.o *.s
