/* Lexes C files */
#include <stdio.h>
#include "file.h"

static FILE *fp = NULL;

char *cp = NULL;

char buffer[BUFF_SIZE];

unsigned int num_read;

void reload_buffer_1()
{
  num_read = fread(buffer, sizeof(char), BUFF_1_SIZE - 1, fp);
  if ((num_read < BUFF_1_SIZE - 1) && feof(fp))
  {
    buffer[num_read] = EOF;
  }
  cp = buffer;
}

void reload_buffer_2()
{
  num_read = fread(&buffer[BUFF_1_SIZE], sizeof(char), BUFF_2_SIZE - 1, fp);
  if ((num_read < BUFF_2_SIZE - 1) && feof(fp))
  {
    buffer[BUFF_1_SIZE + num_read] = EOF;
  }
  cp = &buffer[BUFF_1_SIZE];
}

int open_file(char *filepath)
{
  fp = fopen(filepath, "r");
  buffer[BUFF_1_SIZE - 1] = EOF;
  buffer[BUFF_SIZE - 1] = EOF;
  reload_buffer_1();
  return 0;
}

int close_file()
{
  if (fp == NULL)
  {
    printf("No file is currently open\n");
    return 1;
  }
  return fclose(fp);
}
