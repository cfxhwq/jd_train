SRCS = $(wildcard *.cpp)

all: %.out

%.out: %.cpp

.cpp.out:
	g++  $< -o $*.out
