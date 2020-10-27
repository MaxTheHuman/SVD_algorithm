#pragma once

#include <vector>

#include "vector_math.h"
#include "../matrix/matrix_class.h"

void compute_b(const std::vector<double>& a, std::vector<double>& b,
               Matrix& mtrx);

void compute_a(std::vector<double>& a, const std::vector<double>& b,
               Matrix& mtrx);


// function below computes unnormalized singular vectors
void compute_singular_vectors(std::vector<std::vector<double> >& left_singular_vectors,
                              std::vector<std::vector<double> >& right_singular_vectors,
                              Matrix& mtrx);

// function below computes singular values and normalizes singular vectors
void compute_singular_values(std::vector<std::vector<double> >& left_singular_vectors,
                             std::vector<std::vector<double> >& right_singular_vectors,
                             std::vector<double>& singular_values,
                             int n, int m);

void svd(Matrix mtrx, std::vector<std::vector<double> >& left_singular_vectors,
         std::vector<std::vector<double> >& right_singular_vectors,
         std::vector<double>& singular_values);
