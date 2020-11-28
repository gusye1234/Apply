#include "operator.h"
#include <random>
#include <algorithm>
#include <time.h>


using namespace std;
namespace py = pybind11;

int NUM_THREADS = 8;
// -------------------------------------------------------
// helper functions

// check the support of omp
bool openmp()
{
    #if _OPENMP
        return true;
    #else
        return false;
    #endif
}

void set_num_threads(int num_threads){
    omp_set_num_threads(num_threads);
}

// for fun 
void hello()
{
    int iam = 0, nt = 0;
    #pragma omp parallel private(iam, nt)
    {
        iam = omp_get_thread_num();
        nt = omp_get_num_threads();
        printf("Hello from %d %d \n", iam, nt);
    }
}

void show_size(){
    printf("SIZE int %lu\n", sizeof(int));
    printf("SIZE long %lu\n", sizeof(long));
    printf("SIZE long long%lu\n", sizeof(long long));
    printf("SIZE float %lu\n", sizeof(float));
    printf("SIZE double %lu\n", sizeof(double));
    printf("SIZE double double %lu\n", sizeof(long double));
}

// Count the current num of threads
int omp_thread_count()
{
    int n = 0;
    #pragma omp parallel reduction(+:n)
    n += 1;
    return n;
}
// -------------------------------------------------------



using namespace py::literals;

PYBIND11_MODULE(omp, m)
{
    srand(time(0));
    m.doc() = "example plugin";
    m.def("openmp", &openmp, "If support OpenMP in your platform");
    m.def("num_threads", &omp_thread_count, "num of threads omp will use");
    m.def("set_num_threads", &set_num_threads, "Set num of threads of omp");
    m.def("hello", &hello, "say hello");
    m.def("SIZE", &show_size, "show sizes of different types");
    m.def("add_scalar_int32", &add_scalar_int32, "test");
    m.def("add_scalar_int64", &add_scalar_int64, "test");
    m.def("add_scalar_float32", &add_scalar_float32, "test");
    m.def("add_scalar_float64", &add_scalar_float64, "test");
    m.def("add_scalar_float128", &add_scalar_float128, "test");
    m.def("add_vector_int32", &add_vector_int32, "test");
    m.def("add_vector_int64", &add_vector_int64, "test");
    m.def("add_vector_float32", &add_vector_float32, "test");
    m.def("add_vector_float64", &add_vector_float64, "test");
    m.def("add_vector_float128", &add_vector_float128, "test");
}

// py::class_<Matrix>(m, "Matrix", py::buffer_protocol())
//     .def_buffer(&matrix_buff)
//     .def(py::init<size_t, size_t>())
//     .def("get_value", &Matrix::get_value);
