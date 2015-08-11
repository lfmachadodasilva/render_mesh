/**
*/

#ifndef TPV_CUT_GEOMETRY_H
#define TPV_CUT_GEOMETRY_H

#include <GL/glew.h>

#include <ds/array.h>
#include "geometry.h"
#include <topsview/defines.h>
#include <alg/plane.h>
#include <tops/model.h>

#include <stdio.h>

class TpvFemTriangulator;

/**
  Generic cutting plane geometry.
  Extracts polygons of the intersection of the elements of the model
  with a given cutting plane. 
  Currently, only convex elements are supported, thus only convex polygons
  are generated.
  Each created triangle is composed by the vertices of the parent polygon
  and is of the form, for vertex vi: (v(i),v(i+1),v(i+1)).
*/
class TPV_API TpvCutGeometry : public TpvGeometry
{
public:
  TpvCutGeometry ();
  
  virtual ~TpvCutGeometry ();

  TpvTriangleSet* GetTriangleSet ();

  virtual void SetModel (TopModel* m);

  virtual bool SetActiveElements (const bool* active_elems);
  
  virtual void SetField (TpvProperty* p);
  
  virtual void SetFieldOutdated ();

  virtual void SetPerElemColors (TpvProperty* p);

  virtual void SetPerElemColorsOutdated ();
   
  virtual void SetVBOEnabled (bool flag);
  
  virtual void SetBaseElemId (int id);

  virtual void SetDisplacement (float factor, TpvProperty* disp); 

  void SetPlane(float a, float b, float c, float d);

  void GetPlane(float* a, float* b, float* c, float* d);

private:
  enum PlaneStatus {
    PLANE_AT = 0,
    PLANE_IN,
    PLANE_OUT,
    PLANE_CROSS
  };

  // Maps point to (x,y) coordinates in the cutting plane.
  void GetPointInPlane(float x, float y, float z, float* px, float* py)
  {
    x -= m_invbase[12]; y -= m_invbase[13]; z -= m_invbase[14];
    // Ver: É necessário inverter a orientação da base para o algoritmo
    // de fecho convexo ordenar os pontos na direção correta.
    *px = -(m_invbase[0]*x + m_invbase[4]*y + m_invbase[8]*z);
    *py = m_invbase[1]*x + m_invbase[5]*y + m_invbase[9]*z;
  }

  void SortPointsInPlane(int np, 
                         AlgVector* pos, 
                         int* ids, 
                         int* np_out, 
                         int* ids_out);

  PlaneStatus IntersectLinePlane (const AlgVector& p0, 
                                  const AlgVector& dir, 
                                  const AlgPlane& plane, 
                                  float* o_t, 
                                  AlgVector* o_p);

  void ClipElem(const TopElement& el);

  float GetEdgeField(const TopEdgeUse& eu, float t);

  void ExtractGeometry ();

private:
  TpvTriangleSet* m_triset; 
  TpvFemTriangulator* m_triangulator;
  float m_disp_factor;
  TpvProperty* m_disp;

  AlgPlane m_plane;
  float m_invbase[16];
};
#endif

