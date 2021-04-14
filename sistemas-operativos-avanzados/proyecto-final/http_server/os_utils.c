#include "os_utils.h"

int os_open_image()
{
  if ((os_fd = open(OS_FILENAME, O_RDWR|O_CREAT, 0666)) < 0) {
    printf("Imposible crear archivo, verifique permisos de escritura.\n");
    exit(3);
  }
}

int load_system()
{
  int tmp_fd;

  if ((tmp_fd = open(OS_FILENAME, O_RDONLY)) < 0) {
    os_open_image();
    clean_os_image();
    initial_load();
  } else {
    close(tmp_fd);
    os_open_image();
    load_from_disk();
  }
}

int save_to_disk()
{
  write(os_fd, boot, 1024);
  write(os_fd, fbl, 1024);
  write(os_fd, fil, 1024);
  write(os_fd, inode_list, 1024*4);
  write(os_fd, root, 1024);
}

int initial_load()
{
  inode_list_t inode_list[4][16] = {{{0}}, {{1024, 'D', 0, 0, 0, "rwxrwx", {8}}}};
  dir root[64] = {{2, "."}, {2, ".."}};
  dir root_tmp[64] = {{0, "."}, {0, ".."}};
  int boot[1024] = {0};
  int fbl[256] = {9,10,11};
  int fil[16] = {3,4,5};
  int fil_max = 0;
  int fbl_max = 0;
}

int load_from_disk()
{

}

void print_menu()
{
  printf("\nSeleccione una de las siguientes opciones:\n");
  printf("1) Crear archivo\n");
  printf("2) Crear directorio\n");
  printf("3) Salir de sistema\n");
  printf("\n\n");
}
void clean_os_image()
{
  int reset[1024] = {0};
  lseek(os_fd, 0, SEEK_SET);

  for(int i =0; i<1024; i++) {
    write(os_fd, reset, 1024);
  }

  lseek(os_fd, 0, SEEK_SET);
}

// INICIA - Funciones principales de MENU
int create_directory()
{

}

int create_regular_file()
{
  //
}
// TERMINA - Funciones de MENU


// INICIA - Algoritmos para manipular archivos
int iget()
{

}
// TERMINA - Algoritmos "  "
