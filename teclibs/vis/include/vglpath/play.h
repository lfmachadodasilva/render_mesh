// fabraham@tecgraf.puc-rio.br
// May 2006
#ifndef VGL_PLAY_H
#define VGL_PLAY_H

#include <vgl/handler.h>
#include "defines.h"

class VglPath;
class VglManipViewSurface;

/**
 * Play Path Handler.
 * Reproduces a given camera path file.
 *
 * Keys:
 * - 1 till 9: go to key frame 'n' (if available).
 * - p or P:   play camera path.
 * - F5:       reload camera path file.
 *
 * TODO:
 * - stop / reverse / fast rewind / fast forward
 */
class VGLPATH_API VglPlayPathHandler : public VglHandler
{
public:
  enum
  {
    PLAY_PATH,
    RELOAD_PATH
  };
  static const char* CLASSNAME () { return "PlayPathHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructor
   */
  VglPlayPathHandler (VglManipViewSurface *canvas);
  /**
   * Destructor
   */
  virtual ~VglPlayPathHandler ();
  /**
   * Sets the camera path file and tries to load it.
   * Returns true on success, false otherwise.
   */
  bool SetPathFile (const char *filename);
  /**
   * Specifies that the frame interpolation must happen
   * 'fps' times for every second of the camera path.
   */
  void SetFrameRate (double fps);
  /**
   * Specifies that the frame interpolation must happen
   * according the the current time.
   */
  void SetNoFrameRate ();
  /**
   * Sets a callback that will be called when the animation starts.
   * (right before the first frame is requested)
   */
  void SetPlayStartFunc (VglFunction f, void *data)
  {
    m_play_start_func = f;
    m_play_start_data = data;
  }
  /**
   * Sets a callback that will be called when the animation ends.
   * (right after the final frame is rendered)
   */
  void SetPlayEndFunc (VglFunction f, void *data)
  {
    m_play_end_func = f;
    m_play_end_data = data;
  }
  void SetKey (int function, int key)
  {
    switch(function)
    {
      case PLAY_PATH:   m_play_path_key   = key; break;
      case RELOAD_PATH: m_reload_path_key = key; break;
    }
  }
  /**
   * Starts the path animation.
   */
  void PlayPath ();
  virtual int Keyboard (int k, int st, float x, float y);
private:
  VglManipViewSurface* GetSurface () const
  {
    return m_surface;
  }
  void SetParameters (double time);
  void UpdateCamera ();
  bool ReloadPath ();
  void GotoFrame (int i);
  bool FixedInterpolation () const
  {
    return m_fps != NULL;
  }
  double GetFrameRate () const;
  double GetElapsedTime ();
  void BeginAnimation ();
  void EndAnimation ();
  static void SetParametersIdle (void* data);
private:
  VglManipViewSurface* m_surface;
  VglPath *m_path;
  char *m_pathfile;
  double m_t0;
  // fixed interpolation parameters
  double *m_fps;
  int *m_nframes;
  VglFunction m_play_start_func;
  void *m_play_start_data;
  VglFunction m_play_end_func;
  void *m_play_end_data;
  int m_play_path_key;
  int m_reload_path_key;
};

#endif
