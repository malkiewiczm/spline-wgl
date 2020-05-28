#include "camera.hpp"
#include "glm/gtx/quaternion.hpp"
#include "cart.hpp"

g::Camera g::camera;
g::Camera3d g::camera_3d;
g::CameraOrtho g::camera_ortho;

void g::Camera::init()
{
	m_kind = CAMERA_3D;
}

glm::mat4 g::Camera::calc_projection()
{
	switch (m_kind) {
	case CAMERA_ORTHO: {
		const float zoom = g::camera_ortho.zoom();
		glm::mat4 proj = glm::ortho(-zoom, zoom, -zoom, zoom, -50.f, 50.f);
		if (g::canvas_width > g::canvas_height) {
			return glm::scale(proj, glm::vec3(1.f, g::aspectx(), 1.f));
		} else {
			return glm::scale(proj, glm::vec3(g::aspecty(), 1.f, 1.f));
		}
	}
	default: {
		constexpr float fov = TORAD(45.f);
		return glm::perspective(fov, g::aspectx(), 0.1f, 200.f);
	}
	}
}

glm::mat4 g::Camera::calc_view()
{
	switch (m_kind) {
	case CAMERA_3D: {
		glm::mat4 m = glm::mat4_cast(g::camera_3d.rotation());
		return glm::translate(m, -g::camera_3d.position());
	}
	case CAMERA_ORTHO:
		return g::camera_ortho.transformation();
	case CAMERA_LOOKAT:
		return glm::lookAt(g::camera_3d.position(), m_looking_at, glm::vec3(0.f, 1.f, 0.f));
	case CAMERA_POV: {
		const glm::vec3 offset { 0.f, -0.6f, 0.4f };
		return glm::translate(glm::mat4(1.f), offset)*g::cart.get_transform_inv();
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
}

void g::Camera3d::rotate_x(const float angle)
{
	glm::quat q = glm::angleAxis(angle, glm::vec3(1.f, 0.f, 0.f));
	m_rotation = q*m_rotation;
}

void g::Camera3d::rotate_y(const float angle)
{
	glm::quat q = glm::angleAxis(angle, glm::vec3(0.f, 1.f, 0.f));
	m_rotation *= q;
}

void g::Camera3d::rotate_z(const float angle)
{
	glm::quat q = glm::angleAxis(angle, glm::vec3(0.f, 0.f, 1.f));
	m_rotation = q*m_rotation;
}

void g::Camera3d::reset()
{
	m_position = { 0.f, 0.f, 50.f };
	m_rotation = { 1.f, 0.f, 0.f, 0.f };
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
	m_ortho_rotations[FRONT] = glm::rotate(glm::mat4(1.f), d270, y_axis);
	m_ortho_rotations[BACK] = glm::rotate(glm::mat4(1.f), d90, y_axis);
	reset();
}

const glm::mat4 &g::CameraOrtho::transformation() const
{
	return m_ortho_rotations[m_side];
}

void g::CameraOrtho::reset()
{
	m_side = RIGHT;
	m_zoom = 50.f;
	m_translation.x = 0.f;
	m_translation.y = 0.f;
}
