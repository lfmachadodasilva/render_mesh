//* iupcanvas.h
// celes@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Feb 2003

#ifndef VGL_IUPCANVAS_H
#define VGL_IUPCANVAS_H

#include <vgl/canvas.h>
#include <vgl/vgliup.h>

struct Ihandle_;
typedef struct Ihandle_ Ihandle;

/**
 * This class implements a IUP canvas.\n
 */
class VGLIUPAPI VglIupCanvas : public VglCanvas
{
public:
  /**
   * Constructs a new VglIupCanvas object.
   * \param handle IUP handle that will identify this canvas.
   * \param camera Camera to be associated with this canvas.
   */
  VglIupCanvas (Ihandle* handle, VglCamera* camera);
  /**
   * Destroys a VglIupCanvas object.
   */
  virtual ~VglIupCanvas ();
  /**
   * Gets the IUP window handle.
   * \return IUP window handle.
   */
  Ihandle* GetIupHandle ();
  virtual void SetCursorPos (float x, float y);
  virtual void Activate ();
  virtual bool IsActive ();
  virtual bool IsStereoSupported ();
  virtual void SwapBuffers ();
  virtual int  GetWidth ();
  virtual int  GetHeight ();
  virtual void SetRasterCursor (bool on);
private:
  static int NativeReshape (Ihandle* handle, int w, int h);
  static int NativeRedraw (Ihandle* handle, float x, float y);
  static int NativeKillFocus (Ihandle* handle, Ihandle* newfocus);
private:
  Ihandle* m_handle;
  int m_width;
  int m_height;
  char* m_rastercursor;
  bool m_stereo_supported;
  bool m_stereo_supported_tested;
  bool m_ugl_initialized;
};

#endif
