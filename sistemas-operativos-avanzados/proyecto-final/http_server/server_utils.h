#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>

#define CONNMAX 1000
#define BYTES 1024
#define PORT "10000"
#define ROOT getenv("PWD")

int listenfd, clients[CONNMAX];

void error(char *);

// Inicia el servidor
void startServer(char *port);

// Respuesta a cliente
void respond(int n);
