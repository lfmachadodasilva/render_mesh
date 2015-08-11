//* glutcanvas.h
// celes@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Feb 2003

#ifndef VGL_GLUTCANVAS_H
#define VGL_GLUTCANVAS_H

#include <vgl/canvas.h>
#include <ds/list.h>
#include <vgl/vglglut.h>

/**
 * This class implements a GLUT canvas.
 */
class VGLGLUTAPI VglGlutCanvas : public VglCanvas
{
  int m_win;
  int m_width;
  int m_height;
  int m_rastercursor;

  static void NativeReshape (int w, int h);
  static void NativeRedraw ();
public:
  /**
   * Constructs a new VglGlutCanvas object.
   * \param glutcanvas Glut canvas handle that will identify this canvas.
   * \param camera Camera to be associated with this canvas.
   */
  VglGlutCanvas (int glutwindowhandle, VglCamera* camera);
  /**
   * Destroys a VglGlutCanvas object.
   */
  virtual ~VglGlutCanvas ();
  /**
   * Gets the GLUT window handle.
   * \return GLUT window handle.
   */
  int GetGlutWindow ();
  virtual void SetCursorPos (float x, float y);
  virtual void Activate ();
  virtual bool IsActive ();
  virtual bool IsStereoSupported ();
  virtual void SwapBuffers ();
  virtual int  GetWidth ();
  virtual int  GetHeight ();
  virtual void SetRasterCursor (bool on);
};

#endif
