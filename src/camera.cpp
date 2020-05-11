#include "camera.hpp"
#include "shader.hpp"
#include "glm/gtx/quaternion.hpp"

g::Camera g::camera;
g::Camera3d g::camera_3d;
g::CameraOrtho g::camera_ortho;

void g::Camera::init()
{
	m_kind = CAMERA_3D;
	m_dirty_projection = true;
	m_dirty_modelview = true;
}

void g::Camera::kind(CameraKind l_kind)
{
	m_kind = l_kind;
	update_modelview();
	update_projection();
}

void g::Camera::looking_at(const glm::vec3 &l_looking_at)
{
	m_looking_at = l_looking_at;
	update_modelview();
}

void g::Camera::update_projection()
{
	m_dirty_projection = true;
}

void g::Camera::update_modelview()
{
	m_dirty_modelview = true;
}

void g::Camera::flush_projection()
{
	if (! m_dirty_projection)
		return;
	m_dirty_projection = false;
	switch (m_kind) {
	case CAMERA_ORTHO: {
		const float zoom = g::camera_ortho.zoom();
		glm::mat4 proj = glm::ortho(-zoom, zoom, -zoom, zoom, -50.f, 50.f);
		if (g::canvas_width > g::canvas_height) {
			const float aspect = static_cast<float>(g::canvas_width) / g::canvas_height;
			proj = glm::scale(proj, glm::vec3(1.f, aspect, 1.f));
		} else {
			const float aspect = static_cast<float>(g::canvas_height) / g::canvas_width;
			proj = glm::scale(proj, glm::vec3(aspect, 1.f, 1.f));
		}
		glUniformMatrix4fv(g::shaders.u_projection(), 1, false, &proj[0][0]);
		break;
	}
	default: {
		constexpr float fov = TORAD(45.f);
		const float aspect = static_cast<float>(g::canvas_width) / g::canvas_height;
		glm::mat4 proj = glm::perspective(fov, aspect, 0.1f, 200.f);
		glUniformMatrix4fv(g::shaders.u_projection(), 1, false, &proj[0][0]);
	}
	}
}

void g::Camera::flush_modelview()
{
	if (! m_dirty_modelview)
		return;
	m_dirty_modelview = false;
	switch (m_kind) {
	case CAMERA_3D: {
		glm::mat4 mv = glm::mat4_cast(g::camera_3d.rotation());
		mv = glm::translate(mv, g::camera_3d.position());
		glUniformMatrix4fv(g::shaders.u_modelview(), 1, false, &mv[0][0]);
		break;
	}
	case CAMERA_ORTHO: {
		const glm::mat4 &mv = g::camera_ortho.transformation();
		glUniformMatrix4fv(g::shaders.u_modelview(), 1, false, &mv[0][0]);
		break;
	}
	case CAMERA_LOOKAT: {
		const glm::mat4 &mv = glm::lookAt(-g::camera_3d.position(), m_looking_at, glm::vec3(0.f, 1.f, 0.f));
		glUniformMatrix4fv(g::shaders.u_modelview(), 1, false, &mv[0][0]);
		break;
	}
	}
}

void g::Camera3d::init()
{
	reset();
}

void g::Camera3d::move_relative(const glm::vec3 &v)
{
	const glm::vec3 rv = glm::rotate(glm::conjugate(m_rotation), v);
	m_position += rv;
	g::camera.update_modelview();
}

void g::Camera3d::rotate_x(const float angle)
{
	glm::quat q = glm::angleAxis(angle, glm::vec3(1.f, 0.f, 0.f));
	m_rotation = q*m_rotation;
	g::camera.update_modelview();
}

void g::Camera3d::rotate_y(const float angle)
{
	glm::quat q = glm::angleAxis(angle, glm::vec3(0.f, 1.f, 0.f));
	m_rotation *= q;
	g::camera.update_modelview();
}

void g::Camera3d::rotate_z(const float angle)
{
	glm::quat q = glm::angleAxis(angle, glm::vec3(0.f, 0.f, 1.f));
	m_rotation = q*m_rotation;
	g::camera.update_modelview();
}

void g::Camera3d::reset()
{
	m_position = { 0.f, 0.f, -50.f };
	m_rotation = { 1.f, 0.f, 0.f, 0.f };
	g::camera.update_modelview();
}

void g::CameraOrtho::init()
{
	constexpr float d90 = TORAD(90.f);
	constexpr float d180 = TORAD(180.f);
	constexpr float d270 = TORAD(270.f);
	const glm::vec3 x_axis { 1.f, 0.f, 0.f };
	const glm::vec3 y_axis { 0.f, 1.f, 0.f };
	m_ortho_rotations[RIGHT] = glm::mat4(1.f);
	m_ortho_rotations[LEFT] = glm::rotate(glm::mat4(1.f), d180, y_axis);
	m_ortho_rotations[TOP] = glm::rotate(glm::mat4(1.f), d90, x_axis);
	m_ortho_rotations[BOTTOM] = glm::rotate(glm::mat4(1.f), d270, x_axis);
	m_ortho_rotations[FRONT] = glm::rotate(glm::mat4(1.f), d90, y_axis);
	m_ortho_rotations[BACK] = glm::rotate(glm::mat4(1.f), d270, y_axis);
	reset();
}

const glm::mat4 &g::CameraOrtho::transformation() const
{
	return m_ortho_rotations[m_side];
}

void g::CameraOrtho::side(OrthoSide l_side)
{
	if (l_side == m_side)
		return;
	m_side = l_side;
	g::camera.update_modelview();
}

void g::CameraOrtho::reset()
{
	m_side = RIGHT;
	m_zoom = 50.f;
	m_translation.x = 0.f;
	m_translation.y = 0.f;
	g::camera.update_modelview();
}
