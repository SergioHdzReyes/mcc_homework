#include "os_utils.h"

// Elementos principales
inode_list_t inode_list[16][4] = {{{0}}, {{1024, 'D', 0, 0, 0, "rwxrwx", {8}}}};
dir root[64] = {{2, "."}, {2, ".."}};
dir root_tmp[64] = {{0, "."}, {0, ".."}};
int boot[1024] = {0};
// TODO rellenar
int fbl[256] = {9,10,11,12,13,14,15};
int fil[16] = {3,4,5,6,7,8,9,10};
int fil_max = 0; //tope
int fbl_max = 0; //tope

char dir_nombre[MAX_FILENAME_SIZE];
char blocks[50][1024] = {'\0'};
// Estatus del sistema, 0 no instalado, 1 instalado
int OS_STATUS = 0;


int os_open_image()
{
  if ((os_fd = open(OS_FILENAME, O_RDWR|O_CREAT, 0666)) < 0) {
    printf("Imposible crear archivo, verifique permisos de escritura.\n");
    exit(3);
  }

  return 0;
}

int load_system()
{
  int tmp_fd;

  if ((tmp_fd = open(OS_FILENAME, O_RDONLY)) < 0) {
    os_open_image();
    clean_os_image();
  } else {
    close(tmp_fd);
    os_open_image();
    load_from_disk();
  }

  return 0;
}

int save_to_disk()
{
  write(os_fd, boot, 1024);
  write(os_fd, fbl, 1024);
  write(os_fd, fil, 1024);
  write(os_fd, inode_list, 1024*4);
  write(os_fd, root, 1024);

  return 0;
}

int load_from_disk()
{
  return 0;
}

void print_menu()
{
  printf("\nSeleccione una de las siguientes opciones:\n");
  printf("1) Crear directorio\n");
  printf("2) Crear archivo\n");
  printf("3) Mostrar archivos\n");
  printf("9) Salir de sistema\n");
  printf("\n\n");
}

void clean_os_image()
{
  int reset[1024] = {0};
  lseek(os_fd, 0, SEEK_SET);

  for(int i =0; i<1024; i++) {
    write(os_fd, reset, 1024);
  }

  lseek(os_fd, 0, SEEK_SET);
}

int set_os_status()
{
  int tmp_fd;

  if ((tmp_fd = open(OS_FILENAME, O_RDONLY)) < 0) {
    OS_STATUS = 0;
  } else {
    close(tmp_fd);
    OS_STATUS = 1;
  }
  
  return 0;
}

// INICIA - FUNCIONES DE COMANDOS
int create_directory(char *name)
{
  int c, f;
  for (int count = 2; count < 62; count++) {
    if (root[count].inode  == 0) { // Primer espacio para inodo
      strcpy(root[count].nombre, name);
      root[count].inode = fil[fil_max]; // siguiente inodo disponible
      fil_max++;

      // utilizar el directorio actual, modificar
      root_tmp[0].inode = root[count].inode;
      root_tmp[1].inode = root[0].inode;
      c = root[count].inode / 16;
      f = (root[count].inode % 16 - 1)*64;

      inode_list[f][c].type = 'd';
      inode_list[f][c].size = 1024;
      inode_list[f][c].date = 170421;

      inode_list[f][c].content_table[0] = fbl[fbl_max];
      fbl_max++;
      memcpy(blocks[inode_list[f][c].content_table[0]] - 9, root_tmp, 1024);
      break;
    }
  }

  return 0;
}

void show_files_list()
{
  for (int aux=0; aux < 64; aux++) {
    if (root[aux].inode != 0) {
      printf("%d %s", root[aux].inode, root[aux].nombre);
    }
  }
}

int create_regular_file(char *name)
{
  int c, f;
  for (int count = 2; count < 62; count++) {
    if (root[count].inode  == 0) { // Primer espacio para inodo
      strcpy(root[count].nombre, name);
      root[count].inode = fil[fil_max]; // siguiente inodo disponible
      fil_max++;

      // utilizar el directorio actual, modificar
      root_tmp[0].inode = root[count].inode;
      root_tmp[1].inode = root[0].inode;
      c = root[count].inode / 16;
      f = (root[count].inode % 16 - 1)*64;

      inode_list[f][c].type = '-';
      inode_list[f][c].size = 1024;
      inode_list[f][c].date = 170421;

      inode_list[f][c].content_table[0] = fbl[fbl_max];
      fbl_max++;
      memcpy(blocks[inode_list[f][c].content_table[0]] - 9, root_tmp, 1024);
      break;
    }
  }
  
  return 0;
}

int install()
{
  char opc;
  
  if (OS_STATUS) {
    printf("El sistema operativo ya se encuentra instalado.\nDesea formatearlo? (s/n):");
    scanf("%c", &opc);

    if (opc != 's') {
      return 0;
    }
  }

  // Se guarda informacion actual del sistema a disco
  save_to_disk();

  if (OS_STATUS)
    printf("\nSe formateo correctamente el sistema.\n");
  else
    printf("\nSe instalo correctamente el sistema.\n");
  getchar();
  
  return 0;
}
// TERMINA - FUNCIONES DE COMANDOS


// INICIA - PARAMETROS
int process_params(int argc, char **argv)
{
  int c;
  set_os_status();

  while (1) {
    static struct option long_options[] = {
      {"install", no_argument,       0, 'i'},
      {"port",    required_argument,       0, 'p'},
    };
      
    int option_index = 0;

    c = getopt_long (argc, argv, "ip",
		     long_options, &option_index);

    // Se detecta final de las opciones.
    if (c == -1)
      break;

    switch (c) {
    case 0:
      /* If this option set a flag, do nothing else now. */
      if (long_options[option_index].flag != 0)
	break;
      printf ("option %s", long_options[option_index].name);
      if (optarg)
	printf (" with arg %s", optarg);
      printf ("\n");
      break;
	
    case 'i':
      install();
      break;
    case 'p':
      printf("PUERTO: \n");
      break;
    case '?':
      /* getopt_long already printed an error message. */
      break;	
    default:
      abort ();
    }
  }
  
  return 0;
}

// TERMINA - PARAMETROS
