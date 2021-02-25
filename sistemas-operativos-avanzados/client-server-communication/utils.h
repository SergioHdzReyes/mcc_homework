#ifndef MCC_CSC_UTILS_H
#define MCC_CSC_UTILS_H
#include <stdio.h>

int pid;
struct {
  char *name;
  char *lastname;
  int type;
} client_info;

void set_client_info();
char *get_str_code();

#endif
