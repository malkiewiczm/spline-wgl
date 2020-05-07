#pragma once

#include "common.hpp"
#include "vao.hpp"

namespace g {
	namespace spline {
		void edit_click(VAO &control_vao, VAO &curve_vao);
		void add_pt(const glm::vec3 &p, VAO &control_vao, VAO &curve_vao);
	}
}
