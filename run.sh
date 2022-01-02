#!/bin/bash
set -e

## To run Problem 123 use the command:
##      `./run.sh 123`

SRC=./src
BIN=./bin
NAME=p$1

if [ -a $SRC/$NAME.cxx ]
then

    make $BIN/$NAME
    echo "Running..."
    ./$BIN/$NAME

elif [ -a $SRC/$NAME.py ]
then 

    echo "Running..."
    python $SRC/$NAME.py

else

    >&2 echo "No solution found."
    exit 1

fi
