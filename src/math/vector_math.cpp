#include <cmath>
#include <cstdlib>
#include <time.h>
#include <vector>

#include "vector_math.h"


void normalize_vector(std::vector<double>& v) {
    int sum = 0;

    for (const double& elem : v) {
        sum += elem * elem;
    }
    for (double& elem : v) {
        elem /= sqrt(sum);
    }
}

void fill_random_vector(std::vector<double>& v) {
    srand(time(0));

    for (double& elem : v) {
        elem = rand() % 1000;
    }
}

double scalar_composition(const std::vector<double>& a,
                          const std::vector<double>& b) {
    double result = 0;

    for (size_t i = 0; i  < a.size(); ++i) {
        result += a[i] * b[i];
    }

    return result;
}

void transpose(std::vector<std::vector<double> >& m) {
    std::vector<std::vector<double> > result(m[0].size(), std::vector<double>(m.size(), 0));

    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m[0].size(); ++j) {
            result[j][i] = m[i][j];
        }
    }

    m = result;
}