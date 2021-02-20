#!/usr/bin/python
#ANSWER 0.464399

"""

Straight forward probability question. Just make sure you do a breadth-first
tree search.

""" 

from time import time

def next_job(prob_space):
    """ Iterates the probability space one step down the tree. """
    # dictionary to store events. Format:
    # (single sheets instances, A1, A2, A3, A4, A5): probability 
    new_prob_space = {}
    for event, prob in prob_space.items():
        norm = sum(event) - event[0]
        # generate new events by cutting each sheet
        for i in range(1, 6):
            if event[i] != 0:
                new_prob = prob*event[i]/norm
                new_event = list(event)
                new_event[i] -= 1
                for j in range(i+1, 6):
                    new_event[j] += 1
                if norm == 1:
                    new_event[0] += 1
                new_event = tuple(new_event)

                # adding to dictionary
                if new_event in new_prob_space:
                    new_prob_space[new_event] += new_prob
                else:
                    new_prob_space[new_event] = new_prob
    return new_prob_space

def p151():
    prob_space = {(0, 0, 1, 1, 1, 1): 1.}
    for i in range(14):
        prob_space = next_job(prob_space)
    norm = float(sum(prob_space.values()))
    prob = sum(event[0]*num for event, num in prob_space.items()) / norm
    return "{0:.6f}".format(prob)

if __name__ == '__main__':
    time_start = time()
    print(p151())
    print("Time: {0:.3f}".format(time()-time_start))

