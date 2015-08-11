// Camera class
// celes@tecgraf.puc-rio.br
// Jan 2003

#ifndef VGL_CAMERA_H
#define VGL_CAMERA_H

#include <alg/matrix.h>
#include <alg/plane.h>
#include <ds/stack.h>
#include <stdio.h>
#include "defines.h"
#include "frustum.h"

class UtlWriter;

class VGL_API VglCamera
{
  bool      m_updated;
  bool      m_auxfrustumupdated;
  bool      m_ortho;
  bool      m_autofit;
  bool      m_box_set;
  bool      m_stdist;
  int       m_fitmode;
  int       m_curreye;
  int       m_headlight;
  float     m_angle;
  float     m_aspect;
  float     m_znear, m_zfar;
  float     m_fitfactor;
  float     m_shiftx, m_shifty;
  float     m_zcenter;
  float     m_pmin, m_pmax;
  float     m_width, m_distance;
  float     m_zps, m_vzps;
  float     m_tc, m_hit;

  AlgVector m_pos;
  AlgVector m_target;
  AlgVector m_up;
  AlgVector m_dop;

  AlgVector m_center;
  AlgVector m_box[8];

  AlgStackMatrix m_stack;
  AlgMatrix m_currmatrix;
  AlgMatrix m_lasttransf;
  AlgMatrix m_rotation;
  AlgVector m_vmin, m_vmax;   // view volume (calculated)
  AlgVector m_uvmin, m_uvmax;   // view volume (user specified)

  int (*m_validate)(void*);
  void* m_vdata;


  class VGL_API ZoomStack
  {
  public:
    struct ZoomData {
      float factor;
      float tx;
      float ty;
      ZoomData(){}
      ZoomData(float s, float x, float y)
        : factor(s), tx(x), ty(y)
      {
      }
    };
  private:
    int m_top;
    DsArray<ZoomData> m_array;
  public:
    ZoomStack ();
    ZoomStack (ZoomStack &zs);
    void operator= (ZoomStack &zs);
    void Clear ();
    bool Undo ();
    bool Redo ();
    bool CanUndo ();
    bool CanRedo ();
    void Zoom (ZoomData& d);
    bool WasZoomed ();
    bool IsChanged ();
    ZoomData* Top ();
    friend class VglCamera;
  };
  ZoomStack m_zoomstack;

public:
  static const char* CLASSNAME () { return "Camera"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
  * Constructs a new VglCamera object.
  */
  VglCamera ();
  /**
   * Constructs a copy of 'camera'.
   */
  VglCamera (VglCamera *camera);
  /**
  * Destroys a VglCamera object.
  */
  virtual ~VglCamera ();
  /**
   * Copy of the parameters of a 'camera'.
   */
  void SetCamera (VglCamera *camera);
  /**
  * Sets orthographic or perspective projection.
  * \param value true for orthographic, false for perspective projection.
  */
  void SetOrtho (bool flag);
  /**
  * Gets projection type.
  * \return true for orthographic, false for perspective projection.
  */
  bool GetOrtho () const
  {
    return m_ortho;
  }
  /**
  * Sets the camera position in world coordinates.
  * \param x x coordinate.
  * \param y y coordinate. 
  * \param z z coordinate.
  */
  void SetPosition (float x, float y, float z);
  /**
   * Obtains the observer position set through 'SetPosition'.
   * For an updated position, use GetUpdatedPosition.
   */
  void GetPosition (float* ox, float* oy, float* oz) const
  {
    *ox = m_pos.x;
    *oy = m_pos.y;
    *oz = m_pos.z;
  }
  /**
   * Obtains the current observer position in world coordinates.
   */
  void GetUpdatedPosition (float* ox, float* oy, float* oz)
  {
    AlgVector pos = GetUpdatedPosition();
    *ox = pos.x;
    *oy = pos.y;
    *oz = pos.z;
  }
  /**
   * Obtains the current observer position in world coordinates, vector form.
   */
  AlgVector GetUpdatedPosition ();
  /**
  * Sets the camera target in world coordinates (where to look at).
  * \param x x coordinate.
  * \param y y coordinate. 
  * \param z z coordinate.
  */
  void SetTarget (float x, float y, float z);
  void GetTarget (float* x, float* y, float* z);

  /**
  * Sets the camera up vector.
  * \param nx x coord.
  * \param ny y coord.
  * \param nz z coord.
  */
  void SetUp (float nx, float ny, float nz);
  /**
   * Obtains the up vector set through 'SetUp'.
   * For an updated vector, use GetUpdatedUp.
   */
  void GetUp (float* nx, float* ny, float* nz);
  /**
   * Obtains the current up vector in world coordinates.
   */
  void GetUpdatedUp (float* onx, float* ony, float* onz)
  {
    AlgVector up = GetUpdatedUp();
    *onx = up.x;
    *ony = up.y;
    *onz = up.z;
  }
  /**
   * Obtains the current up vector in world coordinates, vector form.
   */
  AlgVector GetUpdatedUp ();
  /**
  * Sets the angle of the field of view in the x-z plane.
  * 'fovy' is the angle in degrees, 0 < fovy < 180.
  */
  void SetAngle (float fovy);
  /**
   * Obtains the camera's field of view angle set through SetAngle.
   * For an updated value, use GetUpdatedAngle.
   */
  float GetAngle () const { return m_angle; }
  /**
   * Obtains the current field of view angle (Y) in degrees, vector form.
   */
  float GetUpdatedAngle ();
  /**
  * Sets the camera aspect ratio (width/height).
  */
  void SetAspect (float aspect);
  /**
   * Gets the camera aspect radio (width/height).
   */
  float GetAspect () const
  {
    return m_aspect;
  }
  /**
   * Sets the near and far clipping planes.
   * \param znear Near plane.
   * \param zfar Far plane.
   */
  void SetZPlanes (float znear, float zfar);
  /**
   * Obtains the near and far planes set through SetZPlanes.
   * For updated values, use GetUpdatedZPlanes.
   */
  void GetZPlanes (float *znear, float *zfar) const
  {
    *znear = m_znear;
    *zfar = m_zfar;
  }
  /**
   * Obtains the current near and far plane distances to the observer.
   */
  void GetUpdatedZPlanes (float *znear=NULL, float *zfar=NULL);
  /**
   * Obtains the current near plane distance to the observer.
   */
  float GetUpdatedZNear ();
  /**
   * Obtains the current far plane distance to the observer.
   */
  float GetUpdatedZFar ();
  /**
   * Sets the aimed camera rotation.
   * \param rotation Camera rotation matrix. 
   */
  void SetRotation (const AlgMatrix& rotation);
  /**
   * Sets the aimed camera rotation.
   * \param angle Camera rotation angle. 
   * \param x     Camera rotation axis x. 
   * \param y     Camera rotation axis y. 
   * \param z     Camera rotation axis z. 
   */
  void SetRotation (float angle, float x, float y, float z);
  /**
   * Sets the camera shift.
   * shiftx and shifty are in normalized coordinates.
   */
  void SetShift (float shiftx, float shifty);
  /**
   * Gets the camera shift.
   */
  void GetShift (float* shiftx, float* shifty)
  {
    *shiftx = m_shiftx;
    *shifty = m_shifty;
  }
  float GetZCenter ();
  virtual AlgMatrix GetModelview ()
  {
    return GetViewMatrix();
  }
  virtual AlgMatrix GetViewMatrix ();
  AlgMatrix GetProjection ()
  {
    return GetProjectionMatrix();
  }
  AlgMatrix GetProjectionMatrix ();
  /**
   * Sets the current view volume. Only used in orthographic projection when autofit is disabled.
   * The view volume is calculated when autofit is enabled and when a perspective projection is used.
   */
  void SetViewVolume (float xmin, float ymin, float zmin, float xmax, float ymax, float zmax);
  /**
   * Obtains the current view volume.
   */
  void GetViewVolume (float* xmin, float* ymin, float* zmin, float* xmax, float* ymax, float* zmax);
  /**
   * Sets the model's bounding box.
   * Only useful in autofit mode.
   */
  void SetBox (float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
  /**
   * Obtains the box set by 'SetBox'.
   */
  void GetBox (float* xmin, float* xmax, float* ymin, float* ymax, float* zmin, float* zmax);
  /**
   * Obtains the box vertices set by 'SetBox'. (vector form, 8 vertices)
   */
  const AlgVector* GetBox ();
  const AlgVector* GetViewBox ()
  {
    return GetBox();
  }
  /**
   * Obtains the center of the given bounding box (same coordinate system).
   */
  void GetBoxCenter (float *oxc, float *oyc, float *ozc);
  /**
   * Enables/disables automatic model fitting.
   * If enabled, requires the configuration of a model bounding box.
   */
  void SetAutoFit (bool flag);
  /**
   * Specifies the fitting mode.
   * VGL_FIT_SPHERE considers the possibility of box rotation, so it fits the
   * sphere that bounds the box into the frustum.
   * VGL_FIT_2D fits the box into the frustum, disconsidering rotations.
   */
  void SetFitMode (int mode);
  /**
   * Obtains the current fit mode.
   */
  int GetFitMode ()
  {
    return m_fitmode;
  }
  /**
   * Specifies the direction of projection (for model autofitting).
   */
  void SetDOP (float x, float y, float z);
  void SetDOP (AlgVector dop)
  {
    SetDOP(dop.x,dop.y,dop.z);
  }
  /**
   * Obtains the current view direction vector in world coordinates.
   */
  void GetUpdatedViewDir (float* ovx, float* ovy, float* ovz)
  {
    AlgVector dop = GetUpdatedViewDir();
    *ovx = dop.x;
    *ovy = dop.y;
    *ovz = dop.z;
  }
  /**
   * Obtains the current view direction vector in world coordinates, vector form.
   */
  AlgVector GetUpdatedViewDir ();
  /**
   * Specifies the automatic model fitting fit factor (a scale factor applied to the fitting).
   */
  void SetFitFactor (float factor);
  /**
   * Enables automatic model fitting (computes camera parameters to fit the entire model in the direction of projection)
   * x,y,z are the direction of projection (DOP)
   * factor specifies a scale factor applied to the fitting.
   */
  void EnableAutoFit (float x=0.0f, float y=0.0f, float z=0.0f, float factor=0.0f)
  {
    SetAutoFit(true);
    SetDOP(x,y,z);
    SetFitFactor(factor);
  }
  void DisableAutoFit ()
  {
    SetAutoFit(false);
  }
  //* Stereo parameters
  // Set the current eye (-1=stereo left, 0=mon, 1=stereo right)
  void SetCurrEye (int eye);
  int GetCurrEye ();

  // Set parallax min and max (in degrees)
  void SetParallax (float pmin, float pmax);
  void GetParallax (float* opmin=NULL, float *opmax=NULL) const
  {
    if (opmin != NULL)
      *opmin = m_pmin;
    if (opmax != NULL)
      *opmax = m_pmax;
  }
  // Set screen
  void SetPhysicalScreen (float w, float d);
  void GetPhysicalScreen (float *ow=NULL, float *od=NULL) const
  {
    if (ow != NULL)
      *ow = m_width;
    if (od != NULL)
      *od = m_distance;
  }
  // Set zero parallax setting (from 0.0 to 1.0)
  void SetZeroParallax (float zps);

  // Avoid stereo distortion in depth?
  void SetStereoDistortion(bool avoid);

  float GetComputedZPS ();

  //* Utility functions 

  /**
   * Centers the view.
   * Requires a previously set model bounding box.
   */
  void CenterView ();

  /**
   * Fits the model's bounding box inside the current frustum.
   * Maintains the rotations to the model.
   * A fitting factor, specified in SetFitFactor will be used.
   * Requires a previously set model bounding box.
   */
  void FitView ();
  /**
   * Sets up a light source located in the observers' head.
   * GL_LIGHT0 <= 'lightid' <= GL_LIGHT7 or lightid == 0 (disables headlight).
   */
  void SetHeadlight (int lightid);
  // Loads the corresponding modelview and projection matrices.
  void Load ();

  //* Transform functions

  //* Push transformation
  void PushMatrix ();

  //* Pop transformation
  void PopMatrix ();

  //* Load identity
  void LoadIdentity ();

  //* Translate
  void Translate (float x, float y, float z);

  //* Translate camera in world coordinates
  void TranslateW (float x, float y, float z);

  //* Rotate
  void Rotate (float angle, float x, float y, float z);

  //* Translate view
  void TranslateView (float x, float y, float z);

  //* Translate zoom
  void TranslateZoom (float x, float y);

  //* Rotate view
  void RotateView (float angle, float x, float y, float z);

  //* Scale view
  void ScaleView (float sx, float sy, float sz);

  //* Scale zoom
  void ScaleZoom (float s);

  //* Undo last transformation
  void UndoTransform ();

  //* Redo last transformation
  void RedoTransform ();

  //* Set validation callback
  // It should return 0 if transform is to be invalidated.
  void SetValidateFunc (int (*func)(void*), void* data=0);

  //* Zoom
  void Zoom (float factor, float x=0.5f, float y=0.5f);

  //* Zoom to a box
  void Zoom (float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);

  //* Undo Zoom
  int UndoZoom ();

  //* Redo Zoom
  int RedoZoom ();

  //* Reset Zoom
  void ResetZoom ();
  /**
   * Is camera in zoom mode?
   */
  bool HasZoom ()
  {
    return m_zoomstack.IsChanged();
  }
  /**
   * Can a camera zoom be undone?
   */
  bool CanUndoZoom ()
  {
    return m_zoomstack.CanUndo();
  }
  /**
   * Can a camera zoom be redone?
   */
  bool CanRedoZoom ()
  {
    return m_zoomstack.CanRedo();
  }
  //* I/O functions
  bool Write (const char* filename);
  bool Write (FILE* fp);
  void Write (UtlWriter* writer);
  bool Read (const char* filename);
  bool Read (FILE* fp);
  bool Skip (FILE* fp);
  void Print ()
  {
    Write(stdout);
  }

  //* Reset zoom and matrix
  void Reset ();
  
  void ApplyTransform (AlgMatrix& t);

  /**
   * Obtains the top of the transformation stack.
   */
  AlgMatrix GetTransform ();

private:
  VglFrustum m_auxfrustum;
  void SetOutdated ()
  {
    m_updated = false;
    m_auxfrustumupdated = false;
  }
  void UpdateAuxFrustum ();
  void NormalizeZoomCenter (float x, float y, float* nx, float* ny);
  void DenormalizeZoomCenter (float nx, float ny, float* x, float* y);
  void ComputeFrustum ();
  void FindMinMax (AlgVector& axis, float* min, float* max);
  AlgVector ComputeBoxSize ();
  void ComputeStereo ();
  float AvoidStereoDistortion(float tc, float pmin, float pmax);
  void CalcBoxMinMaxClipping (float xmin, float xmax, float ymin, float ymax, float zmin, float zmax, AlgVector *oclipmin, AlgVector *oclipmax);
  void CopyBoxParams(VglCamera* camera);
  void CopyStack(VglCamera* camera);
};

#endif
