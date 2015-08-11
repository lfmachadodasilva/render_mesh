// ------------------------------------------------------------------------------------------------- 
// Anflex Project -- Tecgraf/PUC-Rio  CENPES/Petrobras 
// www.tecgraf.puc-rio.br 
// 
// Created by lfmachado in April/2011.
// 
// $URL: $ 
// $Revision: $ 
// $Date: $ 
// 
// $LastChangedBy: $ 
// -------------------------------------------------------------------------------------------------

#ifndef ANFLEX_INTERFACE_MAIN_DIALOG_H
#define ANFLEX_INTERFACE_MAIN_DIALOG_H

#include "string"
using std::string;

#include "canvas\box.h"

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>

class cObject;
class cCanvasMain;
class cCanvasAttach;
class cFPS;

#define CANVAS_MAIN "canvas_main"

class cMainDialog
{
private:

  sBox m_bbox;

  // handle
  Ihandle *m_dg, *m_subcanvas_menu, *m_detail_menu,
          *m_bt_zoom, *m_bt_zoom_in, *m_bt_zoom_out, *m_bt_undo_view, *m_bt_redo_view, *m_bt_reset, 
          *m_bt_projetion_xy, *m_bt_projetion_xz, *m_bt_projetion_yz, *m_bt_projetion_xyz,
          *m_bt_ortho, *m_bt_detail, *m_bt_fit, *m_bt_show,
          *m_tg_pick, *m_tg_fps, *m_tg_wireframe, *m_tg_bbox, *m_tg_va, *m_tg_vbo, *m_tg_shader,
          *m_tg_pick_object, *m_tg_pick_element, *m_tg_pick_disable, *m_tg_vertex_mesh_quad,
          *m_tg_vertex_mesh_pts,
          *it_subcanvas_fit, *it_subcanvas_zoom_in, *it_subcanvas_zoom_out,
          *it_subcanvas_projection_xy, *it_subcanvas_projection_xz, 
          *it_subcanvas_projection_yz, *it_subcanvas_ortho,
          *it_subcanvas_manip, *it_subcanvas_navig,
          *it_subcanvas_detach, *it_subcanvas_close,
          *it_detail_fit, *it_detail_zoom_in, *it_detail_zoom_out,
          *it_detail_projection_xy, *it_detail_projection_xz, 
          *it_detail_projection_yz, *it_detail_ortho,
          *it_detail_manip, *it_detail_navig,
          *it_detail_attach, *it_detail_close; 

  Ihandle* create_dialog(void);
  void set_callbacks(void);
  void init_dialog(void);

  bool create_scene(void);

  void create_object(string filename);
  void add_object(std::string filename, 
                  float tx, float ty, float tz, 
                  float rx, float ry, float rz,
                  float sx, float sy, float sz);
  void add_object(float tx, float ty, float tz, 
                  float rx, float ry, float rz,
                  float sx, float sy, float sz);


  static void open_subcanvas_menu(void *data);
  static void open_detail_menu(void *data);

  // callback
  static int cb_zoom(Ihandle* ih);
  static int cb_projection(Ihandle* ih);
  static int cb_subcanvas_menu(Ihandle* ih);
  static int cb_detail_menu(Ihandle* ih);
  static int cb_main(Ihandle* ih);
  static int cb_drop_file(Ihandle *h, const char* filename, int /*num*/, int /*x*/, int /*y*/);

protected:

public:

  /**
	* @brief Constructor
	*/
	cMainDialog(void);

	/**
	* @brief Destructor
	*/
	~cMainDialog(void);

	/**
	* @brief Show dialog
	*/
	void show_dialog(void);
};

#endif // ANFLEX_INTERFACE_MAIN_DIALOG_H