# compilar el main con g++
main: main.cpp
	g++ -Wall -Wpedantic -O3 -std=c++26 -o main main.cpp
