#ifndef VFL_VECTORINTEGRATOR_H
#define VFL_VECTORINTEGRATOR_H

//----------//
// Includes //
//----------//

#include "defines.h"
#include "baseintegrator.h"

#include <alg/vector.h>

//----------------------//
// Forward Declarations //
//----------------------//

class VflVectorField;

//-------------------------------------------------//
// Abstract Class Definition - VflVectorIntegrator //
//-------------------------------------------------//

class VFL_API VflVectorIntegrator : public VflBaseVectorIntegrator
{
public:

  // Constructors and Destructor

  VflVectorIntegrator ()
  : VflBaseVectorIntegrator()
  , m_vectorField(NULL)
  {
  }

  virtual ~VflVectorIntegrator ()
  {
  }

  // Vector Field

  void SetVectorField (VflVectorField* vectorField);
  VflVectorField* GetVectorField ()
  {
    return m_vectorField;
  }

  // Setup

  void SetCurPosition (const AlgVector& position);

protected:

  // Integration

  virtual bool DoIntegrationBegin ();
  virtual void DoIntegrationEnd ();

protected:

  VflVectorField *m_vectorField;

};

//---------------------------------------------//
// Class Definition - VflVectorIntegratorEuler //
//---------------------------------------------//

class VFL_API VflVectorIntegratorEuler : public VflVectorIntegrator
{
public:

  // Constructors and Destructor

  VflVectorIntegratorEuler ()
  : VflVectorIntegrator()
  {
  }

  virtual ~VflVectorIntegratorEuler ()
  {
  }

protected:

  // Integration

  virtual bool DoIntegrationStep ();

};

//-------------------------------------------//
// Class Definition - VflVectorIntegratorRK4 //
//-------------------------------------------//

class VFL_API VflVectorIntegratorRK4 : public VflVectorIntegrator
{
public:

  // Constructors and Destructor

  VflVectorIntegratorRK4 ()
  : VflVectorIntegrator()
  {
  }

  virtual ~VflVectorIntegratorRK4 ()
  {
  }

protected:

  // Integration

  virtual bool DoIntegrationStep ();

};

#endif // VFL_VECTORINTEGRATOR_H
