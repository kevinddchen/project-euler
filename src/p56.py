# ANSWER 972

from time import time


def p56():
    return max(sum(int(d) for d in str(a**b)) for a in range(2, 101) for b in range(2, 101))


if __name__ == "__main__":
    time_start = time()
    print(p56())
    print("Time: {0:.3f}".format(time() - time_start))
