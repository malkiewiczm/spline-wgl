#include "mouse.hpp"

g::Mouse g::mouse;

glm::vec2 g::Mouse::get_ui_coordinates()
{
	const float w = static_cast<float>(g::canvas_width);
	const float h = static_cast<float>(g::canvas_height);
	const glm::mat3 m {
		2.f/w, 0.f, 0.f, 0.f, -2.f/h, 0.f, -1.f, 1.f, 1.f
	};
	glm::vec3 v(m_x, m_y, 1.f);
	v = m*v;
	return glm::vec2(v.x, v.y);
}
