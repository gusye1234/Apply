import numpy as np
from .base import base_tracer, device, SUPPORT_TYPE, match_types
from . import openmp

def array(*args, **kwargs):
    arr = np.array(*args, **kwargs)
    return tracer(arr)




class tracer(base_tracer):
    def astype(self, types):
        assert types in SUPPORT_TYPE
        if self._scalar:
            if types.startswith('float'):
                data = float(self._data)
            elif types.startswith('int'):
                data = int(self._data)
            else:
                raise TypeError(f"Not supported type {types} for scalar")
        else:
            data = self._data.astype(types)
        return _COPY(data, self)

    def __getattr__(self, name):
        data = self._data.__getattribute__(name)
        if isinstance(data, np.ndarray):
            data = _COPY(data, self)
        return data

    def moveAndMatch(self, b):
        if not isinstance(b, tracer):
            b = _COPY(b, self)
        types = match_types(self, b)
        return b, types

    def __neg__(self):
        if self._device == 'omp':
            data = openmp.omp_neg(self._data, self.dtype)
        return _COPY(data, self)

    def __add__(self, b):
        b, types = self.moveAndMatch(b)
        if self._device == 'omp':
            data = openmp.omp_add(self._data, b._data, types)
        return _COPY(data, self)

    def __radd__(self, b):
        return self.__add__(b)

    def __sub__(self, b):
        b, types = self.moveAndMatch(b)
        if self._device == 'omp':
            data = openmp.omp_sub(self._data, b._data, types)
        return _COPY(data, self)

    def __rsub__(self, b):
        b, types = self.moveAndMatch(b)
        if self._device == 'omp':
            data = openmp.omp_sub(self._data, b._data, types, right=True)
        return _COPY(data, self)

    def __mul__(self, b):
        b, types = self.moveAndMatch(b)
        if self._device == 'omp':
            data = openmp.omp_mul(self._data, b._data, types)
        return _COPY(data, self)

    def __rmul__(self, b):
        return self.__mul__(b)

    def __truediv__(self, b):
        b, types = self.moveAndMatch(b)
        if self._device == 'omp':
            data = openmp.omp_div(self._data, b._data, types)
        return _COPY(data, self)
        # return _COPY(self._data.__truediv__(b), self)
        # return _COPY(self._data.__floordiv__(b), self)

    def __rtruediv__(self, b):
        b, types = self.moveAndMatch(b)
        if self._device == 'omp':
            data = openmp.omp_div(self._data, b._data, types, right=True)
        return _COPY(data, self)
        # return _COPY(self._data.__rtruediv__(b), self)

    def exp(self):
        if self._device == 'omp':
            data = openmp.omp_exp(self._data, self.dtype)
        return _COPY(data, self)

    def sin(self):
        if self._device == 'omp':
            data = openmp.omp_sin(self._data, self.dtype)
        return _COPY(data, self)

    def cos(self):
        if self._device == 'omp':
            data = openmp.omp_cos(self._data, self.dtype)
        return _COPY(data, self)


def _COPY(data: np.ndarray, src):
    return tracer(data, device_name=src.get_device())