from .utils import timer
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
    from .openmp import support_omp, omp_num_threads, omp_set_num_threads
    from .utils import timer

    # omp.see()
    if support_omp():
        print("Openmp support")
    omp.hello()

def test_arr():
    from . import omp
    from . import openmp
    import numpy as np
    omp.SIZE()
    omp.hello()
    a = np.random.rand(20000000).astype('float')
    b = np.random.rand(20000000).astype('float')
    omp.add_scalar_float(a, 10)
    with timer(name="omp"):
        for _ in range(10):
            omp.add_vector_float(a, b)
    print(f"mean {timer.get('omp') / 10}")
    with timer(name="np"):
        for _ in range(10):
            c = a + b
    print(f"mean {timer.get('np') / 10}")
    print(omp.add_scalar_float(a, 10))
    print(a)

def test_add():
    from . import omp
    import numpy as np
    omp.hello()
    def omp_add(a : np.ndarray,
                b : np.ndarray,
                types : str):
        if np.isscalar(b):
            print('scalar')
            return getattr(omp, 'add_scalar_' + types)(a, b)
        else:
            if a.shape != b.shape:
                a, b = broadcast(a._data, b)
            return getattr(omp, 'add_vector_' + types)(a, b)

    a = np.random.rand(2000, 50000).astype('float32')
    b = np.random.rand(2000, 50000).astype('float32')
    print(a.dtype)
    print(b.dtype)
    with timer(name="omp"):
        for _ in range(10):
            omp_add(a, b, 'float32')
    print(f"mean {timer.get('omp') / 10}")
    with timer(name="np"):
        for _ in range(10):
            c = a + b
    print(f"mean {timer.get('np') / 10}")

if __name__ == "__main__":
    # test_ad()
    # # test_omp()
    # test_arr()
    test_add()