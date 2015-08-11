
#ifndef _TOP_PLT_READER_H
#define _TOP_PLT_READER_H

#include "reader.h"
#include <tops/model.h>
#include <stdio.h>

class TOPSRD_API TopPltReader : public TopReader
{
private:
  enum {
    VAR_MAX = 16
  };

  TopModel* m_model;
  char m_filename[FILENAME_MAX];
  FILE* m_fp;
  bool m_is_open;

  int  m_nvars;
  int  m_nfields;
  char m_field_str[VAR_MAX][BUFSIZ];
  double* m_field_data[VAR_MAX];
  int  m_coord_to_var[3];
  int  m_var_to_coord[VAR_MAX];
  int  m_field_to_var[VAR_MAX];
  int  m_var_to_field[VAR_MAX];

  int m_nnodes;
  int m_nelems;
  int m_elem_type;
  int m_nelem_nodes;
  TopNode* m_nodes;
  
  int ReadHeader();
  int ReadNodes();
  int ReadElems();

public: 
  TopPltReader(TopModel* m, const char* filename);

  virtual ~TopPltReader();

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
};


#endif
