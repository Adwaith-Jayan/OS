#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void main()
{
   char* name="/adwaithjayan";
   int size=1000;
   int fd=shm_open(name,O_CREAT | O_RDWR,0666);
   if(fd<0)
   {
      printf("ERROR");
      exit(1);
   }
   ftruncate(fd,size);;

   void* ptr=mmap(0,size,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
   char choice;
   do
   {
      printf("Enter message to write\n");
      char* string;
      string=(char*)malloc(100);
      scanf(" %[^\n]",string);
      strcpy(ptr,string);
      free(string);
      printf("Do you want to continue(y/n)?:");
      scanf(" %c",&choice);
   }while(choice=='y'|| choice =='Y');
}

