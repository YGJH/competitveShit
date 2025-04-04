#!/usr/bin/python3

import random as rd
import itertools as it
import math

t = rd.randint(1 , 3)

with open("in" , 'w') as f:
    f.write(f'{t}\n')
    for i in range(t):
        n , k , v = rd.randint(1, 5) , rd.randint(1 , 3) , rd.randint(3, 10)
        f.write(f'{n} {k} {v}\n')
        for j in range(n):
            f.write(f'{rd.randint(1 ,10)} ')
        f.write('\n')