#ifndef VFL_ADVECTOR_H
#define VFL_ADVECTOR_H

//----------//
// Includes //
//----------//

#include "defines.h"
#include "baseadvector.h"

#include <alg/vector.h>
#include <ds/array.h>

//----------------------//
// Forward Declarations //
//----------------------//

class VflVectorIntegrator;

//--------------------------------//
// Class Definition - VflAdvector //
//--------------------------------//

class VFL_API VflAdvector : public VflBaseAdvector
{
public:

  // Constructors and Destructor

  VflAdvector ()
  : VflBaseAdvector()
  , m_integrator(NULL)
  , m_seedPositions()
  {
  }

  virtual ~VflAdvector ()
  {
  }

  // Integrator

  void SetIntegrator (VflVectorIntegrator* integrator);
  VflVectorIntegrator* GetIntegrator ()
  {
    return m_integrator;
  }

  // Seeds

  void AddSeed (const AlgVector& position);
  void ClearSeeds ();

protected:

  // Advection

  virtual int GetSeedCount ()
  {
    return m_seedPositions.Size();
  }

  virtual int Advect (float* magnitudes,
                      float* vertices,
                      float* tangents,
                      int seedNumber,
                      int maxVerts,
                      bool backwards);

private:

  VflVectorIntegrator* m_integrator;

  DsArray<AlgVector> m_seedPositions;

};

#endif // VFL_ADVECTOR_H
