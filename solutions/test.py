#!/usr/bin/python

import os

for i in range(0, 10):
    if os.path.isfile("p{}.py".format(i)):
        filename = "p{}.py".format(i)
        language = "Python"
    elif os.path.isfile("p{}".format(i)):
        filename = "p{}".format(i)
        language = "C++"
    else:
        continue

    print(" === Problem {} - {} === ".format(i, language))
    os.system("./{}".format(filename))

