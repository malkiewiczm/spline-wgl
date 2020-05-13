#pragma once

#include "common.hpp"

namespace g {
	class Mouse {
	public:
		ACC_V(bool, down)
		ACC_V(bool, locked)
		ACC_V(int, x)
		ACC_V(int, y)
		glm::vec2 get_ui_coordinates();
	private:
		bool m_down;
		bool m_locked;
		int m_x;
		int m_y;
	};
	extern Mouse mouse;
}
