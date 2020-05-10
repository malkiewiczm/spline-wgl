#pragma once

#include "common.hpp"
#include "vao.hpp"

namespace g {
	namespace cart {
		extern VAO *vao;
		void step(float dt);
		void draw();
	}
}
