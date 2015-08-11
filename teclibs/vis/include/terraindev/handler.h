//* handler.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mai 2009

#ifndef TRN_HANDLER_H
#define TRN_HANDLER_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "baseclass.h"
#include "viewparameters.h"
#include <alg/vector.h>
#include <vgl/viewsurface.h>
#include <vgl/hnd/transformcenter.h>

class TrnTerrain;
class TrnTerrainGroup;

//--------------------------//
// TrnCenterSpecifier Class //
//--------------------------//

class TERRAINAPI TrnCenterSpecifier : public VglTransformCenterSpecifier, public TrnBaseClass
{
public:

  // Class Name

  static const char* CLASSNAME () { return "TrnCenterSpecifier"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  // Constructor and Destructor

  TrnCenterSpecifier ()
    : VglTransformCenterSpecifier()
    , TrnBaseClass()
    , m_center(0.0f, 0.0f, 0.0f)
  {
  }

  virtual ~TrnCenterSpecifier ()
  {
  }

  // VglTransformCenterSpecifier Virtual Methods 

  virtual void UpdateTransformCenter ()
  {
    // Ignored. Nothing to do.
  }

  virtual void GetTransformCenter (float *ocx, float *ocy, float *ocz)
  {
    *ocx = m_center.x;
    *ocy = m_center.y;
    *ocz = m_center.z;
  }

  virtual void SetTransformCenter (float cx, float cy, float cz)
  {
    m_center.x = cx;
    m_center.y = cy;
    m_center.z = cz;
  }

private:

  AlgVector m_center;

};

//------------------//
// TrnHandler Class //
//------------------//

// This class implements a handler suitable for flat-world terrains

class TERRAINAPI TrnHandler : public TrnBaseClass
{
public:

  // Class Name

  static const char* CLASSNAME () { return "TrnHandler"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  // Constructor and Destructor

  TrnHandler (VglViewSurface* surface, TrnViewSpecifier* viewSpecifier)
  : TrnBaseClass()
  , m_terraingroup(NULL)
  , m_viewSpecifier(viewSpecifier)
  , m_surface(surface)
  {
  }

  virtual ~TrnHandler ()
  {
  }

  // View Parameters Methods

  void CalculateSecondaryParameters (TrnViewParameters& view);
  void UpdateViewParameters (TrnViewParameters& view);

  // Setters and Getters

  void SetTerrainGroup (TrnTerrainGroup* terraingroup)
  {
    m_terraingroup = terraingroup;
  }

  TrnTerrainGroup* GetTerrainGroup () const
  {
    return m_terraingroup;
  }

  void SetViewSurface (VglViewSurface *surface)
  {
    m_surface = surface;
  }

  VglViewSurface* GetViewSurface () const
  {
    return m_surface;
  }

  void SetViewSpecifier (TrnViewSpecifier *viewSpecifier)
  {
    m_viewSpecifier = viewSpecifier;
  }

  TrnViewSpecifier* GetViewSpecifier () const
  {
    return m_viewSpecifier;
  }

  void GetCanvasSize (const TrnViewParameters& view, int* width, int* height) const;

private:

  TrnTerrainGroup* m_terraingroup;
  TrnViewSpecifier* m_viewSpecifier;
  VglViewSurface* m_surface;

};

#endif // TRN_HANDLER_H
