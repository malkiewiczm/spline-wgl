#pragma once

#include "common.hpp"
#include "glm/glm.hpp"

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
	const int element_count;
	const GLenum draw_mode;
	void gen_buffers();
public:
	VAO(GLenum l_draw_mode, const std::vector<Vertex_PN> &vertices, const std::vector<GLuint> indices);
	VAO(GLenum l_draw_mode, const std::vector<Vertex_PT> &vertices, const std::vector<GLuint> indices);
	VAO(GLenum l_draw_mode, const std::vector<Vertex_PC> &vertices, const std::vector<GLuint> indices);
	void draw() const;
};
