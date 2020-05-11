#pragma once

#include "common.hpp"
#include "vao.hpp"

namespace g {
	class Cart {
	public:
		void init();
		VAO vao;
		void reset();
		void step(float dt);
		void draw();
		void update_buffers();
		LAZY_GETR(glm::vec3, draw_position)
	private:
		float m_position;
		float m_velocity;
		glm::vec3 m_draw_position;
	};
	extern Cart cart;
}
