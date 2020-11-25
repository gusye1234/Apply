from . import operator_omp
from .operator import support_omp, omp_num_threads, omp_set_num_threads
from .utils import timer

# operator_omp.see()
if support_omp():
    print("Openmp support")

operator_omp.hello()
omp_set_num_threads(8)


# shape2 = operator_omp.para_table().shape

with timer(name="one"):
    for _ in range(10):
        shape1 = operator_omp.table().shape
print(f"cost {timer.get('one')/10}")

with timer(name="omp"):
    for _ in range(10):
        shape2 = operator_omp.para_table().shape
assert shape1 == shape2
print(f"cost {timer.get('omp')/10}")
