pyflingfd
=========

A simple Python binding for https://github.com/sharvil/flingfd - a small, standalone C library to pass file descriptors across processes on Linux.

```python
import flingfd
import os

fd = flingfd.simple_recv( '/tmp/uniquefile' )
os.write( fd, 'fling!' )
os.fsync( fd )
```

```python
import flingfd
import sys

flingfd.simple_send( '/tmp/uniquefile', sys.stdout )
```

Installing is super easy: `pip install -U .` or `python setup.py install` should work out of the box.
