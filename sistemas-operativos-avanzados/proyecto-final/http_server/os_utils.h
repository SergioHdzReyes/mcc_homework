#ifndef OPERATING_SYSTEM_OS_UTILS_H
#define OPERATING_SYSTEM_OS_UTILS_H

#include <linux/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define OS_FILENAME "os_image"
#define MAX_FILENAME_SIZE 12

// Estructura de inodo
typedef struct inode {
  int size;
  char type;
  char owner;
  int date;
  int dummy;
  char permissions[6];
  int content_table[11];
} inode_list_t;

// Estructura de directorio
typedef struct directory {
  int inode;
  char nombre[MAX_FILENAME_SIZE];
} dir;

int os_fd;


// Se intenta abrir archivo de imagen
int os_open_image();

// Se carga el sistema en memoria
int load_system();

// Se carga sistema desde disco
int load_from_disk();

// Guarda datos del Sistema Operativo a disco
int save_to_disk();

// Menu para probar sistema
void print_menu();

// Se limpia imagen de SO
void clean_os_image();

// Se establece estatus del sistema
int set_os_status();


// INICIA - FUNCIONES DE COMANDOS
// Crea un directorio
int create_directory(char *name);

// Mostrar archivos
void show_files_list();

// Crea un archivo regular
int create_regular_file(char *name);

// Instala el sistema operativo
void install();
// TERMINA - FUNCIONES DE COMANDOS

// INICIA - PARAMETROS
int process_params(int argc, char **argv);
// TERMINA - PARAMETROS




// UTILERIAS PARA SERVIDOR
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>


#define CONNMAX 1000
#define BYTES 1024
#define PORT "80"
#define ROOT getenv("PWD")
#define PID_PATH "/var/run/os_mcc.pid"

int listenfd, clients[CONNMAX];

void error(char *);

// Inicia el servidor
void startServer(char *port);

// Se procesa peticion de cliente
void process_request(int n);

// Se procesa la ruta, se llena estructura de parametros
void process_route(char *route);

// Con base en estructura de parametros se ejecuta comando correspondiente
void process_command();

// Se detiene el servidor que corre en background por medio de señales
void stop_server();

// Administrador de señales
void signal_handler(int num_sig);

// Se dan de alta señales para nuestro servidor
void set_signals();

// Se guarda pid de servidor en archivo temporal
int save_process_info();

// Funcion para convertir el proceso a demonio, corriendo en background
int set_daemon_process();

#endif
