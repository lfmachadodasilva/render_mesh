#ifndef VFL_BASEINTEGRATOR_H
#define VFL_BASEINTEGRATOR_H

//----------//
// Includes //
//----------//

#include "defines.h"

#include <alg/vector.h>

//----------------------//
// Forward Declarations //
//----------------------//

//-----------------------------------------------//
// Abstract Class Definition - VflBaseIntegrator //
//-----------------------------------------------//

class VFL_API VflBaseIntegrator
{
public:

  // Constructors and Destructor

  VflBaseIntegrator ()
  : m_timeStep(0.1f)
  , m_numSteps(1)
  , m_integrating(false)
  {
  }

  virtual ~VflBaseIntegrator ()
  {
  }

  // Parameters

  void SetTimeStep (float timeStep);
  float GetTimeStep () const
  {
    return m_timeStep;
  }

  void SetNumSteps (int numSteps);
  int GetNumSteps () const
  {
    return m_numSteps;
  }

  // Integration

  bool BeginIntegration () // Returns whether the integration can be performed
  {
    if (m_integrating || !DoIntegrationBegin())
      return false;
    m_integrating = true;
    return true;
  }

  bool Integrate () // Returns whether the produced point should be the last and terminate the integration
  {
    for (int step = 0; step < m_numSteps; ++step)
    {
      if (!DoIntegrationStep())
        return false;
    }
    return true;
  }

  virtual void EndIntegration ()
  {
    m_integrating = false;
    DoIntegrationEnd();
  }

protected:

  // Integration

  virtual bool DoIntegrationBegin () = 0;
  virtual bool DoIntegrationStep () = 0;
  virtual void DoIntegrationEnd () = 0;

protected:

  float m_timeStep;
  int m_numSteps;
  bool m_integrating;

};

//-----------------------------------------------------//
// Abstract Class Definition - VflBaseVectorIntegrator //
//-----------------------------------------------------//

class VFL_API VflBaseVectorIntegrator : public VflBaseIntegrator
{
public:

  // Constructors and Destructor

  VflBaseVectorIntegrator ()
  : VflBaseIntegrator()
  , m_curPosition(0.0f, 0.0f, 0.0f)
  , m_curDirection(0.0f, 0.0f, 0.0f)
  , m_curMagnitude(0.0f)
  {
  }

  virtual ~VflBaseVectorIntegrator ()
  {
  }

  // Results

  const AlgVector& GetCurPosition () const
  {
    return m_curPosition;
  }

  const AlgVector& GetCurDirection () const
  {
    return m_curDirection;
  }

  float GetCurMagnitude () const
  {
    return m_curMagnitude;
  }

protected:

  // Integration

  virtual bool DoIntegrationBegin () = 0;
  virtual bool DoIntegrationStep () = 0;
  virtual void DoIntegrationEnd () = 0;

protected:

  AlgVector m_curPosition;
  AlgVector m_curDirection;
  float m_curMagnitude;

};

//-----------------------------------------------------//
// Abstract Class Definition - VflBaseScalarIntegrator //
//-----------------------------------------------------//

class VFL_API VflBaseScalarIntegrator : public VflBaseIntegrator
{
public:

  // Constructors and Destructor

  VflBaseScalarIntegrator ()
  : VflBaseIntegrator()
  , m_curValue(0.0)
  , m_curSlope(0.0)
  {
  }

  virtual ~VflBaseScalarIntegrator ()
  {
  }

  // Results

  double GetCurX () const
  {
    return m_curX;
  }

  double GetCurValue () const
  {
    return m_curValue;
  }

  double GetCurSlope () const
  {
    return m_curSlope;
  }

protected:

  // Integration

  virtual bool DoIntegrationBegin () = 0;
  virtual bool DoIntegrationStep () = 0;
  virtual void DoIntegrationEnd () = 0;

protected:

  double m_curX;
  double m_curValue;
  double m_curSlope;

};

#endif // VFL_BASEINTEGRATOR_H
