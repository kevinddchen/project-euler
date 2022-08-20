#!/bin/bash
set -e

show_help () {
    echo
    echo "Run Project Euler solutions"
    echo "==========================="
    echo 
    echo "To run a problem:     ./$(basename $0) 123"
    echo "To run tests:         ./$(basename $0) tests"
    echo
}

if [[ -z "$1" ]]; then
    show_help
    exit 1
fi

DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd $DIR

SRC=src
BIN=bin
NUM=$1

if [[ $NUM = "tests" ]]; then

    make $BIN/test_mathfuncs
    echo "Running tests..."
    $BIN/test_mathfuncs

elif [[ -a $SRC/p$NUM.cxx ]]; then

    make $BIN/p$NUM
    echo "Running c++ solution #${NUM}..."
    $BIN/p$NUM

elif [[ -a $SRC/p$NUM.py ]]; then

    echo "Running python solution #${NUM}..."
    python -m $SRC $NUM

else

    >&2 echo "No solution found for '${NUM}'."
    show_help
    exit 1

fi
