#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include <vector>
#include <array>
#include <iostream>

void _die(const char *msg, const char *file, int line);
#define die(msg) _die(msg, __FILE__, __LINE__)
#define TRACE (std::cout << '[' << __FILE__ << ':' << __LINE__ << "] ")
#define trace(what)(TRACE << #what " = " << (what) << std::endl)

#define UNUSED(what) ((void)(what))

#define TORAD(a) (0.0174532f * (a))
#define TODEG(a) (57.295779f * (a))

#define LAZY_SET(type, name) void name(type l_ ## name) { m_ ## name = l_ ## name; }
#define LAZY_SETR(type, name) void name(const type &l_ ## name) { m_ ## name = l_ ## name; }
#define LAZY_GET(type, name) type name() const { return m_ ## name; }
#define LAZY_GETR(type, name) const type &name() const { return m_ ## name; }
#define LAZY_ACCESSOR(type, name) LAZY_GET(type, name) LAZY_SET(type, name)
#define LAZY_ACCESSORR(type, name) LAZY_GETR(type, name) LAZY_SETR(type, name)

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

static inline std::ostream &operator<< (std::ostream &o, const glm::vec2 &v)
{
	o << "{ " << v.x << ", " << v.y << " }";
	return o;
}

static inline std::ostream &operator<< (std::ostream &o, const glm::vec3 &v)
{
	o << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
	return o;
}

namespace g {
	extern int canvas_width;
	extern int canvas_height;
	extern bool is_edit_mode;
}
