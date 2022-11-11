#!/bin/bash

#compile and run Loui.c

gcc -Wall -Wextra -Werror Loui.c -o microshell
if [ $? -eq 0 ];then
#./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
#./microshell /bin/echo WOOT "; /bin/echo NOPE;" "; ;" ";" /bin/echo YEAH
./microshell ls ";" echo poop ";" one two three four five | seven;

#echo -e "\n\nCOMPARE:\n\n(1)\nmicroshell\ni love my microshell"
#echo -e "\n(2)\nWOOT ; /bin/echo NOPE; ; ;\nYEAH\n"
fi