//
// Created by sergio on 29/09/21.
//

#include "Conexion.h"

Conexion::Conexion(int type) {
    if ( (this->socketFD = socket(AF_INET, type, 0)) < 0 ) {
        perror("Creacion de socket fallida");
        exit(EXIT_FAILURE);
    }

    memset(&this->serveraddr, 0, sizeof(this->serveraddr));
    memset(&this->cliaddr, 0, sizeof(this->cliaddr));
}

Conexion::~Conexion() {
    cout << "Conexion Destructor" << endl;
}

void Conexion::setAsServer() {
    int new_socket;
    const char *answer = "Hola de servidor";
    int opt = 1;

    socklen_t len;
    len = sizeof(this->cliaddr);

    // Se rellena informacion de servidor
    this->serveraddr.sin_family    = AF_INET; // IPv4
    this->serveraddr.sin_addr.s_addr = INADDR_ANY;
    this->serveraddr.sin_port = htons(PORT);

    // Se forza que el socket escuche en puerto 8080
    if (setsockopt(this->socketFD, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt error");
        exit(EXIT_FAILURE);
    }

    // Se enlaza el socket con la direccion del servidor
    if ( bind(this->socketFD, (const struct sockaddr *)&this->serveraddr, sizeof(this->serveraddr)) < 0 ) {
        perror("Enlazado fallido");
        exit(EXIT_FAILURE);
    }

    if (listen(this->socketFD, 3) < 0) {
        perror("Error al escuchar en puerto");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(this->socketFD, (struct sockaddr *)&this->serveraddr, (socklen_t*)&len))<0) {
        perror("Error al aceptar conexiones");
        exit(EXIT_FAILURE);
    }

    read( new_socket , this->buffer, 1024);
    printf("%s\n",this->buffer );
    send(new_socket , answer , strlen(answer) , 0 );
    printf("Mensaje hola enviado\n");
}

void Conexion::setAsClient() {
    int sock;
    const char *hello = "Hola desde cliente";
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error al crear socket \n");
        exit(EXIT_FAILURE);
    }

    this->serveraddr.sin_family = AF_INET;
    this->serveraddr.sin_port = htons(PORT);

    // Se convierten direcciones IPv4 e IPv6, de texto a binario
    if(inet_pton(AF_INET, "127.0.0.1", &this->serveraddr.sin_addr)<=0) {
        printf("\nDireccion invalida/Direccion no soportada \n");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&this->serveraddr, sizeof(this->serveraddr)) < 0) {
        printf("\nConexion fallida\n");
        exit(EXIT_FAILURE);
    }

    send(sock , hello , strlen(hello) , 0 );
    if (!read( sock , this->buffer, 1024)) {
        throw MyException();
    }
    printf("%s\n",this->buffer );
}