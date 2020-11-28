
// #define GENERIC_ADD(type) type add_##type(type i, type j)
// #define GENERIC_multi(type) type multi_##type(type i, type j)
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <iostream>
#include <omp.h>


typedef int int32;
typedef long int64;
typedef float float32;
typedef double float64;
typedef long double float128;

namespace py = pybind11;
int omp_thread_count();

//  | py::array::forcecast

#define ADD_SCALARNAME(type) py::array_t<type> add_scalar_##type(py::array_t<type, py::array::c_style> &in_array, type scalar)
#define ADD_VECTORNAME(type) py::array_t<type> add_vector_##type(py::array_t<type, py::array::c_style> &in_array, py::array_t<type, py::array::c_style> &sec_array)
#define SUB_SCALARNAME(type) py::array_t<type> sub_scalar_##type(py::array_t<type, py::array::c_style> &in_array, type scalar)
#define SUB_VECTORNAME(type) py::array_t<type> sub_vector_##type(py::array_t<type, py::array::c_style> &in_array, py::array_t<type, py::array::c_style> &sec_array)
#define MUL_SCALARNAME(type) py::array_t<type> mul_scalar_##type(py::array_t<type, py::array::c_style> &in_array, type scalar)
#define MUL_VECTORNAME(type) py::array_t<type> mul_vector_##type(py::array_t<type, py::array::c_style> &in_array, py::array_t<type, py::array::c_style> &sec_array)
#define DIV_SCALARNAME(type) py::array_t<type> mul_scalar_##type(py::array_t<type, py::array::c_style> &in_array, type scalar)
#define DIV_VECTORNAME(type) py::array_t<type> mul_vector_##type(py::array_t<type, py::array::c_style> &in_array, py::array_t<type, py::array::c_style> &sec_array)
#define EXP_VECTORNAME(type) py::array_t<type> exp_vector_##type(py::array_t<type, py::array::c_style> &in_array)
#define SIN_VECTORNAME(type) py::array_t<type> sin_vector_##type(py::array_t<type, py::array::c_style> &in_array)
#define COS_VECTORNAME(type) py::array_t<type> cos_vector_##type(py::array_t<type, py::array::c_style> &in_array)

ADD_SCALARNAME(int32);
ADD_SCALARNAME(int64);
ADD_SCALARNAME(float32);
ADD_SCALARNAME(float64);
ADD_SCALARNAME(float128);
ADD_VECTORNAME(int32);
ADD_VECTORNAME(int64);
ADD_VECTORNAME(float32);
ADD_VECTORNAME(float64);
ADD_VECTORNAME(float128);
MUL_SCALARNAME(int32);
MUL_SCALARNAME(int64);
MUL_SCALARNAME(float32);
MUL_SCALARNAME(float64);
MUL_SCALARNAME(float128);
MUL_VECTORNAME(int32);
MUL_VECTORNAME(int64);
MUL_VECTORNAME(float32);
MUL_VECTORNAME(float64);
MUL_VECTORNAME(float128);

// Can you see me?
// class Matrix
// {
// public:
//     Matrix(size_t rows, size_t cols) : m_rows(rows), m_cols(cols)
//     {
//         m_data = new float[rows * cols];
//     }
//     float *data() { return m_data; }
//     size_t rows() const { return m_rows; }
//     size_t cols() const { return m_cols; }
//     float get_value(size_t row, size_t col) const {
//         return this->m_data[row*this->m_cols + col];
//     }
// private:
//     size_t m_rows, m_cols;
//     float *m_data;
// };
// py::buffer_info matrix_buff(Matrix &m);