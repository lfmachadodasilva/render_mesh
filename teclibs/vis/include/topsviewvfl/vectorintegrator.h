#ifndef TPVVFL_VECTORINTEGRATOR_H
#define TPVVFL_VECTORINTEGRATOR_H

//----------//
// Includes //
//----------//

#include "defines.h"

#include <vfl/baseintegrator.h>
#include <tops/tops.h>
#include <alg/vector.h>

//----------------------//
// Forward Declarations //
//----------------------//

class TpvVflVectorField;

//----------------------------------------------------//
// Abstract Class Definition - TpvVflVectorIntegrator //
//----------------------------------------------------//

class TPVVFL_API TpvVflVectorIntegrator : public VflBaseVectorIntegrator
{
public:

  // Constructors and Destructor

  TpvVflVectorIntegrator ()
  : VflBaseVectorIntegrator()
  , m_vectorField(NULL)
  , m_curElement()
  {
  }

  virtual ~TpvVflVectorIntegrator ()
  {
  }

  // Vector Field

  void SetVectorField (TpvVflVectorField* vectorField);
  TpvVflVectorField* GetVectorField ()
  {
    return m_vectorField;
  }

  // Setup

  void SetCurPosition (const TopElement& element, const AlgVector& position);

  // Results

  const TopElement& GetCurElement ()
  {
    return m_curElement;
  }

protected:

  // Integration

  virtual bool DoIntegrationBegin ();
  virtual void DoIntegrationEnd ();

  // Element Search
  // @param curElement  Receives the current element by reference, returns the next element
  // @param curPosition Receives the current position by reference, returns the next position
  // @param step        Receives the desired step by value, remains unaltered in the caller
  // @return            Whether the step was completely finished in a valid active element

  bool FindTarget (TopElement& curElement, AlgVector& curPosition, AlgVector step);

protected:

  TpvVflVectorField *m_vectorField;
  TopElement m_curElement;

};

//------------------------------------------------//
// Class Definition - TpvVflVectorIntegratorEuler //
//------------------------------------------------//

class TPVVFL_API TpvVflVectorIntegratorEuler : public TpvVflVectorIntegrator
{
public:

  // Constructors and Destructor

  TpvVflVectorIntegratorEuler ()
  : TpvVflVectorIntegrator()
  {
  }

  virtual ~TpvVflVectorIntegratorEuler ()
  {
  }

protected:

  // Integration

  virtual bool DoIntegrationStep ();

};

//----------------------------------------------//
// Class Definition - TpvVflVectorIntegratorRK4 //
//----------------------------------------------//

class TPVVFL_API TpvVflVectorIntegratorRK4 : public TpvVflVectorIntegrator
{
public:

  // Constructors and Destructor

  TpvVflVectorIntegratorRK4 ()
  : TpvVflVectorIntegrator()
  {
  }

  virtual ~TpvVflVectorIntegratorRK4 ()
  {
  }

protected:

  // Integration

  virtual bool DoIntegrationStep ();

};

#endif // TPVVFL_VECTORINTEGRATOR_H
