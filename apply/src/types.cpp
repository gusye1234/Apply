#include "operator.h"

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
void Arrange(size_t arr_size, int &max_threads, int &arrange){
    max_threads = omp_thread_count();
    arrange = (int)std::ceil((float)arr_size / max_threads);
}

#define ADD_SCALAR(type) \
    ADD_SCALARNAME(type) \
    VECTOR_SCALAR_TYPE(type, type, ptr_in[index] + scalar)

#define ADD_VECTOR(type) \
    ADD_VECTORNAME(type) \
    VECTOR_VECTOR_TYPE(type, type, ptr_in[index] + ptr_sec[index])

#define SUB_SCALAR(type) \
    SUB_SCALARNAME(type) \
    VECTOR_SCALAR_TYPE(type, type, ptr_in[index] - scalar)

#define RSUB_SCALAR(type) \
    RSUB_SCALARNAME(type) \
    VECTOR_SCALAR_TYPE(type, type, scalar - ptr_in[index])

#define SUB_VECTOR(type) \
    SUB_VECTORNAME(type) \
    VECTOR_VECTOR_TYPE(type, type, ptr_in[index] - ptr_sec[index])

#define MUL_SCALAR(type) \
    MUL_SCALARNAME(type) \
    VECTOR_SCALAR_TYPE(type, type, ptr_in[index] * scalar)

#define MUL_VECTOR(type) \
    MUL_VECTORNAME(type) \
    VECTOR_VECTOR_TYPE(type, type, ptr_in[index] * ptr_sec[index])

#define RDIV_SCALAR(type, type2) \
    RDIV_SCALARNAME(type, type2) \
    VECTOR_SCALAR_TYPE(type, type2, scalar / ptr_in[index])

#define DIV_SCALAR(type, type2) \
    DIV_SCALARNAME(type, type2) \
    VECTOR_SCALAR_TYPE(type, type2, ptr_in[index] / scalar)

#define DIV_VECTOR(type, type2) \
    DIV_VECTORNAME(type, type2) \
    VECTOR_VECTOR_TYPE(type, type2, ptr_in[index] / ptr_sec[index])

#define NEG_VECTOR(type) \
    NEG_VECTORNAME(type) \
    VECTOR_TYPE(type, type, -ptr_in[index])

#define EXP_VECTOR(type, type2) \
    EXP_VECTORNAME(type, type2) \
    VECTOR_TYPE(type, type2, std::exp(ptr_in[index]))

#define COS_VECTOR(type) \
    COS_VECTORNAME(type) \
    VECTOR_TYPE(type, float32, std::cos(ptr_in[index]))

#define SIN_VECTOR(type) \
    SIN_VECTORNAME(type) \
    VECTOR_TYPE(type, float32, std::sin(ptr_in[index]))

ALLTYPE(ADD_SCALAR);
ALLTYPE(ADD_VECTOR);

ALLTYPE(MUL_SCALAR);
ALLTYPE(MUL_VECTOR);

ALLTYPE(SUB_SCALAR);
ALLTYPE(SUB_VECTOR);
ALLTYPE(RSUB_SCALAR);

// TODO: int64 return float32, fix it
ALLTYPE_FLOAT(DIV_SCALAR);
ALLTYPE_FLOAT(RDIV_SCALAR);
ALLTYPE_FLOAT(DIV_VECTOR);
// ALLTYPE(RDIV_SCALAR);
ALLTYPE_FLOAT(EXP_VECTOR);

ALLTYPE(NEG_VECTOR);
ALLTYPE(COS_VECTOR);
ALLTYPE(SIN_VECTOR);
