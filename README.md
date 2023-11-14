# project-euler

## Introduction

These are my solutions to [Project Euler](https://projecteuler.net/) problems.
Please do not blindly copy numerical answers.

Most of the newer solutions are written in C++, and most of the older solutions are written in Python.

## Running solutions

Clone this repo and run the command below to install third-party dependencies.
For C++, this just downloads Eigen, which is a header-only library.
For Python, this installs `numpy` and `scipy`.
Note that we use the `C++20` standard and Python version >= 3.9

```bash
# install c++ third-party dependency
git submodule init
git submodule update

# install python third-party dependencies
pip install .
```

To run any solution, run the following command,

```bash
./run $NUM
```

where `$NUM` is the problem number.
If the solution is written in C++, this will compile and run the code.

[EulerSolutions.pdf](docs/EulerSolutions.pdf) contains write-ups for problems that can be solved by hand.

## Development

Install additional Python dependencies for development by running,
```bash
pip install -e .[dev]
pre-commit install
```

To run C++ and Python tests,
```bash
./run tests
```
