import numpy as np
from .base import base_tracer, device
from . import openmp

def array(*args, **kwargs):
    arr = np.array(*args, **kwargs)
    return tracer(arr)

def _COPY(data : np.ndarray, src: tracer):
    return tracer(data, device_name=src.get_device())


class tracer(base_tracer):
    def __getattr__(self, name):
        data = self._data.__getattribute__(name)
        if isinstance(data, np.ndarray):
            data = _COPY(data, self)
        return data

    def __neg__(self):
        pass

    def __add__(self, b):
        if not isinstance(b, tracer):
            b = _COPY(b, self)
        if self._device == 'omp':
            data = openmp.omp_add(self._data, b._data)

    def __radd__(self, b):
        return self.__add__(b)

    def __sub__(self, b):
        pass

    def __rsub__(self, b):
        pass

    def __mul__(self, b):
        pass

    def __rmul__(self, b):
        pass

    def __truediv__(self, b):
        if self._device == 'omp':
            return _COPY(self._data.__truediv__(b), self)

    def __floordiv__(self, b):
        return _COPY(self._data.__floordiv__(b), self)

    def __rtruediv__(self, b):
        return _COPY(self._data.__rtruediv__(b), self)
