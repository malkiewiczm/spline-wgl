#pragma once

#include "common.hpp"

namespace g {
	class Camera {
	public:
		enum CameraKind {
			CAMERA_3D, CAMERA_ORTHO, CAMERA_LOOKAT
		};
		void init();
		GET_V(CameraKind, kind)
		void kind(CameraKind l_kind);
		GET_CR(glm::vec3, looking_at)
		void looking_at(const glm::vec3 &l_looking_at);
		bool is_camera_3d() const {
			return m_kind == CAMERA_3D;
		}
		bool is_camera_ortho() const {
			return m_kind == CAMERA_ORTHO;
		}
		bool is_camera_lookat() const {
			return m_kind == CAMERA_LOOKAT;
		}
		void update_projection();
		void update_modelview();
		void flush_projection();
		void flush_modelview();
	private:
		CameraKind m_kind;
		bool m_dirty_projection;
		bool m_dirty_modelview;
		glm::vec3 m_looking_at;
	};
	class Camera3d {
	public:
		void init();
		GET_CR(glm::vec3, position)
		GET_CR(glm::quat, rotation)
		void move_relative(const glm::vec3 &v);
		void rotate_x(const float angle);
		void rotate_y(const float angle);
		void rotate_z(const float angle);
		void reset();
	private:
		glm::vec3 m_position;
		glm::quat m_rotation;
	};
	class CameraOrtho {
	public:
		enum OrthoSide {
			RIGHT, LEFT, TOP, BOTTOM, FRONT, BACK,
		};
		void init();
		const glm::mat4 &transformation() const;
		GET_V(float, zoom)
		GET_V(OrthoSide, side)
		void side(OrthoSide l_side);
		void reset();
	private:
		glm::mat4 m_ortho_rotations[6];
		float m_zoom;
		glm::vec2 m_translation;
		OrthoSide m_side;
	};
	extern Camera camera;
	extern Camera3d camera_3d;
	extern CameraOrtho camera_ortho;
}
