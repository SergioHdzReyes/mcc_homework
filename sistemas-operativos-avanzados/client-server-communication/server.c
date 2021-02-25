#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "server_utils.h"

#define SERVER_FILE "fifo_server"
#define SIZE_MSG 100

int main(int c, char *s[])
{
  int fd_server;
  char msg[SIZE_MSG];

  // Se intenta abrir fifo para recibir informacion de clientes
  if (mkfifo(SERVER_FILE, 0644) == -1) {
    printf("Error al crear archivo fifo");
    return 1;
  }
  fd_server = open(SERVER_FILE, O_RDONLY);

  if(fd_server != -1) {
    //    while(1) {
    read(fd_server, msg, SIZE_MSG);
    process_client_info(msg);
    //    }
  } else {
    printf("No fue posible crear fifo de servidor.\nAbortando...");
    return 1;
  }

  close(fd_server);
  unlink(SERVER_FILE);

  return 0;
}
