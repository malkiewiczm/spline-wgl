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
	private:
		float m_position;
		float m_velocity;
		glm::vec3 m_draw_position;
	};
	extern Cart cart;
}
