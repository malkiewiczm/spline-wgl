#include "obj_loader.hpp"
#include <cstring>

struct ObjVertex {
	glm::vec3 position;
	glm::vec2 texture;
	glm::vec3 normal;
};

static GLuint read_u32(const void *&data)
{
	int ret = 0;
	std::memcpy(&ret, data, 4);
	data = reinterpret_cast<const char *>(data) + 4;
	return static_cast<GLuint>(ret);
}

static float read_f32(const void *&data)
{
	float ret = 0;
	std::memcpy(&ret, data, 4);
	data = reinterpret_cast<const char *>(data) + 4;
	return ret;
}

static void load_obj_generic(const void *data, std::vector<ObjVertex> &vertices, std::vector<GLuint> &indices)
{
	const int vertex_len = read_u32(data);
	vertices.resize(vertex_len);
	for (int i = 0; i < vertex_len; ++i) {
		ObjVertex &v = vertices[i];
		v.position.x = read_f32(data);
		v.position.y = read_f32(data);
		v.position.z = read_f32(data);
		v.texture.x = read_f32(data);
		v.texture.y = read_f32(data);
		v.normal.x = read_f32(data);
		v.normal.y = read_f32(data);
		v.normal.z = read_f32(data);
	}
	const int index_len = read_u32(data);
	indices.resize(index_len);
	for (int i = 0; i < index_len; ++i) {
		indices[i] = read_u32(data);
	}
}

void load_object_PNC(const void *data, const glm::vec3 &color, VAO<Vertex_PNC> &vao)
{
	std::vector<ObjVertex> vertices_old;
	std::vector<GLuint> indices;
	load_obj_generic(data, vertices_old, indices);
	std::vector<Vertex_PNC> vertices(vertices_old.size());
	for (size_t i = 0; i < vertices.size(); ++i) {
		vertices[i].position = vertices_old[i].position;
		vertices[i].normal = vertices_old[i].normal;
		vertices[i].color = color;
	}
	vao.update_buffers(vertices, indices);
}
