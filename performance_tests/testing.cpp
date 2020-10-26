#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h>
#include <string>
#include <utility>
#include <vector>

#include "vector_math.h"
#include "matrix_class.h"
#include "matrix_math.h"

using namespace std;


double accuracy(const vector<vector<double> >& input_matrix,
                const vector<vector<double> >& left_singular_vectors,
                const vector<vector<double> >& right_singular_vectors,
                const vector<double>& singular_values) {
    double result = 0;
    vector<vector<double> > output_matrix(input_matrix.size(),
                                          vector<double>(input_matrix[0].size()));
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

    for (size_t i = 0; i < input_matrix.size(); ++i) {
        for (size_t j = 0; j < input_matrix[0].size(); ++j) {
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

    unsigned int cl_start, cl_end;  // for counting time

    ofstream test_results;
    test_results.open("TestResults.txt", ios::out);
    test_results.write("", 0);
    for (int k = 100; k <= 640; k += 10) {
        double average_error = 0, average_time = 0;
        for (int j = 0; j < repeat; ++j) {
            /// start of creating random matrix
            ofstream output_file;
            output_file.open("C:\\Users\\Max\\programming\\C++\\simple SVD\\input.txt",
                     ios::out);
            output_file.write("", 0);
            output_file << one_dim << " " << k << "\n";
            srand(time(0));
            for (int i = 1; i <= one_dim; ++i) {
                for (int j = 1; j <= k; ++j) {
                    output_file << static_cast<double>(rand()) / 1000 << " ";
                }
                output_file << "\n";
            }
            output_file.close();
            /// end of creating random matrix

            /// start of reading created matrix
            int rows_number, columns_number;
            ifstream input_file;
            input_file.open("input.txt");
            input_file >> rows_number >> columns_number;
            vector<vector<double> >
                input_matrix(rows_number,
                     vector<double>(columns_number, 0.0));
            get_input_matrix(input_file, input_matrix,
                     rows_number, columns_number);
            input_file.close();
            /// end of reading

            cl_start = clock();
            vector<vector<double> > left_singular_vectors, right_singular_vectors;
            vector<double> singular_values;
            svd(rows_number, columns_number, input_matrix,
                left_singular_vectors, right_singular_vectors, singular_values);
            cl_end = clock();
            average_error += accuracy(input_matrix, left_singular_vectors,
                    right_singular_vectors, singular_values);
            average_time += static_cast<double>(cl_end - cl_start) / CLOCKS_PER_SEC;
        }
        average_error = average_error / repeat;
        average_time = average_time / repeat;
        test_results << k << " " << average_error <<
                    " " << average_time
                    << "\n";
        cout << k << "\n";
    }
    test_results.close();
    return 0;
}
