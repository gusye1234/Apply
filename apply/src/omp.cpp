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

int num_threads(){
    return omp_get_num_threads();
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
// -------------------------------------------------------



using namespace py::literals;

PYBIND11_MODULE(omp, m)
{
    srand(time(0));
    m.doc() = "example plugin";
    m.def("openmp", &openmp, "If support OpenMP in your platform");
    m.def("num_threads", &num_threads, "num of threads omp will use");
    m.def("set_num_threads", &set_num_threads, "Set num of threads of omp");
    m.def("hello", &hello, "say hello");
    m.def("add", &add, "test");
    m.def("add_one_int", &add_one_int, "test");
    m.def("add_one_float", &add_one_float, "test");
    py::class_<Matrix>(m, "Matrix", py::buffer_protocol())
        .def_buffer(&matrix_buff)
        .def(py::init<size_t, size_t>())
        .def("get_value", &Matrix::get_value);
}
