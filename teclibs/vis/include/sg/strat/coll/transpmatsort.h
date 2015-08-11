// Transparent/opaque material sorting collector
// fabraham@tecgraf.puc-rio.br
// Oct 2003

/**
 * This collector will generate a ColScene with 2 bins:
 * - Opaque objects
 * - Transparent objects
 */

#ifndef SG_TRANSP_MATSORT_H
#define SG_TRANSP_MATSORT_H

#include <sg/strat/coll/abstractmatsort.h>
#include <ds/stack.h>

class SGAppearance;
class SGColScene;
class SGBin;
class SGObject;

class SG_API SGTranspMatSort : public SGAbstractMatSort
{
  bool     m_nextopaque;
  BinStack m_obinstack;
  BinStack m_tbinstack;
  DsStack<int> m_whichstack;
  DsStack<int> m_whichtopop;
public:
  SGTranspMatSort();
  virtual ~SGTranspMatSort();
  // strategy methods
  virtual void Load (SGState* c);
  virtual void Unload (SGState* c);
protected:
  virtual void CreateBins   (SGColScene* s);
  virtual void PopBins      ();
  virtual void PushBins     (int slot, SGState* state);
  virtual void InsertObject (int slot, SGColObject* obj, SGState* state);
  /**
   * Obtain each bin Stack
   */
  const BinStack& GetOpaqueBinStack () const
  {
      return m_obinstack;
  }
  const BinStack& GetTranspBinStack () const
  {
      return m_tbinstack;
  }
  const DsStack<int>& GetWhichStack () const
  {
      return m_whichstack;
  }
};

#endif
