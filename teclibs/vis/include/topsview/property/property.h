#ifndef TPV_PROPERTY_H_
#define TPV_PROPERTY_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <topsview/defines.h>

#define TPV_PROPERTY_MAX_DIMENSION 8

/**
  Represents a property data array associated to a model.
*/
class TPV_API TpvProperty
{
public:
  /**
      Defines where property values are located.
  */
  enum PropType
  {
    PROP_NODE = 0,
    PROP_ELEMENT,      
    PROP_ELEMENT_NODE,
    PROP_ELEMENT_POINT
  };

  /**
      Creates a new empty property object.
  */
  TpvProperty(PropType type=PROP_ELEMENT, int dimension=1)
    : m_values(NULL), m_values_ownership(false)
  {
    Reset(type, dimension);
  }

  ~TpvProperty()
  {
    if (m_values && m_values_ownership)
      free(m_values);
  }

  /**
      Sets the dimension of the property data.
    1: scalar, > 1: vector
  */
  void SetDimension(int dim)
  {
    m_dimension = dim;
  }

  /**
      Gets the dimension of the property data.
    1: scalar, > 1: vector
  */
  int GetDimension() const
  {
    return m_dimension;
  }

  /**
    Sets the property data array.
    The total size of the array (in number of floats) is 
    dimension*num_values.
    If take_ownership is true this object will be responsible for deleting the
    array, by calling free(values) when necessary. In such case,
    the array must be allocated by using the malloc/calloc/realloc family of functions.
  */  
  void SetValues(int num_values, float* values, bool take_ownership = false)
  {
    m_num_values = num_values;
    m_values = values;
    m_values_ownership = take_ownership;
  }

  /**
      Gets the number of values of property data.
    The total size of the array, in number of floats, is dimension*num_values.
  */
  int GetNumOfValues() const
  {
    return m_num_values;
  }

  /**
      Gets the property data array.
  */
  float* GetValues() const
  {
    return m_values;
  }

  /**
      Sets base global id.
    Default base global id is 1.
  */
  void SetBaseGlobalId(int gid)
  {
    m_base_gid = gid;
  }

  int GetBaseGlobalId() const
  {
    return m_base_gid;
  }

  /**
      Gets the scalar value of the element or node with the given global id 
    and local id.
  */
  float* GetValue(int gid, int lid = 0) const
  {
    int inc;
    gid -= m_base_gid;
    // Indirection is required for PROP_ELEMENT_NODE and PROP_ELEMENT_POINT
    if (m_indirection != NULL) {
      if (m_local_indirection)
        inc = m_dimension*m_local_indirection[m_indirection[gid] + lid];
      else
        inc = m_dimension*(m_indirection[gid] + lid);
    }
    else
      inc = m_dimension*gid;
    assert(inc < m_dimension*m_num_values);

    return m_values + inc;
  }

  void SetMinValue(float* minvalue)
  {
    for (int i = 0; i < m_dimension; i++)
      m_minvalue[i] = minvalue[i];
  }

  float* GetMinValue() const
  {
    return (float*) m_minvalue;
  }

  void SetMaxValue(float* maxvalue)
  {
    for (int i = 0; i < m_dimension; i++)
      m_maxvalue[i] = maxvalue[i];
  }

  float* GetMaxValue() const
  {
    return (float*) m_maxvalue;
  }

  /**
      Sets property indirection array. 
    indirection[id-1] = offset_in_values
  */
  void SetIndirection(const int* ind)
  {
    m_indirection = ind;
  }

  const int* GetIndirection() const
  {
    return m_indirection;
  }

  void SetLocalIndirection(const int* ind)
  {
    m_local_indirection = ind;
  }

  const int* GetLocalIndirection() const
  {
    return m_local_indirection;
  }

  float NormalizeScalar(float s) const
  {
    return (s-m_minvalue[0])/(m_maxvalue[0]-m_minvalue[0]);
  }

  PropType GetType() const
  {
    return m_type;
  }

  void Reset(PropType type=PROP_ELEMENT, int dimension=1)
  {
    assert(dimension <= TPV_PROPERTY_MAX_DIMENSION);
    m_type = type;
    m_dimension = dimension;
    m_base_gid = 1;
    m_base_lid = 0;
    m_num_values = 0;
    if (m_values && m_values_ownership)
      free(m_values);
    m_values = NULL;
    m_values_ownership = false;
    m_indirection = NULL;
    m_local_indirection = NULL;
    for (int i = 0; i < TPV_PROPERTY_MAX_DIMENSION; i++) {
      m_minvalue[i] = 0.0f;
      m_maxvalue[i] = 0.0f;
    }
  }

  void Print(const char* msg = NULL);

private:
  PropType   m_type;
  int        m_dimension;
  int        m_base_gid;
  int        m_base_lid;
  int        m_num_values;
  float*     m_values;
  const int* m_indirection;
  const int* m_local_indirection;
  float      m_minvalue[TPV_PROPERTY_MAX_DIMENSION];
  float      m_maxvalue[TPV_PROPERTY_MAX_DIMENSION];
  bool       m_values_ownership;
};
#endif

