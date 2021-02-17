#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int c, char *s[])
{
  int  fd1;
  char msg[100]="";

  fd1 = open("fifo", O_RDONLY);

  if(fd1 != -1) {
    read(fd1, msg, 100);
    puts(msg);
  }

  close(fd1);
}
