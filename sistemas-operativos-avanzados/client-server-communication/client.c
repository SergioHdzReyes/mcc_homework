#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int c, char *s[])
{
  int fd;
  char msg[100] = "Mensaje del cliente";

  fd = open("fifo", O_WRONLY);

  if (fd != -1) {
    write(fd, msg, 100);
  }

  close(fd);

  return 1;
}
