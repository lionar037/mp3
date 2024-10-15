#!/bin/bash

#####################################################################
#
#
#               compilar
#
#
#
#####################################################################


#g++ -o app src/main.cpp  -lmpg123
# g++ -o app src/main.cpp  -lmpg123 -I/home/pi/src/mp3/include/assets/

ALL=$1
CC=$2

if [[ $CC == "clang" ]]; then 
    #cmake -DUSE_CLANG=ON build/
    cmake -DUSE_CLANG=ON -S . -B build/
    echo -e "\nUsando Clang como compilador\n"
fi



if [[ $ALL == "all" ]]; then
    rm -Rf build/
    cmake -S . -B build/
else
	make -j4 -C build/
fi

