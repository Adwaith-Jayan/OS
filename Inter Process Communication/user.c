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
    ptr->c=1;
    ptr->exit=0;
    while(!ptr->exit)
    {
        if(ptr->c==1)
        {
            printf("Enter the message: ");
            scanf("%s",ptr->msg);
            if(!strcmp(ptr->msg,"exit"))
            {
                ptr->exit=1;
            }
            ptr->c=4;
        }
        else if(ptr->c==2)
        {
            printf("Message from receiver: %s\n",ptr->msg);
            ptr->c=1;
        }
        sleep(1);
    }
    printf("\n Exited-%d\n",ptr->exit);
    sleep(2);
    munmap(ptr,sizeof(resource));
    shm_unlink(name);
    return 0;
}
