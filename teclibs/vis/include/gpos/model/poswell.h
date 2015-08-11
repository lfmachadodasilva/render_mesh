//* well.h
// A well, it's completions and it's properties.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef RES_POS_WELL_H
#define RES_POS_WELL_H

#include "common/ds/array.h"
#include "elemprop.h"
#include "completion.h"
#include "posmodel.h"
#include "well.h"
#include "elempropd.h"
#include <gpos/defines.h>
#include <ds/array.h>

#include <assert.h>
#include <stdio.h>

class ResPosModel;
class ResPosCompletion;
class ResPosElementPropertyData;

//* 'ResPosCompletionArray' Type
// Represents an array of completions
typedef PSArray<ResPosCompletion*> ResPosCompletionArray;

//* 'ResPosElementPropertyDataArray' Type
// Represents an array of property data
typedef PSArray<ResPosElementPropertyData*> ResPosElementPropertyDataArray;

//* 'ResPosWell'
// Represents a GRD well, suitable for viewing.
class RES_API ResPosWell : public ResWell
{
protected:
  char *m_name;
  char *m_lgrname;
  int m_step_appear;
  int m_step_production_first;
  int m_step_production_last;
  // indicates whether the well is opened or not
  // updated when the reference step is adjusted
  int m_open;
  ResPosModel *m_resposmodel;
  ResPosCompletionArray m_completions;
  ResPosElementPropertyDataArray vPropertiesValues;
  // step constants
  enum {
    ATTR_STEP_APPEAR = 0,
    ATTR_STEP_PRODUCTION_FIRST,
    ATTR_STEP_PRODUCTION_LAST
  };
public:
  ResPosWell (const char* name, ResPosModel *model);
  virtual ~ResPosWell();
  void SetGroup (int ts, const char* group);
  void SetHasProperty (const char* name)
  {
    m_has_prop.Set(name, true);
  }

  // time step when the well appear
  void SetStepAppear(int s)
  {
    m_step_appear = s;
  }
  // time step when the first production occurs
  void SetStepProductionFirst(int s)
  {
    m_step_production_first = s;
  }
  // time step when the last production occurs
  void SetStepProductionLast(int s)
  {
    m_step_production_last = s;
  }
  
    //* Name query
    // Returns the well name.
  const char * getName()
  {
    return m_name;
  }

    //* LGRName query
    // Returns the well lgr name.
  const char * GetLGRName()
  {
    return m_lgrname;
  }
    //* Name config
    // Sets the name of the well
  void SetName(const char * name)
  {
    if (m_name)
    {
      PSUtil::Free(m_name);
      m_name = 0;
    }
    if (name)
      m_name = PSUtil::StrDup(name);
  }
  //* LGRName config
    // Sets the lgr name of the well
  void SetLGRName(const char * name)
  {
    if (m_name)
    {
      PSUtil::Free(m_name);
      m_lgrname = 0;
    }
    if (name)
      m_lgrname = PSUtil::StrDup(name);
  }

  int getNCompletions()
  {
    return m_completions.size();
  }
  ResPosElementPropertyOriginal * getProperty(int i);
  ResPosElementPropertyOriginal * getProperty(const char *name);
  ResPosCompletion * getCompletion(int i);
  int getNTimeSteps();
  ResPosModel * getModel()
  {
    return m_resposmodel;
  }
  ResPosElementPropertyData * loadPropertyData(const char *name);
  void unloadPropertyData(const char *name);
    //* Completion addition
    // Adds a completion to this well
  int addCompletion(int depth, const int *i, const int *j, const int *k);
    //* Completion removal
    // Removes the specified completion
    // Returns non zero in case of success, zero otherwise
  int removeCompletion(ResPosCompletion *comp)
  {
    return m_completions.erase(comp);
  }
  //* *ResWell*
  const char * GetName () const
  {
    return m_name;
  }
  const char* GetGroup (int stepindex) const
  {
    if (m_parent_names.Size() == 0)
      return NULL;
    return m_parent_names.Get(stepindex);
  }
  int GetNumberOfCompletions() const
  {
    return m_completions.size();
  }
  ResCompletion * GetCompletion(int i);
  // adjusts the reference step of it's completions to 't'.
  void SetStep(const ResStep *t);
  int GetWellState()
  {
    return m_open;
  }
  void GetRadius(float *i, float *j, float *k);
  void InvertCompletionOrder();
  // virtual methods
  bool PropHasRecordedSteps (const char* prop_name, bool* has_recorded_steps);
  bool HasPropertyData (const char* name)
  {
    return m_has_prop.Find(name);
  }
protected:
  ResPosElementPropertyData * doLoadPropertyData(const char *name)
  {
    return loadPropertyData(name);
  }
  void doUnloadPropertyData(const char *name)
  {
    unloadPropertyData(name);
  }
private:
  // m_parent_names[i] = parent group at time step of index 'i'
  DsArray<char*> m_parent_names;
  DsHash<DsStringKey, bool> m_has_prop;
};

#endif

