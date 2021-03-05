#define PY_SSIZE_T_CLEAN
#include <Python.h>


#define FLOAT_ARG "f"
#define TWO_FLOAT_ARGS "ff"


PyObject * meth_add(PyObject * self, PyObject * args, PyObject * kwargs)
{
    static char * keywords[] = {"number1", "number2", NULL};
    float number1, number2;

    int succeed = PyArg_ParseTupleAndKeywords(
        args,
        kwargs,
        TWO_FLOAT_ARGS,
        keywords,
        &number1,
        &number2
    );

    if (!succeed)
    {
        return 0;
    }

    return Py_BuildValue(FLOAT_ARG, number1 + number2);
}


PyObject * meth_sub(PyObject * self, PyObject * args, PyObject * kwargs)
{
    static char * keywords[] = {"number1", "number2", NULL};
    float number1, number2;

    int succeed = PyArg_ParseTupleAndKeywords(
        args,
        kwargs,
        TWO_FLOAT_ARGS,
        keywords,
        &number1,
        &number2
    );

    if (!succeed)
    {
        return 0;
    }

    return Py_BuildValue(FLOAT_ARG, number1 - number2);
}


PyObject * meth_mul(PyObject * self, PyObject * args, PyObject * kwargs)
{
    static char * keywords[] = {"number1", "number2", NULL};
    float number1, number2;

    int succeed = PyArg_ParseTupleAndKeywords(
        args,
        kwargs,
        TWO_FLOAT_ARGS,
        keywords,
        &number1,
        &number2
    );

    if (!succeed)
    {
        return 0;
    }

    return Py_BuildValue(FLOAT_ARG, number1 * number2);
}


PyObject * meth_div(PyObject * self, PyObject * args, PyObject * kwargs)
{
    static char * keywords[] = {"number1", "number2", NULL};
    float number1, number2;

    int succeed = PyArg_ParseTupleAndKeywords(
        args,
        kwargs,
        TWO_FLOAT_ARGS,
        keywords,
        &number1,
        &number2
    );

    if (!succeed)
    {
        return 0;
    }

    if (number2 == 0.0)
    {
        PyErr_Format(PyExc_ValueError, "Divide by zero error");
        return 0;
    }

    return Py_BuildValue(FLOAT_ARG, number1 / number2);
}


PyObject * meth_sum(PyObject * self, PyObject * args)
{
    PyObject * iter = PyObject_GetIter(args);
    PyObject * item;

    float sum = 0.0;
    while ((item = PyIter_Next(iter)))
    {
        sum += PyFloat_AsDouble(item);
        Py_DECREF(item);
    }

    Py_DECREF(iter);

    return Py_BuildValue(FLOAT_ARG, sum);
}


PyObject * meth_prod(PyObject * self, PyObject * args)
{
    PyObject * iter = PyObject_GetIter(args);
    PyObject * item;

    float prod = 1.0;
    while ((item = PyIter_Next(iter)))
    {
        prod *= PyFloat_AsDouble(item);
        Py_DECREF(item);
    }

    Py_DECREF(iter);

    return Py_BuildValue(FLOAT_ARG, prod);
}

PyMethodDef module_methods[] = {
    {"add", (PyCFunction)meth_add, METH_VARARGS | METH_KEYWORDS, 0},
    {"sub", (PyCFunction)meth_sub, METH_VARARGS | METH_KEYWORDS, 0},
    {"mul", (PyCFunction)meth_mul, METH_VARARGS | METH_KEYWORDS, 0},
    {"div", (PyCFunction)meth_div, METH_VARARGS | METH_KEYWORDS, 0},
    {"sum", (PyCFunction)meth_sum, METH_VARARGS, 0},
    {"prod", (PyCFunction)meth_prod, METH_VARARGS, 0},
    {0},
};


PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "discern", 0, -1, module_methods, 0, 0, 0, 0};


PyObject * PyInit_discern()
{
    PyObject * module = PyModule_Create(&module_def);
    return module;
}
