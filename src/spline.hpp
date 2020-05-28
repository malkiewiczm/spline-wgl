#pragma once

#include "common.hpp"
#include "vao.hpp"

namespace g {
	class Spline {
	public:
		struct Piece {
			glm::vec3 position;
			glm::vec3 tangent;
			glm::vec3 normal;
			glm::vec3 binormal;
			float distance;
		};
		struct ControlPoint {
			glm::vec3 position;
		};
		enum EditMode {
			EM_SELECT, EM_INSERT, EM_MOVE
		};
		void init();
		void edit_click();
		void edit_unclick();
		void edit_mouse_move();
		void edit_delete_selected();
		void edit_select_all();
		void add_pt(const glm::vec3 &p);
		Piece get_piece(const float distance);
		GET_V(EditMode, edit_mode)
		void edit_mode(EditMode l_edit_mode);
		ACC_V(bool, show_control_mesh)
		GET_V(bool, show_ui)
		GET_CR(VAO<Vertex_PC>, control_vao)
		GET_CR(VAO<Vertex_PNC>, track_vao)
		GET_CR(VAO<Vertex_PC>, ui_vao)
	private:
		EditMode m_edit_mode;
		bool m_show_control_mesh;
		bool m_show_ui;
		glm::vec2 m_selection_rect[2];
		std::vector<int> m_selection;
		VAO<Vertex_PC> m_control_vao;
		VAO<Vertex_PNC> m_track_vao;
		VAO<Vertex_PC> m_ui_vao;
		std::vector<Piece> m_curve_pts;
		std::vector<ControlPoint> m_control_pts;
		std::vector<ControlPoint> m_original_control_pts;
		void update_control_vao();
		void update_track_vao();
		void update_ui_select_vao();
		void update_ui_insert_vao();
		void update_ui_move_vao();
		void recalculate_curve_all();
		void edit_click_place();
		void edit_click_start_select();
		void edit_click_select();
		void edit_click_stop_select();
		void edit_click_start_move();
		void edit_click_move();
		void edit_click_stop_move();
	};
	extern Spline spline;
}
