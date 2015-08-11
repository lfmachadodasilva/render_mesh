//* fixheightnavig.h
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mar 2003

#ifndef VGL_FIX_HEIGHT_NAVIG_H
#define VGL_FIX_HEIGHT_NAVIG_H

#include "navig.h"
#include "selection.h"

class VglViewSurface;

/**
 * This class implements a Navig Handler that keeps a constant distance to the ground.
 * That is done by tracing a ray from the camera position to the negative y axis 
 * direction and using this distance to correct the camera position height.
 *
 * TODO:
 * - enable the specification of the 'ground' direction
 */
class VGL_API VglFixHeightNavigHandler : public VglNavigHandler, public VglSelectionHandler
{
  float m_height;
  bool m_heightset;
  float m_zmin;
  float m_tolx, m_toly, m_range;

  float GetIntDistance (AlgVector position, AlgVector direction);
  float GetDistanceToGround (VglCamera *camera);
protected:
  virtual void Translate (float velx, float vely, float velz, double displacement);
  virtual void ProcessFunction (VglSelectionHit* hits, int n);
public:
  static const char* CLASSNAME () { return "FixHeightNavigHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructs a new VglFixHeightNavigHandler.
   * \param surface The view surface associated with this handler.
   * \param maxvel  Maximum navigation velocity.
   * \param accel   Navigation acceleration.
   * \param tolx    Traced ray x tolerance in world coordinates.
   * \param toly    Traced ray y tolerance in world coordinates.
   * \param range   Traced ray range in world coordinates.
   */
  VglFixHeightNavigHandler (VglViewSurface* surface,
                            float maxvel=0.2f,
                            float accel=1.0f,
                            float tolx=0.1f,
                            float toly=0.1f,
                            float range=1000.0f);
  /**
   * Destroys a VglFixHeightNavigHandler object.
   */
  virtual ~VglFixHeightNavigHandler ();
  /**
   * Sets the new default height.
   * \param height Height in world coordinates.
   */
  void SetHeight (float height)
  {
    m_height = height;
    m_heightset = true;
  }
  void SetTolerance (float tolx, float toly)
  {
    m_tolx = tolx;
    m_toly = toly;
  }
  void SetRange (float range)
  {
    m_range = range;
  }
};

#endif
