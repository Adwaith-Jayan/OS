#!/bin/bash

echo "Enter n: "
read n
a=0
b=1
echo -n "$a "
echo -n "$b "
for((i=2;i<n;i++));
do
   c=$((a+b))
   a=$b
   b=$c
   echo -n "$c "
done
echo

