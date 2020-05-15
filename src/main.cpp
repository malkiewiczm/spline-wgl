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

static EM_BOOL on_resize(int eventType, const EmscriptenUiEvent *uiEvent, void *userData)
{
	UNUSED(eventType);
	UNUSED(userData);
	g::canvas_width = uiEvent->windowInnerWidth;
	g::canvas_height = uiEvent->windowInnerHeight;
	emscripten_set_canvas_element_size("#canvas", g::canvas_width, g::canvas_height);
	glViewport(0, 0, g::canvas_width, g::canvas_height);
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
			if (g::camera.is_camera_3d()) {
				g::camera_3d.reset();
			} else if (g::camera.is_camera_ortho()) {
				g::camera_ortho.reset();
			}
			ret = true;
			break;
		case 'H':
			g::spline.show_control_mesh(! g::spline.show_control_mesh());
			ret = true;
			break;
		case 'Q':
			if (g::camera.is_camera_ortho()) {
				if (g::spline.edit_mode() == g::Spline::EM_INSERT) {
					g::spline.edit_mode(g::Spline::EM_SELECT);
				} else {
					g::spline.edit_mode(g::Spline::EM_INSERT);
				}
			}
			ret = true;
			break;
		case 'M':
			if (g::camera.is_camera_ortho()) {
				if (g::spline.edit_mode() == g::Spline::EM_MOVE) {
					g::spline.edit_mode(g::Spline::EM_SELECT);
				} else {
					g::spline.edit_mode(g::Spline::EM_MOVE);
				}
			}
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
			g::camera.kind(g::Camera::CAMERA_3D);
			ret = true;
			break;
		case '4':
			g::camera.kind(g::Camera::CAMERA_LOOKAT);
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
			if (g::camera.is_camera_ortho()) {
				g::spline.edit_mode(g::Spline::EM_SELECT);
			}
			g::key::down_down = true;
			ret = true;
			break;
		case 'D':
			g::key::down_right = true;
			ret = true;
			break;
		}
		if (ret) {
			if (! g::camera.is_camera_3d() && g::mouse.locked()) {
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
			g::spline.edit_click();
			g::cart.reset();
		} else if (eventType == EMSCRIPTEN_EVENT_MOUSEUP) {
			g::mouse.down(false);
			g::spline.edit_unclick();
		}
	} else if (mouseEvent->button == 2 && eventType == EMSCRIPTEN_EVENT_MOUSEDOWN && g::camera.is_camera_3d()) {
		if (g::mouse.locked()) {
			emscripten_exit_pointerlock();
		} else {
			emscripten_request_pointerlock("canvas", false);
		}
		g::key::release_all();
	}
	if (eventType == EMSCRIPTEN_EVENT_MOUSEMOVE) {
		if (g::camera.is_camera_3d() && g::mouse.locked()) {
			glm::vec2 m { mouseEvent->movementX, mouseEvent->movementY };
			m /= 400.f;
			g::camera_3d.rotate_y(m.x);
			g::camera_3d.rotate_x(m.y);
		} else {
			g::spline.edit_mouse_move();
		}
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
	g::camera_3d.init();
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
	g::spline.init();
}

static void update()
{
	constexpr float move_speed = 0.2f;
	if (g::key::down_up) {
		g::camera_3d.move_relative({ 0., 0., -move_speed });
	}
	if (g::key::down_down) {
		g::camera_3d.move_relative({ 0., 0., move_speed });
	}
	if (g::key::down_left) {
		g::camera_3d.move_relative({ -move_speed, 0., 0. });
	}
	if (g::key::down_right) {
		g::camera_3d.move_relative({ move_speed, 0., 0. });
	}
	g::cart.step(0.016667f);
	if (g::camera.is_camera_lookat()) {
		g::camera.looking_at(g::cart.draw_position());
	}
}

static void draw()
{
	update();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	const glm::mat4 view = g::camera.calc_view();
	const glm::mat4 projection = g::camera.calc_projection();
	// draw PNC VAOs
	g::shaders.PNC().use();
	g::shaders.PNC().view(view);
	g::shaders.PNC().projection(projection);
	g::spline.curve_vao().draw();
	g::cart.vao().draw();
	// draw PC vaos
	g::shaders.PC().use();
	g::shaders.PC().view(view);
	g::shaders.PC().projection(projection);
	if (g::spline.show_control_mesh()) {
		g::spline.control_vao().draw();
	}
	// draw UI
	g::shaders.PC().view(glm::mat4(1.f));
	g::shaders.PC().projection(glm::mat4(1.f));
	if (g::spline.show_ui() && (g::camera.is_camera_ortho() || g::spline.edit_mode() == g::Spline::EM_SELECT)) {
		g::spline.ui_vao().draw();
	}
}

int main()
{
	context_setup();
	gl_setup();
	emscripten_set_main_loop(draw, 0, 1);
}
