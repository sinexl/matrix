CXXFLAGS = -std=c++23 -ggdb -Wall -Wextra -Wswitch-enum
main: example.cpp
	g++ $(CXXFLAGS) example.cpp -o main
