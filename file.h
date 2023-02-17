#ifndef FILE_H
#define FILE_H

#define BUFF_1_SIZE 8

#define BUFF_2_SIZE BUFF_1_SIZE

#define BUFF_SIZE (BUFF_1_SIZE + BUFF_2_SIZE)

extern char buffer[BUFF_SIZE];

extern char *cp;

extern unsigned int offset;

#define AT_EOF (*cp == EOF)

#define AT_EOB1 (cp == &buffer[BUFF_1_SIZE - 1])

#define AT_EOB2 (cp == &buffer[BUFF_SIZE - 1])

// New guys
#define AT_EOF_NEW(ptr) (*ptr == EOF)

#define AT_EOB1_NEW(ptr) (ptr == &buffer[BUFF_1_SIZE - 1])

#define AT_EOB2_NEW(ptr) (ptr == &buffer[BUFF_SIZE - 1])

/*
 * Fill buffer 1
 */
void reload_buffer_1();

/*
 * Fill buffer 2
 */
void reload_buffer_2();

/*
 * opens the file
 */
int open_file(char *filepath);

/*
 * closes the file
 */
int close_file();

/*
 * Returns next char in buffer, doing reloading behind the scenes.
 */

char *advance();

void db();

void debug();

#endif