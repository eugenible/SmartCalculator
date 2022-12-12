TEST=test.out
VIEW_DIR=viewModel/Calculator/
SOURCE_FILES=calcModel/*.cpp
BD=./build/
BUILT_APP_PATH=
OS=$(shell uname)
ARCHIVE=calculator-2.00

ifeq ($(OS), Darwin)
	BUILT_APP_PATH=$(VIEW_DIR)Calculator.app/Contents/MacOS/Calculator
else 
ifeq ($(OS), Linux)
	BUILT_APP_PATH=$(VIEW_DIR)Calculator
endif
endif


.PHONY: tests all build clean_build install clean $(TEST)

all: install

install: build clean_build
	clear && echo "Calculator was installed in build directory"

uninstall:
	rm -Rf $(BD)

build:
	cd $(VIEW_DIR) && qmake Calculator.pro && make
	mkdir $(BD)
	cp $(BUILT_APP_PATH) $(BD)
	
check:
	cp ../materials/linters/.clang-format .
	clang-format -n calcModel/*.cpp calcModel/*.h
	cppcheck --enable=all --suppress=unusedFunction --suppress=missingInclude --suppress=unreadVariable --language=c++ --std=c++17 calcModel/*.cpp calcModel/*.h

	clang-format -n controller/*.cpp controller/*.h
	cppcheck --enable=all --suppress=unusedFunction --suppress=missingInclude --suppress=unreadVariable --language=c++ --std=c++17 controller/*.cpp controller/*.h

	clang-format -n $(VIEW_DIR)main.cpp $(VIEW_DIR)mainwindow.cpp $(VIEW_DIR)mainwindow.h \
	$(VIEW_DIR)plotter.cpp $(VIEW_DIR)plotter.h $(VIEW_DIR)credit.h $(VIEW_DIR)credit.cpp
	cppcheck --enable=all --suppress=unusedFunction --suppress=missingInclude --suppress=unreadVariable --language=c++ --std=c++17 $(VIEW_DIR)main.cpp $(VIEW_DIR)mainwindow.cpp \
	$(VIEW_DIR)mainwindow.h $(VIEW_DIR)plotter.cpp $(VIEW_DIR)plotter.h $(VIEW_DIR)credit.h $(VIEW_DIR)credit.cpp
	rm -f .clang-format

$(TEST):
	g++ test.cpp $(SOURCE_FILES) -o $(TEST) -lgtest -lgtest_main -lpthread

tests: $(TEST)
	./$(TEST)

gcov_report: $(TEST)
	g++ --coverage test.cpp $(SOURCE_FILES) -o $(TEST) -lgtest -lpthread
	./$(TEST)
	lcov -t $(TEST) --no-external -o test.info -c -d ./
	genhtml -o report test.info
	open report/index.html

clean: clean_build
	rm -f *.out *.o *.a $(TEST) *.gcda *.gcno *.info *.txt
	rm -Rf report
	rm -Rf $(BD) 
	rm -f $(ARCHIVE).tar.gz

clean_build:
	cd $(VIEW_DIR) && make clean && rm -Rf Calculator.app/ && rm -f .qmake.stash

dist:
	rm -rf $(ARCHIVE) && mkdir $(ARCHIVE)
	cp -r calcModel controller viewModel test.cpp $(ARCHIVE)
	tar -czvf $(ARCHIVE).tar.gz $(ARCHIVE)
	rm -rf $(ARCHIVE)
