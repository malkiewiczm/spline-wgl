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

#define SET_V(type, name) void name(type l_ ## name) { m_ ## name = l_ ## name; }
#define SET_R(type, name) void name(const type &l_ ## name) { m_ ## name = l_ ## name; }
#define GET_V(type, name) type name() const { return m_ ## name; }
#define GET_CR(type, name) const type &name() const { return m_ ## name; }
#define INTERNAL_GET_R(type, name)  type &name() { return m_ ## name; }
#define ACC_V(type, name) GET_V(type, name) SET_V(type, name)
#define ACC_R(type, name) GET_CR(type, name) INTERNAL_GET_R(type, name) SET_R(type, name)

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

static inline std::ostream &operator<< (std::ostream &o, const glm::quat &q)
{
	o << "{ " << q.w << "; " << q.x << ", " << q.y << ", " << q.z << " }";
	return o;
}

namespace g {
	extern int canvas_width;
	extern int canvas_height;
	extern bool is_edit_mode;
	static inline float aspectx() {
		return static_cast<float>(canvas_width) / canvas_height;
	}
	static inline float aspecty() {
		return static_cast<float>(canvas_height) / canvas_width;
	}
}
