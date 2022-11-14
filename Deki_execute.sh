#!/bin/bash

#compile and run Loui.c

gcc -Wall -Wextra -Werror Deki.c -o microshell

if [ $? -eq 0 ];then
#./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell ";" ";"
#./microshell /bin/echo WOOT "; /bin/echo NOPE;" "; ;" ";" /bin/echo YEAH
#./microshell /bin/ls ";" /bin/echo poop ";" /bin/ls -l ";"
#./microshell  /bin/ls -l
./microshell /bin/echoo poop
#echo -e "\n\nCOMPARE:\n\n(1)\nmicroshell\ni love my microshell"
#echo -e "\n(2)\nWOOT ; /bin/echo NOPE; ; ;\nYEAH\n"
fi