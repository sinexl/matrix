CXXFLAGS = -std=c++23 -Wall -Wextra -Wswitch-enum
main: Matrix.cpp
	g++ $(CXXFLAGS) Matrix.cpp -o main
