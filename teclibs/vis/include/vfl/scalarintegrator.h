#ifndef VFL_SCALARINTEGRATOR_H
#define VFL_SCALARINTEGRATOR_H

//----------//
// Includes //
//----------//

#include "defines.h"
#include "baseintegrator.h"



//----------------------//
// Forward Declarations //
//----------------------//

class VflScalarFunction;

//-------------------------------------------------//
// Abstract Class Definition - VflScalarIntegrator //
//-------------------------------------------------//

class VFL_API VflScalarIntegrator : public VflBaseScalarIntegrator
{
public:

  // Constructors and Destructor

  VflScalarIntegrator ()
  : VflBaseScalarIntegrator()
  , m_scalarFunction(NULL)
  {
  }

  virtual ~VflScalarIntegrator ()
  {
  }

  // Scalar Function

  void SetScalarFunction (VflScalarFunction* scalarFunction);
  VflScalarFunction* GetScalarFunction ()
  {
    return m_scalarFunction;
  }

  // Setup

  void SetCurX (double x);

protected:

  // Integration

  virtual bool DoIntegrationBegin ();
  virtual void DoIntegrationEnd ();

protected:

  VflScalarFunction *m_scalarFunction;

};

//---------------------------------------------//
// Class Definition - VflScalarIntegratorEuler //
//---------------------------------------------//

class VFL_API VflScalarIntegratorTrapezoidal : public VflScalarIntegrator
{
public:

  // Constructors and Destructor

  VflScalarIntegratorTrapezoidal ()
  : VflScalarIntegrator()
  {
  }

  virtual ~VflScalarIntegratorTrapezoidal ()
  {
  }

protected:

  // Integration

  virtual bool DoIntegrationStep ();

};

//-------------------------------------------//
// Class Definition - VflScalarIntegratorRK4 //
//-------------------------------------------//

class VFL_API VflScalarIntegratorSimpson : public VflScalarIntegrator
{
public:

  // Constructors and Destructor

  VflScalarIntegratorSimpson ()
  : VflScalarIntegrator()
  {
  }

  virtual ~VflScalarIntegratorSimpson ()
  {
  }

protected:

  // Integration

  virtual bool DoIntegrationStep ();

};

#endif // VFL_SCALARINTEGRATOR_H
