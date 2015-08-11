// Line sets for reservoirs
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_LINE_SET_H
#define TPVRES_LINE_SET_H

#include <topsviewres/defines.h>
#include <ds/array.h>
#include <stdio.h>
#include <topsview/geometry/lineset.h>

class TopMultiModel;
class UGLArray;

class TPVRES_API TpvResLineSet : public TpvLineSet
{
public:
  TpvResLineSet ();
  virtual ~TpvResLineSet ();
  void SetModel (TopMultiModel *m, bool is_radial, float radial_rw);
private:
  void ComputePositions ();
  void ComputePositionsRadial ();
private:
  float m_radial_rw;
  bool m_is_radial;
};

#endif

