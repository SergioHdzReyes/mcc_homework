#include "server_utils.h"

// Se inicia servidor
void startServer(char *port)
{
  struct addrinfo hints, *res, *p;

  // getaddrinfo for host
  memset (&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  if (getaddrinfo( NULL, port, &hints, &res) != 0) {
    perror ("getaddrinfo() error");
    exit(1);
  }

  // socket and bind
  for (p = res; p!=NULL; p=p->ai_next) {
    listenfd = socket (p->ai_family, p->ai_socktype, 0);
    if (listenfd == -1) continue;
    if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) break;
  }

  if (p==NULL) {
    perror ("socket() or bind()");
    exit(1);
  }

  freeaddrinfo(res);

  // listen for incoming connections
  if ( listen (listenfd, 1000000) != 0 ) {
    perror("listen() error");
    exit(1);
  }
}

// Se procesa respuesta a cliente
void respond(int n)
{
  char mesg[99999], *reqline[3], data_to_send[BYTES], path[99999];
  int rcvd, fd, bytes_read;

  memset( (void*)mesg, (int)'\0', 99999 );

  rcvd=recv(clients[n], mesg, 99999, 0);

  if (rcvd<0)    // receive error
    fprintf(stderr,("recv() error\n"));
  else if (rcvd==0)    // receive socket closed
    fprintf(stderr,"Cliente desconectado repentinamente.\n");
  else    // message received
    {
      printf("%s", mesg);
      reqline[0] = strtok (mesg, " \t\n");
      if ( strncmp(reqline[0], "GET\0", 4)==0 ) {
        reqline[1] = strtok (NULL, " \t");
        reqline[2] = strtok (NULL, " \t\n");
        if ( strncmp( reqline[2], "HTTP/1.0", 8)!=0 && strncmp( reqline[2], "HTTP/1.1", 8)!=0 ) {
          write(clients[n], "HTTP/1.0 400 Bad Request\n", 25);
        } else {
	      if ( strncmp(reqline[1], "/\0", 2)==0 )
            reqline[1] = "/index.html";        // Se busca archivo index.html por default

	      strcpy(path, ROOT);
	      strcpy(&path[strlen(ROOT)], reqline[1]);
	      printf("file: %s\n", path);

          // Archivo encontrado
	      if ( (fd=open(path, O_RDONLY))!=-1 ) {
            send(clients[n], "HTTP/1.0 200 OK\n\n", 17, 0);
            while ( (bytes_read=read(fd, data_to_send, BYTES))>0 )
              write (clients[n], data_to_send, bytes_read);
          } else {
            write(clients[n], "HTTP/1.0 404 Not Found\n", 23); // Archivo no encontrado
          }
	    }
      }
    }

  // Se cierra Socket
  shutdown (clients[n], SHUT_RDWR);
  close(clients[n]);
  clients[n]=-1;
}
