#include "vao.hpp"
#include "shader.hpp"

static void *attrib_index_float(const int index)
{
	return reinterpret_cast<void*>(index*sizeof(float));
}

void Vertex_PNC::set_attrib_pointers()
{
	constexpr GLuint a_position = 0;
	constexpr GLuint a_normal = 1;
	constexpr GLuint a_color = 2;
	glVertexAttribPointer(a_position, 3, GL_FLOAT, false, sizeof(Vertex_PNC), attrib_index_float(0));
	glVertexAttribPointer(a_normal, 3, GL_FLOAT, false, sizeof(Vertex_PNC), attrib_index_float(3));
	glVertexAttribPointer(a_color, 3, GL_FLOAT, false, sizeof(Vertex_PNC), attrib_index_float(6));
}

void Vertex_PT::set_attrib_pointers()
{
	constexpr GLuint a_position = 0;
	constexpr GLuint a_uv = 1;
	glVertexAttribPointer(a_position, 3, GL_FLOAT, false, sizeof(Vertex_PT), attrib_index_float(0));
	glVertexAttribPointer(a_uv, 2, GL_FLOAT, false, sizeof(Vertex_PT), attrib_index_float(3));
}

void Vertex_PC::set_attrib_pointers()
{
	constexpr GLuint a_position = 0;
	constexpr GLuint a_color = 1;
	glVertexAttribPointer(a_position, 3, GL_FLOAT, false, sizeof(Vertex_PC), attrib_index_float(0));
	glVertexAttribPointer(a_color, 3, GL_FLOAT, false, sizeof(Vertex_PC), attrib_index_float(3));
}
