# compilar el main con g++
main: main.cpp
	g++ -Wall -Wpedantic -O3 -std=c++26 -o main main.cpp

# if println causes weird errors/warnings -- for Windows/MSYS2/MinGW users
# main: main.cpp
#	g++ -Wall -Wpedantic -O3 -std=c++26 -o main main.cpp -lstdc++exp
