#!/bin/bash

## To run p123.cxx, use the command:
## bash run.sh 123

if [ -a p$1.cxx ]; then

    if ! [ -a cmathfuncs.o ]; then

        echo "Building custom mathfuncs ..."
        g++ -o cmathfuncs.o cmathfuncs.cxx -c -O

    fi

    if [ -a p$1 ]; then

        echo "Removing old program ..."
        rm -f p$1

    fi


    echo "Running file p$1.cxx ..."

    g++ -o p$1 p$1.cxx cmathfuncs.o -O
    ./p$1
    rm -f p$1

else

    echo "File p$1.cxx does not exist."

fi
