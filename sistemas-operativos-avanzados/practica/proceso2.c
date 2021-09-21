#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
int main(void)
{
  int llave, mc;
  char *mensaje, *p;
  llave=ftok(".",30);
  mc=shmget(llave, 512, IPC_CREAT | 0600);//rw- --- ---
  mensaje= shmat(mc,NULL,0);
  
  printf("Cadena %s", mensaje);
  //gets(mensaje);
  /* p=mensaje; */
  /* p+=strlen(mensaje); */
  shmdt(mensaje);
}
