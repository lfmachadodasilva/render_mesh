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

#ifndef ANFLEX_INTERFACE_CANVAS_H
#define ANFLEX_INTERFACE_CANVAS_H

#include <vector>
//using namespace std;

// Project libraries
#include "box.h" 
#include "canvas-manip-handler.h"
#include "canvas-mode-handler.h"
#include "canvas-navig-handler.h"
// End of Project libraries

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
class cCanvas
{
protected:

  /**
	* @brief Control if this canvas is a canvas main
	*/
  bool m_is_canvas_main;

  /**
	* @brief Iup handle of the canvas
	*/
  Ihandle* m_canvas_handle;

  /**
	* @brief Vgl Camera
	*/
  VglCamera *m_camera;

  /**
  * @brief Index of current camera
  */
  int m_current_camera;

  /**
  * @brief Vector of cameras
  *
  *	This vector is used to restore the previous view
  */
  std::vector<VglCamera*> m_vet_camera;

  /**
  * @brief Vector of handlers
  *
  *	This vector is used to restore the previous handler
  */
  std::vector<char> m_vet_camera_handle;

  /**
	* @brief Mode handler
  *
  * This handler control the olher handlers
	*/
  cCanvasModeHandler *m_mode_handler;

  /**
	* @brief Manipulation handler
	*/
  cCanvasManipHandler *m_manip_handler;

  /**
	* @brief Navigation handler
	*/
  cCanvasNavigHandler	*m_navig_handler;

  /**
	* @brief Bouding box of the scene
	*/
  sBox m_bbox;

public:

  /**
	* @brief Enum Type of projetion
	*/
  enum eProjectionType
  {
    PLANE_XY = 1,
    PLANE_MINUS_XY,
    PLANE_XZ,
    PLANE_MINUS_XZ,
    PLANE_YZ,
    PLANE_MINUS_YZ,
    ISOMETRIC
  };

  /**
	* @brief Constructor
	*/
  cCanvas(void);

  /**
	* @brief Destructor
	*/
  virtual ~cCanvas(void);

  /**
	* @brief Get Camera
  *
  *	@return VglCamera* - camera used on canvas
	*/
  VglCamera* get_camera(void) { return m_camera; }

  /**
	* @brief Get number of cameras
  *
  *	@return int - number of cameras
	*/
  int get_num_vet_camera(void) { return (int) m_vet_camera.size(); }

  /**
	* @brief Add camera view
  *
  *	@return bool - True if can add or false otherwise
	*/
  bool add_camera_view(void);

  /**
	* @brief Undo camera view
  *
  *	@return bool - True if can undo or false otherwise
	*/
  bool undo_camera_view(void);

  /**
	* @brief Redo camera view
  *
  *	@return bool - True if can redo or false otherwise
	*/
  bool redo_camera_view(void);

  /**
	* @brief Reset vector camera view
	*/
  void reset_camera_view(void);

  /**
	* @brief Get Iup handle canvas
  *
  *	@return Ihandle* - Iup handle canvas
	*/
  Ihandle* get_iup_canvas(void) const { return m_canvas_handle; }

  /**
	* @brief Repaint canvas, the same as post redraw
	*/
  void repaint(void) { postRedraw(); } //{ repaint(); } 

  /**
	* @brief Activate navigation mode
  *
  * @param[in] fit - fit scene before change to navigation handler or not
	*/
  virtual void activate_navig(bool fit = true) { m_mode_handler->active_navig(fit); }

  /**
	* @brief Activate manipulation mode
  *
  * @param[in] fit - fit scene before change to manipulation handler or not
	*/
  virtual void activate_manip(bool fit = true) { m_mode_handler->active_manip(fit); }
  
  /**
	* @brief Activate overlay mode
  *
  * Used only for subcanvas, his handler mode allow to resize and
  * move the subcanvas in the main canvas
	*/
  void activate_overlay(void) { m_mode_handler->active_overlay(); }

  /**
	* @brief Restore used handler
  *
  * Allow to restore last used handler.
  *
	*/
  void restore_handler(void) { m_mode_handler->restore_handler(); }

  /**
	* @brief Is manipulation handler is activated?
  *
  *	@return bool - True if manipulation is activate or false otherwise
	*/
  virtual bool is_activate_manip(void) 
      { return m_mode_handler->IsCurrentHandler(m_manip_handler); }

  /**
	* @brief Is manipulation handler is activated?
  *
  *	@return bool - True if manipulation is activate or false otherwise
	*/
  virtual bool is_activate_navig(void) 
      { return m_mode_handler->IsCurrentHandler(m_navig_handler); }

  /**
	* @brief Zoom in
  *
  * @param[in] factor - zoom factor
	*/
  void zoom_in(double factor = 1.3);

  /**
	* @brief Zoom out
  *
  * @param[in] factor - zoom factor
	*/
  void zoom_out(double factor = 1.3);

  /**
	* @brief Fit
	*/
  void fit(void);

  /**
	* @brief Fit
  *
  * work around (gambiarra) to recalculate the rotation axes
	*/
  void pan(void);

  /**
	* @brief Set projection
  *
  * Change camera view to a defined projection type
  *
  * @param[in] type - eProjectionType
	*/
  void projection(int type);

  /**
	* @brief Orthographic
  *
  * Change camera view to a defined projection type
  *
  * @param[in] mode - True to activate orthographic or false otherwise
	*/
  void orthographic(bool mode);

  /**
	* @brief Is orthographic activate?
  *
  *	@return bool - True if orthographic is activate or false otherwise
	*/
  bool orthographic(void) { return m_camera->GetOrtho(); }

  /**
	* @brief Reset canvas bounding box
	*/
  void reset_bounding_box(void) { m_bbox.reset(); }
  void reset_bounding_box_to_original(void) { set_bounding_box(m_bbox); }

  /**
	* @brief Get canvas bounding box
  *
  *	@return SBox - bounding box
	*/
  sBox get_bounding_box(void) const { return m_bbox; }

  /**
	* @brief Set canvas bounding box
  *
  * @param[in] bbox - bounding box
	*/
  void set_bounding_box(const sBox &bbox);

  /**
	* @brief Get screen coodinatate of mouse position
  *
  * @param[out] x - x screen coordinate
  * @param[out] y - y screen coordinate
	*/
  void get_mouse_pos(float &x, float &y) { m_mode_handler->get_mouse_pos(x, y); };

  virtual void activate() = 0;
  virtual void postRedraw() = 0;
};

#endif // ANFLEX_INTERFACE_CANVAS_H
