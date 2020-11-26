#include "operator.h"
#include <math.h>

using namespace std;
namespace py = pybind11;

int add(int i, int j){
    return i+j;
}



py::buffer_info matrix_buff(Matrix &m)
{
    return py::buffer_info(
        m.data(),                               /* Pointer to buffer */
        sizeof(float),                          /* Size of one scalar */
        py::format_descriptor<float>::format(), /* Python struct-style format descriptor */
        2,                                      /* Number of dimensions */
        {m.rows(), m.cols()},                   /* Buffer dimensions */
        {sizeof(float) * m.cols(),              /* Strides (in bytes) for each index */
         sizeof(float)});
}


#define ADD(type)     ADDNAME(type)                              \
{                                                                \
    py::buffer_info buf = in_array.request();                    \
    py::array_t<type> temp = py::array_t<type>(buf.shape);       \
    py::buffer_info buf_temp = temp.request();                   \
    size_t arr_size = buf.size;                                  \
    type *ptr = (type *)buf_temp.ptr;                            \
    type *ptr_o = (type *)buf.ptr;                               \
    int max_threads = 8;                                         \
    int arrange = (int)std::ceil((float)arr_size / max_threads); \
    _Pragma("omp parallel for")                                  \
    for (int thread = 0; thread < max_threads; thread++)         \
    {                                                            \
        for (int i = 0; i < arrange; i++)                        \
        {                                                        \
            printf("Now threads is %d\n", omp_get_thread_num()); \
            int index = (thread * arrange + i);                  \
            if (index >= arr_size)                               \
            {                                                    \
                break;                                           \
            }                                                    \
            ptr[index] = ptr_o[index] + 1;                       \
        } \
    } \
    return temp;}\



ADD(int)

ADD(float)
