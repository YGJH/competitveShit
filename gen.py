#!/usr/bin/python3
import os
from itertools import permutations 
import random
# word = "abcdefghijklmnopqrstuvwxyz!@#$%^&*()-=_+{}[];'0987654321"
testCase = random.randint(1 , 10)
# k = random.randint(-10 , 10)
with open('input' , 'w') as f:
# word = list(word)
# random.shuffle(word)
# print("".join(word[:10]))
    f.write(str(testCase) + '\n')
    for i in range(testCase):
        f.write(str(random.randint(1 , 30))+ (' ' if i != testCase-1 else '\n'))
    f.close()