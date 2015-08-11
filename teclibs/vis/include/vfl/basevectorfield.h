#ifndef VFL_BASEVECTORFIELD_H
#define VFL_BASEVECTORFIELD_H

//----------//
// Includes //
//----------//

#include "defines.h"

#include <alg/vector.h>

//----------------------//
// Forward Declarations //
//----------------------//

//------------------------------------------------//
// Abstract Class Definition - VflBaseVectorField //
//------------------------------------------------//

class VFLH_API VflBaseVectorField
{
public:

  // Constructors and Destructor

  VflBaseVectorField ()
  {
  }

  virtual ~VflBaseVectorField ()
  {
  }

  // Field Value

  virtual AlgVector GetFieldValue (const AlgVector& pos) = 0;

};

#endif // VFL_BASEVECTORFIELD_H
