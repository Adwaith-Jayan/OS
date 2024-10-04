#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
    char msg[200];
    int c,exit;
}resource;

int main()
{
    resource *ptr;
    char *name="Naruto";
    int id= shm_open(name,O_CREAT | O_RDWR,0666);
    ftruncate(id,sizeof(resource));
    ptr = mmap(0,sizeof(resource),PROT_WRITE|PROT_READ,MAP_SHARED,id,0);
    while(!ptr->exit)
    {
        if(ptr->c==3)
        {
            printf("Enter the message: ");
            scanf("%s",ptr->msg);
            if(!strcmp(ptr->msg,"exit"))
            {
                ptr->exit=1;
            }
            ptr->c=2;
        }
        else if(ptr->c==4)
        {
            printf("Message from sender: %s\n",ptr->msg);
            ptr->c=3;
        }
    }
    munmap(ptr,sizeof(resource));
    return 0;
}
