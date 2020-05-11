#include "common.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include <string.h>

g::Shaders g::shaders;

static inline bool compile_successful(GLuint obj)
{
	GLint status;
	glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
	if (! status) {
		constexpr int buf_size = 1024;
		std::vector<GLchar> buf(buf_size);
		glGetShaderInfoLog(obj, buf_size, nullptr, &buf[0]);
		puts(&buf[0]);
	}
	return status;
}

static inline bool link_successful(GLuint obj)
{
	GLint status;
	glGetProgramiv(obj, GL_LINK_STATUS, &status);
	if (! status) {
		constexpr int buf_size = 1024;
		std::vector<GLchar> buf(buf_size);
		glGetProgramInfoLog(obj, buf_size, nullptr, &buf[0]);
		puts(&buf[0]);
	}
	return status;
}

static GLuint compile_shader(const GLchar *source, GLenum type)
{
	GLuint handle = glCreateShader(type);
	if (handle == 0)
		die("could not create shader");
	GLint source_len = strlen(source);
	glShaderSource(handle, 1, &source, &source_len);
	glCompileShader(handle);
	if (! compile_successful(handle))
		die("shader program did not compile");
	return handle;
}

static GLuint link_shader(const std::vector<GLuint> &programs)
{
	GLuint handle = glCreateProgram();
	if (handle == 0)
		die("could not create shader program");
	for (auto item : programs) {
		glAttachShader(handle, item);
	}
	glLinkProgram(handle);
	if (! link_successful(handle))
		die("shader program did not link");
	return handle;
}

void g::Shaders::init()
{
	const GLchar *const pn_vs_src = "\n\
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
	const GLchar *const pn_fs_src = "\n\
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
	const GLchar *const pc_vs_src = "\n\
precision mediump float;\n\
attribute vec3 inputPosition;\n\
attribute vec3 inputColor;\n\
\n\
uniform mat4 projection;\n\
uniform mat4 modelview;\n\
\n\
varying vec3 position;\n\
varying vec3 color;\n\
\n\
void main()\n\
{\n\
	position = (modelview*vec4(inputPosition, 1.0)).xyz;\n\
	gl_Position = projection*vec4(position, 1.0);\n\
	color = inputColor;\n\
}\n\
";
	const GLchar *const pc_fs_src = "\n\
precision mediump float;\n\
\n\
varying vec3 position;\n\
varying vec3 color;\n\
\n\
void main()\n\
{\n\
	gl_FragColor = vec4(color, 1.);\n\
}\n\
";
	{
		const GLuint pn_vs = compile_shader(pn_vs_src, GL_VERTEX_SHADER);
		const GLuint pn_fs = compile_shader(pn_fs_src, GL_FRAGMENT_SHADER);
		m_PN = link_shader({ pn_vs, pn_fs });
		glUseProgram(m_PN);
		constexpr GLuint a_position = 0;
		constexpr GLuint a_normal = 1;
		glBindAttribLocation(m_PN, a_position, "inputPosition");
		glBindAttribLocation(m_PN, a_normal, "inputNormal");
		glEnableVertexAttribArray(a_position);
		glEnableVertexAttribArray(a_normal);
		m_PN_u_projection = glGetUniformLocation(m_PN, "projection");
		m_PN_u_modelview = glGetUniformLocation(m_PN, "modelview");
	}
	{
		const GLuint pc_vs = compile_shader(pc_vs_src, GL_VERTEX_SHADER);
		const GLuint pc_fs = compile_shader(pc_fs_src, GL_FRAGMENT_SHADER);
		m_PC = link_shader({ pc_vs, pc_fs });
		glUseProgram(m_PC);
		constexpr GLuint a_position = 0;
		constexpr GLuint a_color = 1;
		glBindAttribLocation(m_PC, a_position, "inputPosition");
		glBindAttribLocation(m_PC, a_color, "inputColor");
		glEnableVertexAttribArray(a_position);
		glEnableVertexAttribArray(a_color);
		m_PC_u_projection = glGetUniformLocation(m_PC, "projection");
		m_PC_u_modelview = glGetUniformLocation(m_PC, "modelview");
	}
	kind(KIND_PC);
}

void g::Shaders::kind(ShaderKind l_kind)
{
	if (m_kind == l_kind)
		return;
	m_kind = l_kind;
	switch (m_kind) {
	case KIND_PN:
		m_u_projection = m_PN_u_projection;
		m_u_modelview = m_PN_u_modelview;
		glUseProgram(m_PN);
		break;
	case KIND_PT:
		die("kind pt shader not made");
		break;
	default:
		m_u_projection = m_PC_u_projection;
		m_u_modelview = m_PC_u_modelview;
		glUseProgram(m_PC);
	}
	g::camera.update_modelview();
	g::camera.update_projection();
	g::camera.flush_modelview();
	g::camera.flush_projection();
}
