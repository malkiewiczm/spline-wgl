#include "spline.hpp"
#include "camera.hpp"
#include "mouse.hpp"
#include <algorithm>

g::Spline g::spline;

void g::Spline::init()
{
	m_place_when_click = false;
	m_show_control_mesh = true;
	m_show_ui = false;
	m_control_vao.init(GL_LINES);
	m_control_vao.update_buffers({ { glm::vec3(-5.f), glm::vec3(1.f, 0., 0.f) }, { glm::vec3(5.f), glm::vec3(0.f, 0., 1.f) } }, { 0, 1 });
	std::vector<Vertex_PNC> vertex_data {
		{ { 0.273279f, 1.050624f, -2.005395f }, { 0.f, 0.f, 1.f }, { 0.89596240119633f, 0.82284005249184f, 0.7466048158208f } },
		{ { -0.857576f, -0.598839f, -2.026340f }, { 0.f, 0.f, 1.f }, { 0.17410809656056f, 0.85894344920194f, 0.71050141911069f } },
		{ { 1.472728f, 0.180840f, 1.731609f }, { 0.f, 0.f, 1.f }, { 0.5135349589526f, 0.30399487289041f, 0.014984588152715f } },
	};
	std::vector<GLuint> index_data {
		0, 1, 2
	};
	m_curve_vao.init(GL_TRIANGLES);
	m_curve_vao.update_buffers(vertex_data, index_data);
	m_ui_vao.init(GL_LINES);
	m_ui_vao.update_buffers({ { glm::vec3(-0.5f), glm::vec3(1.f) }, { glm::vec3(0.5f), glm::vec3(0.f) } }, { 0, 1 });
}

template<int deg>
static g::Spline::Piece decasteljau(const glm::vec3 c[deg + 1], const float u)
{
	const float v = 1.f - u;
	g::Spline::Piece dp[deg + 1];
	for (int i = 0; i <= deg; ++i) {
		dp[i].position = c[i];
	}
	for (int d = deg; d >= 2; --d) {
		for (int i = 0; i < d; ++i) {
			dp[i].position = dp[i].position*v + dp[i + 1].position*u;
		}
	}
	// d = 1
	dp[0].tangent = glm::normalize(dp[1].position - dp[0].position);
	dp[0].position = dp[0].position*v + dp[1].position*u;
	return dp[0];
}

template<int deg>
static void append_bezier(std::vector<g::Spline::Piece> &pts, const glm::vec3 c[deg + 1])
{
	constexpr int num_segs = 30;
	for (int i = 0; i <= num_segs; ++i) {
		const float u = i / static_cast<float>(num_segs);
		pts.push_back(decasteljau<deg>(c, u));
	}
}

static void calc_spline3(const std::vector<glm::vec3> &m_control_pts, std::vector<g::Spline::Piece> &pts)

{
	if (m_control_pts.size() < 4)
		return;
	constexpr int deg = 3;
	std::vector<glm::vec3> c((m_control_pts.size() - 3)*deg + 1);
	const unsigned last_i = m_control_pts.size() - 2;
	for (unsigned i = 1; ; ++i) {
		const glm::vec3 &am = m_control_pts[i - 1];
		const glm::vec3 &a = m_control_pts[i];
		const glm::vec3 &ap = m_control_pts[i + 1];
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

static bool cmp_distance(const g::Spline::Piece &p, const float d)
{
	return p.distance < d;
}

g::Spline::Piece g::Spline::get_piece(const float distance)
{
	Piece ret;
	ret.distance = distance;
	if (m_curve_pts.size() <= 1) {
		ret.position = glm::vec3(0.f);
		ret.tangent = glm::vec3(0.f, 1.f, 0.f);
		return ret;
	}
	auto iter = std::lower_bound(m_curve_pts.begin(), m_curve_pts.end(), distance, cmp_distance);
	if (iter == m_curve_pts.begin()) {
		// implies that a negative distance was given
		const Piece &p = m_curve_pts.front();
		ret.tangent = p.tangent;
		ret.position = p.position + p.tangent*distance;
	} else if (iter == m_curve_pts.end()) {
		// implies that a distance greater than the curve length was given
		const Piece &p = m_curve_pts.back();
		ret.tangent = p.tangent;
		ret.position = p.position + p.tangent*(distance - p.distance);
	} else {
		const Piece &p0 = *(iter - 1);
		const Piece &p1 = *iter;
		const float t = (distance - p0.distance) / (p1.distance - p0.distance);
		ret.tangent = glm::mix(p0.tangent, p1.tangent, t);
		ret.position = glm::mix(p0.position, p1.position, t);
	}
	return ret;
}

void g::Spline::update_control_vao()
{
	const glm::vec3 polygon_color { 0.5f, 0.f, 0.f };
	const glm::vec3 box_color { 0.f, 0.f, 0.5f };
	std::vector<Vertex_PC> vertices;
	std::vector<GLuint> indices;
	std::vector<glm::vec3> cube_corners(8);
	std::vector<GLuint> cube_indices {
		0, 1, 1, 5, 5, 4, 4, 0,
		2, 3, 3, 7, 7, 6, 6, 2,
		2, 0, 3, 1, 7, 5, 6, 4,
	};
	for (int i = 0; i < 8; ++i) {
		constexpr float R = 0.2f;
		cube_corners[i].x = (i & 1) ? R : -R;
		cube_corners[i].y = ((i >> 1) & 1) ? R : -R;
		cube_corners[i].z = ((i >> 2) & 1) ? R : -R;
	}
	for (unsigned i = 0; i < m_control_pts.size(); ++i) {
		vertices.push_back({ m_control_pts[i], polygon_color });
		for (int k = 0; k < 8; ++k) {
			vertices.push_back({ m_control_pts[i] + cube_corners[k], box_color });
		}
	}
	for (unsigned i = 1; i < m_control_pts.size(); ++i) {
		const int k0 = (i - 1)*9;
		const int k1 = i*9;
		indices.push_back(k0);
		indices.push_back(k1);
	}
	for (unsigned i = 0; i < m_control_pts.size(); ++i) {
		for (int k = 0; k < 24; ++k) {
			indices.push_back(i*9 + 1 + cube_indices[k]);
		}
	}
	m_control_vao.update_buffers(vertices, indices);
}

void g::Spline::update_ui_vao()
{
	const glm::vec3 color(0.f);
	std::vector<Vertex_PC> vertices {
		{ { m_selection_rect[0].x, m_selection_rect[0].y, 0.f }, color },
		{ { m_selection_rect[1].x, m_selection_rect[0].y, 0.f }, color },
		{ { m_selection_rect[1].x, m_selection_rect[1].y, 0.f }, color },
		{ { m_selection_rect[0].x, m_selection_rect[1].y, 0.f }, color }
	};
	std::vector<GLuint> indices { 0, 1, 1, 2, 2, 3, 3, 0 };
	m_ui_vao.update_buffers(vertices, indices);
}

void g::Spline::update_curve_vao()
{
	const glm::vec3 color { 0.f, 0.5f, 0.5f };
	std::vector<Vertex_PNC> vertices(m_curve_pts.size()*4);
	std::vector<GLuint> indices;
	constexpr float R = 0.1f;
	const glm::vec3 up { 0.f, 1.f, 0.f };
	glm::vec3 last_binormal { 0.f, 0.f, -1.f };
	for (unsigned i = 0; i < m_curve_pts.size(); ++i) {
		glm::vec3 binormal = glm::cross(m_curve_pts[i].tangent, up);
		if (glm::length(binormal) > 0.01f) {
			binormal = glm::normalize(binormal);
			last_binormal = binormal;
		} else {
			binormal = last_binormal;
		}
		const glm::vec3 normal = glm::normalize(glm::cross(binormal, m_curve_pts[i].tangent));
		const int k = 4*i;
		vertices[k].position = m_curve_pts[i].position - binormal*R;
		vertices[k + 1].position = m_curve_pts[i].position + binormal*R;
		vertices[k + 2].position = vertices[k].position + normal*R;
		vertices[k + 3].position = vertices[k + 1].position + normal*R;
		vertices[k].color = color;
		vertices[k + 1].color = color;
		vertices[k + 2].color = color;
		vertices[k + 3].color = color;
		const glm::vec3 center = m_curve_pts[i].position + normal*R;
		for (int j = 0; j < 4; ++j) {
			vertices[k + j].normal = glm::normalize(center - vertices[k + j].position);
		}
	}
	const int pattern[18] = { 0, 4, 1, 1, 4, 5, 1, 5, 3, 3, 5, 7, 0, 4, 2, 2, 4, 6 };
	for (unsigned i = 1; i < m_curve_pts.size(); ++i) {
		const int k = (i - 1)*4;
		for (int j = 0; j < 18; ++j) {
			indices.push_back(k + pattern[j]);
		}
	}
	m_curve_vao.update_buffers(vertices, indices);
}

void g::Spline::add_pt(const glm::vec3 &p)
{
	m_control_pts.push_back(p);
	if (m_control_pts.size() <= 1)
		return;
	m_curve_pts.clear();
	calc_spline3(m_control_pts, m_curve_pts);
	update_control_vao();
	if (m_curve_pts.empty())
		return;
	update_curve_vao();
	// calculate path length
	{
		m_curve_pts[0].distance = 0.f;
		for (unsigned i = 1; i < m_curve_pts.size(); ++i) {
				const float delta = glm::distance(m_curve_pts[i - 1].position, m_curve_pts[i].position);
			m_curve_pts[i].distance = m_curve_pts[i - 1].distance + delta;
		}
	}
}

void g::Spline::edit_click_place()
{
	static glm::vec3 last_placement { 0.f, 0.f, 0.f };
	glm::vec3 p { g::mouse.x(), g::mouse.y(), 0.f };
	const float zoom = g::camera_ortho.zoom();
	p.x = (2.f*(p.x / g::canvas_width) - 1.f)*zoom;
	p.y = -(2.f*(p.y / g::canvas_height) - 1.f)*zoom;
	if (g::canvas_width > g::canvas_height) {
		const float aspect = static_cast<float>(g::canvas_height) / g::canvas_width;
		p.y *= aspect;
	} else {
		const float aspect = static_cast<float>(g::canvas_width) / g::canvas_height;
		p.x *= aspect;
	}
	if (g::camera_ortho.side() == g::CameraOrtho::TOP || g::camera_ortho.side() == g::CameraOrtho::BOTTOM) {
		p.y = -p.y;
	}
	if (g::camera_ortho.side() == g::CameraOrtho::FRONT || g::camera_ortho.side() == g::CameraOrtho::BACK) {
		p.x = -p.x;
	}
	{
		const glm::mat4 &mv =g::camera_ortho.transformation();
		glm::vec4 v4 { p.x, p.y, p.z, 1. };
		v4 = mv*v4;
		p.x = v4.x;
		p.y = v4.y;
		p.z = v4.z;
		switch (g::camera_ortho.side()) {
		case g::CameraOrtho::RIGHT:
		case g::CameraOrtho::LEFT:
			p.z = last_placement.z;
			break;
		case g::CameraOrtho::TOP:
		case g::CameraOrtho::BOTTOM:
			p.y = last_placement.y;
			break;
		default:
			p.x = last_placement.x;
		}
	}
	last_placement = p;
	add_pt(p);
}

void g::Spline::edit_click_start_drag()
{
	m_show_ui = true;
	m_selection_rect[0] = g::mouse.get_ui_coordinates();
	m_selection_rect[1] = g::mouse.get_ui_coordinates();
	update_ui_vao();
}

void g::Spline::edit_click_drag()
{
	m_selection_rect[1] = g::mouse.get_ui_coordinates();
	update_ui_vao();
}

void g::Spline::edit_click_stop_drag()
{
	m_selection_rect[1] = g::mouse.get_ui_coordinates();
	m_show_ui = false;
}

void g::Spline::edit_click()
{
	if (! g::is_edit_mode)
		return;
	if (! g::camera.is_camera_ortho())
		return;
	if (m_place_when_click) {
		edit_click_place();
		m_place_when_click = false;
	} else {
		edit_click_start_drag();
	}
}

void g::Spline::edit_mouse_move()
{
	if (! g::is_edit_mode)
		return;
	if (! g::camera.is_camera_ortho())
		return;
	if (! m_place_when_click) {
		edit_click_drag();
	}
}

void g::Spline::edit_unclick()
{
	if (! g::is_edit_mode)
		return;
	if (! g::camera.is_camera_ortho())
		return;
	if (! m_place_when_click) {
		edit_click_stop_drag();
	}
}
