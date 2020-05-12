#pragma once

#include "common.hpp"

namespace g {
	class Shader {
	public:
		void init(const char *fs_src, const char *vs_src, const std::vector<std::string> &attrib_names);
		void model(const glm::mat4 &model) {
			glUniformMatrix4fv(m_u_model, 1, false, &model[0][0]);
		}
		void view(const glm::mat4 &view) {
			glUniformMatrix4fv(m_u_view, 1, false, &view[0][0]);
		}
		void projection(const glm::mat4 &projection) {
			glUniformMatrix4fv(m_u_projection, 1, false, &projection[0][0]);
		}
		void use() const;
	private:
		GLuint m_handle;
		GLuint m_u_model;
		GLuint m_u_view;
		GLuint m_u_projection;
		int m_number_of_attribs;
	};
	class Shaders {
	public:
		void init();
		GET_R(Shader, PC)
		GET_R(Shader, PNC)
	private:
		Shader m_PC;
		Shader m_PNC;
	};
	extern Shaders shaders;
}
