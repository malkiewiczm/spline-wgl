#pragma once

#include "vao.hpp"

void load_object_PNC(const void *data, const glm::vec3 &color, VAO<Vertex_PNC> &vao);

namespace g {
	namespace obj {
		extern const unsigned char cart[];
		extern const unsigned char track[];
	}
}
