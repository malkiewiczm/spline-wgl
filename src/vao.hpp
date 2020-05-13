#pragma once

#include "common.hpp"

struct Vertex_PNC {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	static void set_attrib_pointers();
};

struct Vertex_PT {
	glm::vec3 position;
	glm::vec2 uv;
	static void set_attrib_pointers();
};

struct Vertex_PC {
	glm::vec3 position;
	glm::vec3 color;
	static void set_attrib_pointers();
};

template <typename Vertex>
class VAO {
public:
	void init(GLenum l_draw_mode) {
		GLuint bufs[2];
		glGenBuffers(2, bufs);
		m_vertex_buffer = bufs[0];
		m_index_buffer = bufs[1];
		m_draw_mode = l_draw_mode;
	}
	void update_buffers(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices) {
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
		m_element_count = indices.size();
	}
	void draw() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
		Vertex::set_attrib_pointers();
		glDrawElements(m_draw_mode, m_element_count, GL_UNSIGNED_INT, (void*)0);
	}
private:
	GLuint m_vertex_buffer;
	GLuint m_index_buffer;
	int m_element_count;
	GLenum m_draw_mode;
};
