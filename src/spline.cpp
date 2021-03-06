#include "spline.hpp"
#include "camera.hpp"
#include "mouse.hpp"
#include <algorithm>
#include "obj_loader.hpp"

g::Spline g::spline;

void g::Spline::init()
{
	m_edit_mode = EM_SELECT;
	m_show_control_mesh = true;
	m_show_ui = false;
	m_control_vao.init(GL_LINES);
	m_control_vao.update_buffers({ { glm::vec3(-5.f), glm::vec3(1.f, 0., 0.f) }, { glm::vec3(5.f), glm::vec3(0.f, 0., 1.f) } }, { 0, 1 });
	m_track_vao.init(GL_TRIANGLES);
	load_object_PNC(g::obj::track, glm::vec3(0.f, 0.5f, 0.5f), m_track_vao);
	m_ui_vao.init(GL_LINES);
	m_ui_vao.update_buffers({ { glm::vec3(-0.5f), glm::vec3(1.f) }, { glm::vec3(0.5f), glm::vec3(0.f) } }, { 0, 1 });
	m_track_pieces.clear();
}

template<int deg>
static g::Spline::Piece decasteljau(const glm::vec3 c[deg + 1], const float u)
{
	static_assert(deg >= 2, "degree must be at least 2");
	const float v = 1.f - u;
	glm::vec3 dp[deg + 1];
	for (int i = 0; i <= deg; ++i) {
		dp[i] = c[i];
	}
	for (int d = deg; d >= 3; --d) {
		for (int i = 0; i < d; ++i) {
			dp[i] = dp[i]*v + dp[i + 1]*u;
		}
	}
	// d = 2
	const glm::vec3 d2 = glm::normalize(dp[2] - 2.f*dp[1] + dp[0]);
	for (int i = 0; i < 2; ++i) {
		dp[i] = dp[i]*v + dp[i + 1]*u;
	}
	// d = 1
	g::Spline::Piece ret;
	ret.position = dp[0]*v + dp[1]*u;
	ret.tangent = glm::normalize(dp[1] - dp[0]);
	ret.binormal = glm::normalize(glm::cross(ret.tangent, d2));
	ret.normal = glm::normalize(glm::cross(ret.binormal, ret.tangent));
	return ret;
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

static void calc_spline3(const std::vector<g::Spline::ControlPoint> &m_control_pts, std::vector<g::Spline::Piece> &pts)

{
	if (m_control_pts.size() < 4)
		return;
	constexpr int deg = 3;
	std::vector<glm::vec3> c((m_control_pts.size() - 3)*deg + 1);
	const unsigned last_i = m_control_pts.size() - 2;
	for (unsigned i = 1; ; ++i) {
		const glm::vec3 &am = m_control_pts[i - 1].position;
		const glm::vec3 &a = m_control_pts[i].position;
		const glm::vec3 &ap = m_control_pts[i + 1].position;
		const int b = (i - 1)*deg;
		const glm::vec3 r0 = glm::mix(am, a, 2.f/3.f);
		const glm::vec3 r1 = glm::mix(a, ap, 1.f/3.f);
		c[b] = glm::mix(r0, r1, 0.5f);
		if (i == last_i)
			break;
		c[b + 1] = r1;
		c[b + 2] = glm::mix(a, ap, 2.f/3.f);
	}
	for (unsigned i = deg; i < c.size(); i += deg) {
		const glm::vec3 l_c[deg + 1] { c[i - 3], c[i - 2], c[i - 1], c[i] };
		append_bezier<deg>(pts, l_c);
	}
}

static bool cmp_distance(const g::Spline::Piece &p, const float d)
{
	return p.distance < d;
}

g::Spline::Piece g::Spline::get_piece(const float distance)
{
	if (m_curve_pts.size() <= 1) {
		Piece ret;
		ret.distance = distance;
		ret.position = glm::vec3(0.f);
		ret.tangent = glm::vec3(1.f, 0.f, 0.f);
		ret.normal = glm::vec3(0.f, 1.f, 0.f);
		ret.binormal = glm::vec3(0.f, 0.f, 1.f);
		return ret;
	}
	auto iter = std::lower_bound(m_curve_pts.begin(), m_curve_pts.end(), distance, cmp_distance);
	if (iter == m_curve_pts.begin()) {
		// implies that a negative distance was given
		Piece p = m_curve_pts.front();
		p.distance = distance;
		p.position = p.position + p.tangent*distance;
		return p;
	} else if (iter == m_curve_pts.end()) {
		// implies that a distance greater than the curve length was given
		Piece p = m_curve_pts.back();
		p.position = p.position + p.tangent*(distance - p.distance);
		p.distance = distance;
		return p;
	} else {
		const Piece &p0 = *(iter - 1);
		const Piece &p1 = *iter;
		const float t = (distance - p0.distance) / (p1.distance - p0.distance);
		Piece p;
		p.distance = distance;
		p.tangent = glm::mix(p0.tangent, p1.tangent, t);
		p.normal = glm::mix(p0.normal, p1.normal, t);
		p.binormal = glm::mix(p0.binormal, p1.binormal, t);
		p.position = glm::mix(p0.position, p1.position, t);
		return p;
	}
}

void g::Spline::update_control_vao()
{
	const glm::vec3 polygon_color { 0.5f, 0.f, 0.f };
	const glm::vec3 box_color { 0.f, 0.f, 0.5f };
	const glm::vec3 box_color_selected { 1.f, 1.f, 1.f };
	std::vector<Vertex_PC> vertices;
	std::vector<GLuint> indices;
	std::vector<glm::vec3> cube_corners(8);
	std::vector<GLuint> cube_indices {
		0, 1, 1, 5, 5, 4, 4, 0,
		2, 3, 3, 7, 7, 6, 6, 2,
		2, 0, 3, 1, 7, 5, 6, 4,
	};
	for (int i = 0; i < 8; ++i) {
		constexpr float R = 0.5f;
		cube_corners[i].x = (i & 1) ? R : -R;
		cube_corners[i].y = ((i >> 1) & 1) ? R : -R;
		cube_corners[i].z = ((i >> 2) & 1) ? R : -R;
	}
	for (unsigned i = 0; i < m_control_pts.size(); ++i) {
		vertices.push_back({ m_control_pts[i].position, polygon_color });
		glm::vec3 color;
		if (std::find(m_selection.begin(), m_selection.end(), i) != m_selection.end()) {
			color = box_color_selected;
		} else {
			color = box_color;
		}
		for (int k = 0; k < 8; ++k) {
			vertices.push_back({ m_control_pts[i].position + cube_corners[k], color });
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

void g::Spline::update_ui_select_vao()
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

void g::Spline::update_ui_move_vao()
{
	const glm::vec3 color(0.f);
	std::vector<Vertex_PC> vertices {
		{ { m_selection_rect[0].x, m_selection_rect[0].y, 0.f }, color },
		{ { m_selection_rect[1].x, m_selection_rect[1].y, 0.f }, color }
	};
	std::vector<GLuint> indices { 0, 1 };
	m_ui_vao.update_buffers(vertices, indices);
}

void g::Spline::update_ui_insert_vao()
{
	const glm::vec3 color(0.f);
	const glm::vec2 v = g::mouse.get_ui_coordinates();
	constexpr float Rx = 0.02f;
	const float Ry = Rx*g::aspectx();
	std::vector<Vertex_PC> vertices {
		{ { v.x - Rx, v.y - Ry, 0.f }, color },
		{ { v.x + Rx, v.y + Ry, 0.f }, color },
		{ { v.x + Rx, v.y - Ry, 0.f }, color },
		{ { v.x - Rx, v.y + Ry, 0.f }, color },
	};
	std::vector<GLuint> indices { 0, 1, 2, 3 };
	m_ui_vao.update_buffers(vertices, indices);
}

void g::Spline::update_track_transforms()
{
	m_track_pieces.clear();
	constexpr float PIECE_SIZE = 1.0f;
	float current_pos = 0.f;
	for (unsigned i = 0; i < m_curve_pts.size(); ++i) {
		const Piece &piece = m_curve_pts[i];
		if (current_pos >= piece.distance) {
			const glm::mat4 rotation = make_matrix(piece.tangent, piece.normal, piece.binormal);
			const glm::mat4 translation = glm::translate(glm::mat4(1.f), glm::vec3(piece.position));
			m_track_pieces.push_back(translation*rotation);
			current_pos += PIECE_SIZE;
		}
	}
}

void g::Spline::recalculate_curve_all()
{
	if (m_control_pts.empty())
		return;
	m_curve_pts.clear();
	calc_spline3(m_control_pts, m_curve_pts);
	update_control_vao();
	if (m_curve_pts.empty())
		return;
	// calculate path length
	{
		m_curve_pts[0].distance = 0.f;
		for (unsigned i = 1; i < m_curve_pts.size(); ++i) {
				const float delta = glm::distance(m_curve_pts[i - 1].position, m_curve_pts[i].position);
			m_curve_pts[i].distance = m_curve_pts[i - 1].distance + delta;
		}
	}
	update_track_transforms();
}

void g::Spline::add_pt(const glm::vec3 &p)
{
#ifdef HAS_ROLL
	m_control_pts.push_back({ p, 0.f });
#else
	m_control_pts.push_back({ p });
#endif
	recalculate_curve_all();
}

static glm::vec3 to_planar(const glm::vec2 &p_in)
{
	const float zoom = g::camera_ortho.zoom();
	glm::vec3 p { p_in.x*zoom, p_in.y*zoom, 0.f };
	if (g::canvas_width > g::canvas_height) {
		p.y *= g::aspecty();
	} else {
		p.x *= g::aspectx();
	}
	if (g::camera_ortho.side() == g::CameraOrtho::TOP || g::camera_ortho.side() == g::CameraOrtho::BOTTOM) {
		p.y = -p.y;
	}
	if (g::camera_ortho.side() == g::CameraOrtho::FRONT || g::camera_ortho.side() == g::CameraOrtho::BACK) {
		p.x = -p.x;
	}
	return p;
}

void g::Spline::edit_click_place()
{
	static glm::vec3 last_placement { 0.f, 0.f, 0.f };
	glm::vec3 p = to_planar(g::mouse.get_ui_coordinates());
	const glm::mat4 &mv = g::camera_ortho.transformation();
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
	last_placement = p;
	add_pt(p);
}

void g::Spline::edit_click_start_select()
{
	m_show_ui = true;
	m_selection_rect[0] = g::mouse.get_ui_coordinates();
	m_selection_rect[1] = m_selection_rect[0];
	update_ui_select_vao();
}

void g::Spline::edit_click_select()
{
	m_selection_rect[1] = g::mouse.get_ui_coordinates();
	update_ui_select_vao();
}

static bool AABB(float x, float y, float left, float right, float bottom, float top)
{
	return (x >= left && x <= right) && (y >= bottom && y <= top);
}

void g::Spline::edit_click_stop_select()
{
	m_selection_rect[1] = g::mouse.get_ui_coordinates();
	m_show_ui = false;
	m_selection.clear();
	float left, right, top, bottom;
	if (m_selection_rect[0].x > m_selection_rect[1].x) {
		left = m_selection_rect[1].x;
		right = m_selection_rect[0].x;
	} else {
		left = m_selection_rect[0].x;
		right = m_selection_rect[1].x;
	}
	if (m_selection_rect[0].y > m_selection_rect[1].y) {
		bottom = m_selection_rect[1].y;
		top = m_selection_rect[0].y;
	} else {
		bottom = m_selection_rect[0].y;
		top = m_selection_rect[1].y;
	}
	const glm::mat4 view = g::camera.calc_view();
	const glm::mat4 proj = g::camera.calc_projection();
	for (unsigned i = 0; i < m_control_pts.size(); ++i) {
		const glm::vec3 &cp3 = m_control_pts[i].position;
		glm::vec4 cp { cp3.x, cp3.y, cp3.z, 1.f };
		cp = view*cp;
		cp = proj*cp;
		if (AABB(cp.x / cp.w, cp.y / cp.w, left, right, bottom, top)) {
			m_selection.push_back(i);
		}
	}
	update_control_vao();
}

void g::Spline::edit_click_start_move()
{
	m_show_ui = true;
	m_selection_rect[0] = g::mouse.get_ui_coordinates();
	m_selection_rect[1] = m_selection_rect[0];
	m_original_control_pts.resize(m_selection.size());
	for (unsigned i = 0; i < m_selection.size(); ++i) {
		const int k = m_selection[i];
		m_original_control_pts[i] = m_control_pts[k];
	}
	update_ui_move_vao();
}

void g::Spline::edit_click_move()
{
	m_selection_rect[1] = g::mouse.get_ui_coordinates();
	update_ui_move_vao();
	const glm::vec2 diff = m_selection_rect[1] - m_selection_rect[0];
	glm::vec3 p = to_planar(diff);
	const glm::mat4 &mv = g::camera_ortho.transformation();
	glm::vec4 v4 { p.x, p.y, p.z, 1. };
	v4 = mv*v4;
	p.x = v4.x;
	p.y = v4.y;
	p.z = v4.z;
	for (unsigned i = 0; i < m_selection.size(); ++i) {
		const int k = m_selection[i];
#ifdef HAS_ROLL
		m_control_pts[k] = { m_original_control_pts[i].position + p, m_original_control_pts[i].roll };
#else
		m_control_pts[k] = { m_original_control_pts[i].position + p };
#endif
	}
	recalculate_curve_all();
}

void g::Spline::edit_click_stop_move()
{
	m_show_ui = false;
	edit_click_move();
}

void g::Spline::edit_click()
{
	if (! g::is_edit_mode)
		return;
	if (g::mouse.locked())
		return;
	switch (m_edit_mode) {
	case EM_SELECT:
		edit_click_start_select();
		break;
	case EM_INSERT:
		if (g::camera.is_camera_ortho()) {
			edit_click_place();
		}
		break;
	case EM_MOVE:
		if (g::camera.is_camera_ortho()) {
			edit_click_start_move();
		}
		break;
	}
}

void g::Spline::edit_mouse_move()
{
	if (! g::is_edit_mode)
		return;
	if (g::mouse.locked())
		return;
	switch (m_edit_mode) {
	case EM_SELECT:
		if (g::mouse.down()) {
			edit_click_select();
		}
		break;
	case EM_INSERT:
		if (g::camera.is_camera_ortho()) {
			update_ui_insert_vao();
		}
		break;
	case EM_MOVE:
		if (g::mouse.down() && g::camera.is_camera_ortho()) {
			edit_click_move();
		}
		break;
	}
}

void g::Spline::edit_unclick()
{
	if (! g::is_edit_mode)
		return;
	if (g::mouse.locked())
		return;
	switch (m_edit_mode) {
	case EM_SELECT:
		edit_click_stop_select();
		break;
	case EM_INSERT:
		break;
	case EM_MOVE:
		if (g::camera.is_camera_ortho()) {
			edit_click_stop_move();
		}
		break;
	}
}

void g::Spline::edit_mode(EditMode l_edit_mode)
{
	m_edit_mode = l_edit_mode;
	switch (m_edit_mode) {
	case EM_SELECT:
		m_show_ui = false;
		break;
	case EM_INSERT:
		m_show_ui = true;
		update_ui_insert_vao();
		break;
	case EM_MOVE:
		m_show_ui = false;
		break;
	}
}

void g::Spline::edit_delete_selected()
{
	std::sort(m_selection.begin(), m_selection.end(), std::greater<int>());
	for (unsigned i = 0; i < m_selection.size(); ++i) {;
		m_control_pts.erase(m_control_pts.begin() + m_selection[i]);
	}
	m_selection.clear();
	recalculate_curve_all();
}

void g::Spline::edit_select_all()
{
	m_selection.resize(m_control_pts.size());
	for (unsigned i = 0; i < m_control_pts.size(); ++i) {
		m_selection[i] = i;
	}
	update_control_vao();
}
