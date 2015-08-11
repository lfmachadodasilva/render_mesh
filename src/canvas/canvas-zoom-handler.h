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

#ifndef ANFLEX_INTERFACE_CANVAS_ZOOM_HANDLER_H
#define ANFLEX_INTERFACE_CANVAS_ZOOM_HANDLER_H

#include <vgl/vgl.h>
#include <vgl/vgliup.h>

class cCanvas;

class cCanvasZoomHandler : public VglZoomHandler
{
private:

  cCanvas *m_canvas;

protected:
  virtual int MouseButton(int bt, int st, float x, float y);
  virtual int MouseMotion(int bt, float x, float y);

public:

  cCanvasZoomHandler (VglViewSurface* surface);
  virtual ~cCanvasZoomHandler ();

  void set_canvas(cCanvas* canvas);
};

#endif // ANFLEX_INTERFACE_CANVAS_ZOOM_HANDLER_H
