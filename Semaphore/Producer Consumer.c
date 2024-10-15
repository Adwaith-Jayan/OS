#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int E = 10; // Number of empty slots
int S = 1;  // Binary semaphore for mutual exclusion
int F = 0;  // Number of full slots

char buffer[10];
int n = 0;

void wait(int* sem)
{
   while (*sem <= 0);
   (*sem)--;
}

void signal(int* sem)
{
   (*sem)++;
}

void* producer(void* arg)
{
   char nums[] = {'1', '3', '9', '9', '8', '0', '2'};
   char alpha[] = {'e', 'f', 'g', 'h', 'n'};
   int i = 0, j = 0;
   while (1)
   {
      int type = *((int*)arg);
      if (type == 1)
      {
         char num = nums[i++ % 7];
         wait(&E);
         wait(&S);
         buffer[n++] = num;
         printf("Produced: %c\n", num);
         sleep(1);
         signal(&F);
         signal(&S);
      }
      else if (type == 2)
      {
         char alp = alpha[j++ % 5];
         wait(&E);
         wait(&S);
         buffer[n++] = alp;
         printf("Produced: %c\n", alp);
         sleep(1);
         signal(&F);
         signal(&S);
      }
   }
}

void* consumer(void* arg)
{
   while (1)
   {
      wait(&F);
      wait(&S);
      char item = buffer[--n];
      printf("Consumed: %c\n", item);
      sleep(1);
      signal(&E);
      signal(&S);
   }
}

int main()
{
   pthread_t p1, p2, consumerT;
   int type1 = 1, type2 = 2;
   pthread_create(&p1, NULL, producer, &type1);
   pthread_create(&p2, NULL, producer, &type2);
   pthread_create(&consumerT, NULL, consumer, NULL);
   pthread_join(p1, NULL);
   pthread_join(p2, NULL);
   pthread_join(consumerT, NULL);

   return 0;
}

