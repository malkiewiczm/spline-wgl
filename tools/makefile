.PHONY: all clean

MAKEFLAGS += Rr
PROGRAMS := obj_to_bin.exe
CXX := g++
CXXFLAGS := -Wall -Wextra -Wpedantic -Wshadow


all: $(PROGRAMS)

clean:
	rm -f $(PROGRAMS)

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
