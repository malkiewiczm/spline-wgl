#include "cart.hpp"
#include "spline.hpp"

g::Cart g::cart;

static const glm::vec3 GRAVITY { 0.f, -5.f, 0.f };

void g::Cart::init()
{
	vao.gen_buffers();
	vao.draw_mode(GL_TRIANGLES);
	vao.kind(VAO::KIND_PC);
	m_position = 0.f;
	m_velocity = 0.f;
}

void g::Cart::step(float dt)
{
	m_position += m_velocity;
	g::Spline::Piece piece = g::spline.get_piece(m_position);
	m_velocity += glm::dot(piece.tangent, GRAVITY);
}

void g::Cart::draw()
{

}
