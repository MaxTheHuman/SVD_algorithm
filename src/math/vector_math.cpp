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
