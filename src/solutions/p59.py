# ANSWER 107359

"""

Solving this in reasonable time needs certain assumptions. Here, I generated
every possible key, decoded the text, and counted the number of occurances of
the word 'the'. Then the key with the most occurances of 'the' is most likely
to be correct. The key is 'god' and the encrypted text is John 1:1-14

"""

from pathlib import Path


def key_gen():
    """Generate all 3-letter lowercase keys."""
    i = ord("a")
    for a in range(26):
        for b in range(26):
            for c in range(26):
                yield (i + a, i + b, i + c)


def xor_decode(encrypted, password):
    """Decode message using the password by XOR."""
    s = ""
    length = len(password)
    for i, x in enumerate(encrypted):
        s += chr(x ^ password[i % length])
    return s


def p59():
    fl = Path(__file__).parent / "../files/cipher.txt"
    raw = [int(x) for x in fl.read_text().split(",")]

    maxim = (0, (), "")
    for key in key_gen():
        string = xor_decode(raw, key)
        the_count = string.count("the")
        if the_count > maxim[0]:
            maxim = (the_count, key, string)

    return sum(ord(x) for x in maxim[2])
