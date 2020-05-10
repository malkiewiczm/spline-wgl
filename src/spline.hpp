#pragma once

#include "common.hpp"
#include "vao.hpp"

namespace g {
	class Spline {
	public:
		struct Piece {
			glm::vec3 position;
			glm::vec3 tangent;
			float distance;
		};
		void edit_click(VAO &control_vao, VAO &curve_vao);
		void add_pt(const glm::vec3 &p, VAO &control_vao, VAO &curve_vao);
		Piece get_piece(const float distance);
		LAZY_ACCESSOR(bool, place_when_click);
	private:
		bool m_place_when_click;
		std::vector<Piece> curve_pts;
		std::vector<glm::vec3> control_pts;
		void edit_click_place(VAO &control_vao, VAO &curve_vao);
	};
	extern Spline spline;
}
