#ifndef MCC_FILE_TOOLS_H
#define MCC_FILE_TOOLS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int fd, opcion;
char buff[160];
char *filename;
struct {
  int cols;
  int rows;
} matrix_config;

void load_config();
void create_base_file();

#endif
