/*****************************************************************
*                                                                *
*         @module: Handler                                       *
*           @file: manipplane.h                                  *
*             @id: VglManipPlaneHandler                          *
*        @package: VglLib                                        *
*          @owner: TecGraf                                       *
*         @author: MALF/RODESP/TCS                               *
*        @version: 1.0                                           *
*   @creationdate: oct/2006                                      *
*                                                                *
******************************************************************/

/*****************************************************************
 *   Module Controls                                             *
 *****************************************************************/
#ifndef VGL_MANIP_PLANE_HANDLER_H
#define VGL_MANIP_PLANE_HANDLER_H

/*****************************************************************
 *   Includes                                                    *
 *****************************************************************/
#include <alg/vector.h>
#include <alg/plane.h>
#include <vgl/hnd/selection.h>
#include <vgllib/plane.h>
#include <vgllib/defines.h>

/*****************************************************************
 *  Class Definition                                             *
 *  VglManipPlaneHandler.                                        *
 *  Provides facilities for plane visualization and manipulation.*
 *****************************************************************/
class VGLLIBAPI VglManipPlaneHandler : public VglSelectionHandler
{

public:
  typedef void (*PlaneFunc)(VglManipPlaneHandler* handler, void* data);

  typedef void (*RightButtonFunc)( VglManipPlaneHandler* handler,
                                   int st,
                                   float x,
                                   float y,
                                   void* data);

  virtual const char* ClassName () const{ return "ManipPlaneHandler"; }

  VglManipPlaneHandler( VglViewSurface* surface, VglManipPlane* plane);

  virtual ~VglManipPlaneHandler( void );

  VglManipPlane* GetPlane( void );

  /**
   * Sets whether events are ignored and filtered by this handler (true)
   * or not (false).
   */
  void SetFilterEvents( bool flag );

  bool GetFilterEvents( void );

  void SetPointEnabled( int pointid, bool flag )
  {
    m_point_enabled[pointid] = flag;
  }

  bool GetPointEnabled( int pointid )
  {
    return m_point_enabled[pointid];
  }

  /**
   * Enables/disables orthographic projection for plane drawing.
   */
  void SetOrtho( bool ortho )
  {
    m_ortho = ortho;
  }

  bool GetOrtho( void )
  {
    return m_ortho;
  }

  /**
      Sets plane color.
  */
  void SetColor( float r, float g, float b, float a )
  {
    m_r = r; m_g = g; m_b = b, m_a = a;
  }

  void GetColor( float* r, float* g, float* b, float* a )
  {
    *r = m_r; *g = m_g; *b = m_b; *a = m_a;
  }

  /**
      Sets whether a translucent plane mask will be drawn in plane's area.
  */
  void SetMaskEnabled( bool f )
  {
    m_mask_enabled = f;
  }

  /**
      Sets the color of the translucent plene mask.
  */
  void SetMaskColor( float r, float g, float b, float a )
  {
    m_mask_r = r; m_mask_g = g; m_mask_b = b, m_mask_a = a;
  }

  void GetMaskColor( float* r, float* g, float* b, float* a )
  {
    *r = m_mask_r; *g = m_mask_g; *b = m_mask_b; *a = m_mask_a;
  }

  /**
    Returns whether the plane is being dragged or not.
  */
  bool IsDragging( void );

  /**
    Returns the id of the picked point or -1.
  */
  int GetPickedPoint( void );

  /**
    Function called when the plane is dragged.
  */
  void SetDragPlaneFunc     ( PlaneFunc func, void* data       );
  void SetTransformPlaneFunc( PlaneFunc func, void* data       );
  void SetBeginDragPlaneFunc( PlaneFunc func, void* data       );
  void SetEndDragPlaneFunc  ( PlaneFunc func, void* data       );
  void SetRightButtonFunc   ( RightButtonFunc func, void* data );
  /**
    Enables/disabled calling PlaneFunc when the mouse is moved, even if the plane is not
    being dragged.
  */
  void SetMotionEventEnabled(bool flag);

  void ProcessFunction(VglSelectionHit *hits, int n);

  int Keyboard(int k, int st, float x, float y);

  int MouseMotion(int bt, float x, float y);

  int MouseButton(int bt, int st, float x, float y);

  int MouseEntry(bool st);

  int MouseWheel(float delta, float x, float y);

  virtual void SetSelectionRenderFunc(SelectionFunc f, void* data);

  virtual int PostRedraw(void);

private:
  enum {
    PLANE_AREA = VglManipPlane::POINT_MAX
  };

  VglViewSurface* m_surface;
  VglManipPlane* m_plane;
  SelectionFunc m_selection_func;
  void* m_selection_data;
  PlaneFunc m_drag_func;
  void* m_drag_data;
  PlaneFunc m_begin_drag_func;
  void* m_begin_drag_data;
  PlaneFunc m_load_transform_func;
  void* m_load_transform_data;
  PlaneFunc m_end_drag_func;
  void* m_end_drag_data;
  RightButtonFunc m_right_button_func;
  void* m_right_button_data;

  bool m_point_enabled[VglManipPlane::POINT_MAX];

  bool m_isdragging;
  bool m_motionevent;
  int m_pickedpoint;
  bool m_pickedplane;
  bool m_filterevents;

  bool m_ortho;
  float m_radius;
  float m_computed_radius;
  float m_r, m_g, m_b, m_a;
  float m_mask_r, m_mask_g, m_mask_b, m_mask_a;
  bool m_mask_enabled;

  struct PlaneRenderData
  {
    VglManipPlaneHandler* handler;
    AlgVector point;
    AlgVector right;
    AlgVector up;
    PlaneRenderData(VglManipPlaneHandler* h, AlgVector p, AlgVector r, AlgVector u)
      : handler(h), point(p), right(r), up(u) {}
  };

  void ComputeSphereRadius();
  void Draw(bool selection=false);
  void DrawSelection();

  static void PlaneSelectionRender(void* data);
  float ComputeProjEyeDir(AlgVector v);
  static void PlanePointPickRender(void* data);
  void BeginDrag();
  void EndDrag();
  AlgVector RotateVectorPointPick(AlgVector point, AlgVector axis, AlgVector vector,
      float x, float y, PlaneRenderData* data);
  void SpinPlanePointPick(AlgVector point, float x, float y);
  void RotatePlaneUpPointPick(AlgVector point, float x, float y);
  void RotatePlaneRightPointPick(AlgVector point, float x, float y);
  void TranslatePlanePointPick(float dx, float dy);
  AlgVector RotateVector(AlgVector vector, AlgVector rot_axis, AlgVector tang_dir, float x, float y);
  void SpinPlane(int pickedpoint, float x, float y);
  void RotatePlaneUp(int pickedpoint, float x, float y);
  void RotatePlaneRight(int pickedpoint, float x, float y);
  void TranslatePlane(float x, float y);
  void Drag(float x, float y);
  void DrawBoundingBox();
};

#endif
