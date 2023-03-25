CC = g++
FLAGS = -Wall -Werror -Wextra -std=c++17
TEST_FLAGS = -lgtest -lgmock -pthread

#	=== Выполнить все ===
all: gcov_report

#	=== Компиляция библиотеки ===
s21_matrix_oop.a: clean
	$(CC) -c $(FLAGS) s21_*.cc
	ar rc s21_matrix_oop.a s21_*.o

#	=== Запуск unit-тестов ===
test: s21_matrix_oop.a
	@echo --------------------- START ---------------------
	$(CC) $(FLAGS) unit_tests.cc s21_matrix_oop.a -o unit_tests $(TEST_FLAGS)
	./unit_tests
	@echo -------------------- SUCCESS --------------------

#	=== Проверка на утечки памяти ===
leaks: test
	leaks -atExit -- ./unit_tests
	@echo ---------------------- END ----------------------

#	== УСТАНОВКА LCOV ==
lcov:
	cd && brew install lcov

#	== СОЗДАНИЕ GCOV ОТЧЕТА ==
#	Для корректной работы нужно установить lcov: make lcov
gcov_report: leaks
#	$(CC) $(FLAGS) --coverage unit_tests.cc s21_*.cc s21_matrix_oop.a $(TEST_FLAGS) -o gcov_test
#	./gcov_test
#	lcov -t "matrix" -o matrix.info -c -d .
#	genhtml -o report matrix.info
#	open ./report/index.html

	$(CC) $(FLAGS) --coverage unit_tests.cc s21_*.cc s21_matrix_oop.a $(TEST_FLAGS) -o gcov_test
	./gcov_test
	lcov -t "matrix" -o matrix.info -c -d .
	genhtml -o report matrix.info
	open ./report/index.html

	@echo ------------------ OPEN REPORT ------------------

#	=== Очистка ===
clean:
	@echo --------------------- CLEAN ---------------------
	rm -rf *.o *.a *.gcno *.gcda report *.info s21_matrix_oop unit_tests gcov_test
	@echo -------------------- SUCCESS --------------------
