#pragma once

#include "common.hpp"

namespace g {
	class Shaders {
	public:
		enum ShaderKind {
			KIND_PNC, KIND_PT, KIND_PC
		};
		void init();
		LAZY_GET(GLuint, PNC)
		LAZY_GET(GLuint, PC)
		LAZY_GET(GLuint, PNC_u_projection)
		LAZY_GET(GLuint, PNC_u_modelview)
		LAZY_GET(GLuint, PC_u_projection)
		LAZY_GET(GLuint, PC_u_modelview)
		LAZY_GET(GLuint, u_projection)
		LAZY_GET(GLuint, u_modelview)
		LAZY_GET(ShaderKind, kind);
		void kind(ShaderKind l_kind);
	private:
		GLuint m_PNC;
		GLuint m_PC;
		GLuint m_PNC_u_projection;
		GLuint m_PNC_u_modelview;
		GLuint m_PC_u_projection;
		GLuint m_PC_u_modelview;
		GLuint m_u_projection;
		GLuint m_u_modelview;
		ShaderKind m_kind;
	};
	extern Shaders shaders;
}


