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
}

void g::camera3d::rotate_y(const float angle)
{
	glm::quat q = glm::angleAxis(angle, glm::vec3(0.f, 1.f, 0.f));
	g::camera3d::rotation = q*g::camera3d::rotation;
}

void g::camera3d::rotate_z(const float angle)
{
	glm::quat q = glm::angleAxis(angle, glm::vec3(0.f, 0.f, 1.f));
	g::camera3d::rotation = q*g::camera3d::rotation;
}

bool g::camera3d::enabled;
glm::vec3 g::camera3d::position;
glm::quat g::camera3d::rotation;
