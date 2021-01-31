#include "menu.h"

void print_menu()
{
  printf("Practica #3\n\n\n");
  printf("Dado el contenido del archivo anterior, seguir las siguientes reglas:\n");
  printf("-El apartado de '#' (gatos), solo se pueden modificar de uno por uno, por coordenada (columna, fila).\n");
  printf("-El apartado de '0' (ceros) se modifica por columna.\n\n");

  printf("Ingrese una opcion: \n");
  printf("1) Modificar seccion de '#' (gatos)\n");
  printf("2) Modificar seccion de '0' (ceros)\n");
  printf("3) Imprimir archivo.\n");
  printf("4) Reiniciar archivo.\n");
  printf("0) Salir.\n\n");
}
