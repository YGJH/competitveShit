#!/usr/bin/python3

import random as rd
import itertools as it
import math

t = rd.randint(1 , 3)

with open("in" , 'w') as f:
    f.write(f'{t}\n')
    for i in range(t):
        n , query = rd.randint(1, 10) , rd.randint(1, 10)
        f.write(f'{n} {query}\n')
        for j in range(query):
            com = rd.randint(1, 2)
            l= rd.randint(0, n-1)
            r= rd.randint(l , n-1)
            f.write(f'{com} {l} {r}\n')
    
    f.close()