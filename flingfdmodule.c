#include <Python.h>
#include "libflingfd/src/flingfd.h"

static PyObject * pyflingfd_simple_send( PyObject *self, PyObject *args ) {
	const char *path;
	int fd;

	if ( !PyArg_ParseTuple( args, "si", &path, &fd ) )
		Py_RETURN_FALSE;

	if ( flingfd_simple_send( path, fd ) )
		Py_RETURN_TRUE;

	Py_RETURN_FALSE;
}

static PyObject * pyflingfd_simple_recv( PyObject *self, PyObject *args ) {
	const char *path;
	int fd;

	if ( !PyArg_ParseTuple( args, "s", &path ) )
		Py_RETURN_FALSE;
	
	if ( ( fd = flingfd_simple_recv( path ) ) != -1 )
		return Py_BuildValue( "i", fd );
	
	Py_RETURN_FALSE;
}

static PyMethodDef FlingFDMethods[] = {
	{ "simple_send", pyflingfd_simple_send, METH_VARARGS,
		"Sends a single file descriptor to a receiver." },
	{ "simple_recv", pyflingfd_simple_recv, METH_VARARGS,
		"Receives a single file descriptor from a sender." },
	{ NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC initflingfd( void ) {
	(void)Py_InitModule( "flingfd", FlingFDMethods );
}

