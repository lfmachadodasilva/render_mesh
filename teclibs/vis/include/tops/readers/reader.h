
#ifndef _TOP_READER_H
#define _TOP_READER_H

#include "defines.h"

class TopModel;

class TOPSRD_API TopReader
{
public:
  TopReader() {}

  virtual ~TopReader() {}
  
  virtual bool Open() = 0;

  virtual bool IsOpen() = 0;

  virtual bool Close() = 0;

  virtual bool Read() = 0;

  virtual TopModel* GetModel() = 0;

  virtual int GetNumOfResultCases() = 0;

  virtual const char* GetResultCaseTitle(int case_id) = 0;

  virtual int GetNumOfResultFields(int case_id, int type_id) = 0;

  virtual const char* GetResultFieldTitle(int case_id, int type_id, int field_id) = 0;

  virtual int GetNumOfResultSteps(int case_id, int type_id, int field_id) = 0;

  virtual const char* GetResultStepTitle(int case_id, int type_id, int field_id, int step_id) = 0;

  virtual int GetResultData(
      int case_id, int type_id, int field_id, int step_id, double* data) = 0;
};

#endif
