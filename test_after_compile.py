import math_tools
from math_tools import fibonacci
print("The module \"math_tools\" has been imported")

for i in range(10):
    print(i, ":", fibonacci(i))

print("check for number 300:", fibonacci(300) == 222232244629420445529739893461909967206666939096499764990979600)
