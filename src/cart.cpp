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
	m_tangent = { 1.f, 0.f, 0.f };
	m_normal = { 0.f, 1.f, 0.f };
	m_binormal = { 0.f, 0.f, 1.f };
}

static glm::mat4 make_matrix(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2)
{
	return glm::mat4 {
		v0.x, v0.y, v0.z, 0.f, v1.x, v1.y, v1.z, 0.f, v2.x, v2.y, v2.z, 0.f, 0.f, 0.f, 0.f, 1.f
	};
}

glm::mat4 g::Cart::get_transform() const
{
	const glm::mat4 rot = make_matrix(m_tangent, m_normal, m_binormal);
	return glm::translate(glm::mat4(1.f), m_draw_position)*rot;
}

glm::mat4 g::Cart::get_transform_inv() const
{
	// the order is different in order to make a 90 deg rotation
	const glm::mat4 rot = make_matrix(m_binormal, m_normal, -m_tangent);
	return glm::translate(glm::transpose(rot), -m_draw_position);
}

void g::Cart::step(float dt)
{
	m_position += m_velocity*dt;
	g::Spline::Piece piece = g::spline.get_piece(m_position);
	m_velocity += glm::dot(piece.tangent, GRAVITY)*dt;
	m_draw_position = piece.position;
	m_tangent = piece.tangent;
	m_normal = piece.normal;
	m_binormal = piece.binormal;
}
