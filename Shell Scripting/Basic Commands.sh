#!/bin/sh

echo "OS and version, release number, kernal version:"
uname -a
echo

echo "Available shell are:"
cat /etc/shells
echo

echo "CPU information:"
lscpu
echo

echo "Memeory information:"
free -h
echo

echo "Hard Disk information:"
df -h
echo

echo "File System mounted"
mount | column -t
echo
