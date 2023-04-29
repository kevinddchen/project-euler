# project-euler

## Introduction

These are my solutions to [Project Euler](https://projecteuler.net/) problems.
Please do not blindly copy numerical answers.

Clone this repo and install the Python package containing commonly used mathematical functions by running the commands below.
This will also install Python dependencies that are used in some of the solutions.
Note that we use Python version >= 3.9.

```bash
git clone https://github.com/kevinddchen/project-euler.git
cd project-euler
pip install .
```

To run any solution, run the following command,

```bash
./run.sh $NUM
```

where `$NUM` is the problem number.
If the solution is written in Python, this will run the code using the command `python -m src $NUM`.
If the solution is written in C++, this will compile and run the code.
We are using the `C++17` standard.

[EulerSolutions.pdf](docs/EulerSolutions.pdf) contains write-ups for problems that can be solved by hand.

---

## Development

Set-up your local environment by running,
```bash
pip install -e .[dev]
pre-commit install
```

To run C++ tests,
```bash
./run.sh tests
```

To run Python tests,
```bash
pytest
```
