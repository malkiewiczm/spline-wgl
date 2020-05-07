#include "spline.hpp"

template<int deg>
static glm::vec3 decasteljau(const glm::vec3 c[deg + 1], const float u)
{
	const float v = 1.f - u;
	glm::vec3 dp[deg + 1];
	for (int i = 0; i <= deg; ++i) {
		dp[i] = c[i];
	}
	for (int d = deg; d >= 1; --d) {
		for (int i = 0; i < d; ++i) {
			dp[i] = dp[i]*v + dp[i + 1]*u;
		}
	}
	return dp[0];
}

template<int deg>
static void append_bezier(std::vector<glm::vec3> &pts, const glm::vec3 c[deg + 1])
{
	constexpr int num_segs = 20;
	for (int i = 0; i <= num_segs; ++i) {
		const float u = i / static_cast<float>(num_segs);
		pts.push_back(decasteljau<deg>(c, u));
	}
}

static void calc_spline4(const std::vector<glm::vec3> &control_pts, std::vector<glm::vec3> &pts)
{
	if (control_pts.size() < 4)
		return;
	std::vector<glm::vec3> c((control_pts.size() - 3)*4 + 1);
	for (unsigned i = 1; i < control_pts.size() - 1; ++i) {
		const glm::vec3 &am = control_pts[i - 1];
		const glm::vec3 &a = control_pts[i];
		const glm::vec3 &ap = control_pts[i + 1];
		const int b = (i - 1)*4;
		c[b] = 0.75f*a + 0.125f*am + 0.125f*ap;
		c[b + 1] = 0.75f*a + 0.25f*ap;
		c[b + 2] = 0.5f*a + 0.5f*ap;
		c[b + 3] = 0.25f*a + 0.75f*ap;
	}
	for (auto v : c) {
		pts.push_back(v);
	}
}

static std::vector<glm::vec3> control_pts;

void g::spline::add_pt(const glm::vec3 &p, VAO &vao)
{
	control_pts.push_back(p);
	if (control_pts.size() < 4)
		return;
	std::vector<glm::vec3> pts;
	calc_spline4(control_pts, pts);
	std::vector<GLuint> indices(pts.size());
	for (unsigned i = 0; i < pts.size(); ++i) {
		indices[i] = i;
	}
	std::vector<Vertex_PC> vertices(pts.size());
	for (unsigned i = 0; i < pts.size(); ++i) {
		vertices[i].position = pts[i];
		vertices[i].color = glm::vec3(0.f, 0.f, 0.1f);
	}
	vao.update_buffers(vertices, indices);
}
