//* triphase.h
// Special property to allow triphase maps viewing.
// Tecgraf/PUC-Rio
// Nov 2004

#ifndef triphase_map_property_h
#define triphase_map_property_h

#include "model/property.h"

// 'TriPhaseMapProperty' Class
// Represents a special reservoir property to allow triphase maps viewing.
class RES_API TriPhaseMapProperty : public ResProperty
{
  ResProperty *m_so;
  ResProperty *m_sw;
  ResProperty *m_sg;
  char *m_symbol;
  char *m_desc;
  char m_cvdesc[2048];

public:
  // one property may be missing, but no more than one
  TriPhaseMapProperty(ResModel *mdl, ResProperty *SO, ResProperty *SG, ResProperty *SW,
    const char *symbol, const char *desc);

  ~TriPhaseMapProperty();


  // the property behaves like 'SO' for compatibility with the rest of the program

  bool UseColorScale() { return false; }

  const char * GetUnit() const
  {
    if (m_so != NULL)
      return m_so->GetUnit();
    else if (m_sg != NULL)
      return m_sg->GetUnit();
    else if (m_sw != NULL)
      return m_sw->GetUnit();
    else
      return "";
  }

  void GetCellColor(int index, float *r, float *g, float *b)
  {
    float sov = (m_so)?(m_so->GetValue(index)):(0.0f);
    float sgv = (m_sg)?(m_sg->GetValue(index)):(0.0f);
    float swv = (m_sw)?(m_sw->GetValue(index)):(0.0f);

    *r = (m_sg)?(sgv):(1 - (sov+swv));
    *g = (m_so)?(sov):(1 - (sgv+swv));
    *b = (m_sw)?(swv):(1 - (sov+sgv));
  }

  int GetNumberOfCellValues() { return 3; }
  float GetCellValue(int v, int index)
  {
    float sov = (m_so)?(m_so->GetValue(index)):(0.0f);
    float sgv = (m_sg)?(m_sg->GetValue(index)):(0.0f);
    float swv = (m_sw)?(m_sw->GetValue(index)):(0.0f);

    switch(v)
    {
    case 0:
      return (m_sg)?(sgv):(1 - (sov+swv));
    case 1:
      return (m_so)?(sov):(1 - (sgv+swv));
    case 2:
      return (m_sw)?(swv):(1 - (sov+sgv));
    }
    return 0.0f;
  }

  const char * GetCellValueDesc(int v)
  {
    switch(v)
    {
    case 0:
      return "SG";
    case 1:
      return "SO";
    case 2:
      return "SW";
    }
    return 0;
  }

  void SetStep(const ResStep *t)
  {
    if (m_so)
      m_so->SetStep(t);
    if (m_sg)
      m_sg->SetStep(t);
    if (m_sw)
      m_sw->SetStep(t);
  }

  int GetCurrentStepIndex() const
  {
    if (m_so != NULL)
      return m_so->GetCurrentStepIndex();
    else if (m_sg != NULL)
      return m_sg->GetCurrentStepIndex();
    else if (m_sw != NULL)
      return m_sw->GetCurrentStepIndex();
    else
      return -1;
  }

  bool IsInitial()
  {
    return false;
  }
  bool IsComplete () const
  {
    if (m_so != NULL && !m_so->IsComplete()) return false;
    if (m_sg != NULL && !m_sg->IsComplete()) return false;
    if (m_sw != NULL && !m_sw->IsComplete()) return false;
    return true;
  }
  const char * GetSymbol() const { return m_symbol; }

  const char * GetDescription() const { return m_desc; }

  // min/max values won't be used to compute colorscale, since this property doesn't need one
  float GetMinValue() { return (m_so)?(m_so->GetMinValue()):(0.0f); }
  float GetMaxValue() { return (m_so)?(m_so->GetMaxValue()):(0.0f); }

  float GetNull() const { return (m_so)?(m_so->GetNull()):(0.0f); }

  int GetNumberOfStepsLoaded() { return (m_so)?(m_so->GetNumberOfStepsLoaded()):(0); }

  float GetValue(int index) { return (m_so)?(m_so->GetValue(index)):(0.0f); }

  void GetValues(float *buf, int bufsize[], int slice[]);
  bool HasValue(int index);
protected:
  int doLoad(const ResStep *t)
  {
    if (m_so != NULL)
      m_so->Load(t);
    if (m_sg != NULL)
      m_sg->Load(t);
    if (m_sw != NULL)
      m_sw->Load(t);
    return 1;
  }

  int doUnLoad(const ResStep *t)
  {
    if (m_so != NULL)
      m_so->UnLoad(t);
    if (m_sg != NULL)
      m_sg->UnLoad(t);
    if (m_sw != NULL)
      m_sw->UnLoad(t);
    return 1;
  }
};

#endif

