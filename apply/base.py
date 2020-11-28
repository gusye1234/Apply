import numpy as np


SUPPORT_TYPE = ['int32', 'int64','float32', 'float64', 'float128']

TYPE_PRIORITY = {
    SUPPORT_TYPE[i]: i for i in range(SUPPORT_TYPE)
}


class base_tracer:
    def __init__(self,
                 data : np.ndarray,
                 device_name='omp',
                 need_to_move=False):
        if np.isscalar(data):
            self._data = data
        else:
            try:
                assert data.dtype in base_tracer.SUPPORT_TYPE
            except:
                raise NotImplementedError(f"Not support this number type {data.dtype} among {SUPPORT_TYPE}")
        self.dtype = str(data.dtype)
        self._data = data
        self._device = device(device_name)
        if need_to_move:
            self.move_data_to_()

    def get_device(self):
        return self._device

    def get_type(self):
        return base_tracer.Table[str(self._data.dtype)]

    def to(self, name):
        return tracer(np.copy(self._data), name)

    def numpy(self):
        return self._data

    def move_data_to_(self):
        pass

    def __repr__(self):
        array_name = 'tracer' + repr(self._data)[5:-1]
        info = f", {self._device})"
        return f"{array_name}{info}"

    def __getitem__(self, index):
        data = self._data[index]
        return tracer(data, device_name=self._device)

    def __setitem__(self, b, c):
        self._data[b] = c

    def __array__(self):
        return self._data

class device:
    def __init__(self, name):
        assert str(name) in ['omp', 'cuda']
        self._name = str(name)

    def __repr__(self):
        return f"device({self._name})"

    def __str__(self):
        return self._name

    def __eq__(self, b):
        if isinstance(b, str):
            return self._name == b
        elif isinstance(b, device):
            return self._name == b._name
        else:
            return id(self) == id(b)


def broadcast(a, b):
    a, b = np.broadcast_arrays(a, b)
    return np.ascontiguousarray(a), np.ascontiguousarray(b)

def match_types(a, b):
    pass