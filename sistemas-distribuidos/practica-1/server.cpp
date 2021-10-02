//
// Creado por sergio el 22/09/21.
//

// Modelo Cliente-Servidor implementacion UDP
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT     8080
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    const char *hello = "Hola de servidor";
    struct sockaddr_in servaddr, cliaddr;

    // Se crea descriptor de archivo para socket
    // similar a un archivo normal
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("creacion de socket fallida");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Se rellena informacion de servidor
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Se enlaza el socket con la direccion del servidor
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) {
        perror("Enlazado fallido");
        exit(EXIT_FAILURE);
    }

    int n;
    socklen_t len;

    len = sizeof(cliaddr);

    // Se recibe informacion de la primera conexion,
    // se pausa ejecucion de programa
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
    buffer[n] = '\0';
    printf("Cliente : %s\n", buffer);

    // Se responde a cliente
    sendto(sockfd, (const char *)hello, strlen(hello),
           MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
           len);
    printf("Mensaje Hola enviado.\n");

    return 0;
}
