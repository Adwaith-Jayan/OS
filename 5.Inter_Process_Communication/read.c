#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void main()
{
   char* name="/adwaithjayan";
   int size=1000;
   int fd=shm_open(name,O_RDONLY,0666);
   if(fd<0)
   {
      printf("Unsuccesfull\n");
   }
   void* ptr=mmap(0,size,PROT_READ,MAP_SHARED,fd,0);
   char prev[1000]="";
   while(1)
   {
      char current[1000];
      strcpy(current,(char*)ptr);
      if(strcmp(current,prev)!=0)
      {
         printf("Message is: %s\n",current);
         strcpy(prev,current);
      }
   }
   printf("The writtern message is\n");
   printf("%s\n",(char*)ptr);
}
