#include <stdio.h>
#include "file_tools.h"
#include "menu.h"

#define clear() printf("\033[H\033[J")

int main(void)
{
  load_config();
  create_base_file();

  while (1) {
    clear();
    print_menu();
    scanf("%d", &opcion);

    switch (opcion) {
    case 1:
      printf("Ingrese columna a modificar: \n");
      scanf("%d", &col_sel);
      printf("Ingrese fila a modificar: \n");
      scanf("%d", &row_sel);
      modify_coordinate(col_sel, row_sel);
      break;
    case 2:
      printf("Ingrese columna a modificar: \n");
      scanf("%d", &col_sel);
      modify_column(col_sel);
      break;
    case 3:
      read(fd, buff, sizeof(buff));
      printf("%s", buff);
      break;
    case 4:
      create_base_file();
      break;
    case 0:
      printf("Saliendo del sistema...\n\n\n");
      print_file();
      exit(0);
      break;
    default:
      printf("Opcion invalida.");
      break;
    }

    getchar();
  }

  close(fd);

  return 0;
}
