#include "vao.hpp"
#include "shader.hpp"

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
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
	switch (m_kind) {
	case KIND_PN:
		g::shaders.kind(g::Shaders::KIND_PN);
		glVertexAttribPointer(a_position, 3, GL_FLOAT, false, sizeof(Vertex_PN), attrib_index_float(0));
		glVertexAttribPointer(a_normal, 3, GL_FLOAT, false, sizeof(Vertex_PN), attrib_index_float(3));
		break;
	case KIND_PT:
		g::shaders.kind(g::Shaders::KIND_PT);
		glVertexAttribPointer(a_position, 3, GL_FLOAT, false, sizeof(Vertex_PT), attrib_index_float(0));
	glVertexAttribPointer(a_uv, 2, GL_FLOAT, false, sizeof(Vertex_PT), attrib_index_float(3));
		break;
	default:
		g::shaders.kind(g::Shaders::KIND_PC);
		glVertexAttribPointer(a_position, 3, GL_FLOAT, false, sizeof(Vertex_PC), attrib_index_float(0));
	glVertexAttribPointer(a_color, 3, GL_FLOAT, false, sizeof(Vertex_PC), attrib_index_float(3));
	}
}

void VAO::gen_buffers()
{
	GLuint bufs[2];
	glGenBuffers(2, bufs);
	m_vertex_buffer = bufs[0];
	m_index_buffer = bufs[1];
}

void VAO::draw() const
{
	context_switch();
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
	glDrawElements(m_draw_mode, m_element_count, GL_UNSIGNED_INT, (void*)0);
}
