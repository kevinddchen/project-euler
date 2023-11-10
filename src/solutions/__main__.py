import argparse
import importlib
import time
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

    # run with timing
    t_start_ns = time.perf_counter_ns()
    print(func())
    t_end_ns = time.perf_counter_ns()
    t_diff_sec = (t_end_ns - t_start_ns) / 1e9

    print(f"Time: {t_diff_sec:.3f} sec")


if __name__ == "__main__":
    main()
