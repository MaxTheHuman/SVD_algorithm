#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h>
#include <string>
#include <utility>
#include <vector>

// #include "../math/vector_math.h"
#include "../matrix/matrix_class.h"
#include "../math/matrix_math.h"


template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {

    for (const T& elem : v) {
        out << elem << " ";
    }
    out << "\n";

    return out;
}

/*
void print_vectors(std::ostream& out, const std::vector<vector<double> >& m) {

    for (const std::vector<double>& v : m) {
        out << v;
    }
}
*/

template <typename T>
void export_data(std::string file_name, const T& data) {
    std::ofstream output;

    output.open(file_name, std::ios::out);
    output.write("", 0);
    output << data;

    output.close();
}

int main()
{

    int rows_number, columns_number;
    std::ifstream input_file;

    input_file.open("../input/input.txt");
    input_file >> rows_number >> columns_number;

    Matrix mtrx(rows_number, columns_number);
    input_file >> mtrx;

    input_file.close();


    std::vector<std::vector<double> > left_singular_vectors, right_singular_vectors;
    std::vector<double> singular_values;

    svd(mtrx, left_singular_vectors, right_singular_vectors, singular_values);

/*
    cout << "left singular vectors:\n";
    print_matrix(left_singular_vectors);

    cout << "right singular vectors:\n";
    print_matrix(right_singular_vectors);
*/

    export_data("../output/right_singular_vectors.txt", right_singular_vectors);
    export_data("../output/left_singular_vectors.txt", left_singular_vectors);
    export_data("../output/singular_values.txt", singular_values);

    return 0;
}
