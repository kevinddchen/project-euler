# project-euler

## Introduction

These are my solutions to [Project Euler](https://projecteuler.net/) problems.
Please do not blindly copy numerical answers.

To run any solution, use

```bash
./run.sh $NUM
```

where `$NUM` is the problem number.
If the solution is written in C++, this will compile and run the code.
If the solution is written in Python, this will run the code using the command `python -m src $NUM`.
Note that we use Python >= 3.9.

[EulerSolutions.pdf](docs/EulerSolutions.pdf) contains write-ups for problems that can be solved by hand.

---

## Development

To run C++ tests,
```bash
./run.sh tests
```

To run Python tests,
```bash
make test
```

To run Python flake8
```bash
make flake
```
