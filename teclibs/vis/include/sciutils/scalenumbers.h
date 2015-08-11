// Scale number renderer
// malf@tecgraf.puc-rio.br
// Mar 2011

#ifndef SCIUTILS_SCALE_NUMBER_RENDERER_H
#define SCIUTILS_SCALE_NUMBER_RENDERER_H

#include "defines.h"
#include <ds/list.h>
#include <ufont/fontmanager.h>

class SCIH_API SciScaleNumbersRenderer
{
public: 
  SciScaleNumbersRenderer ();
  ~SciScaleNumbersRenderer ();

  void SetVisible (bool state);
  void SetFont (const char *family_name, int size, bool bold = false, bool italic = false);
  void SetColor (float r, float g, float b, float a);
  void GetColor (float* r, float* g, float* b, float* a);
  void SetDisplayListOutDated ();
  void Render (bool faces[6]);
  void SetValues (int intervals[3], float bb[6], float gap);

private:  
  void RenderSet (bool faces[6]);
  bool FlipText (AlgVector v1, AlgVector v2);
  bool CompareFaceNormals (AlgVector n1, AlgVector n2);

private:
  int m_intervals[3];
  float m_xmin;
  float m_xmax;
  float m_ymin;
  float m_ymax;
  float m_zmin;
  float m_zmax;
  float *m_vx;
  float *m_vy;
  float *m_vz;
  bool m_visible;
  UFontManager* m_fontmanager;
  unsigned int m_node_dl;           // Node display list
  bool  m_update_dl;
  float m_color[4];
  float m_gap;
  AlgVector m_viewDir;
};

#endif
