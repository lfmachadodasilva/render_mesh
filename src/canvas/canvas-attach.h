// ------------------------------------------------------------------------
// Anflex Project -- Tecgraf/PUC-Rio
// www.tecgraf.puc-rio.br
//
// $HeadURL: https://subversion.tecgraf.puc-rio.br/svn/anflex-interface/trunk/src/subcanvas.h $
// $Revision: 467 $
// $Date: 2010-12-03 10:26:52 -0200 (sex, 03 dez 2010) $
//
// $Author: lfmachado $
// ------------------------------------------------------------------------

#ifndef ANFLEX_INTERFACE_CANVAS_ATTACH_H
#define ANFLEX_INTERFACE_CANVAS_ATTACH_H

#include <vgl/vgl.h>
#include <vgl/vgliup.h>

#include "canvas.h"

class VglIupOverLayHandler;  

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
class cCanvasAttach : public cCanvas
{
protected:

  VglSubCanvas* m_canvas_attach;

  VglIupOverLayHandler *m_overlay_handler;

public:
  cCanvasAttach(float x, float y, float w, float h,
                VglCanvas* vglParentCanvas,
                VglCamera* vglCamera,
                VglFunction redrawFunction,
                VglFunction redrawEndFunction,
                void(*menuPoupupFunction)(void*),
                void *data);

  /**
	* @brief Get Canvas
  *
  *	@return VglSubCanvas - canvas
	*/
  VglSubCanvas* get_canvas_attach();

  /**
	* @brief Get camera
  *
  *	@return VglCamera - camera
	*/
  VglCamera* get_camera();

  /**
	* @brief Get a camera copy
  *
  *	@return VglCamera - camera
	*/
  VglCamera* get_copy_camera();

  void activate();
  void postRedraw();
};

#endif
