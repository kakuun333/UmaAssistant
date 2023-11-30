#include "../stdafx.h"
#include <Python.h>

PyManager* PyManager::_instance = nullptr;

bool PyManager::_inited = false;

void PyManager::Init()
{
	Py_Initialize();
	_inited = true;
}

void PyManager::event_data_jp2tw()
{
	if (!_inited) return;


	// ¾É¤J event_data_jp2tw_dumper.py
	PyObject* pModule = PyImport_Import(PyUnicode_DecodeFSDefault(global::path::std_event_data_jp2tw_dumper_py.c_str()));
}