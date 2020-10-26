#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h>
#include <string>
#include <utility>
#include <vector>

#include "../src/matrix/matrix_class.h"
#include "../src/math/vector_math.h"
#include "../src/math/matrix_math.h"


using namespace std;


double accuracy(const Matrix& input_matrix,
                // const vector<vector<double> >& input_matrix,
                const vector<vector<double> >& left_singular_vectors,
                const vector<vector<double> >& right_singular_vectors,
                const vector<double>& singular_values) {
    double result = 0;
    Matrix output_matrix(input_matrix.get_rows_number(), input_matrix.get_columns_number());
    vector<vector<double> > transposed_left_singular_vectors;
    vector<vector<double> > copy_right_singular_vectors = right_singular_vectors;
    
    transposed_left_singular_vectors = left_singular_vectors;
    transpose(transposed_left_singular_vectors);

    for (size_t i = 0; i < copy_right_singular_vectors.size(); ++i) {
        for (double& e : copy_right_singular_vectors[i]) {
            e = e * singular_values[i];
        }
    }

    transpose(copy_right_singular_vectors);
    
    for (size_t i = 0; i < transposed_left_singular_vectors.size(); ++i) {
        for (size_t j = 0; j < copy_right_singular_vectors.size(); ++j) {
            output_matrix[i][j] = scalar_composition(transposed_left_singular_vectors[i],
                                                     copy_right_singular_vectors[j]);
        }
    }

    for (size_t i = 0; i < input_matrix.get_rows_number(); ++i) {
        for (size_t j = 0; j < input_matrix.get_columns_number(); ++j) {
            result += (input_matrix[i][j] - output_matrix[i][j]) *
                (input_matrix[i][j] - output_matrix[i][j]);
        }
    }

    return result;
}

int main() {

    const int repeat = 10;
    const int min_dim = 10;
    const int max_dim = 640;
    const int dim_step = 10;

    unsigned int clock_start, clock_end;

    ofstream test_results;
    test_results.open("test_results.txt", ios::out);
    test_results.write("", 0);

    for (int k = min_dim; k <= max_dim; k += dim_step) {
        double average_error = 0, average_time = 0;

        for (int j = 0; j < repeat; ++j) {

            // start of creating random matrix
            ofstream output_file;
            output_file.open("input.txt", ios::out);
            output_file.write("", 0);
            output_file << k << " " << k << "\n";

            srand(time(0));
            for (int i = 1; i <= k; ++i) {
                for (int j = 1; j <= k; ++j) {
                    output_file << static_cast<double>(rand()) / 1000 << " ";
                }
                output_file << "\n";
            }
            
            output_file.close();
            // end of creating random matrix

            // start of reading created matrix
            int rows_number, columns_number;
            std::ifstream input_file;

            input_file.open("input.txt");
            input_file >> rows_number >> columns_number;

            Matrix mtrx(rows_number, columns_number);
            input_file >> mtrx;

            input_file.close();
            // end of reading

            clock_start = clock();

            std::vector<std::vector<double> > left_singular_vectors, right_singular_vectors;
            std::vector<double> singular_values;

            svd(mtrx, left_singular_vectors, right_singular_vectors, singular_values);

            clock_end = clock();

            average_error += accuracy(mtrx, left_singular_vectors,
                                      right_singular_vectors, singular_values);
            average_time += static_cast<double>(clock_end - clock_start) / CLOCKS_PER_SEC;
        }

        average_error = average_error / repeat;
        average_time = average_time / repeat;

        test_results << k << " " << average_error << " " << average_time << "\n";
        cout << k << " average error: " << average_error << ", average time: " << average_time << "\n";
    }

    test_results.close();
    
    return 0;
}
