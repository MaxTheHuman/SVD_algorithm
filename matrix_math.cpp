#include "matrix_math.h"


void compute_b(const std::vector<double>& a, std::vector<double>& b,
               Matrix& mtrx) {

    double scalar, length;

    for (int i = 0; i < mtrx.get_columns_number(); ++i) {
        scalar = 0;
        length = 0;
        for (int k = 0; k < mtrx.get_rows_number(); ++k) {

            scalar += mtrx[k][i] * a[k];
            length += a[k] * a[k];
        }

        b[i] = scalar / length;
    }
}

void compute_a(std::vector<double>& a, const std::vector<double>& b,
               Matrix& mtrx) {

    double scalar, length;

    for (int i = 0; i < mtrx.get_rows_number(); ++i) {
        scalar = 0;
        length = 0;
        for (int k = 0; k < mtrx.get_columns_number(); ++k) {

            scalar += mtrx[i][k] * b[k];
            length += b[k] * b[k];
        }

        a[i] = scalar / length;
    }
}


// function below computes unnormalized singular vectors
void compute_singular_vectors(std::vector<std::vector<double> >& left_singular_vectors,
                              std::vector<std::vector<double> >& right_singular_vectors,
                              Matrix& mtrx) {

    // int n = mtrx.get_rows_number(), m = mtrx.get_columns_number();

    for (int l = 0; l < mtrx.get_rows_number(); ++l) {

        std::vector<double> a(mtrx.get_rows_number(), 0), b(mtrx.get_columns_number(), 0);
        fill_random_vector(a);
        normalize_vector(a);

        double distance_before = 1, distance_after = 0.1;

        while ((distance_before - distance_after) / distance_after > 0.0001) {

            compute_b(a, b, mtrx);
            distance_before = mtrx.distance_to_aXb(a, b);

            compute_a(a, b, mtrx);
            distance_after = mtrx.distance_to_aXb(a, b);
        }

        left_singular_vectors.push_back(a);
        right_singular_vectors.push_back(b);

        mtrx.substract_aXb(a, b);
    }
}

// function below computes singular values and normalizes singular vectors
void compute_singular_values(std::vector<std::vector<double> >& left_singular_vectors,
                             std::vector<std::vector<double> >& right_singular_vectors,
                             std::vector<double>& singular_values,
                             int n, int m) {

    std::vector<double> a, b;
    double new_value, a_length, b_length;

    for (int i = 0; i < n; ++i) {

        a = left_singular_vectors[i];
        b = right_singular_vectors[i];

        a_length = sqrt(scalar_composition(a, a));
        b_length = sqrt(scalar_composition(b, b));

        new_value = a_length * b_length;

        for (int k = 0; k < n; ++k) {
            left_singular_vectors[i][k] = left_singular_vectors[i][k] / a_length;
        }
        for (int k = 0; k < m; ++k) {
            right_singular_vectors[i][k] = right_singular_vectors[i][k] / b_length;
        }

        singular_values.push_back(new_value);
    }
}

void svd(Matrix mtrx, std::vector<std::vector<double> >& left_singular_vectors,
         std::vector<std::vector<double> >& right_singular_vectors,
         std::vector<double>& singular_values) {

    bool is_transposed = 0;

    if (mtrx.get_rows_number() > mtrx.get_columns_number()) {
        mtrx.transpose();  // now n <= m (matrix is n*m)
        is_transposed = 1;
    }

    compute_singular_vectors(left_singular_vectors, right_singular_vectors, mtrx);

    compute_singular_values(left_singular_vectors, right_singular_vectors,
                            singular_values,
                            mtrx.get_rows_number(), mtrx.get_columns_number());

    if (is_transposed) {
        std::swap(right_singular_vectors, left_singular_vectors);
    }
}
