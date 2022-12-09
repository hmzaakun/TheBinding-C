#!/bin/bash
# launch.sh

if [ ! -f app ]
then
    gcc *.c -o app -lm -w  
fi
./app
exit
