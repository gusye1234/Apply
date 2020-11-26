def test_ad():
    from .adventurer import Adventurer
    def test_function(x):
        x = x+1
        x = 2+x
        x += 10
        return -x
    peek = Adventurer(name=test_function.__name__)
    peek = test_function(peek)
    print(peek)
    
def test_omp():
    from . import omp
    from .operator import support_omp, omp_num_threads, omp_set_num_threads
    from .utils import timer

    # omp.see()
    if support_omp():
        print("Openmp support")
    omp.hello()
    
def test_arr():
    from . import omp
    import numpy as np
    a = np.array([1,2,3,4])
    print(omp.add_one_float(a))
    print(a)
    
if __name__ == "__main__":
    # test_ad()
    # test_omp()
    test_arr()