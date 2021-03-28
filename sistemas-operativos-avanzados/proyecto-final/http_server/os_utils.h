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

// Estructura de inodo
typedef struct inode {
  int tamano;
  char tipo;
  char owner;
  int fecha;
  int Dummy;
  char permisos[6];
  int tabla_contenido[11];
} ListaInode_T;

// Estructura de directorio
typedef struct directorio {
  int inode;
  char nombre[12];
} dir;

// Descriptor de arhivo para SO
int os_fd;

// Elementos principales
dir raiz_temp[64];
char boot[1024];
int lbl[256];
int lil[16];
ListaInode_T Lista_inode[4][16];
dir raiz[64];
int lil_tope;
int lbl_tope;
char dir_nombre[12];

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

#endif
