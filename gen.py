#!/usr/bin/python3

import random as rd


with open("input" , "w") as f:
    n = rd.randint(1, 100000)
    m = rd.randint(1 , n+300)
    f.write(f'{n} {m}\n')
    for _ in range(m):
        u , v, w = rd.randint(0, n-1), rd.randint(0 , n-1) , rd.randint(1, 10000)
        f.write(f'{u} {v} {w}\n')
    f.close()