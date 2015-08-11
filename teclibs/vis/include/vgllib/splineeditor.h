// splineeditor.h
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// May 2008
#ifndef VGL_SPLINE_EDITOR_H
#define VGL_SPLINE_EDITOR_H

#include <GL/glew.h>
#include "defines.h"
#include <vgl/utils/selection.h>

#define VGL_SPLINE_LINE   1
#define VGL_SPLINE_HANDLE 2

#define VGL_SPLINE_CURRSPLINE  1
#define VGL_SPLINE_OTHERSPLINE 2

class VglViewSurface;

class VGLLIBAPI VglSplineObject
{
public:
  virtual ~VglSplineObject ();
  void SetBeingEdited (bool flag);
  void SetID (int id)
  {
    m_id = id;
  }
  int GetID () const
  {
    return m_id;
  }
  virtual int GetNumPoints () const = 0;
  virtual void Begin () = 0;
  virtual void AddPosition (float x, float y, float z) = 0;
  virtual void AddPosition (int index, float x, float y, float z) = 0;
  virtual void RemovePosition (int index) = 0;
  virtual void ModifyPosition (int index, float x, float y, float z) = 0;
  virtual void End () = 0;
  virtual void Recompute () = 0;
  virtual void GetPosition (double t, float* x, float* y, float *z) = 0;
  virtual void GetGivenPosition (int index, float* x, float* y, float *z) = 0;
  virtual void Draw () = 0;
protected:
  VglSplineObject ();
  bool IsBeingEdited () const
  {
    return m_being_edited;
  }
private:
  int m_id;
  bool m_being_edited;
};

class VGLLIBAPI VglSplineEditor
{
public:
  typedef VglSplineObject* (*SplineCreateFunc)(void* data);
  typedef VglSplineObject* (*SplineGetFunc)(int stackdepth, const GLuint* namestack, void* data);
  VglSplineEditor (VglViewSurface* surface);
  ~VglSplineEditor ();
  void SetSplineLocationSelectionFunc (VglSelectionFunction func, void* data);
  void SetSplineCreationFunc (SplineCreateFunc func, void* data);
  void SetSplineSelectionFunc (VglSelectionFunction func, void* data);
  void SetSplineGetFunc (SplineGetFunc func, void* data);
  void AddSplineObject (VglSplineObject* object);
  int GetNumSplines () const;
  VglSplineObject* GetSplineObject (int spline_index);
  VglSplineObject* GetCurrSplineObject () const
  {
    return m_curr_spline;
  }
  void BeginCreation (AlgVector& pos, bool atbeginning);
  void SetMouseAt (float x, float y);
  void SetLineEnd (float wx, float wy, float wz);
  void DrawFeedBack ();
  bool IsCreatingAtBeginning () const
  {
    return m_creating_at_beginning;
  }
  void EndCreation ();
  bool IsCreating () const
  {
    return m_creating;
  }
  bool Pick (float x, float y);
  int GetPickedSpline ();
  int GetPickedHandle ();
  bool PickedSplineLine ();
  void CreateHandleAtPickedPos ();
  void SetCurrSpline (int spline_index);
  void SetCurrSpline (VglSplineObject* object);
  int GetCurrSplineIndex ();
  void RemoveNode (int handle_index);
  void BeginMove (int handle_index);
  void Move (float x, float y);
  void EndMove ();
  bool IsMoving () const
  {
    return m_move_handle >= 0;
  }
  void RemoveSpline (VglSplineObject* object);
  void ResetSpline ();
  int GetCurrSplineNumPoints () const
  {
    return m_curr_spline->GetNumPoints();
  }
  void GetPoint (int index, float* x, float* y, float* z);
protected:
  VglViewSurface* GetSurface () const
  {
    return m_surface;
  }
private:
  void SelectSpline ();
  bool PickSplineLocation (float x, float y, float *wx, float *wy, float *wz);
  static void SelectSpline (void* data)
  {
    VglSplineEditor* e = (VglSplineEditor*)data;
    e->SelectSpline();
  }
private:
  VglViewSurface* m_surface;
  VglSelection m_selection;
  VglSelectionRendererCB m_selrenderer;
  VglClosestHitProcessor m_processor;
  VglSelectionFunction m_location_sel_func;
  void* m_location_sel_data;
  SplineCreateFunc m_create_func;
  void* m_create_data;
  VglSelectionFunction m_spline_sel_func;
  void* m_spline_sel_data;
  SplineGetFunc m_spline_get_func;
  void* m_spline_get_data;
  AlgVector m_line_start;
  AlgVector m_line_end;
  DsPList<VglSplineObject> m_splines;
  VglSplineObject* m_curr_spline;
  int m_picked_spline;
  int m_move_handle;
  float m_pick_x;
  float m_pick_y;
  bool m_creating;
  bool m_line_end_set;
  bool m_creating_at_beginning;
};

#endif

