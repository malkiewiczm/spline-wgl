#include "camera.hpp"
#include "glm/gtx/quaternion.hpp"

using namespace g::camera3d;

void g::camera3d::move_relative(const glm::vec3 &v)
{
	const glm::vec3 rv = glm::rotate(glm::conjugate(g::camera3d::rotation), v);
	g::camera3d::position += rv;
	//g::camera3d::position += v;
}

void g::camera3d::rotate_x(const float angle)
{
	glm::quat q = glm::angleAxis(angle, glm::vec3(1.f, 0.f, 0.f));
	g::camera3d::rotation = q*g::camera3d::rotation;
	//g::camera3d::rotation *= q;
}

void g::camera3d::rotate_y(const float angle)
{
	glm::quat q = glm::angleAxis(angle, glm::vec3(0.f, 1.f, 0.f));
	//g::camera3d::rotation = q*g::camera3d::rotation;
	g::camera3d::rotation *= q;
}

void g::camera3d::rotate_z(const float angle)
{
	glm::quat q = glm::angleAxis(angle, glm::vec3(0.f, 0.f, 1.f));
	g::camera3d::rotation = q*g::camera3d::rotation;
}

void g::camera3d::reset()
{
	g::camera3d::position = { 0.f, 0.f, -5.f };
	g::camera3d::rotation = { 1.f, 0.f, 0.f, 0.f };
}


static bool dirty_projection = true;
static bool dirty_modelview = true;

void update_projection()
{
	dirty_projection = true;
}

void update_modelview()
{
	dirty_modelview = true;
}

void flush_projection()
{
	if (! dirty_projection)
		return;
	dirty_projection = false;
	if (g::camera3d::enabled) {
		constexpr float fov = TORAD(45.f);
		const float aspect = static_cast<float>(g::canvas_width) / g::canvas_height;
		glm::mat4 proj = glm::perspective(fov, aspect, 0.1f, 100.f);
		glUniformMatrix4fv(g::u_projection, 1, false, &proj[0][0]);
	} else {
		constexpr float R = 5.f;
		glm::mat4 proj = glm::ortho(-R, R, -R, R, -50.f, 50.f);
		if (g::canvas_width > g::canvas_height) {
			const float aspect = static_cast<float>(g::canvas_width) / g::canvas_height;
			proj = glm::scale(proj, glm::vec3(1.f, aspect, 1.f));
		} else {
			const float aspect = static_cast<float>(g::canvas_height) / g::canvas_width;
			proj = glm::scale(proj, glm::vec3(aspect, 1.f, 1.f));
		}
		glUniformMatrix4fv(g::u_projection, 1, false, &proj[0][0]);
	}
}

void flush_modelview()
{
	if (! dirty_modelview)
		return;
	dirty_modelview = false;
	if (g::camera3d::enabled) {
		glm::mat4 mv = glm::mat4_cast(g::camera3d::rotation);
		mv = glm::translate(mv, g::camera3d::position);
		glUniformMatrix4fv(g::u_modelview, 1, false, &mv[0][0]);
	} else {
		const glm::mat4 &mv = g::ortho_rotations[g::camera_ortho_side];
		glUniformMatrix4fv(g::u_modelview, 1, false, &mv[0][0]);
	}
}

bool g::camera3d::enabled;
glm::vec3 g::camera3d::position;
glm::quat g::camera3d::rotation;
