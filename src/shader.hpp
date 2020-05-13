#pragma once

#include "common.hpp"

namespace g {
	class Shader {
	public:
		void init(const char *vs_src, const char *fs_src, const std::vector<std::string> &attrib_names);
		GET_V(GLuint, handle)
		GET_V(int, number_of_attribs)
		void use() const;
	private:
		GLuint m_handle;
		int m_number_of_attribs;
	};
	class ShaderMVP {
	public:
		void init(const char *vs_src, const char *fs_src, const std::vector<std::string> &attrib_names);
		void model(const glm::mat4 &model) {
			glUniformMatrix4fv(m_u_model, 1, false, &model[0][0]);
		}
		void view(const glm::mat4 &view) {
			glUniformMatrix4fv(m_u_view, 1, false, &view[0][0]);
		}
		void projection(const glm::mat4 &projection) {
			glUniformMatrix4fv(m_u_projection, 1, false, &projection[0][0]);
		}
		void use() const {
			m_shader_base.use();
		}
	private:
		Shader m_shader_base;
		GLuint m_u_model;
		GLuint m_u_view;
		GLuint m_u_projection;
	};
	class Shaders {
	public:
		void init();
		GET_R(ShaderMVP, PC_mvp)
		GET_R(ShaderMVP, PNC_mvp)
	private:
		ShaderMVP m_PC_mvp;
		ShaderMVP m_PNC_mvp;
	};
	extern Shaders shaders;
}
