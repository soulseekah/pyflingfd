pyflingfd
=========

A simple Python binding for https://github.com/sharvil/flingfd

```python
import flingfd
import os

fd = flingfd.simple_recv( '/tmp/uniquefile' )
os.write( fd, 'fling!' )
```

```python
import flingfd
import sys

flingfd.simple_send( '/tmp/uniquefile', sys.stdout )
```

Installing is super easy: `pip install -U .` or `python setup.py install` should work out of the box.
```