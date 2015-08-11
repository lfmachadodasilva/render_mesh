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

#ifndef ANFLEX_INTERFACE_CANVAS_DETACH_H
#define ANFLEX_INTERFACE_CANVAS_DETACH_H

#include "canvas.h"

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
class cCanvasDetach : public cCanvas
{
protected:

  VglCanvas *m_canvas_detach;

  Ihandle *m_dialog;

public:
  cCanvasDetach(Ihandle *iup_canvas,
                VglCanvas *parent_canvas,
                VglCamera *camera,
                VglFunction redraw_function,
                VglFunction redraw_end_function,
                void(*menu_poupup_function)(void*),
                void *data);

  /**
	* @brief Add idle functions
  *
  * @param[in] idle_function
  * @param[in] idle_data
  * @param[in] idle_repeat
	*/
  void add_idle(VglFunction idle_function, void *idle_data, int idle_repeat);

  /**
	* @brief Remove idle functions
  *
  * @param[in] idle_function
  * @param[in] idle_data
	*/
  void rem_idle(VglFunction idle_function, void *idle_data);

  /**
	* @brief Set dialog
  *
  * @param[in] dialog - handle of dialog
	*/
  void set_dialog(Ihandle* dialog) { m_dialog = dialog; }

  /**
	* @brief Get dialog handle
  *
  * @return dialog handle
	*/
  Ihandle* get_dialog() { return m_dialog; }

  /**
	* @brief Get canvas detach
  *
  * @return canvas
	*/
  VglCanvas* get_canvas(void);

  /**
	* @brief Get copy of canvas detach
  *
  * @return canvas
	*/
  VglCamera* get_copy_camera(void);

  /**
	* @brief Zoom
	*/
  void zoom(float factor, float x, float y);

  void activate() { m_canvas_detach->Activate(); }
  void postRedraw() { m_canvas_detach->PostRedraw(); }

};

#endif // ANFLEX_INTERFACE_CANVAS_DETAIL_H
