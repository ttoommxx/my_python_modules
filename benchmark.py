from time import time

from Test import fibonacci


def fib(n):
    v1, v2, v3 = 1, 1, 0    # initialise a matrix [[1,1],[1,0]]
    # perform fast exponentiation of the matrix (quickly raise it to the nth power)
    for rec in bin(n)[3:]:
        calc = v2*v2
        v1, v2, v3 = v1*v1+calc, (v1+v3)*v2, calc+v3*v3
        if rec == '1':
            v1, v2, v3 = v1+v2, v1, v2
    return v2


time1, time2 = 0, 0
for i in range(1000000,1000100):
    start = time()
    t1 = fibonacci(i, parseString=True)
    end = time()
    time1 += end-start

    start = time()
    t2 = fib(i)
    end = time()
    time2 += end-start
    
print("C function:", time1)
print("Python function:", time2)