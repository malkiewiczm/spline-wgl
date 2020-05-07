#include "spline.hpp"
#include "camera.hpp"
#include "mouse.hpp"

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
	for (unsigned i = 1; i < control_pts.size() - 2; ++i) {
		const glm::vec3 &am = control_pts[i - 1];
		const glm::vec3 &a = control_pts[i];
		const glm::vec3 &ap = control_pts[i + 1];
		const int b = (i - 1)*4;
		c[b] = 0.75f*a + 0.125f*am + 0.125f*ap;
		c[b + 1] = 0.75f*a + 0.25f*ap;
		c[b + 2] = 0.5f*a + 0.5f*ap;
		c[b + 3] = 0.25f*a + 0.75f*ap;
	}
	// last point
	{
		const int i = control_pts.size() - 2;
		const glm::vec3 &am = control_pts[i - 1];
		const glm::vec3 &a = control_pts[i];
		const glm::vec3 &ap = control_pts[i + 1];
		const int b = (i - 1)*4;
		c[b] = 0.75f*a + 0.125f*am + 0.125f*ap;
	}
	for (unsigned i = 4; i < c.size(); i += 4) {
		const glm::vec3 l_c[5] { c[i - 4], c[i - 3], c[i - 2], c[i - 1], c[i] };
		append_bezier<4>(pts, l_c);
	}
}

static std::vector<glm::vec3> control_pts;

void g::spline::add_pt(const glm::vec3 &p, VAO &control_vao, VAO &curve_vao)
{
	control_pts.push_back(p);
	if (control_pts.size() <= 1)
		return;
	const glm::vec3 control_color { 0.5f, 0.f, 0.f };
	const glm::vec3 curve_color { 0.f, 0.5f, 0.5f };
	std::vector<glm::vec3> curve_pts;
	calc_spline4(control_pts, curve_pts);
	std::vector<Vertex_PC> vertices(control_pts.size());
	std::vector<GLuint> indices(vertices.size());
	for (unsigned i = 0; i < vertices.size(); ++i) {
		vertices[i].position = control_pts[i];
		vertices[i].color = control_color;
	}
	for (unsigned i = 0; i < indices.size(); ++i) {
		indices[i] = i;
	}
	control_vao.update_buffers(vertices, indices);
	if (curve_pts.empty())
		return;
	vertices.resize(curve_pts.size());
	indices.resize(vertices.size());
	for (unsigned i = 0; i < vertices.size(); ++i) {
		vertices[i].position = curve_pts[i];
		vertices[i].color = curve_color;
	}
	for (unsigned i = 0; i < indices.size(); ++i) {
		indices[i] = i;
	}
	curve_vao.update_buffers(vertices, indices);
}

void g::spline::edit_click(VAO &control_vao, VAO &curve_vao)
{
	if (! g::is_edit_mode)
		return;
	if (g::camera3d::enabled)
		return;
	static glm::vec3 last_placement { 0.f, 0.f, 0.f };
	glm::vec3 p { g::mouse::x, g::mouse::y, 0.f };
	constexpr float R = 5.f;
	p.x = (2.f*(p.x / g::canvas_width) - 1.f)*R;
	p.y = -(2.f*(p.y / g::canvas_height) - 1.f)*R;
	if (g::canvas_width > g::canvas_height) {
		const float aspect = static_cast<float>(g::canvas_height) / g::canvas_width;
		p.y *= aspect;
	} else {
		const float aspect = static_cast<float>(g::canvas_width) / g::canvas_height;
		p.x *= aspect;
	}
	if (g::camera_ortho_side == g::ORTHO_TOP || g::camera_ortho_side == g::ORTHO_BOTTOM) {
		p.y = -p.y;
	}
	if (g::camera_ortho_side == g::ORTHO_FRONT || g::camera_ortho_side == g::ORTHO_BACK) {
		p.x = -p.x;
	}
	{
		const glm::mat4 &mv = g::ortho_rotations[g::camera_ortho_side];
		glm::vec4 v4 { p.x, p.y, p.z, 1. };
		v4 = mv*v4;
		p.x = v4.x;
		p.y = v4.y;
		p.z = v4.z;
		switch (g::camera_ortho_side) {
		case g::ORTHO_RIGHT:
		case g::ORTHO_LEFT:
			p.z = last_placement.z;
			break;
		case g::ORTHO_TOP:
		case g::ORTHO_BOTTOM:
			p.y = last_placement.y;
			break;
		default:
			p.x = last_placement.x;
		}
	}
	last_placement = p;
	g::spline::add_pt(p, control_vao, curve_vao);
}
