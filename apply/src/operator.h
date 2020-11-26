
// #define GENERIC_ADD(type) type add_##type(type i, type j)
// #define GENERIC_multi(type) type multi_##type(type i, type j)
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <iostream>
#include <omp.h>

namespace py = pybind11;


int add(int i, int j);
// py::array_t<int> add_one(py::array_t<int> &in_array);

#define ADDNAME(type) py::array_t<type> add_one_##type(py::array_t<type> &in_array)

ADDNAME(int);
ADDNAME(float);

// Can you see me?
class Matrix
{
public:
    Matrix(size_t rows, size_t cols) : m_rows(rows), m_cols(cols)
    {
        m_data = new float[rows * cols];
    }
    float *data() { return m_data; }
    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }
    float get_value(size_t row, size_t col) const {
        return this->m_data[row*this->m_cols + col];
    }
private:
    size_t m_rows, m_cols;
    float *m_data;
};
py::buffer_info matrix_buff(Matrix &m);