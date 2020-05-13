#include "common.hpp"
#include "shader.hpp"
#include <string.h>

g::Shaders g::shaders;

void g::Shaders::init()
{
	const GLchar *const pnc_vs_src = "\n\
precision mediump float;\n\
attribute vec3 inputPosition;\n\
attribute vec3 inputNormal;\n\
attribute vec3 inputColor;\n\
\n\
uniform mat4 projection;\n\
uniform mat4 model;\n\
uniform mat4 view;\n\
\n\
varying vec3 position;\n\
varying vec3 normal;\n\
varying vec3 color;\n\
\n\
void main() {\n\
	position = (view*model*vec4(inputPosition, 1.0)).xyz;\n\
	gl_Position = projection*vec4(position, 1.0);\n\
	normal = normalize((view*model*vec4(inputNormal, 0.0)).xyz);\n\
	color = inputColor;\n\
}\n\
";
	const GLchar *const pnc_fs_src = "\n\
precision mediump float;\n\
\n\
varying vec3 position;\n\
varying vec3 normal;\n\
varying vec3 color;\n\
\n\
vec3 do_light(vec3 lightDir)\n\
{\n\
	vec3 reflectDir = reflect(-lightDir, normal);\n\
	vec3 viewDir = -normalize(position);\n\
	float lambertian = max(dot(lightDir, normal), 0.0);;\n\
	float specular = 0.0;\n\
	if(lambertian > 0.0) {\n\
		float specAngle = max(dot(reflectDir, viewDir), 0.0);\n\
		specular = pow(specAngle, 10.0);\n\
	}\n\
	vec3 specColor = color + vec3(0.3);\n\
	return 0.3*color + lambertian*color + specular*specColor;\n\
}\n\
void main() {\n\
	vec3 lightA = do_light(normalize(vec3(0., 1., 0.1)));\n\
	gl_FragColor = vec4(lightA, 1.);\n\
}\n\
";
	const GLchar *const pc_vs_src = "\n\
precision mediump float;\n\
attribute vec3 inputPosition;\n\
attribute vec3 inputColor;\n\
\n\
uniform mat4 projection;\n\
uniform mat4 model;\n\
uniform mat4 view;\n\
\n\
varying vec3 position;\n\
varying vec3 color;\n\
\n\
void main()\n\
{\n\
	position = (view*model*vec4(inputPosition, 1.0)).xyz;\n\
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
	m_PNC.init(pnc_vs_src, pnc_fs_src, { "inputPosition", "inputNormal", "inputColor" });
	m_PC.init(pc_vs_src, pc_fs_src, { "inputPosition", "inputColor" });
}

static bool compile_successful(GLuint obj)
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

static bool link_successful(GLuint obj)
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

void g::Shader::init(const char *vs_src, const char *fs_src, const std::vector<std::string> &attrib_names)
{
	const GLuint vs = compile_shader(vs_src, GL_VERTEX_SHADER);
	const GLuint fs = compile_shader(fs_src, GL_FRAGMENT_SHADER);
	m_handle = link_shader({ vs, fs });
	for (unsigned i = 0; i < attrib_names.size(); ++i) {
		const GLuint loc = static_cast<GLuint>(i);
		glBindAttribLocation(m_handle, loc, attrib_names[i].c_str());
	}
	m_number_of_attribs = attrib_names.size();
	m_u_model = glGetUniformLocation(m_handle, "model");
	m_u_view = glGetUniformLocation(m_handle, "view");
	m_u_projection = glGetUniformLocation(m_handle, "projection");
	glUseProgram(m_handle);
	model(glm::mat4(1.f));
	view(glm::mat4(1.f));
	projection(glm::mat4(1.f));
}

void g::Shader::use() const
{
	static int last_number_of_attribs = 0;
	if (last_number_of_attribs != m_number_of_attribs) {
		for (int i = last_number_of_attribs; i < m_number_of_attribs; ++i) {
			glEnableVertexAttribArray(i);
		}
		for (int i = last_number_of_attribs - 1; i >= m_number_of_attribs; --i) {
			glDisableVertexAttribArray(i);
		}
		last_number_of_attribs = m_number_of_attribs;
	}
	glUseProgram(m_handle);
}
