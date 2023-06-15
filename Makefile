TESTNAME= test
TFILENAME = test.cc

SFILENAME = matrix_oop.cc
OFILENAME = matrix_oop.o
LIBNAME = matrix_oop.a

ifeq ($(shell uname), Linux)
	OPEN= xdg-open 
	LIBS= -lgtest -lpthread -pthread -lrt -lsubunit 
	LEAKS= CK_FORK=no valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(TESTNAME)
	CC = g++ -std=c++17 -lstdc++
else
	CC = gcc -std=c++17 -lstdc++ 
	OPEN= open
	LIBS= -lcheck -lgtest -pthread  
	LEAKS= leaks --atExit -- ./$(TESTNAME) 
endif
all: $(LIBNAME) test leaks linter
$(OFILENAME): $(SFILENAME)
	gcc -o $(OFILENAME) $(SFILENAME) -c
$(LIBNAME): $(OFILENAME)
	ar rc $(LIBNAME) $(OFILENAME)
test: $(LIBNAME)
	$(CC) $(TFILENAME) $(LIBNAME) -o $(TESTNAME) $(LIBS)
	./$(TESTNAME)
leaks: $(TESTNAME)
	$(LEAKS)
linter:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cc
	clang-format -n *.h
	rm .clang-format
clean:
	rm -f $(TESTNAME)
	rm -f *.out
	rm -f *.o
	rm -f *.a
