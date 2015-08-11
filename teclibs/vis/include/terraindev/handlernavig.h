//* handlernavig.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Nov 2008

#ifndef TRN_HANDLER_NAVIG_H
#define TRN_HANDLER_NAVIG_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "handler.h"
#include <vgl/hnd/navig.h>

class VglViewSurface;
class TrnTerrain;

//-----------------------//
// TrnHandlerNavig Class //
//-----------------------//

// This class implements a navigation handler that does
// not allow the camera to go below the terrain ground

class TERRAINAPI TrnHandlerNavig : public VglNavigHandler, public TrnHandler
{
public:

  // Class Name

  static const char* CLASSNAME () { return "TrnHandlerNavig"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  // Constructor and Destructor

  TrnHandlerNavig (VglViewSurface* surface, TrnViewSpecifier* viewSpecifier, float maxvel = 0.2f, float accel = 1.0f);
  virtual ~TrnHandlerNavig ();

  // Setters and Getters

  void SetMinDistance (float dist)
  {
    m_minDistance = dist;
  }

  float GetMinDistance ()
  {
    return m_minDistance;
  }

  void SetConstraintActive (bool state)
  {
    m_constraintActive = state;
  }

  bool GetConstraintActive ()
  {
    return m_constraintActive;
  }

protected:

  // VglNavigHandler Virtual Methods

  virtual void Translate (float velx, float vely, float velz, double displacement);

private:

  float m_minDistance;     // Minimum distance to keep from terrain
  bool m_constraintActive; // Enable / Disable minimum distance constraint

};

#endif // TRN_HANDLER_NAVIG_H
