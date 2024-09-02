#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main()
{
   pid_t pid=fork();
   if(pid==0)
   {
       execlp("./cmdsum","cmdsum","10","20",NULL);
       exit(0);
   }
   else if(pid>0)
   {
      wait(NULL);
   }
   else
   {
       printf("Error\n");
   }
}
