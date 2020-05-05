#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <vector>
#include <array>
#include <iostream>

void _die(const char *msg, const char *file, int line);
#define die(msg) _die(msg, __FILE__, __LINE__)
#define TRACE (std::cout << '[' << __FILE__ << ':' << __LINE__ << "] ")
#define trace(what)(TRACE << #what " = " << (what) << std::endl)

#define UNUSED(what) ((void)(what))

#define torad(a) (0.0174532f * (a))
#define todeg(a) (57.295779f * (a))

template <typename T>
static inline std::ostream &operator<< (std::ostream &o, const std::vector<T> &v)
{
	o << "{ ";
	for (auto item : v) {
		o << item;
		o << "; ";
	}
	o << '}';
	return o;
}
