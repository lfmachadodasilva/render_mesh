//* ray.h
// 3D ray with origin and direction floating-point vectors
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// May 2010

#ifndef ALG_RAY_H
#define ALG_RAY_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "defines.h"
#include "vector.h"

//------------------//
// Class Definition //
//------------------//

class ALGH_API AlgRay
{
public:

  AlgVector origin;
  AlgVector direction;

public:

  /**
   * Default Constructor
   */
  AlgRay ()
  : origin()
  , direction()
  {
  }

  /**
   * Copy Constructor
   */
  AlgRay (const AlgRay& ray)
  : origin(ray.origin)
  , direction(ray.direction)
  {
  }

  /**
   * Vector Constructor
   */
  AlgRay (const AlgVector& origin, const AlgVector& direction)
  : origin(origin)
  , direction(direction)
  {
  }

  /**
   * Array Constructor
   */
  AlgRay (const float origin[3], const float direction[3])
  : origin(origin)
  , direction(direction)
  {
  }

  /**
   * Coordinate Constructor
   */
  AlgRay (float ox, float oy, float oz, float dx, float dy, float dz)
  : origin(ox, oy, oz)
  , direction(dx, dy, dz)
  {
  }

  /**
   * Destructor
   */
  ~AlgRay ()
  {
  }

};

#endif // ALG_RAY_H
