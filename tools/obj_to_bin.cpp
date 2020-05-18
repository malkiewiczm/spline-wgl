#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <stdint.h>
#include <map>
#include <tuple>

static void _die(const char *msg, const char *file, int line);
#define die(msg) _die(msg, __FILE__, __LINE__)
#define TRACE (std::cout << '[' << __FILE__ << ':' << __LINE__ << "] ")
#define trace(what)(TRACE << #what " = " << (what) << std::endl)

static void _die(const char *msg, const char *file, int line)
{
	printf("error: %s (%s:%d)\n", msg, file, line);
	abort();
}

struct Vec3 {
	float x, y, z;
	Vec3() = default;
	Vec3(float l_x, float l_y, float l_z)
		: x(l_x), y(l_y), z(l_z) {}
	Vec3(std::stringstream &ss);
};

struct Vec2 {
	float x, y;
	Vec2() = default;
	Vec2(float l_x, float l_y)
		: x(l_x), y(l_y) {}
	Vec2(std::stringstream &ss);
};

struct Vertex {
	Vec3 position;
	Vec2 texture;
	Vec3 normal;
};

Vec3::Vec3(std::stringstream &ss)
{
	ss >> x >> y >> z;
}

Vec2::Vec2(std::stringstream &ss)
{
	ss >> x >> y;
}

static void write_u32(std::ofstream &o, const uint32_t v)
{
	o.write(reinterpret_cast<const char *>(&v), 4);
}

static void write_f32(std::ofstream &o, const float v)
{
	o.write(reinterpret_cast<const char *>(&v), 4);
}

static bool starts_with(const std::string &s, const char *const prefix)
{
	const size_t len = std::strlen(prefix);
	if (s.size() < len)
		return false;
	for (size_t i = 0; i < len; ++i) {
		if (s[i] != prefix[i])
			return false;
	}
	return true;
}

static void read_file(const char *const fname, std::vector<Vertex> &vertices, std::vector<int> &indices)
{
	std::ifstream file(fname);
	if (! file.good()) {
		trace(fname);
		die("could not open file for reading");
	}
	std::string line;
	std::vector<Vec3> positions;
	std::vector<Vec2> uvs;
	std::vector<Vec3> normals;
	using Key_t = std::tuple<int, int, int>;
	std::map<Key_t, int> match;
	indices.clear();
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		ss.ignore(256, ' ');
		if (starts_with(line, "v ")) {
			positions.emplace_back(ss);
		} else if (starts_with(line, "vn ")) {
			normals.emplace_back(ss);
		} else if (starts_with(line, "vt ")) {
			uvs.emplace_back(ss);
		} else if (starts_with(line, "f ")) {
			for (int i = 0; i < 3; ++i) {
				std::string chunk;
				ss >> chunk;
				const size_t one = chunk.find('/');
				const size_t two = chunk.find('/', one + 1);
				if (one == std::string::npos || two == std::string::npos) {
					die("malformed obj file (no normals?)");
				}
				const int p_index = std::stoi(chunk.substr(0, one)) - 1;
				const int t_index = (one + 1 == two) ? 0 : std::stoi(chunk.substr(one + 1, two)) - 1;
				const int n_index = std::stoi(chunk.substr(two + 1)) - 1;
				const Key_t key = std::make_tuple(p_index, t_index, n_index);
				auto iter = match.find(key);
				int index;
				if (iter == match.end()) {
					index = match.size();
					match.emplace(key, index);
				} else {
					index = iter->second;
				}
				indices.push_back(index);
			}
		}
	}
	vertices.resize(match.size());
	trace(positions.size());
	trace(uvs.size());
	trace(normals.size());
	trace(vertices.size());
	trace(indices.size());
	if (uvs.empty()) {
		uvs.push_back({ 0.f, 0.f });
	}
	for (auto kv : match) {
		Vertex &v = vertices[kv.second];
		v.position = positions[std::get<0>(kv.first)];
		v.texture = uvs[std::get<1>(kv.first)];
		v.normal = normals[std::get<2>(kv.first)];
	}
}

static void write_file(const char *const fname, const std::vector<Vertex> &vertices, const std::vector<int> &indices)
{
	std::ofstream file(fname, std::ios::binary);
	if (! file.good()) {
		trace(fname);
		die("could not create file for writing");
	}
	write_u32(file, vertices.size());
	for (auto v : vertices) {
		write_f32(file, v.position.x);
		write_f32(file, v.position.y);
		write_f32(file, v.position.z);
		write_f32(file, v.texture.x);
		write_f32(file, v.texture.y);
		write_f32(file, v.normal.x);
		write_f32(file, v.normal.y);
		write_f32(file, v.normal.z);
	}
	write_u32(file, indices.size());
	for (auto i : indices) {
		write_u32(file, i);
	}
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		std::cout << "usage: filename.obj filename.bin" << std::endl;
		return 0;
	}
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	read_file(argv[1], vertices, indices);
	write_file(argv[2], vertices, indices);
}
