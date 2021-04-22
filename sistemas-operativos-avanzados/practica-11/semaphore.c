#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>

pthread_t tid[2];
int counter=0;
pthread_mutex_t lock;
sem_t semaphore;

void* doSomeThing(void * args)
{
  unsigned long i = 0;

  // Seccion critica
  sem_wait(&semaphore);
  counter += 1;
  //sem_post(&semaphore);

  printf("\n Job %d started\n", counter);
  //for(i=0; i<(0xFFFFFFFF);i++);
  printf("\n Job %d finished\n", counter);
  sem_post(&semaphore);

  return NULL;
}

void* doSomeThing2(void * args)
{
  unsigned long i = 0;

  // Seccion critica
  sem_wait(&semaphore);
  counter -= 1;
  //sem_post(&semaphore);

  printf("\n Job %d started\n", counter);
  //for(i=0; i<(0xFFFFFFFF);i++);
  printf("\n Job %d finished\n", counter);
  sem_post(&semaphore);

  return NULL;
}

int main(void)
{
  int i = 0;
  int err;
  sem_init(&semaphore, 0, 1);

  err = pthread_create(&(tid[0]), NULL, &doSomeThing, NULL);
  err = pthread_create(&(tid[1]), NULL, &doSomeThing2, NULL);

  /* while(i < 2) */
  /*   { */
  /*     err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL); */
  /*     if (err != 0) */
  /*       printf("\ncan't create thread :[%s]", strerror(err)); */
  /*     i++; */
  /*   } */

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);

  return 0;
}
