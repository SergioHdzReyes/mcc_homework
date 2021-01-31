#include <stdio.h>
#include "file_tools.h"
#include "menu.h"

int main(void)
{
  load_config();
  create_base_file();

  system("clear");
  while (1) {
    //system("clear");
    print_menu();

    scanf("%d", &opcion);

    switch (opcion) {
    case 1:
      break;
    case 2:
      break;
    case 3:
      read(fd, buff, sizeof(buff));
      printf("%s", buff);
      break;
    case 4:
      create_base_file();
      break;
    case 0:
      printf("Saliendo del sistema...\n");
      exit(0);
      break;
    default:
      printf("Opcion invalida.");
      break;
    }

    //getchar();
  }

  return 0;
}
