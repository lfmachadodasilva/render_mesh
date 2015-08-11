//* planeinbox.h
// Tecgraf/PUC-Rio
// Jan 2003

#ifndef VGL_PLANEINBOX_H
#define VGL_PLANEINBOX_H

#include <vgl/handler.h>
#include <vgl/hnd/objectpick.h>
#include <vgllib/defines.h>


#include "alg/vector.h"
#include "alg/matrix.h"

class VglViewSurface;

/*
** VGL Plane-in-Box Handler
*/
class VGLLIBAPI VglPlaneInBoxHandler : public VglObjectPickHandler
{
public:
  typedef int  (*MenuFunc)(VglPlaneInBoxHandler* handler, void* data);
  typedef void (*DragFunc)(VglPlaneInBoxHandler* handler, void* data);

  static const char* CLASSNAME () { return "PlaneInBoxHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  VglPlaneInBoxHandler (VglViewSurface* surface);
  virtual ~VglPlaneInBoxHandler ();
  virtual int MouseButton (int bt, int st, float x, float y);
  virtual int MouseMotion (int bt, float x, float y);
  virtual int PostRedraw ();

  void SetMenuFunc (MenuFunc func, void * data);
  void SetEndDragFunc (DragFunc func, void * data);
  void SetBeginDragFunc (DragFunc func, void * data);

  void SetFitFactor (float factor);
  void SetBox 
    (float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
  void SetRenderingTransform (const AlgMatrix& m);
  void SetRenderingOffsets( float minZOffset, float maxZOffset );
  void SetAxis (int axis);
  void SetInversion (bool flag);
  void SwapSide (void);
  void SetEnabled (bool flag);

  const AlgPlane& GetPlane (bool rendering);
  void GetPlaneEquation (bool rendering, float* a, float* b, float* c, float* d);
  bool GetBoxState (void);
  bool GetPlaneState (void);

  void SetPlaneVisibility (bool visible);
  void SwapPlaneVisibility (void);
  void SetBoxVisibility (bool visible);
  void SwapBoxVisibility (void);
  void SetPlaneOpacity (float opacity);
  void SetSphereRadius (float radius);
  void SetHighlightColor (float r, float g, float b);
  void SetPlaneColor (float r, float g, float b);
  void SetSphereColor (float r, float g, float b);
  void SetBoxColor (float r, float g, float b);

private:
  static void SelectionRender (void* data);
  static void HandlePick (unsigned int id, int bt, void* data);
  const AlgPlane& ExtractPlane (int i0, int i1, int i2);
  AlgVector Intersect 
    (const AlgPlane &p, const AlgVector& o, const AlgVector& d);
  int Intersect 
    (const AlgPlane &p, const AlgVector& o, const AlgVector& d, float *t);
  bool BoxIntersect
    (const AlgVector& o, const AlgVector& d, float *tMin, float *tMax);
  bool InfiniteBoxIntersect
    (const AlgVector& o, const AlgVector& d, float *tMin, float *tMax);
  float AngleDegrees (const AlgVector &o, const AlgVector &d);
  void AdjustControlPoints (void);
  void DrawPlane ();
  void DrawBox ();
  void DrawHelper (int i);
  void DrawSpheres (bool picking=false);
  void UpdateTransforms (void);
  void UpdatePlane (bool adjustCenter = true);
  void TestBoxEdge (const AlgVector &edgeVertex1, const AlgVector &edgeVertex2);
  AlgVector ComputePlaneCentroid (void);
  bool AreInSameFace (const AlgVector &pos1, const AlgVector &pos2);

  void SavePlane (void);
  void RestorePlane (void);

  MenuFunc m_menufunc;
  void * m_menufunc_data;
  DragFunc m_endfunc;
  void * m_endfunc_data;
  DragFunc m_beginfunc;
  void * m_beginfunc_data;

  VglViewSurface* m_surface;
  int m_picked;                               // id of the currently picked sphere handle (-1 = none, 0 = center)
  int m_highlighted;                          // id of the currently highlighted sphere handle
  int m_invertPlane;                          // flag: which side of the plane to cut
  float m_fitFactor;                          // box fit factor (how many times bigger than the enclosed model)
  float m_sRadius[5];                         // spheres handles radius (in world space)
  float m_sRadiusInPixels;                    // spheres radius in pixels
  bool m_pVisible;                            // cut plane visible status
  bool m_bVisible;                            // box visible status
  bool m_enabled;                             // control enabled status
  float m_pOpacity;                           // cut plane opacity
  float m_pRed, m_pGreen, m_pBlue;            // cut plane color
  float m_sRed, m_sGreen, m_sBlue;            // sphere handles color
  float m_bRed, m_bGreen, m_bBlue;            // box color
  float m_hRed, m_hGreen, m_hBlue;            // highlight and helper color
  AlgVector m_normal, m_tangent, m_binormal;  // plane orientation vectors
  AlgVector m_backupNormal, m_backupTangent;  // backup orientation vectors and center...
  AlgVector m_backupBinormal, m_backupCenter; // ...to allow canceling a manipulation
  AlgVector m_box[2];                         // box corner points
  AlgVector m_points[5];                      // positions of the sphere handles
  AlgVector m_planeVertices[6];               // positions of the clipped plane vertices
  AlgMatrix m_externalRenderTransform;        // rendering transform to account for model scale and distortion
  AlgMatrix m_transform;
  AlgMatrix m_renderTransform;
  AlgPlane  m_plane;                          // cut plane
  float m_minZOffset, m_maxZOffset;           // z offsets for rendering to account for layer separation and well height
  int m_numPlaneVertices;
  bool m_frontFaceTarget;
  bool m_decideFaceTarget;
};

#endif
