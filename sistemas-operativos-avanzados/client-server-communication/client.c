#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "client_utils.h"
#define SERVER_FILE "fifo_server"
#define SIZE_MSG 100

int main(int c, char *s[])
{
  int fd_client, fd_server;
  char fifo_name[100], msg[SIZE_MSG];

  // Se intenta abrir comunicacion con servidor
  fd_server = open(SERVER_FILE, O_WRONLY);
  if (fd_server == -1) {
    printf("El servidor no se pudo localizar.\nAbortando...\n");
    return 1;
  }

  set_client_info();
  // Se intenta crear fifo de respuesta, por si server responde ya exista el archivo
  sprintf(fifo_name, "fifo_%d", pid);  
  if (mkfifo(fifo_name, 0644) == -1) {
    printf("Error al crear archivo fifo de respuesta");
    return 1;
  }
  write(fd_server, get_str_code(), 100);

  // Se intenta abrir fifo para recibir info del servidor
  fd_client = open(fifo_name, O_RDONLY);
  if (fd_client != -1) {
    read(fd_client, msg, SIZE_MSG);
  } else {
    printf("No fue posible abrir el archivo fifo\nAbortando...\n");
    close(fd_server);
    return 2;
  }

  printf("Respuesta de servidor:\n%s", msg);

  close(fd_server);
  unlink(fifo_name);

  return 0;
}
