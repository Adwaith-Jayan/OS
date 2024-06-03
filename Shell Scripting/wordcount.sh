#!/bin/sh

filename="words.txt"
echo "Enter word to search"
read word

if grep -q "$word" "$filename";
then
      echo "The word $word is present in file $filename"
else
      echo "The word $word is not present in the file $filename"
fi
