#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <python3.12/Python.h>

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

static PyObject* fibonacci(PyObject* self, PyObject* args)
{
    int n;
    unsigned long long int sts;

    if(!PyArg_ParseTuple(args, "i", &n)){
        return NULL;
    }
    sts = logFib(n);
    return PyLong_FromUnsignedLongLong(sts);
}

static PyObject* version(PyObject* self)
{
    return Py_BuildValue("s", "Version 0.1");
}

static PyMethodDef Tests[] = {
    {"fibonacci", fibonacci, METH_VARARGS, "Calculate the n-th fibonacci number"},
    {"version", (PyCFunction)version, METH_NOARGS, "return the version of the module"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef Test = {
    PyModuleDef_HEAD_INIT,
    "Test",
    "random modules",
    -1,// global state
    Tests
};

//INITIALIZER FUNCTION
PyMODINIT_FUNC PyInit_Test(void)
{
    return PyModule_Create(&Test);
}