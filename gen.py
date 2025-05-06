#!/usr/bin/python3

import random as rd
import itertools as it
import math

n = rd.randint(4 , 14)
m = rd.randint(4 ,  n * (n - 1) // 2)

a , b = rd.randint(0 , n-1) , rd.randint(0 , n-1)
edgeList = []
for i in it.combinations(range(n) , 2):
    edgeList.append((i[0], i[1]))
    edgeList.append((i[1], i[0]))

if a != b:
    with open("in" , 'w') as f:
        f.write(f'{n} {m}\n{a} {b} 0\n')
        for i in range(m):
            x = rd.choice(edgeList)
            edgeList.remove(x)
            f.write(f'{x[0]} {x[1]} 1\n')
    