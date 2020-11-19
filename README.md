# Singular value decomposition

The code runs in /src/svd/main.cpp. It reads dimensions and matrix itself from file /src/input/input.txt, makes decomposition and writes left and right singular vectors and eigenvalues into files "left_singular_vectors.txt", "right_singular_vectors.txt" and "singular_values.txt" in [/src/output/](/src/output/) accordingly.

To run the code move to [/src](/src) directory, compile the code
```sh
make
```
change [/src/input/input.txt](/src/input/input.txt) to the desired one and run main
```sh
. bin/svd
```

This is implementation of an algorithm described here: http://www.machinelearning.ru/wiki/index.php?title=Сингулярное_разложение_тензоров

Complexity is O(nm^2), where m is the smallest of matrix dimension.

File [matrix_class.h](/src/matrix/matrix_class.h) contains class of matrix with needed methods.

File [vector_math.h](/src/math/vector_math.h) contains all nessecary functions to work with vector of doubles.

File [matrix_math.h](/src/math/matrix_math.h) contains decomposition function and helper functions.
