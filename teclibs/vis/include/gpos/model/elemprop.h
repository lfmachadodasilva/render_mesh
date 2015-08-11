//* elemprop.h
// A viewable element property.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef vis_element_property_h
#define vis_element_property_h

#include <gpos/common/util.h>
#include <gpos/defines.h>

//* 'ResPosElementProperty' Class
// Represents an element property suitable for viewing.
class RES_API ResPosElementProperty
{
public:
  virtual ~ResPosElementProperty()
  {
    PSUtil::Free(m_symbol);
    PSUtil::Free(m_description);
  }
  void SetHandle(int handle)
  {
    m_handle = handle;
  }
  int GetHandle() const
  {
    return m_handle;
  }
    //* Symbol query
    // Returns the property symbol.
  const char * GetSymbol() const
  {
    return m_symbol;
  }
    //* Description query
    // Returns the property description.
  const char * GetDescription() const
  {
    return m_description;
  }
    //* Unit query
    // Returns the property unit
  virtual const char * GetUnit() const = 0;

    //* Data query
    // Returns true if this property holds the values for each element
    // Returns false if the system should ask the element instead
  virtual bool HasData()
  {
    return false;
  }

  // the following methods should be used if this entity provides data
  virtual void GetSize(int *nelems, int *nsubelems)
  {
    *nelems = -1;
    *nsubelems = -1;
  }

  virtual float GetValue(int elem, int subelem, int step)
  {
    return 0.0f;
  }
  
  virtual float GetNull()
  {
    return 97654321.0f;
  }
protected:
  ResPosElementProperty(const char *symbol, const char *desc) :
    m_handle(-1)
  {
    m_symbol = PSUtil::StrDup(symbol);
    m_description = PSUtil::StrDup(desc);
  }
private:
  int m_handle;
  char *m_symbol;
  char *m_description;
};

#endif

