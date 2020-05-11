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
		void init();
		void draw();
		void edit_click();
		void add_pt(const glm::vec3 &p);
		Piece get_piece(const float distance);
		LAZY_ACCESSOR(bool, place_when_click)
		LAZY_ACCESSOR(bool, show_control_mesh)
	private:
		bool m_place_when_click;
		bool m_show_control_mesh;
		VAO m_control_vao;
		VAO m_curve_vao;
		std::vector<Piece> m_curve_pts;
		std::vector<glm::vec3> m_control_pts;
		void edit_click_place();
	};
	extern Spline spline;
}
