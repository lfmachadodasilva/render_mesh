/**
*/

#ifndef TPV_LINE_SET_2_H
#define TPV_LINE_SET_2_H

#include <tops/tops.h>
#include <topsview/defines.h>

#include "array.h"
#include "support.h"

#include <stdio.h>
#include <math.h>

/**  
*/
class TPV_API TpvLineSet2
{
private:
  int m_size;
  TpvFloatArray m_pos;
  TpvSupportArray m_supports;
  TpvFloatArray m_field;

public:
  TpvLineSet2() : m_size(0) {}
  ~TpvLineSet2() {}

  void SetSize(int size) { m_size = size; }
  int GetSize() { return m_size; }

  TpvFloatArray* GetPositions() { return &m_pos; }

  /** Preferred support order: EDGE_USE, FACET_USE/ELEMENT2D, ELEMENT. */
  TpvSupportArray* GetSupports() { return &m_supports; }

  TpvFloatArray* GetField() { return &m_field; }

  void Clear()
  {
    m_size = 0;
    m_pos.Clear();
    m_supports.Clear();
    m_field.Clear();
  }

  void Print()
  {
    for (int i = 0; i < m_size; i++) {
      printf("line[%d]:\n", i);
      for (int j = 0; j < 2; j++) {
        if (m_pos.Size() > 0) {
          printf("  pos[%d]: %+6.3e %+6.3e %+6.3e\n", j, 
            m_pos.Get(6*i+3*j), m_pos.Get(6*i+3*j+1), m_pos.Get(6*i+3*j+2));
        }
        if (m_field.Size() > 0) {
          printf("  field[%d]: %+6.3e\n", j, m_field.Get(2*i+j));
        }
      }
    }
  }
};

#endif
