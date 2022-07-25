# ANSWER 709

"""

Just compute log of the value. As log is a monotonically increasing
function, it preserves order, i.e. x<y implies log(x)<log(y).

"""

from math import log
from pathlib import Path
from time import time


def p99():
    maxim = (0, 0)
    fl = Path(__file__).parent / "../files/base_exp.txt"
    for i, line in enumerate(fl.read_text().splitlines()):
        base, exp = line.split(",")
        log_value = int(exp) * log(int(base))
        if log_value > maxim[0]:
            maxim = (log_value, i + 1)
    return maxim[1]


if __name__ == "__main__":
    time_start = time()
    print(p99())
    print("Time: {0:.3f}".format(time() - time_start))
