UNAME_S := $(shell uname -s)

CC = gcc
FLAGS = -Wall -Werror -Wextra
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
ifeq ($(UNAME_S),Darwin)
	TST_LIBS := -I/opt/homebrew/opt/check/include -L/opt/homebrew/opt/check/lib -lcheck 
	TST_FLAG := -I/opt/homebrew/opt/check/include 
else
	TST_LIBS = $(shell pkg-config --libs check) 
	TST_FLAG = 
endif

DIR_FUNC_C = $(wildcard ./)
DIR_TEST_C = $(wildcard $(shell find ./tests -type d))

DIR_FUNC_OBJ = obj_func
DIR_FUNC_GCOV_OBJ = obj_func_gcov
DIR_TEST_OBJ = obj_test

FILES_FUNC_C := $(foreach dir, $(DIR_FUNC_C), $(wildcard $(dir)/*.c))
FILES_FUNC_H := $(foreach dir, $(DIR_FUNC_C), $(wildcard $(dir)/*.h))

FILES_TEST_C := $(foreach dir, $(DIR_TEST_C), $(wildcard $(dir)/*.c))
FILES_TEST_H := $(foreach dir, $(DIR_TEST_C), $(wildcard $(dir)/*.h))

FILES_FUNC_OBJ := $(patsubst %.c, $(DIR_FUNC_OBJ)/%.o, $(FILES_FUNC_C))   
FILES_FUNC_GCOV_OBJ := $(patsubst %.c, $(DIR_FUNC_GCOV_OBJ)/%.o, $(FILES_FUNC_C))
FILES_TEST_OBJ := $(patsubst %.c, $(DIR_TEST_OBJ)/%.o, $(FILES_TEST_C))

all: install gcov_report dvi

TARGET = Calculator_v1.0

install:
	echo "Установка $(TARGET).app:"
	mkdir -p ../build && cd ./QT && qmake && make && make clean && rm -rf Makefile && mv SmartCalc.app ../../build/SmartCalc.app
	echo "Установка прошла успешно, файл для запуска находятся в ../build/ folder!"


uninstall:
	rm -rf ../build
	echo "Успешно удалено!"
	
dist: install
	mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist
	@cp -R . ../dist/src
	@cd ../dist && tar cvzf $(TARGET).tgz *
	@cd ../dist && rm -rf $(TARGET).app
	@rm -rf ../dist/src
	echo "Архив успешно создан!"

dvi:
	doxygen dvi_config.txt

test_run : test
	./s21_test

test : makedirs $(FILES_FUNC_OBJ) $(FILES_TEST_OBJ)
	$(CC) $(FILES_FUNC_OBJ) $(FILES_TEST_OBJ) -o s21_test $(TST_LIBS) -lm

$(DIR_FUNC_OBJ)/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(DIR_TEST_OBJ)/%.o: %.c
	$(CC) $(FLAGS)  -c $< -o $@  $(TST_FLAG) 


gcov_report: makedirs $(FILES_TEST_OBJ) $(FILES_FUNC_GCOV_OBJ)
	$(CC) $(GCOV_FLAGS) $(FILES_TEST_OBJ) $(FILES_FUNC_GCOV_OBJ) -o s21_gcov_test $(TST_LIBS) -lm
	-./s21_gcov_test
	gcovr --html --html-details -o ./report/index.html
	-rm $(DIR_FUNC_GCOV_OBJ)/*gcda $(DIR_FUNC_GCOV_OBJ)/*gcno

$(DIR_FUNC_GCOV_OBJ)/%.o: %.c
	$(CC) $(FLAGS) $(GCOV_FLAGS) -c $< -o $@

makedirs:
	mkdir -p report
	mkdir -p $(foreach dir, $(DIR_FUNC_C), $(DIR_FUNC_OBJ)/$(dir))
	mkdir -p $(foreach dir, $(DIR_FUNC_C), $(DIR_FUNC_GCOV_OBJ)/$(dir))
	mkdir -p $(foreach dir, $(DIR_TEST_C), $(DIR_TEST_OBJ)/$(dir))

clang:
	clang-format -n *.h $(FILES_FUNC_C) $(FILES_FUNC_H) $(FILES_TEST_C) $(FILES_TEST_H) ./QT/*.cpp ./QT/*.h

clang_fix:
	clang-format -i *.h $(FILES_FUNC_C) $(FILES_FUNC_H) $(FILES_TEST_C) $(FILES_TEST_H) ./QT/*.cpp ./QT/*.h


clean: uninstall
	-rm s21_test s21_gcov_test *.a *.gcda *.gcno
	-rm -r obj_func obj_test obj_func_gcov report
	-rm test-* $(DIR_FUNC_GCOV_OBJ)/*.o
	-rm valgrind_grep.log
	-rm valgrind.log
	-rm -r html
	-rm -r ../dist
	-rm  ./QT/.qmake.stash

valgrind: test
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./s21_test 2>valgrind.log
	date +'%T' > valgrind_grep.log
	grep -e "ERROR SUMMARY" -e "jump" valgrind.log >> valgrind_grep.log
