// LOD building strategy
// fabraham@tecgraf.puc-rio.br
// Nov 2004

#ifndef SG_LODBUILDER
#define SG_LODBUILDER

#include <sg/strategy.h>
#include <sg/modules/sglod.h>

class SGNodeList;

/**
 * LOD building strategy.
 * This strategy will traverse a node hierarchy and will
 * create the specified number of LODs for each object
 * with 1 shape of type SGMesh with only trianglesets.
 */
class SGLODAPI SGLODBuilder : public SGStrategy
{
  int m_minfaces;
  int m_maxlods;
  int m_nprimslastlod;
  int m_nprimstotal;
public:
  SGLODBuilder () :
    m_minfaces(-1),
    m_maxlods(1000)
  {
  }
  virtual ~SGLODBuilder ()
  {
  }
  /**
   * Sets the minimum number of faces of the last LOD. Default=-1 (no limit)
   */
  void SetMinFaces (int minfaces)
  {
    m_minfaces = minfaces;  
  } 
  /**
   * Sets the maximum number of LODs. Default=1000.
   */
  void SetMaxLODs (int maxlods)
  {
    m_maxlods = maxlods;
  }
  /**
   * Obtains the percentage of total primitives drawn with the last LOD.
   */
  float GetLastLODEconomy ()
  {
    return (float)m_nprimslastlod/m_nprimstotal;
  }
  virtual int Load (SGObject *o);
  virtual int Load (SGScene *s);
};

#endif
