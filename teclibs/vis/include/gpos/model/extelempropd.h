//* extelempropd.h
// A viewable external element property data.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef vis_ext_element_property_data_h
#define vis_ext_element_property_data_h

#include <assert.h>

#include "elempropd.h"

class ResPosElementProperty;
class ResModel;

//* 'ResPosExtElementPropertyData' Class
// Represents an external element property data suitable for viewing.
class RES_API ResPosExtElementPropertyData : public ResPosElementPropertyData
{
  char *m_symbol;
  char *m_desc;
  char *m_unit;
  char *m_srcfile;
  int m_nsteps;

  float *m_values;

public:
  ResPosExtElementPropertyData() :
    m_symbol(NULL),
    m_desc(NULL),
    m_unit(NULL),
    m_srcfile(NULL),
    m_nsteps(-1),
    m_values(NULL)
  {
  }

  ~ResPosExtElementPropertyData();

    //* Property data export
    // Writes an external property file, given the model, the property and the file name.
    // Returns non zero in case of success, zero otherwise.
  static int WriteFile(ResModel *m, ResPosElementPropertyData *p, const char *filename);

    //* Data file open
    // Opens the given filename and reads in the data, closing it afterwards.
    // Returns non zero in case of success, zero otherwise.
  int ReadFile(ResModel *m, const char *name);

  const char * GetSourceFile() const { return m_srcfile; }

  const char * GetSymbol() const { return m_symbol; }

  void SetSymbol(const char *s);

  const char * GetDescription() const { return m_desc; }

  void SetDescription(const char *s);

  const char * GetUnit() const { return m_unit; }

  void SetUnit(const char *s);


  //* ResPosElementPropertyData

  ResPosElementProperty * GetProperty() { return 0; }

  float GetNull();

  float GetValue(int i)
  {
    assert((i>=0)&&(i<m_nsteps));
    if ((i<0)||(i>=m_nsteps))
      return -1.0f;
    return m_values[i];
  }

  int GetNumberOfSteps() { return m_nsteps; }

};

#endif
