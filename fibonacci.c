#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <python3.12/Python.h>

char* logFib(int n)
{
    mpz_t v1, v2, v3, temp1, temp2;
    mpz_init_set_ui(v1, 1);
    mpz_init_set_ui(v2, 1);
    mpz_init(v3);
    mpz_init(temp1);
    mpz_init(temp2);

    char i;
    for (i = 0; n >> i; i++)
    {
        ;
    }
    for (i -= 2; i >= 0; i--)
    {
        mpz_add(temp1, v1, v3);
        if (n >> i & 1)
        {
            mpz_mul(v3, temp1, v2);

            mpz_mul(temp1, v2, v2);
            mpz_addmul(temp1, v1, v1);
            mpz_set(v2, temp1);

            mpz_add(v1, v2, v3);
        }
        else
        {
            mpz_mul(temp2, v2, v2);

            mpz_mul(v2, temp1, v2);

            mpz_mul(temp1, v1, v1);
            mpz_add(v1, temp1, temp2);

            mpz_mul(temp1, v3, v3);
            mpz_add(v3, temp1, temp2);
        }
    }
    char *s = mpz_get_str(NULL, 10, v2);
    if(!s){
        printf("Memory failed to be allocated\n");
        exit(1);
    }
    mpz_clear(v1);
    mpz_clear(v2);
    mpz_clear(v3);
    mpz_clear(temp1);
    mpz_clear(temp2);
    return s;
}

static PyObject* fibonacci(PyObject* self, PyObject* args, PyObject* kwargs)
{
    int n;
    int parseString = 0;

    static char* kwlist[] = {"n", "parseString", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i|i", kwlist, &n, &parseString))
    {
        return NULL;
    }

    if (n < 0)
    {
        // set value error
        return NULL;
    }

    char *sts = logFib(n);
    PyObject *sol;
    if (parseString != 0)
    {
        sol = PyUnicode_FromString(sts);
    }
    else
    {
        sol = PyLong_FromString(sts, NULL, 10);
    }

    free(sts);
    return sol;
    }

static PyObject* version(PyObject* self)
{
    return Py_BuildValue("s", "Version 0.1");
}

static PyMethodDef Tests[] = {
    {"fibonacci", (PyCFunction)fibonacci, METH_VARARGS | METH_KEYWORDS, "Calculate the n-th fibonacci number"},
    {"version", (PyCFunction)version, METH_NOARGS, "Return the version of the module"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef Test = {
    PyModuleDef_HEAD_INIT,
    "Test",
    "Random modules",
    -1,// global state
    Tests
};

//INITIALIZER FUNCTION
PyMODINIT_FUNC PyInit_Test(void)
{
    return PyModule_Create(&Test);
}