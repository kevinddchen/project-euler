#!/usr/bin/python
#ANSWER 178653872807

"""

See solution explanations. 

"""

from time import time

def minusOne(s):
    """ Subtract one from a binary string. """
    i = 1
    while s[-i] == '0':
        i += 1
    return s[:-i] + ('' if i==len(s) else '0') + '1'*(i-1)

def f(s, mem_dict):
    """ As defined in the problem. """
    if s in mem_dict:
        return mem_dict[s]
    if s[-1] == '0':
        mem_dict[s] = f(s[:-1], mem_dict) + f(minusOne(s[:-1]), mem_dict)
    else:
        mem_dict[s] = f(s[:-1], mem_dict)
    return mem_dict[s]

def p169():
    mem_dict = {'0':1, '':1}
    return f(bin(10**25)[2:], mem_dict)

if __name__ == '__main__':
    time_start = time()
    print(p169())
    print("Time: {0:.3f}".format(time()-time_start))

