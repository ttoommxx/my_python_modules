import math_tools
from math_tools import fibonacci
from time import time
print("The module \"math_tools\" has been imported")

def fibonacci_py(n):
    if n == 0:
        return 0
    v1, v2, v3 = 1, 1, 0
    for bit in bin(n)[3:]:
        if bit == "1":
            v2, v3 = v1*v1+v2*v2, (v1+v3)*v2
            v1 = v2 + v3
        else:
            temp = v2*v2
            v1, v2, v3 = v1*v1+temp, (v1+v3)*v2, v3*v3+temp
    return v2

import sys
sys.set_int_max_str_digits(1000000)

time_c = 0
time_py = 0
for i in range(1000000, 1000100):
    start = time()
    f_c = fibonacci(i)
    end = time()
    time_c += end-start

    start = time()
    f_py = fibonacci_py(i)
    end = time()
    time_py = end-start

print("c takes", time_c, ", python takes", time_py)