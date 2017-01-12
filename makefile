all: app

app: src/gravediggers.cpp
	mpiCC src/*/*.cpp src/gravediggers.cpp -Wall -std=c++11 -o bin/gravediggers
