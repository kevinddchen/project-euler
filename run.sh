#!/usr/bin/env bash
set -euo pipefail

show_help () {
    echo
    echo "Run Project Euler solutions"
    echo "==========================="
    echo
    echo "To run a problem: ./$(basename $0) 123"
    echo "To run tests:     ./$(basename $0) tests"
    echo
}

if [ $# -ne 1 ]; then
    show_help
    exit 1
fi

DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

SRC=src/solutions
BIN=bin
FILES=files
NUM=$1

if [ $NUM = "tests" ]; then

    make tests
    echo "Running c++ tests..."
    for test in $(ls $BIN/cpp/tests/test_*); do
        ./$test
    done
    echo "Running python tests..."
    pytest

elif [ -a $SRC/p$NUM.cpp ]; then

    make $BIN/solutions/p$NUM
    echo "Running c++ solution #${NUM}..."
    time $BIN/solutions/p$NUM

elif [ -a $SRC/p$NUM.py ]; then

    echo "Running python solution #${NUM}..."
    time FILES_DIR="$DIR/$FILES" python "$SRC/__main__.py" $NUM

else

    >&2 echo "Error: No solution found for '${NUM}'."
    show_help
    exit 1

fi
