#include "operator.h"
#include <math.h>

using namespace std;
namespace py = pybind11;

// py::buffer_info matrix_buff(Matrix &m)
// {
//     return py::buffer_info(
//         m.data(),                               /* Pointer to buffer */
//         sizeof(float),                          /* Size of one scalar */
//         py::format_descriptor<float>::format(), /* Python struct-style format descriptor */
//         2,                                      /* Number of dimensions */
//         {m.rows(), m.cols()},                   /* Buffer dimensions */
//         {sizeof(float) * m.cols(),              /* Strides (in bytes) for each index */
//          sizeof(float)});
// }

#define ADD_SCALAR(type)                                                                 \
    ADD_SCALARNAME(type)                                                                 \
    {                                                                                    \
        py::buffer_info buf = in_array.request();                                        \
        py::array_t<type> temp = py::array_t<type>(buf.shape);                           \
        py::buffer_info buf_temp = temp.request();                                       \
        size_t arr_size = buf.size;                                                      \
        type *ptr = (type *)buf_temp.ptr;                                                \
        type *ptr_o = (type *)buf.ptr;                                                   \
        int max_threads = 8;                                                             \
        int arrange = (int)std::ceil((float)arr_size / max_threads);                     \
        _Pragma("omp parallel for") for (int thread = 0; thread < max_threads; thread++) \
        {                                                                                \
            for (int i = 0; i < arrange; i++)                                            \
            {                                                                            \
                int index = (thread * arrange + i);                                      \
                if (index >= arr_size)                                                   \
                {                                                                        \
                    break;                                                               \
                }                                                                        \
                ptr[index] = ptr_o[index] + scalar;                                      \
            }                                                                            \
        }                                                                                \
        return temp;                                                                     \
    }

#define ADD_VECTOR(type)                                                                 \
    ADD_VECTORNAME(type)                                                                 \
    {                                                                                    \
        py::buffer_info buf_in = in_array.request();                                     \
        py::buffer_info buf_sec = sec_array.request();                                   \
        py::array_t<type> temp = py::array_t<type>(buf_in.shape);                        \
        py::buffer_info buf_temp = temp.request();                                       \
        size_t arr_size = buf_in.size;                                                   \
        type *ptr = (type *)buf_temp.ptr;                                                \
        type *ptr_in = (type *)buf_in.ptr;                                               \
        type *ptr_sec = (type *)buf_sec.ptr;                                             \
        int max_threads = omp_thread_count();                                            \
        int arrange = (int)std::ceil((float)arr_size / max_threads);                     \
        _Pragma("omp parallel for") for (int thread = 0; thread < max_threads; thread++) \
        {                                                                                \
            for (int i = 0; i < arrange; i++)                                            \
            {                                                                            \
                int index = (thread * arrange + i);                                      \
                if (index >= arr_size)                                                   \
                {                                                                        \
                    break;                                                               \
                }                                                                        \
                ptr[index] = ptr_in[index] + ptr_sec[index];                             \
            }                                                                            \
        }                                                                                \
        return temp;                                                                     \
    }

ADD_SCALAR(int32);
ADD_SCALAR(int64);
ADD_SCALAR(float32);
ADD_SCALAR(float64);
ADD_SCALAR(float128);
ADD_VECTOR(int32);
ADD_VECTOR(int64);
ADD_VECTOR(float32);
ADD_VECTOR(float64);
ADD_VECTOR(float128);
// MUL_SCALARNAME(int32);
// MUL_SCALARNAME(int64);
// MUL_SCALARNAME(float32);
// MUL_SCALARNAME(float64);
// MUL_SCALARNAME(float128);
// MUL_VECTORNAME(int32);
// MUL_VECTORNAME(int64);
// MUL_VECTORNAME(float32);
// MUL_VECTORNAME(float64);
// MUL_VECTORNAME(float128);
