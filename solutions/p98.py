#!/usr/bin/python
#ANSWER 18769

"""

Brute force. Get all the words, find all anagram pairs, and start
matching squares to the pattern and see if you get a square.

"""

from time import time
from math import ceil

def get_words():
    """Get words from text file into list."""
    with open('files/words.txt', 'r') as fl:
        lst = fl.read().strip('"').split('","')
    return lst

def get_anagrams(words):
    """Goes through list of words and iterates through anagrams."""
    for i, w in enumerate(words):
        for v in words[i+1:]:
            ## if anagram
            if sorted(list(w)) == sorted(list(v)):
                yield w, v

def gen_squares(d):
    """Generate a list of squares with d digits."""
    init = ceil(10**((d-1)/2.))
    fin = ceil(10**(d/2.))
    return [x*x for x in range(init, fin)]

def fit_pattern(word_a, word_b, square):
    """Using word_a and square, create the number based off the pattern of
    word_b as string. If violates anagram rules, returns empty string."""
    square = str(square)
    dct = {}
    for i, char in enumerate(word_a):
        digit = square[i] 
        if (char in dct and dct[char] != digit) or (digit in dct and dct[digit] != char):
            return '' 
        word_b = word_b.replace(char, digit)
        dct[char] = digit 
        dct[digit] = char
    return word_b


def p98():
    maxim = 0
    words = get_words()
    for word_a, word_b in get_anagrams(words):
        squares = gen_squares(len(word_a))
        for sq in squares:
            new_sq = fit_pattern(word_a, word_b, sq)
            if new_sq != '' and int(new_sq) in squares:
                maxim = max(maxim, sq, int(new_sq))
    return maxim

if __name__ == '__main__':
    time_start = time()
    print(p98())
    print("Time: {0:.3f}".format(time()-time_start))
    
