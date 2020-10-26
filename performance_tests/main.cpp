#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;


void get_input_matrix(istream& input_file,
                      vector<vector<double> >& input_matrix, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            input_file >> input_matrix[i][j];
        }
    }
}

void print_vector(const vector<double>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

void print_matrix(const vector<vector<double> >& m) {
    cout << "-------------\n";
    int x = m.size();
    int y = m[0].size();
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "-------------\n";
}

double distance(const vector<double>& a, const vector<double>& b,
                const vector<vector<double> >& input_matrix) {
    double result = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < b.size(); ++j) {
            result += (a[i] * b[j] - input_matrix[i][j]) *
            (a[i] * b[j] - input_matrix[i][j]);
        }
    }
    return result;
}

double frobenius_norm(const vector<vector<double> >& m) {
    double result = 0;
    for (const vector<double>& v : m) {
        for (const double& element: v) {
            result += element * element;
        }
    }
    return sqrt(result);
}

double scalar_composition(const vector<double>& a, const vector<double>& b) {
    double result = 0;
    for (size_t i = 0; i  < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

void transpose(vector<vector<double> >& m) {
    vector<vector<double> > result(m[0].size(), vector<double>(m.size(), 0));
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m[0].size(); ++j) {
            result[j][i] = m[i][j];
        }
    }
    m = result;
}

void svd(int n, int m, const vector<vector<double> >& input_matrix_const,
         vector<vector<double> >& left_singular_vectors,
         vector<vector<double> >& right_singular_vectors,
         vector<double>& singular_values) {
    srand(time(0));
    vector<vector<double> > input_matrix = input_matrix_const;
    bool is_transposed = 0;
    if (n > m) {
        int m_copy;
        m_copy = m;
        m = n;
        n = m_copy;
        transpose(input_matrix);  /// now n < m (matrix is n*m)
        is_transposed = 1;
    }

    for (int l = 0; l < n; ++l) {
        vector<double> random_vector(n, 0.0);
        for (int i = 0; i < n; ++i) {
            random_vector[i] = rand() / 1000;
        }

        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += random_vector[i] * random_vector[i];
        }
        for (int i = 0; i < n; ++i) {
            random_vector[i] = random_vector[i] / sqrt(sum);
        }

        vector<double> a, b(m, 1);
        a = random_vector;
        double distance_before = 1, distance_after = 0.1;
        double scalar = 0, length = 0;
        // int counter = 0;
        while ((distance_before - distance_after) / distance_after > 0.0001) {
            // counter++;
            for (int i = 0; i < m; ++i) {
                scalar = 0;
                length = 0;
                for (int k = 0; k < n; ++k) {
                    scalar += input_matrix[k][i] * a[k];
                    length += a[k] * a[k];
                }
                b[i] = scalar / length;
            }
            distance_before = distance(a, b, input_matrix);
            for (int i = 0; i < n; ++i) {
                scalar = 0;
                length = 0;
                for (int k = 0; k < m; ++k) {
                    scalar += input_matrix[i][k] * b[k];
                    length += b[k] * b[k];
                }
                a[i] = scalar / length;
            }
            distance_after = distance(a, b, input_matrix);
        }
        // cout << counter << "\n";

        left_singular_vectors.push_back(a);
        right_singular_vectors.push_back(b);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                input_matrix[i][j] -= a[i] * b[j];
            }
        }
    }
    vector<double> a, b;
    double new_value, a_length, b_length;
    for (int i = 0; i < n; ++i) {
        a = left_singular_vectors[i];
        b = right_singular_vectors[i];
        a_length = 0;
        b_length = 0;
        for (int p = 0; p < n; ++p) {
            a_length += a[p] * a[p];
        }
        for (int u = 0; u < m; ++u) {
            b_length += b[u] * b[u];
        }
        a_length = sqrt(a_length);
        b_length = sqrt(b_length);
        new_value = a_length * b_length;
        for (int k = 0; k < n; ++k) {
            left_singular_vectors[i][k] = left_singular_vectors[i][k] / a_length;
        }
        for (int k = 0; k < m; ++k) {
            right_singular_vectors[i][k] = right_singular_vectors[i][k] / b_length;
        }
        singular_values.push_back(new_value);
    }
    if (is_transposed) {
        int n_copy;
        n_copy = n;
        n = m;
        m = n_copy;
        vector<vector<double> > vector_helper;
        vector_helper = right_singular_vectors;
        right_singular_vectors = left_singular_vectors;
        left_singular_vectors = vector_helper;
    }
}

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

int main()
{
    unsigned int cl_start, cl_end;  /// for counting time

    const int min_dim = 10;
    const int max_dim = 10;
    ofstream test_results;
    test_results.open("sq_t.txt", ios::out);
    test_results.write("", 0);
    for (int k = min_dim; k <= max_dim; k += 10) {
        double average_error = 0, average_time = 0;
        int repeat = 1;
        for (int j = 0; j < repeat; ++j) {
            /// start of creating random matrix
            ofstream output_file;
            output_file.open("input.txt",
                     ios::out);
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
            /// end of creating random matrix

            /// start of reading created matrix
            int rows_number, columns_number;
            ifstream input_file;
            input_file.open("input.txt");
            input_file >> rows_number >> columns_number;
            vector<vector<double> > input_matrix(rows_number,
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
            cout << "singular values:\n";
            print_vector(singular_values);
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
