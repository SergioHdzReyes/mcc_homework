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
  char name[12];

  os_open_image();
  process_params(argc, argv);

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
      printf("Escribe el nombre del archivo: ");
      scanf("%s", name);
      create_regular_file(name);
      break;
    case 3:
      show_files_list();
      break;
    case 9:
      save_to_disk();
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
