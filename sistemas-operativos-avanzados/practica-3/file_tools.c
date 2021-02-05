#include "file_tools.h"

void load_config()
{
  filename = "system_calls.txt";
  matrix_config.cols = 15;
  matrix_config.rows = 10;
}

// Crea el archivo principal y lo llena
void create_base_file()
{
  int aux = 0;

  if ((fd = open(filename, O_RDWR|O_CREAT, 0666)) < 0) {
    printf("Imposible crear archivo, verifique permisos de escritura");
    exit(3);
  }

  if (fd) {
    for (int a=0;a<matrix_config.rows;a++) {
      for (int i=0;i<matrix_config.cols; i++) {

        switch (i) {
        case 0:
        case 1:
          buff[aux] = '*';
          break;
        case 2:
        case 3:
        case 4:
          buff[aux] = '#';
          break;
        default:
          buff[aux] = '0';
          break;
        }

        aux++;
      }
    }

    write(fd, buff, aux);
  }
}

void modify_column(int col)
{
  char *character;
  int position = 0;
  col--;

  if (((col < 6) || (col > 15))) {
    printf("Columna no permitida, ingrese un valor entre 6 y 15\n");
    getchar();
    return;
  }

  printf("Ingrese el contenido de la columna (max. 15 caracteres)\n");
  scanf("%s", buff);

  if (strlen(buff) > 15) {
    printf("Caracteres ingresados exceden al maximo.");
    return;
  }

  for (int i=0; i<matrix_config.rows; i++) {
    if (i == 0)
      position = col;
    else
      position += (matrix_config.cols);
    lseek(fd, position, SEEK_SET);
    if (i < strlen(buff)) {
      character = &buff[i];
      write(fd, character, 1);
    }
  }
}

void modify_coordinate(int col, int row)
{
  int position = 0;
  if (!((col >= 3) && (col <= 5))) {
    printf("Columna no permitida, ingrese un valor entre 3 y 5\n");
    getchar();
    return;
  }

  printf("Ingrese el contenido de la celda (max. 1 caracter)\n");
  scanf("%s", buff);

  if (strlen(buff) > 1) {
    printf("Caracteres ingresados exceden al maximo.");
    return;
  }

  position = (((row - 1) * matrix_config.cols) + col-1);
  lseek(fd, position, SEEK_SET);
  write(fd, buff, 1);
}

void print_file()
{
  int position = 0;

  lseek(fd, 0, SEEK_SET);

  for (int i=0; i<=matrix_config.rows; i++) {
    memset(buff, 0, sizeof(buff));
    read(fd, buff, 15);
    printf("%s\n", buff);
  }
}
