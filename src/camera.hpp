#pragma once

#include "common.hpp"

namespace g {
	class Camera {
	public:
		enum CameraKind {
			CAMERA_3D, CAMERA_ORTHO, CAMERA_LOOKAT
		};
		void init();
		ACC_V(CameraKind, kind)
		ACC_R(glm::vec3, looking_at)
		bool is_camera_3d() const {
			return m_kind == CAMERA_3D;
		}
		bool is_camera_ortho() const {
			return m_kind == CAMERA_ORTHO;
		}
		bool is_camera_lookat() const {
			return m_kind == CAMERA_LOOKAT;
		}
		glm::mat4 calc_view();
		glm::mat4 calc_projection();
		glm::mat4 calc_ui_projection();
	private:
		CameraKind m_kind;
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
		ACC_V(float, zoom)
		ACC_V(OrthoSide, side)
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
