#ifndef MCC_FILE_TOOLS_H
#define MCC_FILE_TOOLS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fd, opcion, col_sel, row_sel, actions, position;
char buff[150];
char *filename, *number_text[10];

struct {
  int cols;
  int rows;
} matrix_config;

void load_config();
void create_base_file();
void modify_column(int col);
void modify_coordinate(int col, int row);
void print_file();
void save_actions();

#endif
