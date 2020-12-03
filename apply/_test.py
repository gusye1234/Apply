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

def test_sigmoid():
    from . import omp
    from .openmp import omp_add
    from .trace import tracer
    from .base import broadcast
    import numpy as np
    omp.hello()
    a = np.random.rand(2000, 50000).astype('float32')
    a_t = tracer(a)
    with timer(name="omp"):
        for _ in range(10):
            1/(1 + (-a_t).exp())
    with timer(name='np'):
        for _ in range(10):
            1/(1+np.exp(-a))
    print(timer.dict())

def test_mat():
    from . import omp
    from .trace import tracer
    import numpy as np
    a = np.random.rand(1000,1000).astype('float32')
    a_t = tracer(a)
    b = np.random.rand(1000, 1000).astype('float32')
    # a = np.ascontiguousarray(a)
    # b = np.asfortranarray(b)
    with timer(name='omp'):
        # c = omp.matmul(a, b)
        c = 2/a_t
    with timer(name='np'):
        # d = np.matmul(a, b)
        d = 2/a
    print(timer.dict())
    print(c)
    print(d)
    print(c.shape,c.dtype, d.dtype)
    print(np.mean(np.abs(c - d)))

def test_LR():
    from . import omp
    import numpy as np
    data_1 = np.random.rand(10, 50).astype('float32')
    data = np.ones((10, 51)).astype('float32')
    data[:, :50] = data_1
    data[:, 50] = 1
    # data = np.ascontiguousarray(data).astype('float32')
    W = np.random.rand(51, 2).astype('float32')
    # W = np.asfortranarray(W)
    print(data.dtype, W.dtype)
    c = omp.matmul(data, W)
    d = np.matmul(data, W)
    print(c, d)
    print(np.mean(np.abs(c - d)))

def test_cuda():
    from . import base
    # if not base.CUDA_SUPPORT:
    #     raise TypeError("Didn't support cuda or install pyCUDA")
    from .trace import tracer
    import numpy as np
    a = np.random.rand(2000, 50000).astype('float32')
    a_t = tracer(a, device_name='cuda')

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


def test_fusion():
    from . import cuda
    from .trace import array
    func = cuda.fusion("a*b + 10")
    a = array([1,2,3,4,5], dtype='float32')
    b = array([1, 2, 3, 4, 5], dtype='float32')
    c = func(a, b)
    print(c)

if __name__ == "__main__":
    # test_ad()
    # # test_omp()
    # test_arr()
    # test_add()
    # test_sigmoid()
    # test_mat()
    # test_LR()
    test_cuda()