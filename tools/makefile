.PHONY: all clean

MAKEFLAGS += Rr
PROGRAMS := obj_to_bin.exe bin_to_cpp.exe
CXX := g++
CXXFLAGS := -Wall -Wextra -Wpedantic -Wshadow


all: $(PROGRAMS)

clean:
	rm -f $(PROGRAMS)

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
