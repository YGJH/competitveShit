#!/usr/bin/python3

import random as rd
import itertools as it
import math
t = rd.randint(4,5)
with open('in' , 'w') as f:
    f.write(str(t)+'\n')
    for i in range(t):
        n = rd.randint(1,5)
        f.write(str(n)+'\n')
        for j in range(n):
            f.write(str(rd.randint(0, 10))+' ')
        f.write('\n')
