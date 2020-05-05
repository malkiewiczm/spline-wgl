#/bin/sh

objects=''
for fname in ./src/*.cpp; do
	objects+=' './build/$(basename "$fname" .cpp).o
done
echo "
MAKEFLAGS += Rr
CXX := em++
CXXFLAGS := -Wall -Wextra -Wpedantic -Wshadow -std=c++14
OBJECTS := $objects

.PHONY: all clean

all: a.out.js

a.out.js: \$(OBJECTS)
	\$(CXX) \$(OBJECTS)

clean:
	rm -f ./build/*.o a.out.js

./build/%.o: ./src/%.cpp
	\$(CXX) \$(CXXFLAGS) \$< -c -o \$@
" > makefile
for fname in ./src/*.cpp; do
	g++ -MM "$fname" -MT ./build/$(basename "$fname" .cpp).o >> makefile
done
