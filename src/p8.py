# ANSWER 23514624000

from math import prod
from time import time

x = "7316717653133062491922511967442657474235534919493496983520312774506326239\
578318016984801869478851843858615607891129494954595017379583319528532088055111\
254069874715852386305071569329096329522744304355766896648950445244523161731856\
403098711121722383113622298934233803081353362766142828064444866452387493035890\
729629049156044077239071381051585930796086670172427121883998797908792274921901\
699720888093776657273330010533678812202354218097512545405947522435258490771167\
055601360483958644670632441572215539753697817977846174064955149290862569321978\
468622482839722413756570560574902614079729686524145351004748216637048440319989\
000889524345065854122758866688116427171479924442928230863465674813919123162824\
586178664583591245665294765456828489128831426076900422421902267105562632111110\
937054421750694165896040807198403850962455444362981230987879927244284909188845\
801561660979191338754992005240636899125607176060588611646710940507754100225698\
315520005593572972571636269561882670428252483600823257530420752963450"


def p8():
    return max(prod(int(n) for n in x[i : i + 13]) for i in range(len(x) - 12))


if __name__ == "__main__":
    time_start = time()
    print(p8())
    print("Time: {0:.3f}".format(time() - time_start))
