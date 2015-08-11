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

#ifndef ANFLEX_INTERFACE_CANVAS_MAIN_H
#define ANFLEX_INTERFACE_CANVAS_MAIN_H

#include "iup.h"

#include "canvas.h"
#include "canvas-detail-handler.h"
#include "canvas-zoom-handler.h"

class cCanvasAttach;
class cHitProcessor;

static float s_max_speed = 500.0f;
static float s_accel = 5000.0f;
static float s_near = 1.0f;
static float s_far = 1000.0f;
static float s_fovy = 60.0f;
static AlgVector s_target(0.0f, 0.0f, 0.0f);
static AlgVector s_dop(0.0f, 1.0f, 0.0f);
static AlgVector s_up(0.0f, 0.0f, 1.0f);

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
class cCanvasMain : public cCanvas
{
protected:

  /**
	* @brief List of attach canvas
	*
	*	This subcanvas is attached on the canvas main. 
  * To use more than 3 subcanvas need to detached.
	*/
  cCanvasAttach *m_vec_canvas_attach[3];

  /**
	* @brief Vgl canvas
	*/
  VglCanvas *m_canvas;

  /**
	* @brief Zoom handler
  *
  * This handler allow to seleted zoom
	*/
  cCanvasZoomHandler *m_zoom_handler;

  /**
	* @brief Detail handler
  *
  * This handler allow to create a attach and detach canvas.
	*/
  cCanvasDetailHandler *m_detail_handler;

  /**
	* @brief Function to redraw subcanvas
	*/
  VglFunction m_redraw_function_detail;
  VglFunction m_redraw_end_function_datail;

  void *m_data_render;

  /**
	* @brief Function to open the subcanvas menu
	*/
  void (*m_menu_function_detail) (void*);

  void activate() { m_canvas->Activate(); }

public:

  /**
	* @brief Constructor
	*/
  cCanvasMain(std::string label, int w, int h);

  /**
	* @brief Destructor
	*/
  ~cCanvasMain(void);
  
  /**
	* @brief Repaint canvas
	*/
  void postRedraw(void) { m_canvas->PostRedraw(); }

  /**
	* @brief Set vgl parameters
  *
  * @param[in] redraw_function - redraw function
  * @param[in] redraw_end_function - redraw end function
  * @param[in] redraw_pick_function - redraw pick function
  * @param[in] processor - hit processor
  * @param[in] data - Parameter passed to the renderings functions
	*/
  void set_vgl( VglFunction redraw_function, 
                VglFunction redraw_end_function = NULL, 
                VglFunction redraw_pick_function = NULL,
                void (*process_pick)(VglCamera *camera, bool double_click, bool ctrl, int bt, int st) = NULL,
                void *data = NULL);

  /**
	* @brief Activate detail mode
  *
  * This handler mode allow create subcanvas.
	*/
  void activate_detail(void) { m_mode_handler->active_detail(); }

  /**
	* @brief Activate zoom mode
	*/
  void activate_zoom(void) { m_mode_handler->active_zoom(); }

  /**
	* @brief Add idle
  *
  * @param[in] redraw_function - redraw function
  * @param[in] data - Parameter passed to the rendering function
	*/
  void add_idle(void(*func)(void*), void *data = NULL) 
      { m_canvas->AddIdle((VglFunction)func, data, VGL_FOREVER); }

  /**
	* @brief Remove idle
  *
  * @param[in] redraw_function - redraw function
  * @param[in] data - Parameter passed to the rendering function
	*/
  void rem_idle(void(*func)(void*), void *data = NULL) 
      { m_canvas->RemIdle((VglFunction)func, data); }

  /**
	* @brief Overlay subcanvas
  *
  * If to_overlay is true put all subcanvas on overlay mode or
  * false to restore handler of all subcanvas
  *
  * @param[in] to_overlay 
	*/
  void overlay_subcanvas(bool to_overlay);

#pragma region Attach canvas

  //cSubcanvas** get_subcanvas(void) { return &m_subcanvas[0]; }

  /**
	* @brief Create subcanvas
  *
  * As it has only 3 subcanvas spaces, use the first empty.
  *
  * @param[in] vgl_camera - camera view to use on subcanvas
	*/
  bool create_canvas_attach(VglCamera *vgl_camera);
  bool create_canvas_attach(VglCamera *vgl_camera, unsigned int i);

  /**
	* @brief Delete subcanvas
  *
  * @param[in] subcanvas_del - subcanvas to be deleted
	*/
  void delete_canvas_attach(cCanvasAttach *canvas);

  /**
	* @brief Clear subcanvas opengl bufffer
	*/
  void clear_canvas_attach(void *data);

  /**
	* @brief Set canvas attach attributes
  */
  void clear_color_canvas_attach(void *data, float r, float g, float b, float a);
  void set_function_canvas_attach(VglFunction func, VglFunction func_end, VglFunction func_menu)
  {
    m_redraw_function_detail = func;
    m_redraw_end_function_datail = func_end;
    m_menu_function_detail = func_menu;
  }

  /**
	* @brief Redraw all subcanvas
	*/
  void redraw_all_canvas_attach(void);

#pragma endregion End of Subcanvas

  // Detail
  /**
	* @brief Create dettach subcanvas
  *
  * @param[in] vgl_camera - camera view to use on subcanvas
	*/
  bool create_canvas_detach(VglCamera *camera);

  void set_detach_attribute(VglFunction func, 
                            VglFunction func_end, 
                            VglFunction idle,
                            void *data,
                            int repeat,
                            void(*poupup_func)(void*),
                            std::string icon,
                            std::string title, 
                            std::string parent)
  {
    m_detail_handler->set_detach_attribute(func, func_end, idle, data, repeat, poupup_func, icon, title, parent);
  }

  //void set_canvas_detail_menu_function(void(*func)(void*))
  //    { m_detail_handler->set_menu_popup_function(func); } 
  //void set_detail_window_idle(void(*func)(void*), void *data)
  //    { m_detail_handler->set_detail_window_idle((VglFunction) func, data, VGL_FOREVER); }
  //void set_detail_window_redraw(void(*func)(void*))
  //    { m_detail_handler->set_redraw_detail_function((VglFunction) func); }
  //void set_detail_window_end_redraw(void(*func)(void*))
  //    { m_detail_handler->set_redraw_detail_end_function((VglFunction) func); }
  //void set_detail_window_icon(char *icon)
  //    { m_detail_handler->set_detail_window_icon(icon); }
  //void set_detail_window_parent(char *parent)
  //    { m_detail_handler->set_detail_window_parent(parent); }
  //void set_detail_window_title(char *title)
  //    { m_detail_handler->set_detail_window_title(title); } 
  //void close_detail_windows()
  //    { m_detail_handler->close_detail_windows(); }
  //void redraw_detail_windows(void) 
  //    { m_detail_handler->redraw_detail_windows(); }
  // End of Detail

  /**
	* @brief Set navigation attributes
  *
  * Calculate speed and acceleration using the bounding box.
  *
  * @param[in] bbox -
	*/
  void set_navig_att(const sBox &bbox);

  void setStereo(bool b);
  bool isStereoSupported(void);

  VglCanvas* get_vgl_canvas(void) { return m_canvas; } 

  bool get_double_click(void) { return m_mode_handler->GetDoubleClick(); }

  //void save(FILE*, cAnflog*) const;
  //bool read(cNeutralFile&, cAppModel*);
};

#endif // ANFLEX_INTERFACE_CANVAS_MAIN_H
