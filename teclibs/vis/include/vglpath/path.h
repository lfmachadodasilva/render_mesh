// fabraham@tecgraf.puc-rio.br
// May 2006
#ifndef VGL_PATH_H
#define VGL_PATH_H

#include <path/path.h>
#include <ds/array.h>
#include "defines.h"

/**
 * Camera Path, interpolating a set of positions, orientations and
 * camera field of view.
 */
class VGLPATH_API VglPath : public CamPath
{
public:
  VglPath ();
  ~VglPath ();
  void Begin ();
  void AddKeyFrame (double time);
  void SetFovy (double fovy);
  bool ModifyFovy (int i, float fovy);
  /**
   * Adds a keyboard key press to the current key frame.
   */
  void AddKeyFrameKey (int k);
  float GetGivenFovy (int i);
  float GetFovy (double t);
  const DsArray<int>* GetKeys (double t);
  bool Save (const char *filename);
  bool Load (const char *filename);
private:
  DsArray<int>* GetGivenKeys (int i);
private:
  DsArray<float> m_fovy;
  DsArray<DsArray<int>*> m_keys;
  int m_last_i;
};

#endif

