#include "spline.hpp"
#include "camera.hpp"
#include "mouse.hpp"
#include <algorithm>

g::Spline g::spline;

void g::Spline::init()
{
	std::vector<Vertex_PC> vertex_data {
		{ { 0.273279f, 1.050624f, -2.005395f }, { 0.89596240119633f, 0.82284005249184f, 0.7466048158208f } },
		{ { -0.857576f, -0.598839f, -2.026340f }, { 0.17410809656056f, 0.85894344920194f, 0.71050141911069f } },
		{ { 1.472728f, 0.180840f, 1.731609f }, { 0.5135349589526f, 0.30399487289041f, 0.014984588152715f } },
		{ { 0.341872f, -1.468623f, 1.710664f }, { 0.091402935880612f, 0.36445204016236f, 0.14731284524064f } },
		{ { -0.341872f, 1.468623f, -1.710664f }, { 0.16589861751152f, 0.98852504043703f, 0.44569231238746f } },
		{ { -1.472728f, -0.180840f, -1.731609f }, { 0.11908322397534f, 0.0046693319498276f, 0.0089114047669912f } },
		{ { 0.857576f, 0.598839f, 2.026340f }, { 0.3778801843318f, 0.53166295358135f, 0.57118442335276f } },
		{ { -0.273279f, -1.050624f, 2.005395f }, { 0.60176396984771f, 0.60716574602496f, 0.16623432111576f } }
	};
	std::vector<GLuint> index_data {
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 1, 3, 7, 0, 2, 3, 4, 0, 1
	};
	m_control_vao.gen_buffers();
	m_control_vao.draw_mode(GL_LINE_STRIP);
	m_control_vao.update_buffers(vertex_data, index_data);
	m_control_vao.kind(VAO::KIND_PC);
	m_curve_vao.gen_buffers();
	m_curve_vao.draw_mode(GL_LINE_STRIP);
	m_curve_vao.update_buffers(vertex_data, index_data);
	m_curve_vao.kind(VAO::KIND_PC);
}

void g::Spline::draw()
{
	if (m_show_control_mesh)
		m_control_vao.draw();
	m_curve_vao.draw();
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

void g::Spline::add_pt(const glm::vec3 &p)
{
	m_control_pts.push_back(p);
	if (m_control_pts.size() <= 1)
		return;
	const glm::vec3 control_color { 0.5f, 0.f, 0.f };
	const glm::vec3 curve_color { 0.f, 0.5f, 0.5f };
	m_curve_pts.clear();
	calc_spline3(m_control_pts, m_curve_pts);
	std::vector<Vertex_PC> vertices(m_control_pts.size());
	std::vector<GLuint> indices(vertices.size());
	for (unsigned i = 0; i < vertices.size(); ++i) {
		vertices[i].position = m_control_pts[i];
		vertices[i].color = control_color;
	}
	for (unsigned i = 0; i < indices.size(); ++i) {
		indices[i] = i;
	}
	m_control_vao.update_buffers(vertices, indices);
	if (m_curve_pts.empty())
		return;
	vertices.resize(m_curve_pts.size());
	indices.resize(vertices.size());
	for (unsigned i = 0; i < vertices.size(); ++i) {
		vertices[i].position = m_curve_pts[i].position;
		vertices[i].color = curve_color;
	}
	for (unsigned i = 0; i < indices.size(); ++i) {
		indices[i] = i;
	}
	// calculate path length
	{
		m_curve_pts[0].distance = 0.f;
		for (unsigned i = 1; i < m_curve_pts.size(); ++i) {
				const float delta = glm::distance(m_curve_pts[i - 1].position, m_curve_pts[i].position);
			m_curve_pts[i].distance = m_curve_pts[i - 1].distance + delta;
		}
	}
	m_curve_vao.update_buffers(vertices, indices);
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

void g::Spline::edit_click()
{
	if (! g::is_edit_mode)
		return;
	if (! g::camera.is_camera_ortho())
		return;
	if (m_place_when_click) {
		edit_click_place();
		m_place_when_click = false;
	}
}
