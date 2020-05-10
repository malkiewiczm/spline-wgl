#include "common.hpp"
#include "camera.hpp"

void _die(const char *msg, const char *file, int line)
{
	printf("error: %s (%s:%d)\n", msg, file, line);
	abort();
}

GLuint g::standard_shader;
int g::canvas_width;
int g::canvas_height;
GLuint g::u_projection;
GLuint g::u_modelview;
bool g::is_edit_mode;
