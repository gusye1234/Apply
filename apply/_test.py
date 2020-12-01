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
    a = np.random.rand(20000000).astype('int32')
    # b = np.random.rand(20000000).astype('int32')
    with timer(name="omp"):
        for _ in range(10):
            # omp.add_scalar_float32(a, 1)
            # omp.exp_vector_float32(a)
            # omp.cos_vector_float32(a)
            print(openmp.omp_add(a, 2.3).dtype)
    print(f"mean {timer.get('omp') / 10}")
    with timer(name="np"):
        for _ in range(10):
            # c = a+1
            # c = -a
            # np.exp(a)
            # np.cos(a)
            c = a/2.3
            print(c.dtype)
    print(f"mean {timer.get('np') / 10}")
    print(omp.div_scalar_int32(a, 2.3))
    print(a/2)

def test_add():
    from . import omp
    from .openmp import omp_add
    from .trace import tracer
    from .base import broadcast
    import numpy as np
    omp.hello()
    a = np.random.rand(2000, 50000).astype('float32')
    a_t = tracer(a)

    with timer(name='omp cos'):
        a_t.cos()
    with timer(name='omp sin'):
        a_t.sin()
    with timer(name='omp exp'):
        a_t.exp()
    with timer(name='omp sub'):
        a_t - 1
    with timer(name='omp add'):
        a_t + 1
    with timer(name='omp mul'):
        a_t * 1
    with timer(name='omp div'):
        a_t / 1
    with timer(name='omp neg'):
        -a_t
    print(timer.dict())
    timer.zero()
    with timer(name='np cos'):
        np.cos(a)
    with timer(name='np sin'):
        np.sin(a)
    with timer(name='np exp'):
        np.exp(a)
    with timer(name='np sub'):
        a - 1
    with timer(name='np add'):
        a + 1
    with timer(name='np mul'):
        a * 1
    with timer(name='np div'):
        a / 1
    with timer(name='np neg'):
        -a
    print(timer.dict())

if __name__ == "__main__":
    # test_ad()
    # # test_omp()
    # test_arr()
    test_add()