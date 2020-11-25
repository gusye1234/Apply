#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <omp.h>
#include <iostream>
#include <random>
#include <algorithm>
#include <time.h>

typedef unsigned int ui;

using namespace std;
namespace py = pybind11;

int NUM_THREADS = 8;


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


py::array_t<double> para_table()
{
    const int size = 8;
    const int size2 = 1000000;
    int count=0;
    int t_id = 0;
    // double* sinTable = new double[size];
    py::array_t<double> S_array = py::array_t<double>(size*size2);
    py::buffer_info buf_s = S_array.request();
    double *ptr = (double *)buf_s.ptr;

    #pragma omp parallel for private(t_id) shared(count)
    for (int n = 0; n < size; ++n)
    {
        printf("Curretn id %d\n", omp_get_thread_num());
        for (int j=0; j < size2; j++){
            // #pragma omp atomic
            // count = count + 1;
            ptr[n * size2 + j] = sin(n * size2 + j);
        }
    }

    // the table is now initialized
    return S_array;
}

void hello()
{
    int iam=0, nt=0;
    #pragma omp parallel private(iam, nt)
    {
        iam = omp_get_thread_num();
        nt = omp_get_num_threads();
        printf("Hello from %d %d \n", iam, nt);
    }

}


py::array_t<double> table()
{
    const int size = 8000000;
    // double* sinTable = new double[size];
    py::array_t<double> S_array = py::array_t<double>(size);
    py::buffer_info buf_s = S_array.request();
    double *ptr = (double *)buf_s.ptr;

    for (int n = 0; n < size; ++n)
    {
        ptr[n] = sin(n);
    }

    // the table is now initialized
    return S_array;
}

using namespace py::literals;

PYBIND11_MODULE(operator_omp, m)
{
    srand(time(0));
    m.doc() = "example plugin";
    m.def("openmp", &openmp, "If support OpenMP in your platform");
    m.def("num_threads", &num_threads, "num of threads omp will use");
    m.def("set_num_threads", &set_num_threads, "Set num of threads of omp");
    m.def("hello", &hello, "say hello");
    m.def("table", &table, "one thread");
    m.def("para_table", &para_table, "Multi threads");

}