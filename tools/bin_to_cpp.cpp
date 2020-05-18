#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>

static void _die(const char *msg, const char *file, int line);
#define die(msg) _die(msg, __FILE__, __LINE__)
#define TRACE (std::cout << '[' << __FILE__ << ':' << __LINE__ << "] ")
#define trace(what)(TRACE << #what " = " << (what) << std::endl)

static void _die(const char *msg, const char *file, int line)
{
	printf("error: %s (%s:%d)\n", msg, file, line);
	abort();
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		std::cout << "usage: filename.bin filename.cpp" << std::endl;
		return 0;
	}
	std::ifstream ifile(argv[1], std::ios::binary);
	if (! ifile.good()) {
		trace(argv[1]);
		die("cannot open file for reading");
	}
	std::ofstream ofile(argv[2]);
	if (! ofile.good()) {
		trace(argv[2]);
		die("cannot create file for writing");
	}
	ofile << "const unsigned char data[] { ";
	int byte;
	const char *const hex = "0123456789ABCDEF";
	while ((byte = ifile.get()) != EOF) {
		ofile << "0x" << hex[byte >> 4] << hex[byte & 0xF] << ", ";
	}
	ofile << "};";
}
