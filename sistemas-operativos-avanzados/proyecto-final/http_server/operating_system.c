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

//int main(int argc, char **argv)
int main()
{
  int opc, end = 0;
  char buffer[100], name[12], directory_name[12]; //No puede pasar de 12 porque ese es el tamaño que tenemos para el nombre en el directorio.
  user_login();

  while (1) {
    // Remover y correr servidor en lugar de este menu
    print_menu();
    scanf("%d", &opc);

    switch (opc) {
    case 1:
      printf("Escribe el nombre del directorio: ");
      scanf("%s", name);
      create_directory(name);
      break;
    case 2:
      printf("Escribe el nombre del directorio a borrar: ");
      scanf("%s", name);
      remove_directory(name);
      break;
    case 3:
      printf("Escribe el nombre del directorio a mostrar: ");
      scanf("%s", name);
      show_files_list(name);
      break;
    case 4:
      printf("Escribe el nombre del archivo: ");
      scanf("%s", name);

      printf("\nIngresa el contenido del archivo: ");
      scanf("%*c%[^\n]",buffer);
      create_regular_file(name, buffer);
      break;
    case 5:
      printf("Escribe el nombre del archivo a borrar: ");
      scanf("%s", name);
      remove_file(name);
      break;
    case 6:
      printf("Escribe el nombre del archivo a mostrar: ");
      scanf("%s", name);
      show_file_content(name);
      break;
    case 7:  // MOVER ARCHIVO Y ELIMINAR EL ORIGINAL
      printf("Escribe el nombre del archivo a mover: ");
      scanf("%s", name);
      printf("Escribe el directorio destino: ");
      scanf("%s", directory_name);
      move_file(name, directory_name);
      break;
    case 8:
      printf("Escribe el nombre del archivo a copiar: ");
      scanf("%s", name);
      printf("Escribe el directorio destino: ");
      scanf("%s", directory_name);
      copy_file(name, directory_name);
      break;
    case 9:
      printf("Escribe el nombre del directorio: ");
      scanf("%s", name);
      change_directory(name);
      break;
    case 10:
      show_current_directory();
      break;
    case 11:
      user_login();
      break;
    case 12:
      system("clear");
      break;
    case 0:
      end = 1;
      break;
    }
    printf("\n");

    if (end) {
      break;
    }
  }

  return 0;
}
