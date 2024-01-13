import math_tools_c

# calculate fibonacci number
def fibonacci(n: int, parseString: str = False, base:int = 10):
    # check that the argument is a non-negative integer
    if type(n) != int:
        raise ValueError("The argument must be a integer value")
    if n<0:
        raise ValueError("The argument must be >= 0")
    
    # check that the base is an integer between 2 and 36 included
    if type(base) != int:
        raise ValueError("The base must be an integer")
    elif base < 2 or base > 36:
        raise ValueError("The base must be >= 2 and <= 62")

    return math_tools_c.fibonacci(n, parseString, base)