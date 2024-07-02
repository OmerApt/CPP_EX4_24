#!make -f

CXX=clang++
CXXFLAGS=-std=c++17 -g -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=99


all: clean demo maintree

run: demo
	./$^

tree: maintree
	./$^
# run-test: test
# 	./$^

demo: Demo.o
	$(CXX) $(CXXFLAGS) $^ -o demo

maintree:  Complex.o treeMain.o
	$(CXX) $(CXXFLAGS) $^ -o maintree

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

phony: run demo test run-test

clean:
	rm -f *.o demo test