#ifndef SGVGL_EDITABLE_SPLINE_PIPE_H
#define SGVGL_EDITABLE_SPLINE_PIPE_H

#include <vgllib/splineeditor.h>
#include <alg/spline.h>
#include <sgvgl/defines.h>
#include <sg/shape.h>

class SGPipe;

class SGVGLAPI SGEditableSplinePipeFloor
{
public:
  virtual ~SGEditableSplinePipeFloor ()
  {
  }
  virtual float GetHeight (float x, float z) = 0;
};

class SGVGLAPI SGEditableSplinePipe : public SGShape, public VglSplineObject
{
public:
  typedef SGPipe* (*BuildPipeFunc)(float radius, int slices, void* data);
  /**
   * Constructor
   */
  SGEditableSplinePipe (float radius, int slices=16);
  virtual ~SGEditableSplinePipe ();
  void SetRefinement (int r);
  void SetSplineFloor (SGEditableSplinePipeFloor* floor)
  {
    m_floor = floor;
  }
  void SetBuildPipeFunc (BuildPipeFunc func, void* data)
  {
    m_build_pipe_func = func;
    m_build_pipe_data = data;
  }
  void SetBuildTexCoords (bool f)
  {
    m_build_tex_coords = f;
  }
  void SetFloorDisplacement (float d);
  // vglsplineobject
  int GetNumPoints () const;
  void Begin ();
  void AddPosition (float x, float y, float z);
  void AddPosition (int index, float x, float y, float z);
  void RemovePosition (int index);
  void ModifyPosition (int index, float x, float y, float z);
  void End ();
  void Recompute ();
  void GetPosition (double t, float* x, float* y, float *z);
  void GetGivenPosition (int index, float* x, float* y, float *z);
  // sgshape/vglsplineobject
  void Draw ();
  // sgshape
  int GetLineCount ();
  int GetTriangleCount ();
  int GetVertexCount ();
  void GetVertex (int index, float *x, float *y, float *z);
  void Write (UtlWriter* writer);
private:
  void RecomputePipe ();
  void DrawBeingEdited ();
private:
  AlgSpline m_spline;
  SGPipe* m_pipe;
  float m_radius;
  int m_slices;
  int m_refinement;
  SGEditableSplinePipeFloor* m_floor;
  float m_displacement;
  BuildPipeFunc m_build_pipe_func;
  void* m_build_pipe_data;
  bool m_update_pipe;
  bool m_build_tex_coords;
};

SGVGLAPI void sgvgl_add_spline_pipe (VglSplineEditor *editor, SGEditableSplinePipe* pipe);
SGVGLAPI VglSplineObject* sgvgl_cast_to_spline_object (SGEditableSplinePipe* pipe);

#endif

