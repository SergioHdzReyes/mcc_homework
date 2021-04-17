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

int main()
{
  int opc;
  char name[12];
  load_system();

  char command[100], end = 0;

  while (1) {
    // Remover y correr servidor en lugar de este menu
    print_menu();
    scanf("%d", &opc);

    switch (opc) {
    case 1:
      printf("Escribe el nombre del archivo: ");
      scanf("%s", name);
      create_directory(name);
      break;
    case 2:
      create_regular_file();
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

  /* for (int c=2; c<64; c++) { */
  /*   if (raiz[c].inode == 0) { */
  /*     raiz[c].inode = lil[lil_tope]; */
  /*     strcpy(raiz[c].nombre, nombre); */
  /*     lil_tope++; */
  /*   } */

  /*   Lista_inode[lil[lil_tope]][0].tamano = 1024; */
  /*   Lista_inode[lil[lil_tope]][0].tipo = 'D'; */
  /*   Lista_inode[lil[lil_tope]][0].owner = 1; */
  /*   Lista_inode[lil[lil_tope]][0].fecha = 1803; */
  /*   strcpy(Lista_inode[lil[lil_tope]][0].permisos, "rwxrwx"); */
  /*   Lista_inode[lil[lil_tope]][0].Dummy = 1024; */
  /*   Lista_inode[lil[lil_tope]][0].tabla_contenido = lbl[lbl_tope]; */

  /*   lbl_tope++; */
  /*   raiz_temp[0].inode = raiz[c].inode; */
  /*   raiz_temp[1].inode = raiz[0].inode; */
  /*   //      Write = actualizar el inodo, lil, lbl, */
  /* } */

  close(os_fd);
  return 0;
}
