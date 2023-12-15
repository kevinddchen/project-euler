import argparse
import importlib
from typing import Any, Callable


def _get_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("num", type=int, help="Problem number to run")
    return parser.parse_args()


def _get_problem_function(num: int) -> Callable[[], Any]:
    """Gets the `p{num}` function from the `p{num}.py` file."""
    name = f"p{num}"
    module = importlib.import_module(name)
    func = getattr(module, name)
    return func


def main() -> None:
    args = _get_args()
    func = _get_problem_function(args.num)
    print(func())


if __name__ == "__main__":
    main()
