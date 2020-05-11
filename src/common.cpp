#include "common.hpp"
#include "camera.hpp"

void _die(const char *msg, const char *file, int line)
{
	printf("error: %s (%s:%d)\n", msg, file, line);
	abort();
}

int g::canvas_width;
int g::canvas_height;
bool g::is_edit_mode;
