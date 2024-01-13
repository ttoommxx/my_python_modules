#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <python3.12/Python.h>

char *logFib(unsigned long long n, unsigned char base) // implementation of fibonacci using the standard log(n) algorithm
{
    if(n == 0 || n == 1)
    {
        char* s = (char*) malloc(2*sizeof(char));
        sprintf(s, "%d", n);
        return s;
    }
    
    mpz_t v1, v2, v3, temp2;
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

            mpz_add(v3, v1, v3);
            mpz_mul(v3, v3, v2);

            mpz_mul(v2, v2, v2);
            mpz_addmul(v2, v1, v1);

            mpz_add(v1, v2, v3);
        }
        else // only double it
        {
            // v1, v2, v3 = v1*v1+v2*v2, (v1+v3)*v2, v2*v2+v3*v3

            mpz_init_set(temp2, v2);
            
            mpz_add(v2, v1, v3);
            mpz_mul(v2, v2, temp2);

            mpz_mul(temp2, temp2, temp2);

            mpz_mul(v1, v1, v1);
            mpz_add(v1, v1, temp2);

            mpz_mul(v3, v3, v3);
            mpz_add(v3, v3, temp2);

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

static PyObject* fibonacci(PyObject* self, PyObject* args, PyObject* kwargs)
{
    unsigned long long n;
    int parseString = 0;
    unsigned char base = 10;

    static char* kwlist[] = {"n", "parseString", "base", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Kpb", kwlist, &n, &parseString, &base))
    {
        return NULL;
    }

    if (!parseString) // set high base to save on memory
    {
        base = 36;
    }

    char *sts = logFib(n, base);
    if (!sts)
    {
        PyErr_SetString(PyExc_MemoryError, "Memory failed to allocate");
        return NULL;
    }
    
    PyObject *sol;
    if (parseString)
    {
        sol = PyUnicode_FromString(sts);
    }
    else
    {
        sol = PyLong_FromString(sts, NULL, 36);
    } 
    free(sts);

    return sol;
    }

static PyObject* version(PyObject* self)
{
    return Py_BuildValue("s", "Version 0.1");
}

static PyMethodDef methods[] = {
    {"fibonacci", (PyCFunction)fibonacci, METH_VARARGS | METH_KEYWORDS, "Calculate the n-th fibonacci number"},
    {"version", (PyCFunction)version, METH_NOARGS, "Return the version of the module"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef math_tools_c = {
    PyModuleDef_HEAD_INIT,
    "math_tools_c",
    "Random modules",
    -1, // global state
    methods};

//INITIALIZER FUNCTION
PyMODINIT_FUNC PyInit_math_tools_c(void)
{
    return PyModule_Create(&math_tools_c);
}