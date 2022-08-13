.PHONY: clean

exec: main.o lexer.o file.o
	gcc -o exec main.o lexer.o file.o

main.o: main.c file.h
	gcc -c -g main.c

lexer.o: lexer.c lexer.h file.h
	gcc -c -g lexer.c

file.o: file.c file.h
	gcc -c -g file.c

clean:
	rm -f exec *.o *.s
