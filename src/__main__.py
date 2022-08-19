from argparse import ArgumentParser
from importlib import import_module
from time import time


def main() -> None:
    parser = ArgumentParser()
    parser.add_argument("p_num", type=int, help="Problem number to run")
    args = parser.parse_args()

    name = f"p{args.p_num}"
    module = import_module(f".{name}", package=__package__)
    func = getattr(module, name)

    t_start = time()
    print(func())
    t_end = time()

    print(f"Time: {t_end - t_start:.3f}")


if __name__ == "__main__":
    main()
