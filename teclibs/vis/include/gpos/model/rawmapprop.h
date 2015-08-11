//* rawmapprop.h
// A viewable raw map property.
// Tecgraf/PUC-Rio
// Ago 2004

#ifndef vis_rawmapproperty_h
#define vis_rawmapproperty_h

#include "property.h"
#include "model.h"
#include "geometry.h"
#include <common/util.h>
#include <stdio.h>

//* 'ResRawMapProperty' Class
// Represents a raw map property suitable for viewing.
class RES_API ResRawMapProperty : public ResProperty
{
  char * m_symbol;
  char * m_desc;
  char * m_unit;
  int m_nsteps;
  int m_ni, m_nj, m_nk;
  float m_maxvalue, m_minvalue;
  float **m_values;
protected:
  virtual ~ResRawMapProperty();
public:
  ResRawMapProperty(ResModel *model, bool isinitial=false);
  bool IsInitial()
  {
    return m_initial;
  }
  void GeometryChanged ();
  void SetUnit(const char * u)
  {
    PSUtil::StrSubst(&m_unit, u);
  }
  const char * GetUnit() const
  {
    return m_unit;
  }
  void SetSymbol(const char *s)
  {
    PSUtil::StrSubst(&m_symbol, s);
  }
  const char * GetSymbol() const
  {
    return m_symbol;
  }
  void SetDescription(const char *d)
  {
    PSUtil::StrSubst(&m_desc, d);
  }
  const char * GetDescription() const
  {
    return m_desc;
  }
  float GetMinValue()
  {
    return m_minvalue;
  }
  float GetMaxValue()
  {
    return m_maxvalue;
  }
  float GetNull() const
  {
    return 97654321.0f;
  }
  int GetNumberOfStepsLoaded()
  {
    return m_nsteps;
  }
  void SetValue(int step, float value, int i, int j, int k)
  {
    SetValue(step,value,index(i,j,k));
  }
  void SetValue(int step, float value, int index);
  void SetNullValue(int step, int i, int j, int k)
  {
    SetNullValue(step,index(i,j,k));
  }
  void SetNullValue(int step, int index)
  {
    m_values[step][index] = GetNull();
  }
  float GetValue(int i, int j, int k);
  float GetValue(int index);
  void GetValues(float *buf, int bufsize[], int slice[]);
  /**
   * Specifies the property as complete (values for all cells) or
   * incomplete (values only for active cells).
   *
   * Default: complete property
   */
  void SetComplete (bool complete)
  {
    m_complete = complete;
  }
  // reimplemented virtual methods
  bool IsComplete () const
  {
    return m_complete;
  }
protected:
  int doLoad(const ResStep *t = 0) { return 1; }
  int doUnLoad(const ResStep *t = 0) { return 1; }
  int getmstep(const ResStep *t);
  void cleanup();
  int index(int i, int j, int k)
  {
    return RES_LINEAR_INDEX(i,j,k,m_ni,m_nj,m_nk);
  }
private:
  bool m_anyvalue;
  bool m_initial;
  bool m_complete;
};

#endif

