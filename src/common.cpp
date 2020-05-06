#include "common.hpp"
#include "camera.hpp"

void _die(const char *msg, const char *file, int line)
{
	printf("error: %s (%s:%d)\n", msg, file, line);
	abort();
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
		glm::mat4 proj(1.f);
		if (g::canvas_width > g::canvas_height) {
			const float aspect = static_cast<float>(g::canvas_width) / g::canvas_height;
			glm::scale(proj, { 1.f, aspect, 1.f });
		} else {
			const float aspect = static_cast<float>(g::canvas_height) / g::canvas_width;
			glm::scale(proj, { aspect, 1.f, 1.f });
		}
		proj = glm::scale(proj, glm::vec3(0.2f));
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
		constexpr float d90 = TORAD(90.f);
		constexpr float d180 = TORAD(180.f);
		constexpr float d270 = TORAD(270.f);
		glm::mat4 mv(1.f);
		switch (g::camera_ortho_side) {
		case g::ORTHO_LEFT:
			mv = glm::rotate(mv, d180, { 0.f, 1.f, 0.f });
			break;
		case g::ORTHO_TOP:
			mv = glm::rotate(mv, d90, { 1.f, 0.f, 0.f });
			break;
		case g::ORTHO_BOTTOM:
			mv = glm::rotate(mv, d270, { 1.f, 0.f, 0.f });
			break;
		case g::ORTHO_FRONT:
			mv = glm::rotate(mv, d90, { 0.f, 1.f, 0.f });
			break;
		case g::ORTHO_BACK:
			mv = glm::rotate(mv, d270, { 0.f, 1.f, 0.f });
			break;
		default:
			// ORTHO_RIGHT is no rotation
			break;
		}
		glUniformMatrix4fv(g::u_modelview, 1, false, &mv[0][0]);
	}
}

GLuint g::standard_shader;
int g::canvas_width;
int g::canvas_height;
GLuint g::u_projection;
GLuint g::u_modelview;
int g::camera_ortho_side;
bool g::is_edit_mode;
