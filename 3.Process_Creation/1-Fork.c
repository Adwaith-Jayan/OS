#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void main()
{
   pid_t pid=fork();
   if(pid==0)
   {
      printf("Child process ID= %d\n",getpid());
      printf("Parent Process ID= %d\n",getppid());
      exit(0);
   }
   else if(pid>0)
   {
     wait(NULL);
   }
   else
   {
      printf("Error creating process\n");
   }
}
