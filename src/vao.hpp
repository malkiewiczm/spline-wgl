#pragma once

#include "common.hpp"

struct Vertex_PN {
	glm::vec3 position;
	glm::vec3 normal;
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
private:
	GLuint vertex_buffer;
	GLuint index_buffer;
	int element_count;
	const GLenum draw_mode;
	const int kind;
	void context_switch() const;
	void gen_buffers();
public:
	template <typename Vertex>
	void update_buffers(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices) {
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
		element_count = indices.size();
	}
	VAO(GLenum l_draw_mode, const std::vector<Vertex_PN> &vertices, const std::vector<GLuint> indices);
	VAO(GLenum l_draw_mode, const std::vector<Vertex_PT> &vertices, const std::vector<GLuint> indices);
	VAO(GLenum l_draw_mode, const std::vector<Vertex_PC> &vertices, const std::vector<GLuint> indices);
	void draw() const;
};
