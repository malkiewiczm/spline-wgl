#pragma once

#include "common.hpp"
#include "vao.hpp"

namespace g {
	class Cart {
	public:
		void init();
		VAO vao;
		void step(float dt);
		void draw();
	private:
		float m_position;
		float m_velocity;
	};
	extern Cart cart;
}
