# Сингулярное разложение матрицы

Выполняющий код находится в main.cpp. Он считывает размеры матрицы и саму матрицу из файла input.txt, выполняет разложение и записывает левые и правые сингулярные векторы и сингулярные значения в файлы "left_singular_vectors.txt", "right_singular_vectors.txt" и "singular_values.txt" соответственно.

Программа реализует алгоритм, описанный на странице: http://www.machinelearning.ru/wiki/index.php?title=Сингулярное_разложение_тензоров

Сложность алгоритма - O(nm^2), где m - меньший из размеров матрицы (n - больший).

В файл vector_math.h вынесены необходимые для алгоритма функции с объектами типа std::vector &lt double>.

В файле matrix_class.h находится описание класса матрицы, использующегося в реализации.

Наконец, в файле matrix_math.h находится сама функция декомпозиции и вспомогательные функции.
