#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
  int cont = 0;
  int pid = fork();

  if (pid == -1) {
    printf("Error");
  } else if (pid) {
    sleep(5);
    kill(pid, SIGINT);
    //printf("Mate a mi hijo con ID: %d\n", pid);
    //fflush(stdout);
    system("ps");
  } else {
    while (cont < 100) {
      printf("Contador: %d\n", cont);
      sleep(1);

      cont++;
    }
  }
}
