//
// Created by sergio on 24/09/21.
//

#ifndef PRACTICA_2_CONEXION_H
#define PRACTICA_2_CONEXION_H

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <unistd.h>

using namespace std;

#define PORT 8080
#define MAXLINE 1024

struct MyException : public exception {
    [[nodiscard]] const char *what() const noexcept override {
        return "C++ Exception (what)";
    }
};

class Conexion
{
public:
    int socketFD;
    char buffer[MAXLINE]{};
    struct sockaddr_in serveraddr{}, cliaddr{};

    explicit Conexion(int type);
    ~Conexion();
    void setAsServer();
    void setAsClient();
};

#endif //PRACTICA_2_CONEXION_H
