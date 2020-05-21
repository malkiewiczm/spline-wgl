#include "cart.hpp"
#include "spline.hpp"
#include "obj_loader.hpp"

g::Cart g::cart;

static const glm::vec3 GRAVITY { 0.f, -9.8f, 0.f };

void g::Cart::init()
{
	m_vao.init(GL_TRIANGLES);
	reset();
	load_object_PNC(g::obj::cart, glm::vec3(0.8f, 0.f, 0.f), m_vao);
}

void g::Cart::reset()
{
	m_position = 0.f;
	m_velocity = 0.f;
	m_draw_position = { 0.f, 0.f, 0.f };
	m_rotation = glm::mat4(1.f);
}

glm::mat4 g::Cart::get_transform() const
{
	return glm::translate(glm::mat4(1.f), m_draw_position)*m_rotation;
}

glm::mat4 g::Cart::get_transform_inv() const
{
	return glm::translate(glm::mat4(1.f), m_draw_position)*m_rotation;
}

static glm::mat4 make_matrix(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2)
{
	return glm::mat4 {
		v0.x, v0.y, v0.z, 0.f, v1.x, v1.y, v1.z, 0.f, v2.x, v2.y, v2.z, 0.f, 0.f, 0.f, 0.f, 1.f
	};
}

void g::Cart::step(float dt)
{
	m_position += m_velocity*dt;
	g::Spline::Piece piece = g::spline.get_piece(m_position);
	m_velocity += glm::dot(piece.tangent, GRAVITY)*dt;
	m_draw_position = piece.position;
	m_rotation = make_matrix(piece.tangent, piece.normal, piece.binormal);
}
