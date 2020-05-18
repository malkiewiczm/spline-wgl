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
}

void g::Cart::update_buffers()
{
}

void g::Cart::step(float dt)
{
	m_position += m_velocity*dt;
	g::Spline::Piece piece = g::spline.get_piece(m_position);
	m_velocity += glm::dot(piece.tangent, GRAVITY)*dt;
	m_draw_position = piece.position;
	update_buffers();
}
