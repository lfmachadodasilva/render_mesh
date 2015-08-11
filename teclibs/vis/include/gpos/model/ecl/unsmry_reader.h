#pragma once
#include <gpos/defines.h>
#include <gpos/model/loadernew.h>
#include <gpos/model/modelnew.h>
#include <gpos/common/util.h>
#include <ds/array.h>
#include <ds/hash.h>
#include "common.h"

typedef struct {
  size_t offset;
  int    ts;
} SummaryData;

//* 'SummaryDataArray' Type
// Represents an array of SummaryData.
typedef DsArray<SummaryData*> SummaryDataArray;

class SMSPECReader;

class ECLReader;

class UNSMRYReader : public ECLFormatReader
{
public:
  UNSMRYReader (const char* rootname, 
                ResECLError *errors, 
                int start_day,
                int start_month,
                int start_year,
                int parameters_count,
                int time_pos,
                int day_pos,
                int month_pos,
                int year_pos);
  ~UNSMRYReader();
  bool ReadKeywords (ResPosLoaderNew* loader);
  bool FileExists ();
  bool ValidateFiles (bool required);
  int GetDataCount ();
  size_t GetDataOffset (int pos);
  void ReadValue (size_t offset, float* value) throw (bool);
  int GetTimeStepCount ();
  bool GetTimeStep (int index, double* ndays, int* day, int* month, int* year);
private:
  void ReadSEQHDR (ECLReader *rd) throw (bool);
  void ReadMINISTEP (ECLReader *rd)  throw (bool);
  void ReadPARAMS (ECLReader *rd) throw (bool);
  void AddTimestep (float day, float month, float year, float time) throw (bool);
  void AddTimestep (float time) throw (bool);
private:
  struct WellTimeStep
  {
    double time;
    int day;
    int month;
    int year;
  } ;
  char* m_filename;
  char* m_rootname;
  ResECLError* m_errors;
  ECLReader *m_summary_rd;
  SMSPECReader* m_smspec_reader;
  int m_summary_index;
  SummaryDataArray *m_summary_data; 
  ResPosModelNew* m_modelnew;
  DsArray<WellTimeStep> m_wellsteps;
  int m_start_day;
  int m_start_month;
  int m_start_year;
  int m_parameters_count;
  int m_time_pos;
  int m_day_pos;
  int m_month_pos;
  int m_year_pos;
};
