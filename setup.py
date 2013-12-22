from setuptools import setup, Extension

pyflingfd = Extension( 'flingfd', sources=[ 'flingfdmodule.c', 'libflingfd/src/flingfd.c' ], extra_compile_args= [ '-std=c99' ] )

setup(
	name = 'flingfd',
	version = '0.1',
	description = 'A Python wrapper for flingfd, a library to pass file descriptors across processes on Linux.',
	keywords = ( 'ipc', 'files' ),
	author = 'Gennady Kovshenin',
	author_email = 'gennady@kovshenin.com',
	url = 'https://github.com/soulseekah/pyflingfd',
	
	ext_modules = [ pyflingfd ]
)
