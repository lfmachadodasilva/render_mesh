#ifndef VFL_PARTICLES_H
#define VFL_PARTICLES_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "defines.h"

#include <alg/vector.h>
#include <ds/array.h>

#include <float.h>

class VflVectorField;

//------------------//
// Class Definition //
//------------------//

class VFL_API VflParticles
{
public:

  // Constructors and Destructor

  VflParticles ()
  : m_vectorField(NULL)
  , m_particles()
  , m_timeStep(0.01f)
  , m_minSqrVelocity(0.0f)
  , m_maxSqrVelocity(FLT_MAX)
  , m_integrationOrder(2)
  {
  }

  virtual ~VflParticles ()
  {
  }

  // Configuration

  void SetVectorField (VflVectorField* vectorField)
  {
    m_vectorField = vectorField;
  }

  void SetTimeStep (float timeStep)
  {
    m_timeStep = timeStep;
  }

  void SetMinSqrVelocity (float minSqrVelocity)
  {
    m_minSqrVelocity = minSqrVelocity;
  }

  void SetMaxSqrVelocity (float maxSqrVelocity)
  {
    m_maxSqrVelocity = maxSqrVelocity;
  }

  void SetIntegrationOrder (int order)
  {
    m_integrationOrder = order;
  }

  VflVectorField* GetVectorField () const
  {
    return m_vectorField;
  }

  float GetTimeStep () const
  {
    return m_timeStep;
  }

  float GetMinSqrVelocity () const
  {
    return m_minSqrVelocity;
  }

  float GetMaxSqrVelocity () const
  {
    return m_maxSqrVelocity;
  }

  int GetIntegrationOrder () const
  {
    return m_integrationOrder;
  }

  // Particles

  void AddSeed (const AlgVector& position)
  {
    m_seeds.Append(position);
    m_particles.Append(position);
  }

  // Simulation

  bool SimulationStep ()
  {
    switch(GetIntegrationOrder())
    {
    case 4: StepTransportRK4(); return true;
    case 2: StepTransportRK2(); return true;
    case 1: StepTransportRK1(); return true;
    }
    return false;
  }

  // Render

  void Render ();

protected:

  // Simulation

  void StepTransportRK1 ();
  void StepTransportRK2 ();
  void StepTransportRK4 ();

protected:

  VflVectorField* m_vectorField;

  DsArray<AlgVector> m_seeds;
  DsArray<AlgVector> m_particles;

  float m_timeStep;
  float m_minSqrVelocity;
  float m_maxSqrVelocity;
  int m_integrationOrder;

};

#endif // VFL_PARTICLES_H
