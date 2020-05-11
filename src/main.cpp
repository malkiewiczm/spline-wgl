#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include "shader.hpp"
#include "common.hpp"
#include "vao.hpp"
#include "camera.hpp"
#include "mouse.hpp"
#include "key.hpp"
#include "spline.hpp"
#include "cart.hpp"

static bool s_show_control_mesh = true;
static VAO s_control_vao;
static VAO s_curve_vao;

static EM_BOOL on_resize(int eventType, const EmscriptenUiEvent *uiEvent, void *userData)
{
	UNUSED(eventType);
	UNUSED(userData);
	g::canvas_width = uiEvent->windowInnerWidth;
	g::canvas_height = uiEvent->windowInnerHeight;
	emscripten_set_canvas_element_size("#canvas", g::canvas_width, g::canvas_height);
	glViewport(0, 0, g::canvas_width, g::canvas_height);
	g::camera.update_projection();
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
		bool ret = false;
		switch (keyCode) {
		case '1':
			if (g::camera.is_camera3d()) {
				g::camera3d.reset();
			} else if (g::camera.is_camera_ortho()) {
				g::camera_ortho.reset();
			}
			ret = true;
			break;
		case 'H':
			s_show_control_mesh = ! s_show_control_mesh;
			ret = true;
			break;
		case 'Q':
			g::spline.place_when_click( ! g::spline.place_when_click());
			ret = true;
			break;
		case 'F':
			g::camera_ortho.side(g::CameraOrtho::FRONT);
			g::camera.kind(g::Camera::CAMERA_ORTHO);
			ret = true;
			break;
		case 'B':
			g::camera_ortho.side(g::CameraOrtho::BACK);
			g::camera.kind(g::Camera::CAMERA_ORTHO);
			ret = true;
			break;
		case 'R':
			g::camera_ortho.side(g::CameraOrtho::RIGHT);
			g::camera.kind(g::Camera::CAMERA_ORTHO);
			ret = true;
			break;
		case 'L':
			g::camera_ortho.side(g::CameraOrtho::LEFT);
			g::camera.kind(g::Camera::CAMERA_ORTHO);
			ret = true;
			break;
		case 'T':
			g::camera_ortho.side(g::CameraOrtho::TOP);
			g::camera.kind(g::Camera::CAMERA_ORTHO);
			ret = true;
			break;
		case 'Y':
			g::camera_ortho.side(g::CameraOrtho::BOTTOM);
			g::camera.kind(g::Camera::CAMERA_ORTHO);
			ret = true;
			break;
		case '3':
			g::camera.kind(g::Camera::CAMERA3D);
			ret = true;
			break;
		case 'W':
			g::key::down_up = true;
			ret = true;
			break;
		case 'A':
			g::key::down_left = true;
			ret = true;
			break;
		case 'S':
			g::key::down_down = true;
			ret = true;
			break;
		case 'D':
			g::key::down_right = true;
			ret = true;
			break;
		}
		if (ret) {
			if (g::camera.is_camera_ortho() && g::mouse.locked()) {
				emscripten_exit_pointerlock();
			}
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
	g::mouse.x(mouseEvent->clientX);
	g::mouse.y(mouseEvent->clientY);
	if (eventType == EMSCRIPTEN_EVENT_MOUSELEAVE) {
		g::mouse.down(false);
	} else if (mouseEvent->button == 0) {
		if (eventType == EMSCRIPTEN_EVENT_MOUSEDOWN) {
			g::mouse.down(true);
			g::spline.edit_click(s_control_vao, s_curve_vao);
			g::cart.reset();
		} else if (eventType == EMSCRIPTEN_EVENT_MOUSEUP) {
			g::mouse.down(false);
		}
	} else if (mouseEvent->button == 2 && eventType == EMSCRIPTEN_EVENT_MOUSEDOWN && g::camera.is_camera3d()) {
		if (g::mouse.locked()) {
			emscripten_exit_pointerlock();
		} else {
			emscripten_request_pointerlock("canvas", false);
		}
		g::key::release_all();
	}
	if (eventType == EMSCRIPTEN_EVENT_MOUSEMOVE && g::camera.is_camera3d() && g::mouse.locked()) {
		glm::vec2 m { mouseEvent->movementX, mouseEvent->movementY };
		m /= 400.f;
		g::camera3d.rotate_y(m.x);
		g::camera3d.rotate_x(m.y);
	}
	return true;
}

static EM_BOOL on_pointerlock(int eventType, const EmscriptenPointerlockChangeEvent *pointerlockChangeEvent, void *userData)
{
	UNUSED(eventType);
	UNUSED(userData);
	g::mouse.locked(pointerlockChangeEvent->isActive);
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
	emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, on_key);
	emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, on_key);
	emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, on_resize);
	emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, on_mouse);
	emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, on_mouse);
	emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, on_mouse);
	emscripten_set_mouseleave_callback("canvas", nullptr, false, on_mouse);
	emscripten_set_pointerlockchange_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, on_pointerlock);
	g::camera.init();
	g::camera3d.init();
	g::camera_ortho.init();
	g::cart.init();
	g::is_edit_mode = true;
	{
		// calling this event updates the projection
		EmscriptenUiEvent evt;
		evt.windowInnerWidth = 1112;
		evt.windowInnerHeight = 920;
		on_resize(EMSCRIPTEN_EVENT_RESIZE, &evt, nullptr);
	}
	g::shaders.init();
}

static void gl_setup()
{
	glClearColor(0.933333f, 0.933333f, 0.933333f, 1.f);
	glEnable(GL_DEPTH_TEST);
	setup_shader();
	std::vector<Vertex_PC> vertex_data {
		{ { 0.273279f, 1.050624f, -2.005395f }, { 0.89596240119633f, 0.82284005249184f, 0.7466048158208f } },
		{ { -0.857576f, -0.598839f, -2.026340f }, { 0.17410809656056f, 0.85894344920194f, 0.71050141911069f } },
		{ { 1.472728f, 0.180840f, 1.731609f }, { 0.5135349589526f, 0.30399487289041f, 0.014984588152715f } },
		{ { 0.341872f, -1.468623f, 1.710664f }, { 0.091402935880612f, 0.36445204016236f, 0.14731284524064f } },
		{ { -0.341872f, 1.468623f, -1.710664f }, { 0.16589861751152f, 0.98852504043703f, 0.44569231238746f } },
		{ { -1.472728f, -0.180840f, -1.731609f }, { 0.11908322397534f, 0.0046693319498276f, 0.0089114047669912f } },
		{ { 0.857576f, 0.598839f, 2.026340f }, { 0.3778801843318f, 0.53166295358135f, 0.57118442335276f } },
		{ { -0.273279f, -1.050624f, 2.005395f }, { 0.60176396984771f, 0.60716574602496f, 0.16623432111576f } }
	};
	std::vector<GLuint> index_data {
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 1, 3, 7, 0, 2, 3, 4, 0, 1
	};
	s_control_vao.gen_buffers();
	s_control_vao.draw_mode(GL_LINE_STRIP);
	s_control_vao.update_buffers(vertex_data, index_data);
	s_control_vao.kind(VAO::KIND_PC);
	s_curve_vao.gen_buffers();
	s_curve_vao.draw_mode(GL_LINE_STRIP);
	s_curve_vao.update_buffers(vertex_data, index_data);
	s_curve_vao.kind(VAO::KIND_PC);
}

static void update()
{
	constexpr float move_speed = 0.2f;
	if (g::key::down_up) {
		g::camera3d.move_relative({ 0., 0., move_speed });
	}
	if (g::key::down_down) {
		g::camera3d.move_relative({ 0., 0., -move_speed });
	}
	if (g::key::down_left) {
		g::camera3d.move_relative({ move_speed, 0., 0. });
	}
	if (g::key::down_right) {
		g::camera3d.move_relative({ -move_speed, 0., 0. });
	}
	g::camera.flush_modelview();
	g::camera.flush_projection();
}

static void draw()
{
	update();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (s_show_control_mesh) {
		s_control_vao.draw();
	}
	s_curve_vao.draw();
	g::cart.step(0.016667f);
	g::cart.draw();
}

int main()
{
	context_setup();
	gl_setup();
	emscripten_set_main_loop(draw, 0, 1);
}
