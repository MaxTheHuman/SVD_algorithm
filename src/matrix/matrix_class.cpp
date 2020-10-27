#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

#include "matrix_class.h"

    Matrix::Matrix(int rows_number, int columns_number) :
                n(rows_number), m(columns_number),
                data(rows_number, std::vector<double>(columns_number, 0)) {}

    void Matrix::transpose() {

        std::vector<std::vector<double> > result(m, std::vector<double>(n, 0));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                result[j][i] = data[i][j];
            }
        }

        data = result;
        std::swap(n, m);
    }

    double Matrix::frobenius_norm() const {

        double result = 0;

        for (const std::vector<double>& v : data) {
            result  += scalar_composition(v, v);
        }

        return sqrt(result);
    }

    double Matrix::distance_to_aXb(const std::vector<double>& a,
                           const std::vector<double>& b) const {

        double result = 0;

        for (size_t i = 0; i < a.size(); ++i) {
            for (size_t j = 0; j < b.size(); ++j) {
                result += pow((a[i] * b[j] - data[i][j]), 2);
            }
        }

        return result;
    }

    void Matrix::substract_aXb(const std::vector<double>& a, const std::vector<double>& b) {

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                data[i][j] -= a[i] * b[j];
            }
        }
    }

    const std::vector<double>& Matrix::operator[](size_t i) const {
        return data[i];
    }

    std::vector<double>& Matrix::operator[](size_t i) {
        return data[i];
    }

    int Matrix::get_rows_number() const {
        return n;
    }

    int Matrix::get_columns_number() const {
        return m;
    }


std::istream& operator>>(std::istream& in, Matrix& m) {

        for (int i = 0; i < m.get_rows_number(); ++i) {
            for (int j = 0; j < m.get_columns_number(); ++j) {
                in >> (m.data)[i][j];
            }
        }

        return in;
    }
