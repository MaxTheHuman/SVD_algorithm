bin/svd: svd/main.o math/vector_math.o math/matrix_math.o matrix/matrix_class.o
	g++ svd/main.o math/vector_math.o math/matrix_math.o matrix/matrix_class.o -o bin/svd

svd/main.o: svd/main.cpp
	g++ -c svd/main.cpp -o svd/main.o

math/vector_math.o: math/vector_math.cpp math/vector_math.h
	g++ -c math/vector_math.cpp -o math/vector_math.o

matrix/matrix_class.o: math/vector_math.o matrix/matrix_class.cpp matrix/matrix_class.h
	g++ -c matrix/matrix_class.cpp -o matrix/matrix_class.o

math/matrix_math.o: math/vector_math.o matrix/matrix_class.o math/matrix_math.cpp math/matrix_math.h
	g++ -c math/matrix_math.cpp -o math/matrix_math.o

clean:
	rm svd/main.o math/vector_math.o matrix/matrix_class.o math/matrix_math.o bin/svd