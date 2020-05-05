#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include "shader.hpp"
#include "common.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace g {
	static GLuint standard_shader;
	static int canvas_width;
	static int canvas_height;
	static GLuint u_projection;
	static GLuint u_modelview;
	constexpr GLuint a_position = 0;
	constexpr GLuint a_normal = 1;
	static GLuint vertex_buffer;
	static GLuint index_buffer;
	static int element_count;
	static float camera_angle = 0.f;
}

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
};

static void update_projection();
static void update_modelview();

static EM_BOOL on_resize(int eventType, const EmscriptenUiEvent *uiEvent, void *userData)
{
	UNUSED(eventType);
	UNUSED(userData);
	g::canvas_width = uiEvent->windowInnerWidth;
	g::canvas_height = uiEvent->windowInnerHeight;
	emscripten_set_canvas_element_size("#canvas", g::canvas_width, g::canvas_height);
	glViewport(0, 0, g::canvas_width, g::canvas_height);
	update_projection();
	return true;
}

static void context_setup()
{
	EmscriptenWebGLContextAttributes attr;
	emscripten_webgl_init_context_attributes(&attr);
	attr.alpha = false;
	attr.majorVersion = 1;
	attr.minorVersion = 0;
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context("#canvas", &attr);
	emscripten_webgl_make_context_current(ctx);
}

static void setup_shader()
{
	const GLchar *const vs_src = "\n\
precision mediump float;\n\
attribute vec3 inputPosition;\n\
attribute vec3 inputNormal;\n\
\n\
uniform mat4 projection;\n\
uniform mat4 modelview;\n\
\n\
varying vec3 position;\n\
varying vec3 normal;\n\
\n\
void main() {\n\
	position = (modelview*vec4(inputPosition, 1.0)).xyz;\n\
	gl_Position = projection*vec4(position, 1.0);\n\
	normal = normalize((modelview*vec4(inputNormal, 0.0)).xyz);\n\
}\n\
";
	const GLchar *const fs_src = "\n\
precision mediump float;\n\
\n\
varying vec3 position;\n\
varying vec3 normal;\n\
\n\
vec3 do_light(vec3 lightPos, vec3 diffuseColor, vec3 specColor)\n\
{\n\
	vec3 lightDir = normalize(lightPos - position);\n\
	vec3 reflectDir = reflect(-lightDir, normal);\n\
	vec3 viewDir = -normalize(position);\n\
	float lambertian = max(dot(lightDir, normal), 0.0);;\n\
	float specular = 0.0;\n\
	if(lambertian > 0.0) {\n\
		float specAngle = max(dot(reflectDir, viewDir), 0.0);\n\
		specular = pow(specAngle, 10.0);\n\
	}\n\
	return 0.1*diffuseColor + lambertian*diffuseColor + specular*specColor;\n\
}\n\
void main() {\n\
	vec3 lightA = do_light(vec3(1., 1., 2.), vec3(0.66, 0.66, 0.), vec3(1.));\n\
	gl_FragColor = vec4(lightA, 1.);\n\
}\n\
";
	const GLuint vs = compile_shader(vs_src, GL_VERTEX_SHADER);
	const GLuint fs = compile_shader(fs_src, GL_FRAGMENT_SHADER);
	g::standard_shader = link_shader({ vs, fs });
	glUseProgram(g::standard_shader);
	glBindAttribLocation(g::standard_shader, g::a_position, "inputPosition");
	glBindAttribLocation(g::standard_shader, g::a_normal, "inputNormal");
	glEnableVertexAttribArray(g::a_position);
	glEnableVertexAttribArray(g::a_normal);
	g::u_projection = glGetUniformLocation(g::standard_shader, "projection");
	g::u_modelview = glGetUniformLocation(g::standard_shader, "modelview");
	update_modelview();
	emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, on_resize);
	{
		// this updates the projection
		EmscriptenUiEvent evt;
		evt.windowInnerWidth = 800;
		evt.windowInnerHeight = 600;
		on_resize(EMSCRIPTEN_EVENT_RESIZE, &evt, nullptr);
	}
}

static void update_projection()
{
	const float fov = torad(45.f);
	const float aspect = static_cast<float>(g::canvas_width) / g::canvas_height;
	glm::mat4 proj = glm::perspective(fov, aspect, 0.1f, 100.f);
	glUniformMatrix4fv(g::u_projection, 1, false, &proj[0][0]);
}

static void update_modelview()
{
	glm::mat4 mv = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -5.f));
	mv = glm::rotate(mv, g::camera_angle, glm::vec3(0.408248f, 0.816497f, 0.408248f));
	glUniformMatrix4fv(g::u_modelview, 1, false, &mv[0][0]);
}

static inline void *attrib_index_float(const int index)
{
	return reinterpret_cast<void*>(index*sizeof(float));
}

static void gl_setup()
{
	glClearColor(0.933333f, 0.933333f, 0.933333f, 1.f);
	glEnable(GL_DEPTH_TEST);
	setup_shader();
	constexpr float Ap = 1.f;
	constexpr float An = 0.577350f;
	std::vector<Vertex> vertex_data {
		{ { -Ap, -Ap, -Ap }, { -An, -An, -An } },
		{ { -Ap, Ap, Ap }, { -An, An, An } },
		{ { Ap, -Ap, Ap }, { An, -An, An } },
		{ { Ap, Ap, -Ap }, { An, An, -An } },
	};
	std::vector<GLuint> index_data {
		0, 1, 2, 0, 3, 2, 0, 3, 1, 3, 1, 2
	};
	g::element_count = index_data.size();
	{
		GLuint bufs[2];
		glGenBuffers(2, bufs);
		g::vertex_buffer = bufs[0];
		g::index_buffer = bufs[1];
	}
	glBindBuffer(GL_ARRAY_BUFFER, g::vertex_buffer);
	glVertexAttribPointer(g::a_position, 3, GL_FLOAT, false, sizeof(Vertex), attrib_index_float(0));
	glVertexAttribPointer(g::a_normal, 3, GL_FLOAT, false, sizeof(Vertex), attrib_index_float(3));
	glBufferData(GL_ARRAY_BUFFER, vertex_data.size()*sizeof(vertex_data[0]), &vertex_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g::index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data.size()*sizeof(index_data[0]), &index_data[0], GL_STATIC_DRAW);
}

static void draw()
{
	g::camera_angle += 0.03f;
	update_modelview();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawElements(GL_TRIANGLES, g::element_count, GL_UNSIGNED_INT, (void*)0);
}

int main()
{
	context_setup();
	gl_setup();
	emscripten_set_main_loop(draw, 0, 1);
}
