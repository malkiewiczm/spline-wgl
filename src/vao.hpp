#pragma once

#include "common.hpp"

struct Vertex_PNC {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
};

struct Vertex_PT {
	glm::vec3 position;
	glm::vec2 uv;
};

struct Vertex_PC {
	glm::vec3 position;
	glm::vec3 color;
};

class VAO {
public:
	enum VAOKind {
		KIND_PNC, KIND_PT, KIND_PC
	};
	template <typename Vertex>
	void update_buffers(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices) {
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
		m_element_count = indices.size();
	}
	void gen_buffers();
	void draw() const;
	LAZY_ACCESSOR(GLenum, draw_mode)
	LAZY_ACCESSOR(VAOKind, kind)
private:
	GLuint m_vertex_buffer;
	GLuint m_index_buffer;
	int m_element_count;
	GLenum m_draw_mode;
	VAOKind m_kind;
	void context_switch() const;
};
