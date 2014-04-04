#include "StdAfx.h"
#include "Enemy.h"
#include <Python.h>


Enemy::Enemy(void)
{
}


Enemy::~Enemy(void)
{
}

float Enemy::wander()
{
	PyObject *pName, *pModule, *pDict, *pFunc, *pValue, *pArgs;
	float ret;

	Py_Initialize();

	pName = PyBytes_FromString("testPython");

	pModule = PyImport_ImportModule("testPython");

	pDict = PyModule_GetDict(pModule);

	pFunc = PyDict_GetItemString(pDict, "wander");


	if (PyCallable_Check(pFunc))
	{
		pArgs = PyTuple_New(0 /*number of arguments*/);

		pValue = PyObject_CallObject(pFunc, pArgs);

		ret = (float)PyFloat_AsDouble(pValue);

	}
	Py_Finalize();

	return ret;
}

vector2 Enemy::seek(float x,float y,float xt,float yt,float speed)
{
	PyObject *pName, *pModule, *pDict, *pFunc, *pValue, *pArgs;
	vector2 ret;

	Py_Initialize();

	pName = PyBytes_FromString("testPython");

	pModule = PyImport_ImportModule("testPython");

	pDict = PyModule_GetDict(pModule);

	pFunc = PyDict_GetItemString(pDict, "seekX");


	if (PyCallable_Check(pFunc))
	{
		pArgs = PyTuple_New(5 /*number of arguments*/);

		// Argument 1
		pValue = PyFloat_FromDouble((double)x);
		PyTuple_SetItem(pArgs, 0, pValue);

		// Argument 2
		pValue = PyFloat_FromDouble((double)y);
		PyTuple_SetItem(pArgs, 1, pValue);

		// Argument 3
		pValue = PyFloat_FromDouble((double)xt);
		PyTuple_SetItem(pArgs, 2, pValue);

		// Argument 4
		pValue = PyFloat_FromDouble((double)yt);
		PyTuple_SetItem(pArgs, 3, pValue);

		// Argument 5
		pValue = PyFloat_FromDouble((double)speed);
		PyTuple_SetItem(pArgs, 4, pValue);

		pValue = PyObject_CallObject(pFunc, pArgs);

		ret.x = (float)PyFloat_AsDouble(pValue);

	}

	pFunc = PyDict_GetItemString(pDict, "seekY");


	if (PyCallable_Check(pFunc))
	{
		pArgs = PyTuple_New(5 /*number of arguments*/);

		// Argument 1
		pValue = PyFloat_FromDouble((double)x);
		PyTuple_SetItem(pArgs, 0, pValue);

		// Argument 2
		pValue = PyFloat_FromDouble((double)y);
		PyTuple_SetItem(pArgs, 1, pValue);

		// Argument 3
		pValue = PyFloat_FromDouble((double)xt);
		PyTuple_SetItem(pArgs, 2, pValue);

		// Argument 4
		pValue = PyFloat_FromDouble((double)yt);
		PyTuple_SetItem(pArgs, 3, pValue);

		// Argument 5
		pValue = PyFloat_FromDouble((double)speed);
		PyTuple_SetItem(pArgs, 4, pValue);

		pValue = PyObject_CallObject(pFunc, pArgs);

		ret.y = (float)PyFloat_AsDouble(pValue);

	}
	Py_Finalize();

	return ret;
}