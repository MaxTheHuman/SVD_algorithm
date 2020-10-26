#pragma once
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

#include "../math/vector_math.h"


class Matrix {
private:
    int n, m;
    std::vector<std::vector<double> > data;

public:

    Matrix(int rows_number, int columns_number);

    void transpose();

    double frobenius_norm() const;

    double distance_to_aXb(const std::vector<double>& a,
                           const std::vector<double>& b) const;

    void substract_aXb(const std::vector<double>& a, const std::vector<double>& b);

    friend std::istream& operator>>(std::istream& in, Matrix& m);

    const std::vector<double>& operator[](size_t i) const;

    int get_rows_number() const;

    int get_columns_number() const;

};
