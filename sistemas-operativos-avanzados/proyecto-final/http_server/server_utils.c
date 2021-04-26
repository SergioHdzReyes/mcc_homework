#include "os_utils.h"

// Se inicia servidor
void startServer(char *port)
{
  struct addrinfo hints, *res, *p;

  // getaddrinfo for host
  memset (&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  if (getaddrinfo( NULL, port, &hints, &res) != 0) {
    perror ("getaddrinfo() error");
    exit(1);
  }

  // socket and bind
  for (p = res; p!=NULL; p=p->ai_next) {
    listenfd = socket (p->ai_family, p->ai_socktype, 0);
    if (listenfd == -1) continue;
    if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) break;
  }

  if (p==NULL) {
    perror ("socket() or bind()");
    exit(1);
  }

  freeaddrinfo(res);

  // listen for incoming connections
  if ( listen (listenfd, 1000000) != 0 ) {
    perror("listen() error");
    exit(1);
  }

  save_process_info();
}

// Se procesa solicitud
void process_request(int n)
{
  char mesg[99999], *reqline[3];
  int rcvd, success = 0;

  memset( (void*)mesg, (int)'\0', 99999 );
  rcvd = recv(clients[n], mesg, 99999, 0);

  if (rcvd < 0) {    // receive error
    fprintf(stderr,("recv() error\n"));
  } else if (rcvd == 0) {   // receive socket closed
    fprintf(stderr, "Cliente desconectado repentinamente.\n");
  } else {    // message received
    printf("%s", mesg);
    reqline[0] = strtok (mesg, " \t\n");
    
    if ( strncmp(reqline[0], "GET\0", 4) == 0 ) {
      reqline[1] = strtok (NULL, " \t");
      reqline[2] = strtok (NULL, " \t\n");
      
      if ((strncmp( reqline[2], "HTTP/1.0", 8) == 0) || (strncmp( reqline[2], "HTTP/1.1", 8) == 0)) {
	if ( strncmp(reqline[1], "/\0", 2)==0 ) {
	  printf("Ingrese una ruta valida\n");
	} else {
	  success = 1;

	  reqline[1] = strtok(reqline[1], "/");
	  // Se procesa ruta ingresada
	  process_route(reqline[1]);
	}
      }
    }
  }

  if (success) {
    char *reply = 
      "HTTP/2 200 OK\n"
      //"Date: Thu, 25 Apr 2021 23:47:04 GMT\n"
      //"Server: Apache/2.2.3\n"
      //"Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
      "Content-Type: application/json; charset=UTF-8\n"
      "Content-Length: 33\n"
      "Access-Control-Allow-Origin: *\n"
      "Connection: close\n"
      "\n"
      "callback_shr({\"response\": false})";
    send(clients[n], reply, strlen(reply), 0);
  } else {
    write(clients[n], "HTTP/1.0 400 Bad Request\n", 25);
  }

  // Se cierra Socket
  shutdown (clients[n], SHUT_RDWR);
  close(clients[n]);
  clients[n]=-1;
}

void process_route(char *route)
{
  int opc = -1;
  char *commands[10] = {"mkdir", "ls"};
  char command[50], params[100];  
  printf("Procesando ruta: %s\n", route);

  strcpy(command, strtok(route, "?"));
  strcpy(params, strtok(NULL, "\r\n"));
  printf("COMMAND: %s\n", command);
  printf("PARAMS: %s\n", params);
  
  for (int i = 0; i < 10; i++)
    if (commands[i] == command)
      opc = i;

  if (opc >= 0) {
    switch(opc) {
    case 0:
      create_directory(params);
      break;
    }
  }
  printf("Termino process_route\n");
}

void stop_server()
{
  int pid_fd, pid;
  char pid_str[10];
  
  if ((pid_fd = open(PID_PATH, O_RDONLY)) < 0) {
    printf("Imposible leer archivo pid, verifique permisos de lectura.\n");
    exit(3);
  }

  read(pid_fd, pid_str, 10);
  printf("PID: %s", pid_str);

  sscanf(pid_str, "%d", &pid);

  close(pid_fd);
  kill(pid, SIGKILL);
  printf("\nDeteniendo servidor...\n\n");

  // TODO Utilizar el remove del signal_handler
  remove(PID_PATH);
  
  exit(0);
}

void signal_handler(int sig_num)
{
  if (sig_num == SIGKILL) {
    printf("\nDeteniendo servidor...\n\n%s", PID_PATH);
    
    if (remove(PID_PATH) != 0) {
      printf("No fue posible detener el servidor. Debe ser usuario root.\n");
    }
    exit(0);
  }
}

void set_signals()
{
  signal(SIGKILL, signal_handler);
}

int save_process_info()
{
  int pid_fd, pid;
  char pid_str[10];
  
  if ((pid_fd = open(PID_PATH, O_RDWR|O_CREAT, 0644)) < 0) {
    printf("Imposible crear archivo de proceso, verifique permisos de escritura.\n");
    exit(3);
  }

  pid = getpid();
  sprintf(pid_str, "%d", pid);
  write(pid_fd, pid_str, sizeof(pid_str));
  close(pid_fd);

  return 0;
}

int set_daemon_process()
{
  pid_t process_id = 0;
  pid_t sid = 0;

  // Se crea proceso hijo
  process_id = fork();
  // Indica que fork() fallo
  if (process_id < 0) {
    printf("No se pudo crear el proceso hijo!\n");
    exit(1);
  }

  // Proceso padre necesita matarse
  if (process_id > 0) {
    printf("process_id de proceso hijo %d \n", process_id);
    exit(0);
  }

  //unmask the file mode
  umask(0);

  // Se configura nueva sesion
  /* sid = setsid(); */
  /* if(sid < 0) { */
  /*   exit(1);  // Fallo */
  /* } */
  
  return 0;
}
