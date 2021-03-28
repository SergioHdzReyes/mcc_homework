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
  write(os_fd, lbl, 1024);
  write(os_fd, lil, 1024);
  write(os_fd, Lista_inode, 1024*4);
  write(os_fd, raiz, 1024);
}

int initial_load()
{
  ListaInode_T Lista_inode[4][16] = {{{0}}, {{1024, 'D', 0, 0, 0, "rwxrwx", {8}}}};
  dir raiz[64] = {{2, "."}, {2, ".."}};
  dir raiz_temp[64] = {{0, "."}, {0, ".."}};
  int boot[1024] = {0};
  int lbl[256] = {9,10,11};
  int lil[16] = {3,4,5};
  int lil_tope = 0;
  int lbl_tope = 0;
}

int load_from_disk()
{

}

void print_menu()
{
  printf("\nSeleccione una de las siguientes opciones:\n");
  printf("1) Crear archivo\n");
  printf("2) Crear directorio\n");
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
