//* extelemprop.h
// A viewable external element property.
// Tecgraf/PUC-Rio
// Jun 2005

#ifndef vis_ext_element_property_h
#define vis_ext_element_property_h

#include "elemprop.h"

//* 'ResPosExtElementProperty' Class
// Represents an external element property suitable for viewing.
class RES_API ResPosExtElementProperty : public ResPosElementProperty
{
  char *m_unit;
  int m_nelems;
  int m_nsubelems;
  float *m_values;

  int index(int elem, int subelem, int step)
  {
    return ((step*m_nsubelems)+subelem)*m_nelems+elem;
  }

  /*
   * file format:
   *
   * for elem=1, nelems do
   *   for subelem=1, nsubelems do
   *     for step=1, nsteps do
   *        READ/WRITE value
   */

public:
  ResPosExtElementProperty(int nelems, int nsubelems, const char *symbol,
    const char *desc, const char *unit);

  ~ResPosExtElementProperty();
  const char * GetUnit() const
  {
    return m_unit;
  }

  bool HasData()
  {
    return true;
  }

  // the following methods should be used if this entity provides data
  void GetSize(int *nelems, int *nsubelems)
  {
    *nelems = m_nelems;
    *nsubelems = m_nsubelems;
  }

  float GetValue(int elem, int subelem, int step)
  {
    return (m_values)?(m_values[index(elem, subelem, step)]):(-1.0f);
  }

    //* Property data export
    // Returns non zero in case of success, zero otherwise.
  static int WriteFile(ResPosElementProperty *p, int nsteps, const char *filename);

    //* Data file read
    // Opens the given filename, reads in its contents and closes it afterwards.
    // Consistency check is made with current settings.
    // Returns non zero in case of success, zero otherwise.
  int ReadFile(int nsteps, const char *filename);
};

#endif

