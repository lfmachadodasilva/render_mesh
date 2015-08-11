// gridboxrenderer.cpp
// malf@tecgraf.puc-rio.br
// Mar 2011

#ifndef SCIUTILS_GRID_BOX_RENDERER_H
#define SCIUTILS_GRID_BOX_RENDERER_H

#include <stdlib.h>
#include <ugl/gridtex.h>

#include "defines.h"
#include "scalenumbers.h"
#include "gridbox.h"

class UGLFrameBuffer;
class UGLTexture;

/**
 * 
 * Requires:
 *   EXT_framebuffer_object
 */
class SCIH_API SciGridBoxRenderer
{
public:
  typedef void (*ModelRenderFunc) (void *data); 

 /**
  * Constructs a new SciGridBox object.
  */
  SciGridBoxRenderer ();  
 /**
  * Destroys a SciGridBox object.
  */
  ~SciGridBoxRenderer ();

  /**
   * Returns whether gridbox rendering is supported by the current
   * graphics context.
   */
  static bool IsSupported ();
 /**
  * Sets the grid's color.
  */
  void SetGridColor (float r, float g, float b, float a);
 /**
  * Sets the scale numbers' color
  */
  void SetScaleNumbersColor(float r, float g, float b, float a);
 /**
  * Sets the box's color.
  */
  void SetBoxColor (float r, float g, float b, float a);
 /**
  * Enables/Disables the background box.
  */
  void SetEnabledBox (bool state);
 /**
  * Enables/Disables the grid.
  */
  void SetEnabledGrid (bool state);
 /**
  * Enables/Disables the projection.
  */
  void SetEnabledProjection (bool state);
 /**
  * 
  */
  //void SetGridPosAtFront (bool state);
 /**
  * Sets the tick enabled.
  */
  void SetGridTickEnabled (bool state);
 /**
  * Enable the fbo to draw the texture again.
  */
  void SetOutDated ();
 /**
  * Sets the render callback.
  */
  void SetModelRenderFunc (ModelRenderFunc func, void *data=NULL);
  /**
   * Sets whether mipmaping will be used, if available.
   * The method Update() must be called in order to update gridbox's data.
   * Default: false
   */
  void SetMipmapEnabled (bool enabled);

 /**
  * Render method.
  */
  void Render ();
  void SetBoundingBox (float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
  void Update ();

private:
  void DrawBox ();
  void DrawGrid ();
  void DrawProjection ();
  void DrawScaleNumbers (bool faces[6]);
  void GenerateTextures ();
  void RenderModelToTexture ();
  void CalcVisibleFaces ();


private:
  SciGridBox *m_gridbox;
  GLfloat m_box_color[4];       // Color array for the box (r,g,b,a).
  GLfloat m_grid_color[4];      // Color array for the grid (r,g,b,a).
  GLfloat m_scalenumber_color[4];// Color array for the scale numbers(r,g,b,a).
  bool m_box_draw;              // Boolean for controlling the drawing of the box.
  bool m_grid_draw;             // Boolean for controlling the drawing of the grid.
  bool m_proj_draw;             // Boolean for controlling the drawing of the projection.
  bool m_updated;               // Boolean for updating the fbo textures.
  //bool m_grid_pos_front;        // Boolean for controlling the drawing of grid in the front or back of the grid.
  bool m_grid_tick;             // Boolean for controlling the "tick" drawing.
  GLuint m_faces_query[6];      // Faces occlusion query id. Order: front, back, top, bottom, right, left
  UGLGridTex * m_grid_tex;      // Texture for the grid.
  UGLFrameBuffer *m_proj_fbo;   // FBO for the projective images.
  UGLTexture *m_proj_tex[6];    // Texture array for the projective image (FF, BF, TF, BF, RF & LF).
  ModelRenderFunc m_render;     // Render Callback for the model.
  void* m_data;                 // Data for the render callback.
  SciScaleNumbersRenderer* m_axis;
  bool m_fvis[6];  // visible faces
  int m_intervals[3];
  bool m_mipmap_enabled;
  int m_mipmap_max_level;
};

#endif
