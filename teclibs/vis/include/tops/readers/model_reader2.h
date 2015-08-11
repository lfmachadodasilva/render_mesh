
#ifndef _TOP_MODEL_READER2_H
#define _TOP_MODEL_READER2_H

#include "defines.h"

class  TopModel;

class TOPSRD_API TopModelReader2
{
  TopModel* m_model;
  int m_structured;
  char m_filename[512];
  int  m_nelem_scalar;
  int  m_nelem_node_scalar;
  int  m_nnode_scalar;
  int  m_elem_type;
  int  m_nelem_nodes;

  int ReadNodes();
  int ReadElem();
  int ReadUnstructuredGrid();
  int ReadStructuredGrid();

public: 
  enum {
    PROP_ELEM_SCALAR=0,
    PROP_ELEM_NODE_SCALAR,
    PROP_NODE_SCALAR,
  };
  
  TopModelReader2();
  ~TopModelReader2();

  // file.model
  int ReadInfo(const char* filename);
 
  // file.ele, file.nodes
  TopModel* ReadGrid();
  int    GetNElemScalarProp() { return m_nelem_scalar; }
  float* ReadElemScalarProp(int i);
  int    GetNElemNodeScalarProp() { return m_nelem_node_scalar; }
  float* ReadElemNodeScalarProp(int i);
  int    GetNNodeScalarProp() { return m_nnode_scalar; }
  float* ReadNodeScalarProp(int i);
};

class TOPSRD_API TopModelWriter2
{
  TopModel* m_model;
  char m_filename[512];
  int  m_elem_type;

  int WriteNodes();
  int WriteElem();
public: 
  TopModelWriter2();
  ~TopModelWriter2();

  int WriteInfo(const char* filename, TopModel* m,
      int nelem_scalars, int nelem_node_scalars, int nnode_scalars);
  int WriteGrid();
  int WriteElemScalarProp(int i, float* sv);
  int WriteElemNodeScalarProp(int i, float* sv);
  int WriteNodeScalarProp(int i, float* sv);
};

#endif
