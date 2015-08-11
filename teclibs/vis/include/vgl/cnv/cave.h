//* cave.h
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Feb 2003

#ifndef VGL_CAVE_H
#define VGL_CAVE_H

#include <vgl/viewsurface.h>
#include <ds/list.h>

class VglCanvas;

/**
 * This class represents the abstraction of a cave.
 * A cave is treated as a collection of canvases.
 * All methods are propagated to the entire canvases collection.
 * (An exception is the SetCamera method, which does not propagate by default)
 */
class VGL_API VglCave : public VglViewSurface
{
  typedef DsPList<VglCanvas> CanvasList;
  CanvasList m_canvases;
public:
  /**
   * Constructs a new VglCave object.
   * \param camera Camera associated with this canvas.
   */
  VglCave (VglCamera* camera);
  /**
   * Destroys a VglCave object.
   */
  virtual ~VglCave ();
  /**
   * Sets the camera for this canvas.
   * \param camera New camera object associated with this canvas.
   * \param propagate If true, camera setup is propagated to the canvas collection.
   */
  virtual void SetCamera (VglCamera* camera, bool propagate=false);
  /**
   * Sets the reshape function for the cave.
   * The function and its data is propagated to the canvas collection.
   *
   * It is expected that this function is called after the canvases have been added.
   */
  virtual void SetReshapeFunc (VglReshapeFunction func, void* data=NULL);
  /**
   * Sets the redraw function for the cave.
   * The function and its data is propagated to the canvas collection.
   *
   * It is expected that this function is called after the canvases have been added.
   */
  virtual void SetRedrawFunc (VglFunction func, void* data=NULL);
  /**
   * Sets the end redraw function for the cave.
   * The function and its data is propagated to the canvas collection.
   *
   * It is expected that this function is called after the canvases have been added.
   */
  virtual void SetEndRedrawFunc (VglFunction func, void* data=NULL);
  /**
   * Inserts a new canvas to the cave.
   * \param canvas Canvas object.
   */
  void AddCanvas (VglCanvas* canvas);
  /**
   * Removes a canvas from the cave.
   * \param canvas Canvas object.
   */
  void RemCanvas (VglCanvas* canvas);
  void SwapBuffers ();
  virtual void PostRedraw ();
  virtual void Redraw ();
  virtual void DrawItem (VglFunction func, void* data=NULL);
  virtual void SetCursorPos (float x, float y);
  virtual void SetRasterCursor (bool f);
};

#endif
