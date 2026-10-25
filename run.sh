#!/usr/bin/env bash
set -euo pipefail

readonly SCRIPT_NAME=$(basename "${BASH_SOURCE[0]}")
readonly DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
readonly SRC=src/solutions
readonly BIN=bin
readonly FILES=files

show_help () {
    echo
    echo "Run Project Euler solutions"
    echo "==========================="
    echo
    echo "To run a problem:      ./$SCRIPT_NAME 123"
    echo "To run all problems:   ./$SCRIPT_NAME all"
    echo "To run tests:          ./$SCRIPT_NAME tests"
    echo
}

run_tests () {
    local test

    make tests
    echo "Running c++ tests..."
    for test in "$BIN"/cpp/tests/test_*; do
        "./$test"
    done
    echo "Running python tests..."
    pytest
}

run_problem () {
    local num=$1

    if [ -e "$SRC/p$num.cpp" ]; then

        make "$BIN/solutions/p$num"
        echo "Running c++ solution #${num}..."
        time "$BIN/solutions/p$num"

    elif [ -e "$SRC/p$num.py" ]; then

        echo "Running python solution #${num}..."
        time FILES_DIR="$DIR/$FILES" python -m solutions "$num"

    else

        >&2 echo "Error: No solution found for '${num}'."
        show_help
        return 1

    fi
}

run_all () {
    local num

    # Problem numbers from p<num>.cpp / p<num>.py, sorted numerically
    for num in $(ls "$SRC" | sed -nE 's/^p([0-9]+)\.(cpp|py)$/\1/p' | sort -un); do
        echo
        run_problem "$num"
    done
}

main () {
    if [ $# -ne 1 ]; then
        show_help >&2
        exit 1
    fi

    cd "$DIR"

    case $1 in
        tests) run_tests ;;
        all)   run_all ;;
        *)     run_problem "$1" ;;
    esac
}

main "$@"
