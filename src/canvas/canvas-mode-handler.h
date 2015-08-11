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

#ifndef ANFLEX_INTERFACE_CANVAS_MODE_HANDLER_H
#define ANFLEX_INTERFACE_CANVAS_MODE_HANDLER_H

#include <vgl/vgl.h>
#include <vgl/vgliup.h>

class cCanvas;

static const char MODE_NONE = '-';
static const char MODE_MANIP = 'm';
static const char MODE_NAVIG = 'n';
static const char MODE_ZOOM = 'c';
static const char MODE_DETAIL = 'v';
static const char MODE_OVERLAY = 'l';

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
class cCanvasModeHandler : public VglModeHandler
{
private:
 
  /**
	* @brief Current handler - MODE_MANIP, MODE_NAVIG, ...
	*/
  char m_mode_handler_type;

  /**
	* @brief Last handler used - MODE_MANIP, MODE_NAVIG, ...
	*/
  char m_mode_handler_type_backup;

  /**
	* @brief Boolean to control if right button is press or not
	*/
  bool m_is_right_press;

  /**
	* @brief Boolean to control if the mouse is moving (motion)
	*/
  bool m_is_motion;

  /**
	* @brief Boolean to check if is in a main canvas
	*/
  bool m_is_main_canvas;

  /**
	* @brief Press mouse coordinates
  * Store a screen coodinate, not using the Z coordinate
	*/
  AlgVector m_old_coord;
  
  /**
  * @brief pointer to canvas
  */
  cCanvas *m_canvas;

  /**
  * @brief Process pick function
  *
  * @param[in] camera
  * @param[in] double_click
  * @param[in] ctrl
  * @param[in] bt - id of used mouse button
  * @param[in] st - VGL_RELEASE or VGL_PRESS
  */
  void (*m_process_pick)(VglCamera *camera, bool double_click, bool ctrl, int bt, int st);

  float m_mouse_x, m_mouse_y;

protected:

	virtual int Keyboard (int k, int st, float x, float y);
  virtual int MouseButton(int bt, int st, float x, float y);
  virtual int MouseMotion(int k, float x, float y);

public:

  /**
	* @brief Constructor
  *
  * @param[in] VglManipViewSurface
	*/
	cCanvasModeHandler(VglManipViewSurface *manipviewsurface);

  /**
	* @brief Get screen coodinatate of mouse position
  *
  * @param[out] x - x screen coordinate
  * @param[out] y - y screen coordinate
	*/
  void get_mouse_pos(float &x, float &y) { x = m_mouse_x; y = m_mouse_y; } 

  /**
	* @brief Set canvas
  *
  * @param[in] canvas
	*/
  void set_canvas(cCanvas* canvas);

  /**
	* @brief Set function to process pick
  *
  * @param[in] function
	*/
  void set_func_process_pick(void (*process_pick)(VglCamera *camera, bool double_click, bool ctrl, int bt, int st))
    { m_process_pick = process_pick; }

  /**
	* @brief Set if is main canvas
  *
  * @param[in] main_canvas
	*/
  void set_main_canvas(bool main_canvas) { m_is_main_canvas = main_canvas; }
  bool is_main_canvas(void) { return m_is_main_canvas; }

  /**
	* @brief Restore handler
  *
  * Restore to the last used handler
	*/
  void restore_handler(void);

  /**
	* @brief Active manipulation handler
  *
  * @param[in] fit - need to fit the model or not
	*/
  void active_manip(bool fit = true);

  /**
	* @brief Active navigation handler
  *
  * @param[in] fit - need to fit the model or not
	*/
  void active_navig(bool fit = true);

  /**
	* @brief Active zoom handler
	*/
  void active_zoom(void);

  /**
	* @brief Active detail handler
	*/
  void active_detail(void);

  /**
	* @brief Active overlay handler on attach canvas
	*/
  void active_overlay(void);
};

#endif
