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
    if (aux == LIMIT_DATA) {
      break;
    }

    printf( " %s\n", token );
    token = strtok(NULL, s);

    data[aux] = malloc(strlen(token)*sizeof(char) +1);
    strcpy(data[aux], token);
  }

  received.pid = atoi(data[0]);
  received.fullname = malloc(strlen(data[1])*sizeof(char) +1);
  strcpy(received.fullname, data[1]);
  received.type = atoi(data[2]);
}
