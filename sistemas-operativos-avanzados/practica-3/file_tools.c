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

  if ((fd = open(filename, O_RDONLY)) < 0)
    exit(2);
  if ((fd = open(filename, O_WRONLY|O_CREAT)) < 0)
    exit(3);

  if (fd) {
    for (int a=0;a<matrix_config.rows;a++) {
      for (int i=0;i<=matrix_config.cols; i++) {
        if (i == matrix_config.cols) {
          buff[aux] = 0x0A;
          aux++;
          continue;
        }

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

  close(fd);
}
