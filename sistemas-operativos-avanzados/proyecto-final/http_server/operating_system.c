/*****************************************************************************************************************************************************************************

File system: superbloque, bootblock, lista de inodos, bloque de datos.
bloque de 1k
nuestro sistema tendra 1MB de informacion.
1k = botblock
1k = LBL
1k = 16 # de inode libres, otros datos
4k = lista de inodes

50 Archivos

*******************************************************************************************************************************************************************************/

#include "os_utils.h"

int main(int argc, char **argv)
{
  int opc, end = 0;
  char name[12], directory_name[12]; //No puede pasar de 12 porque ese es el tamaño que tenemos para el nombre en el directorio. 

  os_open_image();
  //process_params(argc, argv);

  while (1) {
    // Remover y correr servidor en lugar de este menu
    //system("clear");
    print_menu();
    scanf("%d", &opc);

    switch (opc) {
    case 1:
      printf("Escribe el nombre del directorio: ");
      scanf("%s", name);
      system("clear");
      create_directory(name);
      break;
    case 2:
      printf("Escribe el nombre del directorio a borrar: ");
      scanf("%s", name);
      system("clear");
      remove_directory(name);
      break;
    case 3:
      show_files_list();
      break;
    case 4:
      printf("Escribe el nombre del archivo: ");
      scanf("%s", name);
      system("clear");
      create_regular_file(name);
      break;
    case 5:
      printf("Escribe el nombre del archivo a borrar: ");
      scanf("%s", name);
      system("clear");
      //remove_file(name);
      break;
    case 6:
      printf("Escribe el nombre del archivo a mostrar: ");
      scanf("%s", name);
      //show_file_content(name);
      break;
    case 7:  // MOVER ARCHIVO Y ELIMINAR EL ORIGINAL
      printf("Escribe el nombre del archivo a mover: ");
      scanf("%s", name);
      printf("Escribe el directorio destino: ");
      scanf("%s", directory_name);
      //move_file(name, directory_name);
      break;
    case 8:
      printf("Escribe el nombre del archivo a copiar: ");
      scanf("%s", name);
      printf("Escribe el directorio destino: ");
      scanf("%s", directory_name);
      //move_file(name, directory_name);
      break;
    case 0:
      //save_to_disk();
      end = 1;
      break;
    }

    if (end) {
      break;
    }
  }

  close(os_fd);
  return 0;
}
