import argparse
import importlib


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("num", type=int, help="Problem number to run")
    args = parser.parse_args()

    # Import function
    name = f"p{args.num}"
    module = importlib.import_module(name)

    func = getattr(module, name)
    answer = getattr(module, "ANSWER")

    # Run
    result = func()
    if result != answer:
        raise ValueError(f"Expected answer {answer}, got {result}.")
    print(result)


if __name__ == "__main__":
    main()
