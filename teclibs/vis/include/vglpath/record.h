// fabraham@tecgraf.puc-rio.br
// May 2006
#ifndef VGL_RECORD_H
#define VGL_RECORD_H

#include <vgl/handler.h>
#include <ds/array.h>
#include "defines.h"

class VglViewSurface;
class VglPath;

/**
 * Record Path Handler.
 * Records a camera path file.
 *
 * Keys:
 * - F1: start a brand new camera path
 * - F2: add a key frame, given the current camera
 * position/orientation/field of view
 * - F3: save camera path file (set up by SetPathFile)
 */
class VGLPATH_API VglRecordPathHandler : public VglHandler
{
  VglViewSurface *m_surface;
  VglPath *m_path;
  char *m_pathfile;
  VglViewSurface *GetSurface ()
  {
    return m_surface;
  }
  void NewPath ();
  void AddKeyFrame ();
  bool SavePath ();
public:
  static const char* CLASSNAME () { return "RecordPathHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructor
   */
  VglRecordPathHandler (VglViewSurface *surface);
  /**
   * Destructor
   */
  virtual ~VglRecordPathHandler ();
  /**
   * Specifies if key presses should be recorded to path.
   */
  void SetRecordKeys (bool f)
  {
    m_record_keys = f;
  }
  /**
   * Sets the camera path file to be saved.
   */
  void SetPathFile (const char *filename);
  /**
   * Load an existing camera path and continues the edition of the camera path.
   * Returns true on success, false otherwise.
   */
  bool LoadPath ();
  virtual int Keyboard (int k, int st, float x, float y);
private:
  DsArray<int> m_pressed_keys;
  bool m_record_keys;
};

#endif
