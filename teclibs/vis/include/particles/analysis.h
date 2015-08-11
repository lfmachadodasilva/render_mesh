/************************************************************************
  PtcAnalysis Class Header
  Provides particle data analysis.
  rcosta@tecgraf.puc-rio.br
  Mar 2009
*************************************************************************/

#ifndef _PARTICLES_ANALYSIS_H_
#define _PARTICLES_ANALYSIS_H_

#include <alg/vector.h>
#include "model.h"
#include "defines.h"

/************************************************************************
  Forward Declarations
*************************************************************************/

class PtcLoader;

/************************************************************************
  Class Declaration
*************************************************************************/

class PARTICLES_API PtcAnalysis
{
public:
  PtcAnalysis (PtcModel::Dimension dim);
  ~PtcAnalysis ();

  // Gets the average scalar sample at the specified point. The loader must be set before.
  float GetScalarSampleAtPoint (int fieldid, const AlgVector& point, float radius);

  // Sets the loader. The "LoadBasicInfo" loader method must be called before.
  void SetLoader (PtcLoader* loader);

private:
  PtcModel m_model;
  PtcLoader* m_loader;
};

/************************************************************************
  Inline Methods
*************************************************************************/

inline void PtcAnalysis::SetLoader (PtcLoader* loader)
{
  m_loader = loader;
}

#endif