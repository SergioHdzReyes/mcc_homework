#include "utils.h"
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

void set_client_info()
{
  char str[100];
  int val;

  pid = getpid();
  
  printf("Servicio social y Practicas profesionales\n\n\n");
  printf("Ingrese su nombre:\n");
  scanf("%s", str);
  client_info.name = malloc((strlen(str) + 1)*sizeof(char));
  strcpy(client_info.name, str);

  printf("\nIngrese su apellido:\n");
  scanf("%s", str);
  client_info.lastname = malloc((strlen(str) +1)*(sizeof(char)));
  strcpy(client_info.lastname, str);
  
  printf("\nSeleccione el tipo de tramite que quiere realizar:\n1) Servicio Social\n2) Practicas Profesionales\n");
  scanf("%d", &val);
  client_info.type = val;
}

char *get_str_code()
{
  char strng[100];
  char aux[10];
  sprintf(aux, "%d", client_info.type);

  sprintf(strng, "%d", pid);
  strcat(strng, "|");
  strcat(strng, client_info.name);
  strcat(strng, " ");
  strcat(strng, client_info.lastname);
  strcat(strng, "|");
  strcat(strng, aux);

  char *final = malloc(strlen(strng)*sizeof(char)+1);
  final = strng;
  return final;
}
