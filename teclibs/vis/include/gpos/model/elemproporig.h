//* elemeprop.h
// A grid element property (well, completion, blocks, etc) and it's data.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef pposp_elementproperty_h
#define pposp_elementproperty_h

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <gpos/common/util.h>
#include "elemprop.h"
#include "elempropd.h"
#include <gpos/defines.h>

class ResPosModel;

/**
 * ResPosElementPropertyOriginal
 *
 * An element property that was loaded from the reservoir model file.
 */
class RES_API ResPosElementPropertyOriginal : public ResPosElementProperty
{
public:
  ResPosElementPropertyOriginal (ResPosModel *mdl,
                                 const char *symbol,
                                 const char *desc,
                                 ResValueType type,
                                 const char* unit)
  : ResPosElementProperty(symbol,desc)
  , m_mdl(mdl)
  , m_type(type)
  , m_unit(PSUtil::StrDup(unit))
  {
  }
  ~ResPosElementPropertyOriginal()
  {
    free(m_unit);
  }
  ResValueType GetType() const
  {
    return m_type;
  }
  const char * GetUnit() const
  {
    return m_unit;
  }
  float GetNull();
private:
  ResPosModel *GetModel() const
  {
    return m_mdl;
  }
private:
  ResPosModel *m_mdl;
  ResValueType m_type;
  int iUnit;
  char* m_unit;
};

//* 'ResPosElementPropertyDataOriginal' Class
// Represents the data of a given property, suitable for viewing.
class ResPosElementPropertyDataOriginal : public ResPosElementPropertyData
{
protected:
  ResPosElementPropertyOriginal *pElementProperty;
public:

  ResPosElementPropertyDataOriginal(ResPosElementPropertyOriginal *property)
    : pElementProperty(property)
  {
  }

  ResPosElementPropertyOriginal * getProperty()
  {
    return pElementProperty;
  }

    //* Value query
    // Returns the value at the ith step.
    // If there are more than one value per step, returns the jth value.
  virtual float Data(int i, int j = 0) = 0;
  ResPosElementProperty * GetProperty()
  {
    return getProperty();
  }

  float GetNull()
  {
    return getProperty()->GetNull();
  }

  float GetValue(int i)
  {
    return Data(i);
  }

};

//TODO: ver se eh possivel remover o template (o cast pra float ja eh feito nos loaders)

//* 'ResPosElementPropertyDataOriginal1D' Class
// Represents a property data that holds only one value per step.
template <class T>
class ResPosElementPropertyDataOriginal1D : public ResPosElementPropertyDataOriginal
{
protected:
  T *vValues;
  int iNumValues;
public:

  ResPosElementPropertyDataOriginal1D( ResPosElementPropertyOriginal *property, T *values, int nvalues)
    : ResPosElementPropertyDataOriginal(property), vValues(values), iNumValues(nvalues)
  {
    SetMinMaxValues();
  }

  ~ResPosElementPropertyDataOriginal1D()
  {
    PSUtil::Free(vValues);
  }

  float Data(int i, int j = 0)
  {
    assert((i >= 0) && (i < iNumValues));
    return (float)vValues[i];
  }

  int GetNumberOfSteps() { return iNumValues; }
};

#endif

