CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Default target
all: Main

# Compile demo
Main: demo.cpp
	$(CXX) $(CXXFLAGS) demo.cpp -o main 

# Compile and run demo
main: Main
	./main

# Compile and run tests
test: test/test.cpp
	$(CXX) $(CXXFLAGS) test/test.cpp -o test_container
	./test_container

# Run valgrind on tests
valgrind: test/test.cpp
	$(CXX) $(CXXFLAGS) -g test/test.cpp -o test_container
	valgrind --leak-check=full ./test_container

# Cleanup
clean:
	rm -f main test_container