#pragma once

#include "common.hpp"

namespace g {
	class Shaders {
	public:
		enum ShaderKind {
			KIND_PN, KIND_PT, KIND_PC
		};
		void init();
		LAZY_GET(GLuint, PN)
		LAZY_GET(GLuint, PC)
		LAZY_GET(GLuint, PN_u_projection)
		LAZY_GET(GLuint, PN_u_modelview)
		LAZY_GET(GLuint, PC_u_projection)
		LAZY_GET(GLuint, PC_u_modelview)
		LAZY_GET(GLuint, u_projection)
		LAZY_GET(GLuint, u_modelview)
		LAZY_GET(ShaderKind, kind);
		void kind(ShaderKind l_kind);
	private:
		GLuint m_PN;
		GLuint m_PC;
		GLuint m_PN_u_projection;
		GLuint m_PN_u_modelview;
		GLuint m_PC_u_projection;
		GLuint m_PC_u_modelview;
		GLuint m_u_projection;
		GLuint m_u_modelview;
		ShaderKind m_kind;
	};
	extern Shaders shaders;
}


