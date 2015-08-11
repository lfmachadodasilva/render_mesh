// smoothquad.h
// Represents a smooth quad-strip based on a spline


#ifndef path_smoothquad_h
#define path_smoothquad_h

#include "alg/vector.h"
#include "ds/array.h"
#include "alg/spline.h"
#include "defines.h"

class PATH_API ShpSmoothQuad
{
public:

  ShpSmoothQuad (float* verts, int nv);
  ShpSmoothQuad (AlgSpline* spl, int nseg=100);
  ~ShpSmoothQuad ();
  void ComputeStrip (float delta, float ux, float uy, float uz);
  void SetSizeFactor (float factor);
  void SetUseTexCoord1 (bool state);
  void SetTexCoord1 (int seg, float s);
  void Draw ();
  void DrawTail (float headfactor=1.0f);
  void DrawHead (float headfactor=1.0f);
  void DrawBody (float tailfactor=1.0f, float headfactor=1.0f);

private:

  int FindHeadIndex (float dist);
  int FindTailIndex (float dist);
  float SegLength (int itail, int ihead);

private:

  struct Pair {
    Pair () { }
    Pair (float x, float y) : s(x), t(y) { }
    float s,t;
  };

  float m_delta;
  float m_sizefactor;
  AlgVector m_normal;
  DsArray<AlgVector> m_pts;
  DsArray<AlgVector> m_coord;
  DsArray<Pair> m_texcoord0;
  DsArray<float> m_texcoord1;
  bool m_usetexcoord1;
};

#endif
