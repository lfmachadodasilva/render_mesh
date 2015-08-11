#ifndef CMG_DICT_H
#define CMG_DICT_H

#include <stdio.h>
#include <stdlib.h>
#include <ds/hash.h>
#include <gpos/model/loadernew.h>
#include "common.h"

class CMGTextReader;

typedef DsArray<int> UnitArray;

typedef struct {
  char *short_name;   // brief descriptive name of the entry (must be unique)
  char *sr_name;      // the SR2 keyword that corresponds to the entry
                      // (opt-must be unique)
  char *sr_title;     // Titles are typically descriptive strings for the particular 
                      // keyword. The default value is the empty string "".  This 
                      // string must not be longer than 40 characters
  char *sr_notes;     // string of notes to be associated with the sr2 keyword.  
                      // The default value is the empty string ""
  char *sr_type;      // specifies the data type associated with the sr2 keyword.  
                      // The following types are defined:
                      //   "s" - symbolic size keyword (stored as an integer)
                      //   "r" - floating point keyword
                      //   "i" - integer keyword
                      //   "l" - logical keyword
                      // The default type is s (symbolic size).
  char *sr_ssize;     // This optional attribute specifies the symbolic size of 
                      // associated with the sr2 keyword.  This string is either a 
                      // numeric constant (1 to 999999), a symbolic size name 
                      // (ie NPTCS), or an empty string ("") indicating a default 
                      // value of 1.  The default value is the empty string indicating 
                      // a value of 1.
  int  sr_ssvalue;    // This optional attribute is describes the length of a single
                      // ocurrence the item (if known).  For keywords whose ssize 
                      // specifies a numeric constant, then the ssvalue must be that 
                      // value.  Otherwise, this value must be the default value of 1.  
                      // The default value is 1. 
  char *sr_packing;   // This optional attribute specifies the grid storage mechanism 
                      // for the variable.  The following packing types are defined:
                      //  " " - this keyword is not associated with a grid array
                      //  "s" - this keyword is associated with a spatial storage grid array
                      //  "p" - this keyword is associated with a packed storage grid array
                      //  "c" - this keyword is associated with a complete storage grid array
                      // The default value is " ".
  char *sif_keyword;  // the SIF keyword that corresponds to the entry (opt)
  char *long_name;    // longer descriptive name of the entry
  UnitArray  *unit;       // index for unit
  bool valid_for_zero_por;
} DictData;

class CMGDictionary
{
public:
  ~CMGDictionary();
  int GetInfo (const DsStringKey& name,
               char* type = NULL,
               char* size = NULL,
               char* packing = NULL,
               char* desc = NULL,
               UnitArray* unit = NULL);
  DictData *GetEntry (const DsStringKey& name)
  {
    return m_dict.Get(name);
  }
  int Read (const char *filename);
  bool GetDescAndUnit (const char* symbol,
                       char* desc,
                       UnitArray* unit)
  {
    char* name = ResCMGGetPropName(symbol);
    DictData* d = GetEntry(name);
    PSUtil::Free(name);

    if (d == NULL)
      return false;

    PSUtil::StrCopy(desc, d->long_name);
  
    int numunits = d->unit->Size();
    unit->Resize(numunits, true);
    for (int i=0; i<numunits; ++i)
      unit->SetConst(i, d->unit->Get(i)); 

    return true;
  }
  static bool IsComplete (const char* packing)
  {
    return !PSUtil::StrEq(packing, "p");
  }
private:
  const char *ReadDictKey (CMGTextReader& rd);
  DictData* InitData ();
private:
  DsHash<DsStringKey,DictData*> m_dict;
};

#endif

