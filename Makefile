.SUFFIXES:
.SUFFIXES: .cpp

GCC = g++

.cpp:
	$(GCC) -Wall -Wunused -std=c++11 -O2 $< -o $@ `pkg-config --cflags --libs opencv4 cairo`


