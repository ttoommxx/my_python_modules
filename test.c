#include <stdio.h>
#include <stdlib.h>

void test(unsigned int n)
{
    if(n<0)
    {
        printf("%d is less than 0\n", n);
    }
    else
    {
        printf("%d is not less than 0\n", n);
    }
}

int main()
{
    int n1 = -1, n2 = 1;
    printf("n1: ");
    test(n1);
    printf("n2: ");
    test(n2);
    return 0;
}