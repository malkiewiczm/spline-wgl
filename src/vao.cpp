#include "vao.hpp"

void VAO::gen_buffers()
{
	GLuint bufs[2];
	glGenBuffers(2, bufs);
	vertex_buffer = bufs[0];
	index_buffer = bufs[1];
}

static void *attrib_index_float(const int index)
{
	return reinterpret_cast<void*>(index*sizeof(float));
}

// assumes array buffer is already bound
template <typename Vertex>
static void fill_buffers(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices, const GLuint index_buffer)
{
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
}

VAO::VAO(GLenum l_draw_mode, const std::vector<Vertex_PN> &vertices, const std::vector<GLuint> indices)
	: element_count(indices.size()), draw_mode(l_draw_mode)
{
	constexpr GLuint a_position = 0;
	constexpr GLuint a_normal = 1;
	using Vertex = Vertex_PN;
	gen_buffers();
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(a_position, 3, GL_FLOAT, false, sizeof(Vertex), attrib_index_float(0));
	glVertexAttribPointer(a_normal, 3, GL_FLOAT, false, sizeof(Vertex), attrib_index_float(3));
	fill_buffers(vertices, indices, index_buffer);
}

VAO::VAO(GLenum l_draw_mode, const std::vector<Vertex_PT> &vertices, const std::vector<GLuint> indices)
	: element_count(indices.size()), draw_mode(l_draw_mode)
{
	constexpr GLuint a_position = 0;
	constexpr GLuint a_uv = 1;
	using Vertex = Vertex_PT;
	gen_buffers();
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(a_position, 3, GL_FLOAT, false, sizeof(Vertex), attrib_index_float(0));
	glVertexAttribPointer(a_uv, 2, GL_FLOAT, false, sizeof(Vertex), attrib_index_float(3));
	fill_buffers(vertices, indices, index_buffer);
}

VAO::VAO(GLenum l_draw_mode, const std::vector<Vertex_PC> &vertices, const std::vector<GLuint> indices)
	: element_count(indices.size()), draw_mode(l_draw_mode)
{
	constexpr GLuint a_position = 0;
	constexpr GLuint a_color = 1;
	using Vertex = Vertex_PN;
	gen_buffers();
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(a_position, 3, GL_FLOAT, false, sizeof(Vertex), attrib_index_float(0));
	glVertexAttribPointer(a_color, 3, GL_FLOAT, false, sizeof(Vertex), attrib_index_float(3));
	fill_buffers(vertices, indices, index_buffer);
}

void VAO::draw() const
{
	glDrawElements(draw_mode, element_count, GL_UNSIGNED_INT, (void*)0);
}
