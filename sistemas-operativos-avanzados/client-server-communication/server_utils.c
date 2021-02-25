#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "server_utils.h"

void process_client_info(char *message)
{
  const char s[2] = "|";
  char *token;
  char *data[LIMIT_DATA];
  int aux = 0;
   
  token = strtok(message, s);
  data[aux] = malloc(strlen(token)*sizeof(char) +1);
  strcpy(data[aux], token);
   
  while( token != NULL ) {
    aux++;
    if (aux > LIMIT_DATA) {
      printf("El maximo numero de datos enviados es de %d", LIMIT_DATA);
      exit(1);
    }

    printf( " %s\n", token );
    token = strtok(NULL, s);

    data[aux] = malloc(strlen(token)*sizeof(char) +1);
    strcpy(data[aux], token);
  }

  strcpy(received.pid, data[0]);
  strcpy(received.fullname, data[1]);
  strcpy(received.type, data[2]);
}
