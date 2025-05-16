#!/usr/bin/python3

import random as rd
import itertools as it
import math
import string
with open('in' ,'w') as f:
    x , y = rd.randint(1 , 100) , rd.randint(1,100)
    n = rd.randint(1 , 5)
    f.write(f"{x} {y}\n{n}\n")
    for i in range(n):
        f.write(f"{rd.randint(1, x-1)+rd.random()} {rd.randint(1 ,y-1) + rd.random()}\n")
