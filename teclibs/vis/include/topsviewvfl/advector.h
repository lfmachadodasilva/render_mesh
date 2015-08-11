#ifndef TPVVFL_ADVECTOR_H
#define TPVVFL_ADVECTOR_H

//----------//
// Includes //
//----------//

#include "defines.h"

#include <vfl/baseadvector.h>
#include <alg/vector.h>
#include <ds/array.h>

//----------------------//
// Forward Declarations //
//----------------------//

class TopElement;

class TpvVflVectorIntegrator;

//-----------------------------------//
// Class Definition - TpvVflAdvector //
//-----------------------------------//

class TPVVFL_API TpvVflAdvector : public VflBaseAdvector
{
public:

  // Constructors and Destructor

  TpvVflAdvector ()
  : VflBaseAdvector()
  , m_integrator(NULL)
  , m_seedElements()
  , m_seedPositions()
  {
  }

  virtual ~TpvVflAdvector ()
  {
  }

  // Integrator

  void SetIntegrator (TpvVflVectorIntegrator* integrator);
  TpvVflVectorIntegrator* GetIntegrator ()
  {
    return m_integrator;
  }

  // Seeds

  void AddSeed (const TopElement& element, const AlgVector& position);
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

  TpvVflVectorIntegrator* m_integrator;

  DsArray<TopElement> m_seedElements;
  DsArray<AlgVector> m_seedPositions;

};

#endif // TPVVFL_ADVECTOR_H
