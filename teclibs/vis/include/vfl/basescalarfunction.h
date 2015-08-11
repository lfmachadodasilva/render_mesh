#ifndef VFL_BASESCALARFUNCTION_H
#define VFL_BASESCALARFUNCTION_H

//----------//
// Includes //
//----------//

#include "defines.h"

//----------------------//
// Forward Declarations //
//----------------------//

//---------------------------------------------------//
// Abstract Class Definition - VflBaseScalarFunction //
//---------------------------------------------------//

class VFLH_API VflBaseScalarFunction
{
public:

  // Constructors and Destructor

  VflBaseScalarFunction ()
  {
  }

  virtual ~VflBaseScalarFunction ()
  {
  }

  // Function Value

  virtual double GetFunctionValue (double x) = 0;

};

#endif // VFL_BASESCALARFUNCTION_H
