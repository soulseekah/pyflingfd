#include <Python.h>
#include "libflingfd/src/flingfd.h"

static PyObject * pyflingfd_simple_send( PyObject *self, PyObject *args ) {
	const char *path;
	PyObject *fp;
	int fd;

	if ( !PyArg_ParseTuple( args, "sO", &path, &fp ) )
		return NULL;

	#if PY_MAJOR_VERSION >= 3
		fd = PyObject_AsFileDescriptor( fp );
		if ( fd == -1 )
			return PyErr_SetFromErrno( PyExc_IOError );
	#else
		if ( !PyFile_Check( fp ) ) {
			PyErr_SetString( PyExc_IOError, "Not a file object" );
			return NULL;
		}
		fd = fileno( PyFile_AsFile( fp ) );
		if ( fd == -1 )
			return PyErr_SetFromErrno( PyExc_IOError );
	#endif

	if ( flingfd_simple_send( path, fd ) )
		Py_RETURN_TRUE;

	PyErr_SetFromErrno( PyExc_IOError );
	return NULL;
}

static PyObject * pyflingfd_simple_recv( PyObject *self, PyObject *args ) {
	const char *path;
	int fd;

	if ( !PyArg_ParseTuple( args, "s", &path ) )
		return NULL;
	
	if ( ( fd = flingfd_simple_recv( path ) ) != -1 )
		return Py_BuildValue( "i", fd );
	
	PyErr_SetFromErrno( PyExc_IOError );
	return NULL;
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

