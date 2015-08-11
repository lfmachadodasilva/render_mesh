// Material sorting collector
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_MATSORT_H
#define SG_MATSORT_H

#include <sg/strat/coll/abstractmatsort.h>

class SGState;
class SGBin;
class SGColObject;
class SGColScene;

class SG_API SGMatSort : public SGAbstractMatSort
{
public:
  SGMatSort();
  virtual ~SGMatSort();
protected:
  virtual void CreateBins   (SGColScene* s);
  virtual void PopBins      ();
  virtual void PushBins     (int slot, SGState* state);
  virtual void InsertObject (int slot, SGColObject* obj, SGState* state);
private:
  BinStack    m_binstack;
};

#endif

