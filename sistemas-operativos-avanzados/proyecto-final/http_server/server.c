#include "server_utils.h"

int main(int argc, char* argv[])
{
  struct sockaddr_in clientaddr;
  socklen_t addrlen;
  char c;
  int slot = 0;

  // Se ponen los clientes como -1, significa no hay conectados
  int i;
  for (i=0; i<CONNMAX; i++) {
    clients[i]=-1;
  }

  startServer(PORT);
  printf("Servidor iniciado en el puerto %s%s%s\n", "\033[92m", PORT,"\033[0m");

  // Se queda en ciclo esperando conexiones
  while (1) {
    addrlen = sizeof(clientaddr);
    clients[slot] = accept (listenfd, (struct sockaddr *) &clientaddr, &addrlen);

    if (clients[slot]<0) {
      error ("accept() error");
    } else {
      if ( fork()==0 ) {
        respond(slot);
        exit(0);
      }
    }

    while (clients[slot]!=-1) {
      slot = (slot+1)%CONNMAX;
    }
  }

  return 0;
}
