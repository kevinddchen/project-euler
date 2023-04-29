import argparse
from importlib import import_module
from time import perf_counter_ns
from typing import Any, Callable


def _get_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("num", type=int, help="Problem number to run")
    return parser.parse_args()


def _get_problem_function(num: str) -> Callable[[], Any]:
    """Gets the `p{num}` function from the `p{num}.py` file."""
    name = f"p{num}"
    module = import_module(f".{name}", package=__package__)
    func = getattr(module, name)
    return func


def main() -> None:
    args = _get_args()
    func = _get_problem_function(args.num)

    # run with timing
    t_start = perf_counter_ns()
    print(func())
    t_end = perf_counter_ns()
    t_diff = (t_end - t_start) / 1e9

    print(f"Time: {t_diff:.3f} sec")


if __name__ == "__main__":
    main()
