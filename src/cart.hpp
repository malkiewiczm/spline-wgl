#pragma once

#include "common.hpp"
#include "vao.hpp"

namespace g {
	class Cart {
	public:
		void init();
		void reset();
		void step(float dt);
		glm::mat4 get_transform() const;
		glm::mat4 get_transform_inv() const;
		GET_CR(glm::vec3, draw_position)
		GET_CR(VAO<Vertex_PNC>, vao)
	private:
		float m_position;
		float m_velocity;
		glm::vec3 m_draw_position;
		VAO<Vertex_PNC> m_vao;
		glm::vec3 m_tangent;
		glm::vec3 m_normal;
		glm::vec3 m_binormal;
	};
	extern Cart cart;
}
