#!/bin/bash
set -e

#
# Usage:
# To run Problem 123, use the command `./run.sh 123`
#

DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd $DIR

SRC=src
BIN=bin
NAME=p$1

if [ -a $SRC/$NAME.cxx ]
then

    make $BIN/$NAME
    echo "Running c++ solution..."
    $BIN/$NAME

elif [ -a $SRC/$NAME.py ]
then

    echo "Running python solution..."
    python -m $SRC.$NAME

else

    >&2 echo "No solution found."
    exit 1

fi
