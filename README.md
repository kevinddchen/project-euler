# project-euler

## Introduction

These are my solutions to [Project Euler](https://projecteuler.net/) problems.
Please do not blindly copy numerical answers.

Most of the older solutions are written in Python, and most of the newer solutions are written in C++.

---

## Running solutions

Clone this repo and install the Python package containing commonly used mathematical functions by running the commands below.
This will also install third-party Python dependencies that are used in some of the solutions.
Note that we use Python version `>=3.9`.

```bash
git clone https://github.com/kevinddchen/project-euler.git
cd project-euler
pip install .
```

For C++, we are using the `C++17` standard without any third-party libraries.

To run any solution, run the following command,

```bash
./run $NUM
```

where `$NUM` is the problem number.
If the solution is written in C++, this will compile and run the code.

[EulerSolutions.pdf](docs/EulerSolutions.pdf) contains write-ups for problems that can be solved by hand.

---

## Development

Set-up your local environment by running,
```bash
pip install -e .[dev]
pre-commit install
```

To run C++ and Python tests,
```bash
./run tests
```
