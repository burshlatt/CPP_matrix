CC = g++
FLAGS = -Wall -Werror -Wextra -std=c++17
TEST_FLAGS = -lgtest -lgmock -pthread

#	=== Выполнить все ===
all: leaks

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

#	=== Очистка ===
clean:
	@echo --------------------- CLEAN ---------------------
	rm -rf *.o *.a s21_matrix_oop unit_tests
	@echo -------------------- SUCCESS --------------------
