#pragma once

#include "common.hpp"
#include "vao.hpp"

namespace g {
	namespace spline {
		struct Piece {
			glm::vec3 position;
			glm::vec3 tangent;
			float distance;
		};
		void edit_click(VAO &control_vao, VAO &curve_vao);
		void add_pt(const glm::vec3 &p, VAO &control_vao, VAO &curve_vao);
		Piece get_piece(const float distance);
		extern bool place_when_click;
	}
}
