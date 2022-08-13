#include <stdio.h>
#include "file.h"

extern unsigned int num_read;
int main(int argc, char **argv)
{
  if (argc != 2)
  {
    return 1;
  }
  open_file(argv[1]);
  int cnt = 0;

  while (1)
  {
    switch (*cp)
    {
    case EOF:
      if (AT_EOB1)
      {
        // printf("ata buff1");
        printf("Num Read: %d\n", num_read);
        // printf("%c", *cp);
        reload_buffer_2();
      }
      else if (AT_EOB2)
      {
        printf("Num Read: %d\n", num_read);
        // printf("ata buff2");
        reload_buffer_1();
      }
      else
      {
        printf("Num Read: %d\n", num_read);
        // printf("We good? %d\n", close_file());
        return 0;
      }
      break;
    default:
      // printf("%d\n", cnt);
      // printf("%c", *cp);
    }
    ++cp;
    ++cnt;
  }
  // printf("%s", buffer);
  printf("We good? %d\n", close_file());
  return 0;
}