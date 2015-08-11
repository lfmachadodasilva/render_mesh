// Retained Strategy
// fabraham@tecgraf.puc-rio.br
// Mar 2003

#ifndef SG_RETAINED
#define SG_RETAINED

#include <alg/matrixstack.h>
#include "transfstrategy.h"

/**
 * This class defines the SGRetained strategy type.
 * It contains a transformation stack on the CPU.
 */
class SG_API SGRetained : public SGTransfStrategy
{
  AlgMatrixStack m_stack;
protected:
	/**
	 * Constructor.
	 */
  SGRetained () : m_stack()
	{
	}	
public:
	/**
	 * Destructor.
	 */
	virtual ~SGRetained ()
	{
	}
	virtual AlgStack* GetStack ()
	{
		return &m_stack;
	}
  virtual AlgMatrix GetBase ()
  {
    AlgMatrix P = GetProjection(); // P
    P.Accum(GetView());            // PV
    return P;
  }
};

#endif
