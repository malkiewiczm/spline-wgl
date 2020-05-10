#pragma once

#include "common.hpp"

namespace g {
	class Mouse {
	public:
		LAZY_ACCESSOR(bool, down)
		LAZY_ACCESSOR(bool, locked)
		LAZY_ACCESSOR(int, x)
		LAZY_ACCESSOR(int, y)
	private:
		bool m_down;
		bool m_locked;
		int m_x;
		int m_y;
	};
	extern Mouse mouse;
}
