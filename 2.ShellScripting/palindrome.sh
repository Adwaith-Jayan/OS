#!/bin/bash

num1=$1
num2=$2

echo "Palindrome numbers between $num1 and $num2 are: "
isPalindrome()
{
   num=$1
   reverse=$(echo "$num" | rev)
   if [ "$num" -eq "$reverse" ];
   then
       return 0
   else
       return 1
   fi
}

for((i=num1;i<=num2;i++));
do
   if isPalindrome "$i";
   then
         echo -n "$i "
   fi
done
