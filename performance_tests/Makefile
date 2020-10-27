bin/tests: tests/tests.o ../src/math/vector_math.o ../src/math/matrix_math.o ../src/matrix/matrix_class.o
	g++ tests/tests.o ../src/math/vector_math.o ../src/math/matrix_math.o ../src/matrix/matrix_class.o -o bin/tests

tests/tests.o: tests/tests.cpp
	g++ -c tests/tests.cpp -o tests/tests.o

../src/math/vector_math.o: ../src/math/vector_math.cpp ../src/math/vector_math.h
	g++ -c ../src/math/vector_math.cpp -o ../src/math/vector_math.o

../src/matrix/matrix_class.o: ../src/math/vector_math.o ../src/matrix/matrix_class.cpp ../src/matrix/matrix_class.h
	g++ -c ../src/matrix/matrix_class.cpp -o ../src/matrix/matrix_class.o

../src/math/matrix_math.o: ../src/math/vector_math.o ../src/matrix/matrix_class.o ../src/math/matrix_math.cpp ../src/math/matrix_math.h
	g++ -c ../src/math/matrix_math.cpp -o ../src/math/matrix_math.o


clean:
	rm tests/tests.o ../src/math/vector_math.o ../src/matrix/matrix_class.o ../src/math/matrix_math.o bin/tests
