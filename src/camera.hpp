#pragma once

#include "common.hpp"

namespace g {
	class Camera {
	public:
		enum CameraKind {
			CAMERA3D, CAMERA_ORTHO
		};
		void init();
		LAZY_GET(CameraKind, kind)
		void kind(CameraKind l_kind);
		bool is_camera3d() const {
			return m_kind == CAMERA3D;
		}
		bool is_camera_ortho() const {
			return m_kind == CAMERA_ORTHO;
		}
		void update_projection();
		void update_modelview();
		void flush_projection();
		void flush_modelview();
	private:
		CameraKind m_kind;
		bool m_dirty_projection;
		bool m_dirty_modelview;
	};
	class Camera3d {
	public:
		void init();
		LAZY_GETR(glm::vec3, position)
		LAZY_GETR(glm::quat, rotation)
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
		LAZY_GET(float, zoom)
		LAZY_GET(OrthoSide, side)
		void side(OrthoSide l_side);
		void reset();
	private:
		glm::mat4 m_ortho_rotations[6];
		float m_zoom;
		glm::vec2 m_translation;
		OrthoSide m_side;
	};
	extern Camera camera;
	extern Camera3d camera3d;
	extern CameraOrtho camera_ortho;
}
