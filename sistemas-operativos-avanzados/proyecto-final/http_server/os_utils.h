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

// Valores por default al arrancar por primera vez el SO
int initial_load();

// Menu para probar sistema
void print_menu();

// Se limpia imagen de SO
void clean_os_image();

// Se establece estatus del sistema
int set_os_status();


// INICIA - FUNCIONES DE COMANDOS
// Crea un directorio
int create_directory();

// Mostrar archivos
void show_files_list();

// Crea un archivo regular
int create_regular_file();

// Instala el sistema operativo
int install();
// TERMINA - FUNCIONES DE COMANDOS


// INICIAN - Algoritmos
int iget();
// TERMINA - Algoritmos

// INICIA - PARAMETROS
int process_params(int argc, char **argv);
// TERMINA - PARAMETROS

#endif
