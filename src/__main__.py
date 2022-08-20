from argparse import ArgumentParser
from importlib import import_module
from time import time
from typing import Any, Callable


def get_parser() -> ArgumentParser:
    parser = ArgumentParser()
    parser.add_argument("num", type=int, help="Problem number to run")
    return parser


def get_problem_function(num: str) -> Callable[[], Any]:
    """Gets the `p{num}` function from the `p{num}.py` file."""
    name = f"p{num}"
    module = import_module(f".{name}", package=__package__)
    func = getattr(module, name)
    return func


def main() -> None:
    args = get_parser().parse_args()
    func = get_problem_function(args.num)

    # run with timing
    t_start = time()
    print(func())
    t_end = time()

    print(f"Time: {t_end - t_start:.3f}")


if __name__ == "__main__":
    main()
