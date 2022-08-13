#ifndef FILE_H
#define FILE_H

#define BUFF_1_SIZE 4096

#define BUFF_2_SIZE BUFF_1_SIZE

#define BUFF_SIZE (BUFF_1_SIZE + BUFF_2_SIZE)

extern char buffer[BUFF_SIZE];

extern char *cp;

#define AT_EOF (*cp == EOF)

#define AT_EOB1 (cp == &buffer[BUFF_1_SIZE - 1])

#define AT_EOB2 (cp == &buffer[BUFF_SIZE - 1])

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

#endif