#ifndef OPERATING_SYSTEM_OS_UTILS_H
#define OPERATING_SYSTEM_OS_UTILS_H

#include <linux/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Descriptor de arhivo para SO
int os_fd;

// Elementos principales
dir root_tmp[64];
char boot[1024];
int fbl[256];
int fil[16];
inode_list_t inode_list[4][16];
dir root[64];
int fil_max;
int fbl_max;
char dir_nombre[MAX_FILENAME_SIZE];

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

// Crea un directorio
int create_directory();

// Crea un archivo regular
int create_regular_file();

// INICIAN - Algoritmos
int iget();
// TERMINA - Algoritmos

#endif
