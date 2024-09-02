#include <stdlib.h>
#include <stdio.h>

void main(int argc,char* argv[])
{
   if(argc!=3)
      return;
   int num1=atoi(argv[1]);
   int num2=atoi(argv[2]);
   int sum=num1+num2;
   printf("Sum= %d\n",sum);
}

