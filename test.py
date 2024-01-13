n1 = 213213
n2 = 532
n3 = 943221

def invert_binary(n):
    sol = 1
    while n:
        sol <<= 1
        sol += n&1
        n >>= 1
    return sol


# this algorithm is for calculating the actual number to check &1 and divide each time.
# This way I can input arbitrary input and use the gmp library to also include arbitrary input!


def fibonacci_py(n):
    if n==0:
        return 0
    v1,v2,v3 = 1,1,0
    for bit in bin(n)[3:]:
        if bit == "1":
            v2, v3 = v1*v1+v2*v2, (v1+v3)*v2
            v1 = v2 + v3
        else:
            temp = v2*v2
            v1, v2, v3 = v1*v1+temp, (v1+v3)*v2, v3*v3+temp
    return v2

for i in range(20):
    print(i, fibonacci_py(i))