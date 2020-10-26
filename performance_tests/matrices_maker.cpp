#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
/*
    cout << "left singular vectors:\n";
    for (vector<double>& v : left_singular_vectors) {
        print_vector(v);
    }

    cout << "right singular vectors:\n";
    for (vector<double>& v : right_singular_vectors) {
        print_vector(v);
    }

    cout << "singular values:\n";
    print_vector(singular_values);
    cout << frobenius_norm(input_matrix) << " <- left\n";
*/
}
    ofstream output_file;
    output_file.open("C:\\Users\\Max\\programming\\C++\\simple SVD\\input.txt",
                     ios::out);
    output_file.write("", 0);
    output_file << "42 64\n";
    srand(time(0));
    for (int i = 1; i <= 42; ++i) {
        for (int j = 1; j <= 64; ++j) {
            output_file << rand() % 1000 << " ";
        }
        output_file << "\n";
    }
    output_file.close();
    return 0;
}
