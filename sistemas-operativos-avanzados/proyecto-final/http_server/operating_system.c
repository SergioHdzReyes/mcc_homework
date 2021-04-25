/*****************************************************************************************************************************************************************************

File system: superbloque, bootblock, lista de inodos, bloque de datos.
bloque de 1k
nuestro sistema tendra 1MB de informacion.
1k = botblock
1k = LBL
1k = 16 # de inode libres, otros datos
4k = lista de inodes

50 Archivos

*******************************************************************************************************************************************************************************/

#include "os_utils.h"

int main(int argc, char **argv)
{
  int pid_fd;
  system("clear");
  set_signals();
  process_params(argc, argv);

  
  
  if ((pid_fd = open(PID_PATH, O_RDONLY)) > 0) {
    printf("El servidor ya esta ejecutandose.\nSaliendo...\n");
    close(pid_fd);
    exit(0);
  }

  
  set_daemon_process();

  struct sockaddr_in clientaddr;
  socklen_t addrlen;
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

    printf("\nSiguiente peticion...\n\n");
  }

  close(os_fd);
  return 0;
}
