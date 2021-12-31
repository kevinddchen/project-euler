#!/usr/bin/python
#ANSWER 107359

"""

Solving this in reasonable time needs certain assumptions. Here, I generated
every possible key, decoded the text, and counted the number of occurances of
the word 'the'. Then the key with the most occurances of 'the' is most likely
to be correct. The key is 'god' and the encrypted text is John 1:1-14

"""

from time import time

def key_gen():
    """Generate all 3-letter lowercase keys."""
    i = ord('a')
    for a in range(26):
        for b in range(26):
            for c in range(26):
                yield (i+a, i+b, i+c)

def xor_decode(encrypted, password):
    """Decode message using the password by XOR."""
    s = ''
    length = len(password)
    for i, x in enumerate(encrypted):
        s += chr(x ^ password[i%length])
    return s


    
def p59():
    with open('files/cipher.txt', 'r') as fl:
        raw = [int(x) for x in fl.read().split(',')]

    maxim = (0, (), '')
    for key in key_gen(): 
        string = xor_decode(raw, key)
        the_count = string.count('the')
        if the_count > maxim[0]:
            maxim = (the_count, key, string)

    return sum(ord(x) for x in maxim[2])

if __name__ == '__main__':
    time_start = time()
    print(p59())
    print("Time: {0:.3f}".format(time()-time_start))

