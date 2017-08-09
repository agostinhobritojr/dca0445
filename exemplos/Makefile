.SUFFIXES:
.SUFFIXES: .c .cpp

CC = gcc
GCC = g++

.c:
	$(CC) -I$(INCDIR) $(CFLAGS) $< $(GL_LIBS) -o $@

.cpp:
	$(GCC) -std=c++11 -O2 `pkg-config --cflags opencv` $< -o $@ `pkg-config --libs opencv`


