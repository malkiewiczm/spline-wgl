#include "cart.hpp"
#include "spline.hpp"

g::Cart g::cart;

static const glm::vec3 GRAVITY { 0.f, -9.8f, 0.f };

void g::Cart::init()
{
	vao.gen_buffers();
	vao.draw_mode(GL_TRIANGLES);
	vao.kind(VAO::KIND_PN);
	reset();
	update_buffers();
}

void g::Cart::reset()
{
	m_position = 0.f;
	m_velocity = 0.f;
	m_draw_position = { 0.f, 0.f, 0.f };
}

void g::Cart::update_buffers()
{
	//constexpr float W = 1.5f;
	//constexpr float H = 0.6f;
	constexpr float S = 0.5f;
	constexpr float R = 0.5773502f;
	std::vector<Vertex_PN> vertices {
		{ m_draw_position + glm::vec3(-S, -S, -S), { -R, -R, -R } },
		{ m_draw_position + glm::vec3(-S, -S, S), { -R, -R, R } },
		{ m_draw_position + glm::vec3(-S, S, -S), { -R, R, -R } },
		{ m_draw_position + glm::vec3(-S, S, S), { -R, R, R } },
		{ m_draw_position + glm::vec3(S, -S, -S), { R, -R, -R } },
		{ m_draw_position + glm::vec3(S, -S, S), { R, -R, R } },
		{ m_draw_position + glm::vec3(S, S, -S), { R, R, -R } },
		{ m_draw_position + glm::vec3(S, S, S), { R, R, R } },
	};
	std::vector<GLuint> indices {
		0, 1, 2, 1, 3, 2,
		1, 5, 7, 1, 7, 3,
		5, 4, 6, 5, 6, 7,
		0, 2, 6, 0, 6, 4,
		1, 5, 4, 1, 4, 0,
		3, 7, 6, 3, 6, 2
	};
	vao.update_buffers(vertices, indices);
}

void g::Cart::step(float dt)
{
	m_position += m_velocity*dt;
	g::Spline::Piece piece = g::spline.get_piece(m_position);
	m_velocity += glm::dot(piece.tangent, GRAVITY)*dt;
	m_draw_position = piece.position;
}

void g::Cart::draw()
{
	update_buffers();
	vao.draw();
}
