"""

Just compute log of the value. As log is a monotonically increasing
function, it preserves order, i.e. x<y implies log(x)<log(y).

"""

from math import log

from mathfuncs import read_text

ANSWER = 709


def p99():
    maxim = (0, 0)
    text = read_text("base_exp.txt")
    for i, line in enumerate(text.splitlines()):
        base, exp = line.split(",")
        log_value = int(exp) * log(int(base))
        if log_value > maxim[0]:
            maxim = (log_value, i + 1)
    return maxim[1]
