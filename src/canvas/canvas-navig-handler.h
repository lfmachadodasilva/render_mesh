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

#ifndef ANFLEX_INTERFACE_CANVAS_NAVIG_HANDLER_H
#define ANFLEX_INTERFACE_CANVAS_NAVIG_HANDLER_H

#include <vgl/vgl.h>
#include <vgl/vgliup.h>

class cCanvas;

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
class cCanvasNavigHandler : public VglNavigHandler
{
private:

  /**
  * @brief Poupup menu
  */
  void(*poupup_menu_function)(void*);

  /**
  * @brief pointer to canvas
  */
  cCanvas *m_canvas;

protected:

  virtual int MouseButton(int bt, int st, float x, float y);
  virtual int Keyboard (int k, int st, float x, float y);
  virtual int MouseMotion(int bt, float x, float y);

public:

  /**
	* @brief Constructor
  *
  * @param[in] surface
  * @param[in] maxspeed
  * @param[in] accel
  * @param[in] is_main_canvas - is the main canvas
	*/
  cCanvasNavigHandler(VglViewSurface *surface, 
                      double maxspeed, 
                      double accel, 
                      bool is_main_canvas = true);


  /**
	* @brief Set poupup function
  *
  * @param[in] func - poupup function
	*/
  void set_menu_popup_function(void(*func)(void*));

  /**
	* @brief Set canvas
  *
  * @param[in] canvas
	*/
  void set_canvas(cCanvas *canvas);
};

#endif
