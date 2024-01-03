#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

unsigned long long int logFib(int n)
{
    unsigned long long int v1 = 1, v2 = 1, v3 = 0, temp, temp1, temp2, temp3;
    char i;
    for(i=0; n>>i; i++){
        ;
    }
    for(i-=2; i>=0; i--){
        if (n >> i & 1){
            temp1 = v1 * v1 + v2 * v2;
            temp2 = (v1 + v3) * v2;
            v1 = temp1+temp2;
            v2 = temp1;
            v3 = temp2;
        } else{
            temp = v2 * v2;
            temp1 = v1 * v1 + temp;
            temp2 = (v1 + v3) * v2;
            temp3 = temp + v3 * v3;
            v1 = temp1;
            v2 = temp2;
            v3 = temp3;
        }
    }
    return v2;
}

char* logFibBig(int n)
{
    mpz_t v1, v2, v3, temp1, temp2;
    mpz_init_set_ui(v1, 1);
    mpz_init_set_ui(v2, 1);
    mpz_init(v3);
    mpz_init(temp1);
    mpz_init(temp2);

    char i;
    for(i=0; n>>i; i++){
        ;
    }
    for(i-=2; i>=0; i--){
        mpz_add(temp1, v1, v3);
        if (n >> i & 1){
            mpz_mul(v3, temp1, v2);
            
            mpz_mul(temp1, v2, v2);
            mpz_addmul(temp1, v1, v1);
            mpz_set(v2, temp1);

            mpz_add(v1, v2, v3);
        } else{
            mpz_mul(temp2, v2, v2);
            
            mpz_mul(v2, temp1, v2);

            mpz_mul(temp1, v1, v1);
            mpz_add(v1, temp1, temp2);

            mpz_mul(temp1, v3, v3);
            mpz_add(v3, temp1, temp2);
        }
    }
    char* s;
    convert v2 to s!!
    mpz_clear(v1);
    mpz_clear(v2);
    mpz_clear(v3);
    mpz_clear(temp1);
    mpz_clear(temp2);
    return s;
}

int main(int argc, char *argv[])
{
    if(argc == 1){
        printf("Missing number!\n");
        return 0;
    } else if(argc > 2){
        printf("Too many arguments!\n");
        return 0;
    }

    int i = atoi(argv[1]);
    if(i>93){
        printf("WARNING: integer overflow, using big int from GMP library.\n");

        clock_t start, end;
        start = clock();
        char* fib = logFibBig(i);
        end = clock();

        gmp_printf("logFibInt(%d) = %s\n", i, fib);
        free the variable fib

        int time_taken = end-start;
        printf("Time taken %d\n", time_taken);
    } else{
        printf("logFib(%d) = %llu\n", i, logFib(i));
    }
    
    return 0;
}