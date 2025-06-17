#!/usr/bin/python3

import random as rd
import itertools as it
import math

alpha = "ab"

print("".join(rd.choices(alpha, k=16)))