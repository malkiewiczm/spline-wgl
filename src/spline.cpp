#include "spline.hpp"
#include "camera.hpp"
#include "mouse.hpp"
#include <algorithm>

template<int deg>
static g::spline::Piece decasteljau(const glm::vec3 c[deg + 1], const float u)
{
	const float v = 1.f - u;
	g::spline::Piece dp[deg + 1];
	for (int i = 0; i <= deg; ++i) {
		dp[i].position = c[i];
	}
	for (int d = deg; d >= 1; --d) {
		for (int i = 0; i < d; ++i) {
			dp[i].position = dp[i].position*v + dp[i + 1].position*u;
		}
	}
	dp[0].tangent = glm::normalize(dp[1].position - dp[0].position);
	return dp[0];
}

template<int deg>
static void append_bezier(std::vector<g::spline::Piece> &pts, const glm::vec3 c[deg + 1])
{
	constexpr int num_segs = 30;
	for (int i = 0; i <= num_segs; ++i) {
		const float u = i / static_cast<float>(num_segs);
		pts.push_back(decasteljau<deg>(c, u));
	}
}

static void calc_spline3(const std::vector<glm::vec3> &control_pts, std::vector<g::spline::Piece> &pts)
{
	if (control_pts.size() < 4)
		return;
	constexpr int deg = 3;
	std::vector<glm::vec3> c((control_pts.size() - 3)*deg + 1);
	const unsigned last_i = control_pts.size() - 2;
	for (unsigned i = 1; ; ++i) {
		const glm::vec3 &am = control_pts[i - 1];
		const glm::vec3 &a = control_pts[i];
		const glm::vec3 &ap = control_pts[i + 1];
		const int b = (i - 1)*deg;
		const glm::vec3 r0 = glm::mix(am, a, 2.f/3.f);
		const glm::vec3 r1 = glm::mix(a, ap, 1.f/3.f);
		c[b] = glm::mix(r0, r1, 0.5f);
		if (i == last_i)
			break;
		c[b + 1] = r1;
		c[b + 2] = glm::mix(a, ap, 2.f/3.f);
	}
#define MAKE_CURVES
#ifdef MAKE_CURVES
	for (unsigned i = deg; i < c.size(); i += deg) {
		const glm::vec3 l_c[deg + 1] { c[i - 3], c[i - 2], c[i - 1], c[i] };
		append_bezier<deg>(pts, l_c);
	}
#else
	for (unsigned i = 0; i < c.size(); ++i) {
		pts.push_back(c[i]);
	}
#endif
}

static std::vector<g::spline::Piece> curve_pts;
static std::vector<glm::vec3> control_pts;

static bool cmp_distance(const g::spline::Piece &p, const float d)
{
	return p.distance < d;
}

g::spline::Piece g::spline::get_piece(const float distance)
{
	auto iter = std::lower_bound(curve_pts.begin(), curve_pts.end(), distance, cmp_distance);
	g::spline::Piece ret;
	ret.distance = distance;
	if (iter == curve_pts.begin()) {
		// implies that a negative distance was given
		const g::spline::Piece &p = curve_pts.front();
		ret.tangent = p.tangent;
		ret.position = p.position + p.tangent*distance;
	} else if (iter == curve_pts.end()) {
		// implies that a distance greater than the curve length was given
		const g::spline::Piece &p = curve_pts.back();
		ret.tangent = p.tangent;
		ret.position = p.position + p.tangent*distance;
	} else {
		const g::spline::Piece &p0 = *(iter - 1);
		const g::spline::Piece &p1 = *iter;
		const float t = (distance - p0.distance) / (p1.distance - p0.distance);
		ret.tangent = glm::mix(p0.tangent, p1.tangent, t);
		ret.position = glm::mix(p0.position, p1.position, t);
	}
	return ret;
}

static void calc_path_length()
{
	curve_pts[0].distance = 0.f;
	for (unsigned i = 1; i < curve_pts.size(); ++i) {
		const float delta = glm::distance(curve_pts[i - 1].position, curve_pts[i].position);
		curve_pts[i].distance = curve_pts[i - 1].distance + delta;
	}
}

void g::spline::add_pt(const glm::vec3 &p, VAO &control_vao, VAO &curve_vao)
{
	control_pts.push_back(p);
	if (control_pts.size() <= 1)
		return;
	const glm::vec3 control_color { 0.5f, 0.f, 0.f };
	const glm::vec3 curve_color { 0.f, 0.5f, 0.5f };
	curve_pts.clear();
	calc_spline3(control_pts, curve_pts);
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
		vertices[i].position = curve_pts[i].position;
		vertices[i].color = curve_color;
	}
	for (unsigned i = 0; i < indices.size(); ++i) {
		indices[i] = i;
	}
	calc_path_length();
	curve_vao.update_buffers(vertices, indices);
}

static void edit_click_place(VAO &control_vao, VAO &curve_vao)
{
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

void g::spline::edit_click(VAO &control_vao, VAO &curve_vao)
{
	if (! g::is_edit_mode)
		return;
	if (g::camera3d::enabled)
		return;
	if (g::spline::place_when_click) {
		edit_click_place(control_vao, curve_vao);
		g::spline::place_when_click = false;
	}
}

bool g::spline::place_when_click = false;
