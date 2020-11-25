
def support_omp():
    try:
        from . import operator_omp
        return operator_omp.openmp()
    except ModuleNotFoundError:
        return False    
    

def omp_num_threads():
    if support_omp():
        from . import operator_omp
        return operator_omp.num_threads()
    else:
        return -1


def omp_set_num_threads(num):
    if support_omp():
        from . import operator_omp
        operator_omp.set_num_threads(num)