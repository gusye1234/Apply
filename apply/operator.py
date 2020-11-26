
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