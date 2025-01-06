CC = gcc
STDFLAGS =
GCOV_FLAGS=-fprofile-arcs -ftest-coverage 
LINUX_FLAGS=-lsubunit -lrt -lpthread -lm
TESTFLAGS = -lcheck -lm -lpthread -o

SRC=$(wildcard back/*.c)
OBJ=$(patsubst back/%.c,%.o, ${SRC})


OS := $(shell uname -s)

ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

TEST_SRC=$(wildcard ./tests//*.c)
LIBS=-lcheck

all : clean uninstall s21_affin_parser.a install

s21_affin_parser.a: ${SRC} 
	$(CC) -c $(STDFLAGS) $(SRC)
	ar rc $@ $(OBJ)
	ranlib $@
	cp $@ lib$@
	make clean_obj

install: uninstall
	mkdir build
	cd 3dviv_qt_window && qmake && make && make clean && rm Makefile && cd ../ && mv 3dviv_qt_window/3dviv_qt_window.app build

uninstall:
	rm -rf build

dvi:
	open README.md

run:
	cd build && open 3dviv_qt_window.app

test: clean s21_affin_parser.a
ifeq ($(OS), Darwin)
	$(CC) $(STDFLAGS) tests/tests.c ${SRC}  -o test $(LIBS) -lm
else
	$(CC) $(STDFLAGS) tests/tests.c ${SRC} -o test $(LIBS) $(LINUX_FLAGS)
endif
	./test

gcov_report: s21_affin_parser.a clean_test 
ifeq ($(OS), Darwin)
	$(CC) $(STDFLAGS)  $(GCOV_FLAGS) tests/tests.c ${SRC}  -o test $(LIBS) -lm
else
	$(CC) $(STDFLAGS) $(GCOV_FLAGS) tests/tests.c ${SRC} -o test $(LIBS) $(LINUX_FLAGS)
endif
	./test
	lcov -t "stest" -o s21_test.info --no-external --filter range -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

dist:
	mkdir C8_3DViewer_v1.0/
	mkdir C8_3DViewer_v1.0/src
	cp -R 3dviv_qt_window back tests Makefile README.md C8_3DViewer_v1.0/src
	tar cvzf C8_3DViewer_v1.0.tgz C8_3DViewer_v1.0/
	rm -rf C8_3DViewer_v1.0


check : clean s21_affin_parser.a
	checkmk clean_mode=1 tests/checks/test* > tests/tests.c
	${CC} $(STDFLAGS) tests/tests.c s21_affin_parser.a -o unit_tests $(LIBS) -lm
	./unit_tests


clean_obj :
	rm -f *.o

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf *test
	rm -rf report
	rm -rf unit_tests

clean : clean_obj clean_test clean_tgz
	rm -f *.a
	rm -f check
	rm -f debug

clean_tgz:
	rm -f *.tgz

gen_clean :
	rm -rf tests/*.o