#!/usr/bin/python
#ANSWER 21124

"""

Can be solved by hand. See PDF for explanation.

"""

from time import time

def l(x):
    """Returns number of letters used in the word."""
    if x<20:
        if x==0: return 0
        if x==1: return len('one')
        if x==2: return len('two')
        if x==3: return len('three')
        if x==4: return len('four')
        if x==5: return len('five')
        if x==6: return len('six')
        if x==7: return len('seven')
        if x==8: return len('eight')
        if x==9: return len('nine')
        if x==10: return len('ten')
        if x==11: return len('eleven')
        if x==12: return len('twelve')
        if x==13: return len('thirteen')
        if x==14: return len('fourteen')
        if x==15: return len('fifteen')
        if x==16: return len('sixteen')
        if x==17: return len('seventeen')
        if x==18: return len('eighteen')
        if x==19: return len('nineteen')
    if x<100:
        start = x//10 
        end = x%10 
        if start==2: return len('twenty')+l(end)
        if start==3: return len('thirty')+l(end)
        if start==4: return len('forty')+l(end)
        if start==5: return len('fifty')+l(end)
        if start==6: return len('sixty')+l(end)
        if start==7: return len('seventy')+l(end)
        if start==8: return len('eighty')+l(end)
        if start==9: return len('ninety')+l(end)
    if x<1000:
        start = x//100 
        end = x%100 
        if start==1: returnval = len('onehundredand')+l(end)
        elif start==2: returnval = len('twohundredand')+l(end)
        elif start==3: returnval = len('threehundredand')+l(end)
        elif start==4: returnval = len('fourhundredand')+l(end)
        elif start==5: returnval = len('fivehundredand')+l(end)
        elif start==6: returnval = len('sixhundredand')+l(end)
        elif start==7: returnval = len('sevenhundredand')+l(end)
        elif start==8: returnval = len('eighthundredand')+l(end)
        elif start==9: returnval = len('ninehundredand')+l(end)
        if end == 0:
            return returnval-len('and')
        return returnval
    if x==1000:
        return len('onethousand')
    
def p17():
    return sum(l(y) for y in range(1,1001))

if __name__ == '__main__':
    time_start = time()
    print(p17())
    print("Time: {0:.3f}".format(time()-time_start))

