#!/usr/bin/python
#ANSWER 871198282

from time import time

def score(name):
    """Returns score of the name"""
    return sum(ord(letter) - ord('A') + 1 for letter in name)

def p22():
    with open('files/names.txt', 'r') as fl:
        lst = [x.strip("\"") for x in fl.read().split(',')]
    return sum(score(name)*(i+1) for i, name in enumerate(sorted(lst)))

if __name__ == '__main__':
    time_start = time()
    print(p22())
    print("Time: {0:.3f}".format(time()-time_start))

