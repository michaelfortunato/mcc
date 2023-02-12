/* Lexes C files */
#include "file.h"

#include <stdio.h>
static FILE *fp = NULL;

char *cp = NULL;

char buffer[BUFF_SIZE];

unsigned int num_read;

unsigned char newest_buffer = 1;

void reload_buffer_1() {
  num_read = fread(buffer, sizeof(char), BUFF_1_SIZE - 1, fp);
  if ((num_read < BUFF_1_SIZE - 1) && feof(fp)) {
    buffer[num_read] = EOF;
  }
  newest_buffer = 1;
  cp = buffer;
}

void reload_buffer_2() {
  num_read = fread(&buffer[BUFF_1_SIZE], sizeof(char), BUFF_2_SIZE - 1, fp);
  if ((num_read < BUFF_2_SIZE - 1) && feof(fp)) {
    buffer[BUFF_1_SIZE + num_read] = EOF;
  }
  newest_buffer = 2;
  cp = &buffer[BUFF_1_SIZE];
}

int open_file(char *filepath) {
  fp = fopen(filepath, "r");
  buffer[BUFF_1_SIZE - 1] = EOF;
  buffer[BUFF_SIZE - 1] = EOF;
  reload_buffer_1();
  return 0;
}

int close_file() {
  if (fp == NULL) {
    printf("No file is currently open\n");
    return 1;
  }
  return fclose(fp);
}

void db() {
  printf("THEN: %d\n", feof(fp));
  reload_buffer_1();
  printf("NOW: %d\n", feof(fp));
}
/*
char advance() {
  if (*cp == EOF) {
    if (AT_EOB1_NEW(cp)) {
      reload_buffer_2();
    } else if (AT_EOB2_NEW(cp)) {
      reload_buffer_1();
    }
  }
  char c = *cp++;
  return c;
}
*/

char *advance() {
  switch (*cp) {
    case EOF:
      if (AT_EOB1_NEW(cp)) {
        // In this scenario, we did a look a head and then backtracked.
        // don't reload the buffer but do go to the beginning of buffer 2
        if (newest_buffer == 2) {
          cp = &buffer[BUFF_1_SIZE];
        } else {
          reload_buffer_2();
        }
      } else if (AT_EOB2_NEW(cp)) {
        if (newest_buffer == 1) {
          cp = &buffer[0];
        } else {
          reload_buffer_1();
        }
      } else {
        // Otherwise do not fall offf the map
        return cp;
      }
      break;
  }
  return cp++;
}

void debug() {
  for (;;) {
    switch (*cp++) {
      case EOF:
        if (AT_EOB1_NEW((cp - 1))) {
          reload_buffer_2();
          // printf("RELOAD BUFFER 2\n");
          // printf("Here\n");
        } else if (AT_EOB2_NEW((cp - 1))) {
          reload_buffer_1();
          // printf("RELOAD BUFFER 1\n");
          // printf("Here\n");
        } else {
          // printf("At end.");
          return -1;
        }
        continue;
      default:
        printf("%c", *(cp - 1));
    }
  }
}