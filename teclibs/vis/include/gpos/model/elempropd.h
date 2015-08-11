//* elempropd.h
// A viewable element property data.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef vis_element_property_data_h
#define vis_element_property_data_h

#include <float.h>
#include <gpos/defines.h>

class ResPosElementProperty;

//* 'ResPosElementPropertyData' Class
// Represents an element property data suitable for viewing.
class RES_API ResPosElementPropertyData
{  
public:

  virtual ~ResPosElementPropertyData()
  {
  }

    //* Property query
    // Returns the property associated with this data.
  virtual ResPosElementProperty * GetProperty() = 0;

    //* Null value query
    // Returns the value which represents a null property value.
  virtual float GetNull() = 0;

    //* Value query
    // Returns the value of the ith timestep.
  virtual float GetValue(int i) = 0;

  virtual int GetNumberOfSteps() = 0; // entity dimension

  float GetMinValue()
  {
    if( m_minValue == FLT_MAX )
      SetMinMaxValues();
    return m_minValue;
  }

  float GetMaxValue()
  {
    if( m_maxValue == -FLT_MAX )
      SetMinMaxValues();
    return m_maxValue;
  }

protected:
  ResPosElementPropertyData():m_maxValue(-FLT_MAX),m_minValue(FLT_MAX){}

  void SetMinMaxValues()
  {
    for( int i = 0; i < GetNumberOfSteps(); ++i )
    {
      float v = GetValue(i);
      if( v != GetNull() )
      {
        m_maxValue = v > m_maxValue ? v : m_maxValue;
        m_minValue = v < m_minValue ? v : m_minValue;
      }
    }
  }

private:
  float m_maxValue;
  float m_minValue;
};

#endif
