# gcc -fprofile-arcs -ftest-coverage -o tst ./tests/*.c *.c -lcheck -I/usr/local/include
# ./tst
# gcov *.c

#brew install gcovr

CC = gcc
FLAGS = -Wall -Werror -Wextra
TST_LIBS =  -I/opt/homebrew/opt/check/include

FUNC_DIR = .
TEST_DIR = ./tests

OBJ_FUNC_DIR = obj_func
OBJ_TEST_DIR = obj_test

FUNC_FILES := $(wildcard $(FUNC_DIR)/s21_*.c)
TEST_FILES := $(wildcard $(TEST_DIR)/*.c)

OBJ_FILES_FUNC := $(patsubst $(FUNC_DIR)/%.c, $(OBJ_FUNC_DIR)/%.o, $(FUNC_FILES))
OBJ_FILES_TEST := $(patsubst $(TEST_DIR)/%.c, $(OBJ_TEST_DIR)/%.o, $(TEST_FILES))

all: s21_string.a test gcov_report
	

test : $(OBJ_FILES_FUNC) $(OBJ_FILES_TEST)
	$(CC) $^ -o s21_test $(TST_LIBS)

$(OBJ_FUNC_DIR)/%.o: $(FUNC_DIR)/%.c
	@if [ ! -d $(OBJ_FUNC_DIR) ]; then \
    	mkdir -p $(OBJ_FUNC_DIR); \
	fi
	$(CC) -c $< -o $@

$(OBJ_TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@if [ ! -d $(OBJ_TEST_DIR) ]; then \
    	mkdir -p $(OBJ_TEST_DIR); \
	fi
	$(CC) -c $< -o $@  $(TST_LIBS)

runTest : test
	./s21_test

s21_string.a:
	$(CC) $(FLAGS) -c s21_*.c 
	ar rcs s21_string.a *.o 
	-rm *.o

gcov_report:
	$(CC) $(FLAGS) $(FUNC_FILES) $(TEST_FILES) -fprofile-arcs -ftest-coverage -o s21_gcov_test $(TST_LIBS)
	-./s21_gcov_test
	gcovr --html --html-details -o coverage_report.html
	-rm test-* *gcda *gcno

clean:
	-rm s21_test s21_gcov_test *.a
	-rm obj_func/*.o obj_test/*.o
	-rm test-* *gcda *gcno
	-rm coverage* *.gcov