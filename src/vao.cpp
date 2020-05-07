#include "vao.hpp"

constexpr int KIND_PN = 0;
constexpr int KIND_PT = 1;
constexpr int KIND_PC = 2;


static void *attrib_index_float(const int index)
{
	return reinterpret_cast<void*>(index*sizeof(float));
}

void VAO::context_switch() const
{
	constexpr GLuint a_position = 0;
	constexpr GLuint a_normal = 1;
	constexpr GLuint a_uv = 1;
	constexpr GLuint a_color = 1;
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	switch (kind) {
	case KIND_PN:
		glVertexAttribPointer(a_position, 3, GL_FLOAT, false, sizeof(Vertex_PN), attrib_index_float(0));
		glVertexAttribPointer(a_normal, 3, GL_FLOAT, false, sizeof(Vertex_PN), attrib_index_float(3));
		break;
	case KIND_PT:
		glVertexAttribPointer(a_position, 3, GL_FLOAT, false, sizeof(Vertex_PT), attrib_index_float(0));
	glVertexAttribPointer(a_uv, 2, GL_FLOAT, false, sizeof(Vertex_PT), attrib_index_float(3));
		break;
	default:
		glVertexAttribPointer(a_position, 3, GL_FLOAT, false, sizeof(Vertex_PC), attrib_index_float(0));
	glVertexAttribPointer(a_color, 3, GL_FLOAT, false, sizeof(Vertex_PC), attrib_index_float(3));
		break;
	}
}

void VAO::gen_buffers()
{
	GLuint bufs[2];
	glGenBuffers(2, bufs);
	vertex_buffer = bufs[0];
	index_buffer = bufs[1];
}

VAO::VAO(GLenum l_draw_mode, const std::vector<Vertex_PN> &vertices, const std::vector<GLuint> indices)
	: draw_mode(l_draw_mode), kind(KIND_PN)
{
	gen_buffers();
	update_buffers(vertices, indices);
}

VAO::VAO(GLenum l_draw_mode, const std::vector<Vertex_PT> &vertices, const std::vector<GLuint> indices)
	: draw_mode(l_draw_mode), kind(KIND_PT)
{
	gen_buffers();
	update_buffers(vertices, indices);
}

VAO::VAO(GLenum l_draw_mode, const std::vector<Vertex_PC> &vertices, const std::vector<GLuint> indices)
	: draw_mode(l_draw_mode), kind(KIND_PC)
{
	gen_buffers();
	update_buffers(vertices, indices);
}

void VAO::draw() const
{
	context_switch();
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glDrawElements(draw_mode, element_count, GL_UNSIGNED_INT, (void*)0);
}
