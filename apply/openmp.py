import numpy as np
from . import omp
from .base import base_tracer, broadcast

def support_omp():
    try:
        from . import omp
        return omp.openmp()
    except ModuleNotFoundError:
        return False    
    

def omp_num_threads():
    if support_omp():
        from . import omp
        return omp.num_threads()
    else:
        return -1


def omp_set_num_threads(num):
    if support_omp():
        from . import omp
        omp.set_num_threads(num)
        
def omp_add(a : np.ndarray,
            b : np.ndarray,
            types : str):
    if np.isscalar(b):
        return getattr(omp, 'add_scalar_' + types)(a, b)
    else:
        a, b = broadcast(a._data, b)
        return getattr(omp, 'add_vector_' + types)(a, b)