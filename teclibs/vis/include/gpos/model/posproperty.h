//* property.h
// A property of a GRD type mesh.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef RES_POS_PROPERTY_H
#define RES_POS_PROPERTY_H

#include <common/util.h>
#include <common/ds/array.h>
#include "posmodel.h"
#include "property.h"
#include "step.h"
#include <assert.h>
#include <stdlib.h>
#include <gpos/defines.h>

//# define DEBUG_LIMITS_RECOMPUTATION

class ResPosMapProperty;

//* 'ResPosData' Class
// Represents the values of a property
class RES_API ResPosData
{
public:
  ResPosData (ResPosMapProperty* prop, bool complete, int n, float nullfloat);
  ResPosData (ResPosMapProperty* prop, bool complete, int n, float nullfloat, int nullint);
  ~ResPosData ();
  void Update();
    //* Amount of stored values query
    // Returns the number of values stored.
  int Size () const
  {
    return d_n;
  }
    //* Value query
    // Returns the ith value (float and int versions)
  float GetValue(int i) const;
    //* All values query
    // For fast computations (aka "macro")
    // 'step' contains which step in 'buf' to put the values in
  void GetValues(float *buf, int bufsize[], int slice[], int step);
  void GetLimits (float *vmin=NULL, float *vmax=NULL)
  {
    if (vmin)
      *vmin = d_vmin;
    if (vmax)
      *vmax = d_vmax;
  }
  float *GetArray() const
  {
    return d_v;
  }
  int* GetArrayInt() const
  {
    return (int*)d_v;
  }
private:
  ResPosMapProperty* m_prop;
  float d_nullfloat;
  int d_nullint;
  int d_n;         // number of values
  float *d_v;      // values array
  float d_vmin;    // min value found when reading
  float d_vmax;    // max value found when reading
  bool d_complete; // indicates whether the data are complete or not
  bool d_isinteger;// indicates whether this is an integer property
};

//* 'ResPosMapProperty' Class
// Represents a general property of a GRD mesh, suitable for viewing.
class RES_API ResPosMapProperty : public ResProperty
{
protected:
  ResPosModel*     d_model;
  char*           d_symbol;
  char*           d_desc;
  ResValueType d_type;
  float           d_vmin;
  float           d_vmax;
  float           d_null;
  void SetCorrectLimits (float min, float max, bool update_instead_of_set)
  {
    if (update_instead_of_set) {
      if (min < d_vmin)
        d_vmin = min;
      if (max > d_vmax)
        d_vmax = max;
    }
    else {
      d_vmin = min;
      d_vmax = max;
    }
  }
public:
  ResPosMapProperty (
    ResPosModel* model,
    const char* symbol,
    const char* desc,
    ResValueType type,
    const char* unit,
    bool iscomplete);
  virtual ~ResPosMapProperty ();

  ResPosModel *GetPosModel() const
  {
    return (ResPosModel*)GetModel();
  }
  char* Symbol () const
  {
    return d_symbol;
  }

  char* Description () const
  {
    return d_desc;
  }

  ResValueType GetArrayType() const
  {
    return d_type;
  }

  const char * GetUnit() const
  {
    return m_unit;
  }

  float MinValue () const
  {
    return d_vmin;
  }

  float MaxValue () const
  {
    return d_vmax;
  }
  // Checks the validity of the file regarding this property.
  virtual bool IsValidInFile () const = 0;
	    //* Property load
  // Load the data of the specified step or -1 to load all steps.
  virtual bool PropLoad (int t=-1) = 0;

      //* Property unload
  // Unload the data of the specified step or -1 to unload all steps.
  virtual void PropUnload (int t=-1) = 0;

  bool IsComplete () const
  {
    return m_iscomplete;
  }
  //* *ResProperty*

  const char * GetSymbol() const
  {
    return d_symbol;
  }

  const char * GetDescription() const
  {
    return d_desc;
  }

  float GetMinValue ();
  float GetMaxValue ();

  float GetNull() const
  {
    return d_null;
  }

  virtual float GetValue(int index) = 0;

protected:
  int doLoad(const ResStep *t);
  int doUnLoad(const ResStep *t);
private:
  char* m_unit;
  bool m_iscomplete;
};

//* 'ResPosIniMapProperty' Class
// Represents an initial property.
class RES_API ResPosIniMapProperty : public ResPosMapProperty
{
  ResPosData* d_data;
  bool *m_loaded; // array of loaded steps, to control load and unload
public:
  ResPosIniMapProperty (
    ResPosModel* model,
    const char* symbol,
    const char* desc,
    ResValueType type,
    const char* unit,
    bool iscomplete);
  
  virtual ~ResPosIniMapProperty ();

  int GetNumberOfStepsLoaded ()
  {
    return d_data ? 1 : 0; 
  }

  virtual bool IsValidInFile () const;

  bool PropLoad (int t=-1);

  void PropUnload (int t=-1);

  //* *ResProperty*

  bool IsInitial()
  {
    return true;
  }
  int GetNumValuesPerStep () const;
  float GetValue(int index);
  // replicate values over all steps
  void GetValues(float *buf, int bufsize[], int slice[]);
private:
  long Size ();
};

//* 'ResPosRecMapProperty' Class
// Represents a recurrent property.
class RES_API ResPosRecMapProperty : public ResPosMapProperty
{
  DsArray<ResPosData*> d_data;
  // given a m_limitsupdated[ts], were property limits updated by searching
  // through the values of time step 'ts' ?
  // added because the limits specified in the ResPos file differ from
  // the actual value limits in the map file.
  bool *m_limitsupdated;
  int m_limitsupdatedsize;
protected:
  bool GetLimitsUpdated (int ts)
  {
    assert(ts >= 0);
    if (ts > m_limitsupdatedsize-1)
    {
      int oldsize = m_limitsupdatedsize;
      m_limitsupdatedsize = ts+1;
      m_limitsupdated = (bool*)realloc(m_limitsupdated,m_limitsupdatedsize*sizeof(bool));
      // first time: Get(0)  -> (for i=0 ; i<1 ; i++) updated[i] = false;
      // first time: Get(15) -> (for i=0 ; i<16; i++) updated[i] = false;
      // later     : Get(18) -> (for i=16; i<19; i++) updated[i] = false;
      for (int i=oldsize; i<m_limitsupdatedsize; i++)
        m_limitsupdated[i] = false;
    }
    return m_limitsupdated[ts];
  }
  void SetLimitsUpdated (int ts)
  {
    assert(0 <= ts && ts < m_limitsupdatedsize);
    m_limitsupdated[ts] = true;
  }
public:
  ResPosRecMapProperty (
    ResPosModel* model,
    const char* symbol,
    const char* desc,
    ResValueType type,
    const char* unit);
  virtual ~ResPosRecMapProperty ();

  int GetNumberOfStepsLoaded ()
  {
    int c = 0;
    for (int i=0; i<d_data.Size(); i++)
      if (d_data[i] != NULL)
        ++c;
    return c;
  }

  virtual bool IsValidInFile () const;
  bool PropLoad (int t=-1);

  void PropUnload (int t=-1);

  //* *ResProperty*

  bool IsInitial()
  {
    return false;
  }
  int GetNumValuesPerStep () const;
  float GetValue(int index);
  void GetValues(float *buf, int bufsize[], int slice[]);
private:
  long Size ();
};

#endif

