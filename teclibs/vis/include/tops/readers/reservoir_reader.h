
#ifndef _TOP_RESERVOIR_READER_H
#define _TOP_RESERVOIR_READER_H

#include "defines.h"
#include <stdio.h>

class  TopModel;

class TOPSRD_API TopReservoirReader
{
  TopModel*       m_model;
  int             m_ncoord;
  char            m_line[2048];

  int             m_eid;
  int             m_nid;

  int             m_nnodes;
  int             m_nnodes_alloc;
  TopNode*       m_nodes;
  int             m_nelem;
  int             m_nelem_alloc;
  TopElement*    m_elem;

  int ReadHeader(FILE* fp);
  int ReadNodes(FILE* fp);
  int ReadElem(FILE* fp);
  void AddTETCellAux(TopNode nodes[4], double scalar);
  void AddTETCell(TopNode el_nodes[8], double scalar);
  void AddCell(int i, int j, int k, TopNode el_nodes[8], double scalar);
  void CheckCells();
  void CheckNodes();

public:
  TopReservoirReader(TopModel* m);
  ~TopReservoirReader();

  /**
    Reads elements from node and element files into a model.
  */
  int Read(const char* filename); 

  int GetNResultCases() { return 1; }

  const char* GetResultCaseTitle(int res_id) 
  { 
    return "CASE_1"; 
  }
  
  int GetNSteps(int res_id) { return 1; }
  
  int GetNNodalScalars(int res_id, int step_id) 
  { 
    return 1;
  }
  const char* GetNodalScalarTitle(int res_id, int step_id, int scalar_id)
  {
    return "SCALAR_1";
  }

  // Reads nodal scalar data into the model's nodes.
  int ReadNodalScalarData(int res_id, int step_id, int scalar_id) {return 1; }

  int Write(const char* filename);
};

#endif
