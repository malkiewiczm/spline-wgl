#pragma once

#include "common.hpp"

namespace g {
	namespace camera3d {
		extern bool enabled;
		extern glm::vec3 position;
		extern glm::quat rotation;
		void move_relative(const glm::vec3 &v);
		void rotate_x(const float angle);
		void rotate_y(const float angle);
		void rotate_z(const float angle);
		void reset();
	}
}

void update_projection();
void update_modelview();
void flush_projection();
void flush_modelview();
