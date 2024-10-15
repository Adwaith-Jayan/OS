#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int semaphore=1;
int state=1;

void* wait(int* semaphore)
{
   while(*semaphore<=0)
      *(semaphore)--;
}

void* signal(int* semaphore)
{
   sleep(1);
   *(semaphore)++;
}

void* PrintOdd(void* arg)
{
   int num=*((int*)arg);
   while(1)
   {
      wait(&semaphore);
      if(state==1)
      {
         printf("%d\n",num);
         num+=2;
         state=2;
      }
      signal(&semaphore);
   }
}

void* PrintEven(void* arg)
{
   int num=*((int*)arg);
   while(1)
   {
      wait(&semaphore);
      if(state==2)
      {
         printf("%d\n",num);
         num+=2;
         state=1;
      }
      signal(&semaphore);
   }
}

void main()
{
   pthread_t oddT, evenT;
   int odd=1,even=2;
   pthread_create(&oddT,NULL,PrintOdd,&odd);
   pthread_create(&evenT,NULL,PrintEven,&even);
   pthread_join(oddT,NULL);
   pthread_join(evenT,NULL);
}
