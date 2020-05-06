#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include "shader.hpp"
#include "common.hpp"
#include "vao.hpp"
#include "camera.hpp"
#include "mouse.hpp"
#include "key.hpp"

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

static EM_BOOL on_key(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData)
{
	UNUSED(userData);
	const bool keydown = eventType == EMSCRIPTEN_EVENT_KEYDOWN;
	char keyCode;
	if (keyEvent->code[0] == 'K')
		keyCode = keyEvent->code[3];
	else if (keyEvent->code[0] == 'D')
		keyCode = keyEvent->code[5];
	else
		keyCode = '?';
	if (keydown) {
		bool new_3d_enabled = g::camera3d::enabled;
		int new_dir = g::camera_ortho_side;
		switch (keyCode) {
		case '1':
			if (g::camera3d::enabled) {
				g::camera3d::reset();
				update_modelview();
			}
			break;
		case 'F':
			new_dir = g::ORTHO_FRONT;
			new_3d_enabled = false;
			break;
		case 'B':
			new_dir = g::ORTHO_BACK;
			new_3d_enabled = false;
			break;
		case 'R':
			new_dir = g::ORTHO_RIGHT;
			new_3d_enabled = false;
			break;
		case 'L':
			new_dir = g::ORTHO_LEFT;
			new_3d_enabled = false;
			break;
		case 'T':
			new_dir = g::ORTHO_TOP;
			new_3d_enabled = false;
			break;
		case 'Y':
			new_dir = g::ORTHO_BOTTOM;
			new_3d_enabled = false;
			break;
		case '3':
			new_3d_enabled = true;
			break;
		case 'W':
			g::key::down_up = true;
			break;
		case 'A':
			g::key::down_left = true;
			break;
		case 'S':
			g::key::down_down = true;
			break;
		case 'D':
			g::key::down_right = true;
			break;
		}
		if (new_3d_enabled != g::camera3d::enabled || new_dir != g::camera_ortho_side) {
			g::camera3d::enabled = new_3d_enabled;
			if (! g::camera3d::enabled && g::mouse::is_locked) {
				emscripten_exit_pointerlock();
			}
			g::camera_ortho_side = new_dir;
			update_projection();
			update_modelview();
			return true;
		}
	} else {
		switch (keyCode) {
		case 'W':
			g::key::down_up = false;
			break;
		case 'A':
			g::key::down_left = false;
			break;
		case 'S':
			g::key::down_down = false;
			break;
		case 'D':
			g::key::down_right = false;
			break;
		}
	}
	return false;
}

static EM_BOOL on_mouse(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
	UNUSED(userData);
	g::mouse::x = mouseEvent->clientX;
	g::mouse::y = mouseEvent->clientY;
	if (eventType == EMSCRIPTEN_EVENT_MOUSELEAVE) {
		g::mouse::is_down = false;
	} else if (mouseEvent->button == 0) {
		if (eventType == EMSCRIPTEN_EVENT_MOUSEDOWN) {
			g::mouse::is_down = true;
		} else if (eventType == EMSCRIPTEN_EVENT_MOUSEUP) {
			g::mouse::is_down = false;
		}
	} else if (mouseEvent->button == 2 && eventType == EMSCRIPTEN_EVENT_MOUSEDOWN && g::camera3d::enabled) {
		if (g::mouse::is_locked) {
			emscripten_exit_pointerlock();
		} else {
			emscripten_request_pointerlock("canvas", false);
		}
		g::key::release_all();
	}
	if (eventType == EMSCRIPTEN_EVENT_MOUSEMOVE && g::camera3d::enabled && g::mouse::is_locked) {
		glm::vec2 m { mouseEvent->movementX, mouseEvent->movementY };
		m /= 400.f;
		g::camera3d::rotate_y(m.x);
		g::camera3d::rotate_x(m.y);
		update_modelview();
	}
	return true;
}

static EM_BOOL on_pointerlock(int eventType, const EmscriptenPointerlockChangeEvent *pointerlockChangeEvent, void *userData)
{
	UNUSED(eventType);
	UNUSED(userData);
	g::mouse::is_locked = pointerlockChangeEvent->isActive;
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
vec3 do_light(vec3 lightDir, vec3 diffuseColor, vec3 specColor)\n\
{\n\
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
	vec3 lightA = do_light(normalize(vec3(1., 1., 2.)), vec3(0.66, 0.66, 0.), vec3(1.));\n\
	gl_FragColor = vec4(lightA, 1.);\n\
}\n\
";
	const GLuint vs = compile_shader(vs_src, GL_VERTEX_SHADER);
	const GLuint fs = compile_shader(fs_src, GL_FRAGMENT_SHADER);
	g::standard_shader = link_shader({ vs, fs });
	glUseProgram(g::standard_shader);
	constexpr GLuint a_position = 0;
	constexpr GLuint a_normal = 1;
	glBindAttribLocation(g::standard_shader, a_position, "inputPosition");
	glBindAttribLocation(g::standard_shader, a_normal, "inputNormal");
	glEnableVertexAttribArray(a_position);
	glEnableVertexAttribArray(a_normal);
	g::u_projection = glGetUniformLocation(g::standard_shader, "projection");
	g::u_modelview = glGetUniformLocation(g::standard_shader, "modelview");
	emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, on_key);
	emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, on_key);
	emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, on_resize);
	emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, on_mouse);
	emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, on_mouse);
	emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, on_mouse);
	emscripten_set_mouseleave_callback("canvas", nullptr, false, on_mouse);
	emscripten_set_pointerlockchange_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, on_pointerlock);
	g::camera3d::enabled = true;
	g::camera_ortho_side = g::ORTHO_RIGHT;
	g::is_edit_mode = true;
	g::camera3d::reset();
	{
		// calling this event updates the projection
		EmscriptenUiEvent evt;
		evt.windowInnerWidth = 800;
		evt.windowInnerHeight = 600;
		on_resize(EMSCRIPTEN_EVENT_RESIZE, &evt, nullptr);
	}
	update_modelview();
}

static VAO *s_vao;

static void gl_setup()
{
	glClearColor(0.933333f, 0.933333f, 0.933333f, 1.f);
	glEnable(GL_DEPTH_TEST);
	setup_shader();
	std::vector<Vertex_PN> vertex_data {
		{ { 0.273279f, 1.050624f, -2.005395f }, { 0.5981f, 0.2994f, -0.7433f } },
		{ { -0.857576f, -0.598839f, -2.026340f }, { -0.0548f, -0.6529f, -0.7555f } },
		{ { 1.472728f, 0.180840f, 1.731609f }, { 0.9427f, 0.0496f, 0.3300f } },
		{ { 0.341872f, -1.468623f, 1.710664f }, { 0.2897f, -0.9027f, 0.3179f } },
		{ { -0.341872f, 1.468623f, -1.710664f }, { -0.2897f, 0.9027f, -0.3179f } },
		{ { -1.472728f, -0.180840f, -1.731609f }, { -0.9427f, -0.0496f, -0.3300f } },
		{ { 0.857576f, 0.598839f, 2.026340f }, { 0.0548f, 0.6529f, 0.7555f } },
		{ { -0.273279f, -1.050624f, 2.005395f }, { -0.5981f, -0.2994f, 0.7433f } }
	};
	std::vector<GLuint> index_data {
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 1, 3, 7, 0, 2, 3, 4, 0, 1
	};
	s_vao = new VAO(GL_TRIANGLES, vertex_data, index_data);
}

static void update()
{
	constexpr float move_speed = 0.1f;
	if (g::key::down_up) {
		g::camera3d::move_relative({ 0., 0., move_speed });
		update_modelview();
	}
	if (g::key::down_down) {
		g::camera3d::move_relative({ 0., 0., -move_speed });
		update_modelview();
	}
	if (g::key::down_left) {
		g::camera3d::move_relative({ move_speed, 0., 0. });
		update_modelview();
	}
	if (g::key::down_right) {
		g::camera3d::move_relative({ -move_speed, 0., 0. });
		update_modelview();
	}
	flush_modelview();
	flush_projection();
}

static void draw()
{
	update();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	s_vao->draw();
}

int main()
{
	context_setup();
	gl_setup();
	emscripten_set_main_loop(draw, 0, 1);
}
