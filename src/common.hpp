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
	extern GLuint standard_shader;
	extern int canvas_width;
	extern int canvas_height;
	extern GLuint u_projection;
	extern GLuint u_modelview;
	extern bool is_edit_mode;
}
