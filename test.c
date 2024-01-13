#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

char *logFib(unsigned long long n, unsigned char base) // implementation of fibonacci using the standard log(n) algorithm
{
    if (n == 0 || n == 1)
    {
        char *s = (char *)malloc(2 * sizeof(char));
        sprintf(s, "%d", n);
        return s;
    }

    mpz_t v1, v2, v3, temp1, temp2;
    mpz_init_set_ui(v1, 1);
    mpz_init_set_ui(v2, 1);
    mpz_init(v3);

    char i;
    for (i = 0; n >> i; i++)
    {
        ; // calculate  number of digits in the binary representation
    }
    for (i -= 2; i > 0; i--)
    {
        if (n >> i & 1) // double it and move by one
        {
            // v1, v2, v3 = v1*v1+v2*v2, (v1+v3)*v2, v2*v2+v3*v3
            // v1, v2, v3 = v1+v2, v1, v2
            // simplify with simple algebra

            mpz_init(temp1); // initialise temp variables

            mpz_add(temp1, v1, v3);
            mpz_mul(v3, temp1, v2);

            mpz_mul(temp1, v2, v2);
            mpz_addmul(temp1, v1, v1);
            mpz_set(v2, temp1);

            mpz_clear(temp1); // clear temp variables

            mpz_add(v1, v2, v3);
        }
        else // only double it
        {
            // v1, v2, v3 = v1*v1+v2*v2, (v1+v3)*v2, v2*v2+v3*v3

            mpz_init(temp1); // initialise temp variable
            mpz_init(temp2);

            mpz_add(temp1, v1, v3);
            mpz_mul(temp2, v2, v2);

            mpz_mul(v2, temp1, v2);

            mpz_mul(temp1, v1, v1);
            mpz_add(v1, temp1, temp2);

            mpz_mul(temp1, v3, v3);
            mpz_add(v3, temp1, temp2);

            mpz_clear(temp1); // clear temp variable
            mpz_clear(temp2);
        }
    }

    // last cycle is simpler and we can use v3 as temp
    if (n & 1) // double it and move by one
    {
        mpz_mul(v3, v2, v2);
        mpz_addmul(v3, v1, v1);
        mpz_set(v2, v3);
    }
    else // only double it
    {
        mpz_add(v3, v1, v3);
        mpz_mul(v2, v3, v2);
    }
    mpz_clear(v1);
    mpz_clear(v3);

    char *s = mpz_get_str(NULL, base, v2);
    mpz_clear(v2);

    return s;
}

int main()
{
    char* s = test();
    printf("%s\n", s);
    free(s);
    return 0;
}