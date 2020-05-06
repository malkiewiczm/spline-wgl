#include "key.hpp"


void g::key::release_all()
{
	g::key::down_up = false;
	g::key::down_down = false;
	g::key::down_left = false;
	g::key::down_right = false;
}

bool g::key::down_up = false;
bool g::key::down_down = false;
bool g::key::down_left = false;
bool g::key::down_right = false;
