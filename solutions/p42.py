#!/usr/bin/python
#ANSWER 162

from time import time

def convert_to_int(word):
    """Converts a word into an integer."""
    return sum(ord(letter) - ord('A') + 1 for letter in word.strip('"'))

def isTriangle(x):
    n = int((2*x + 0.25)**0.5 - 0.5)
    return x == n*(n+1)/2

def p42():
    with open('files/words.txt', 'r') as fl:
        lst = fl.read().split(',')
    lst = [convert_to_int(word) for word in lst]
    return sum(1 for x in lst if isTriangle(x))

if __name__ == '__main__':
    time_start = time()
    print(p42())
    print("Time: {0:.3f}".format(time()-time_start))

