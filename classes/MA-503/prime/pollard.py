from itertools import count
from math import gcd
import sys

number, x = 7919*7717, 5

for cycle in count(1):
  print("\nCycle =", cycle)
  y = x
  print("y =", y)
  for i in range(2 ** cycle):
    x = (x * x + 1) % number
    print("x =", x)
    factor = gcd(x - y, number)
    print("gcd(", x, "-", y, ",", number, ") = ", factor)
    if factor > 1:
      print("factor is", factor)
      sys.exit()
