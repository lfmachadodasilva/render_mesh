
#ifndef _TOP_MODEL_READER_H
#define _TOP_MODEL_READER_H

#include "reader.h"
#include <tops/model.h>
#include <stdio.h>

//TODO split this class into Reader and Writer classes
class TOPSRD_API TopModelReader : public TopReader
{
private:
  TopModel* m_model;
  char m_filename_node[256];
  char m_filename_ele[256];
  char m_filename_coh[256];
  FILE* m_fnode;
  FILE* m_fele;
  FILE* m_fcoh;

  bool m_is_open;
  bool m_has_coh;

  int m_ncoord;
  int m_nnodes;
  int m_nnodes_alloc;
  TopNode* m_nodes;
  double* m_scalars;
  bool m_update_adj;
  bool m_invert_normals;
  
  static TopElement AddElem(TopModel* m, int ncoord, int ninc, 
      const char* el_type, TopNode* nodes, bool update_adj);
  static TopElement AddCohesive(TopModel* m, int ncoord, int ninc, 
    const char* el_type, TopNode* nodes, bool update_adj);

  int ReadNodes();
  int ReadPoly2D(int nelem);
  int ReadElem();
  int ReadCohesive();
  void Init();

public:
  /** Gets the string of an element type. */
  static const char* GetElemTypeName(int el_type);

  /** Gets the element type associated to the given string. */
  static int GetElemType(const char* name);

  // deprecated
  static int Read(TopModel* model, 
      const char* fnodes, const char* felem, const char* fcoh);
  static int Read(TopModel* model, const char* filename);
  static int Write(TopModel* model, 
      const char* fnodes, const char* felem, const char* fcoh);
  static int Write(TopModel* model, const char* filename);


  TopModelReader(TopModel* m,
    const char* fnodes, const char* felem, const char* fcoh);

  TopModelReader(TopModel* m, const char* filename);

  /** 
    Sets whether adjacencies must be updated.
    Default: true.
  */
  void SetUpdateAdjEnabled(bool flag);

  /** 
  Sets if the loader inverts the normal orientation of the faces
  Default: false.
  */
  void SetInvertNormals(bool flag);

  /**
    If enabled, IDs read from the input file will be assigned to the
    elements and nodes in the mesh. 
    Likewise, IDs ids associated to elements and nodes will be writen
    to the output file.
  */
  void SetElemAndNodeIdsEnabled(bool enabled);

  virtual ~TopModelReader();

  virtual bool Open();

  virtual bool IsOpen();

  virtual bool Close();

  virtual bool Read();

  virtual TopModel* GetModel();

  virtual int GetNumOfResultCases();

  virtual const char* GetResultCaseTitle(int case_id);

  virtual int GetNumOfResultFields(int case_id, int type_id);

  virtual const char* GetResultFieldTitle(int case_id, int type_id, int field_id);

  virtual int GetNumOfResultSteps(int case_id, int type_id, int field_id);

  virtual const char* GetResultStepTitle(int case_id, int type_id, int field_id, int step_id);

  virtual int GetResultData(
    int case_id, int type_id, int field_id, int step_id, double* data);

  int Write();

private:
  bool m_elem_and_node_ids_enabled;
};


#endif
