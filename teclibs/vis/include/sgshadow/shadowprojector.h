#ifndef SG_SHADOWPROJECTOR_H
#define SG_SHADOWPROJECTOR_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include <sgshadow/sgshadow.h>
#include <sg/strat/render/transprender.h>
#include <sg/camera.h>
#include <sg/shape.h>
#include <alg/vector.h>
#include <alg/matrix.h>
#include <alg/plane.h>
#include <ds/list.h>

class SGShape;

//-------------------//
// Class Declaration //
//-------------------//

class SGSHADOWAPI SGShadowProjector : public SGTranspRender
{
public:

  static const char* CLASSNAME () { return "SGShadowProjector"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  // Constructors and Destructor

  SGShadowProjector ();
  virtual ~SGShadowProjector ();

  // Setters and Getters

  void SetShadowColor (float r, float g, float b)
  {
    m_rcolor = r;
    m_gcolor = g;
    m_bcolor = b;
  }

  void SetShadowOpacity (float a)
  {
    m_acolor = a;
  }

  void SetType (int type)
  {
    m_type = type;
  }

  void SetPlane (const AlgPlane& plane)
  {
    m_projplane = plane;
  }

  void SetOrigin (const AlgVector& origin)
  {
    m_type = 1;
    m_projvector = origin;
  }

  void SetDirection (const AlgVector& direction)
  {
    m_type = 2;
    m_projvector = direction;
  }

  void SetSkipEntityPattern (const char* name)
  {
    m_skipentitypatterns.Append(strdup(name));
  }

  void SetCamera (SGCamera* camera)
  {
    m_camera = camera;
  }

  // Update Methods

  void Update ();

  // Strategy Methods

  virtual int Load (SGSpace* s);

  virtual void Load (SGShape* s);

protected:

  int m_type;
  float m_rcolor;
  float m_gcolor;
  float m_bcolor;
  float m_acolor;
  AlgPlane m_projplane;
  AlgVector m_projvector;
  AlgMatrix m_projmatrix;
  SGCamera* m_camera;
  DsList<char*> m_skipentitypatterns;
  bool m_outdated;
};

#endif
