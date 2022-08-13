#include <stdlib.h>
#include <stdio.h>
#include "file.h"

char *curr_filepath = NULL;
unsigned int line_number = 0;
unsigned int character_number = 0;

int tokenize_file(char *filepath)
{
  curr_filepath = filepath;
  open_file(filepath);
  return 0;
}

void gettok()
{
  while (1)
  {
    switch (*cp++)
    {
    case EOF:
      if (AT_EOB1)
      {
        reload_buffer_2();
      }
      else if (AT_EOB2)
      {
        reload_buffer_1();
      }
      else
      {
        return 0;
      }
      break;
    default:
    }
  }
}