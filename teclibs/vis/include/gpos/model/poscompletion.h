//* completion.h
// A well completion and it's properties.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef RES_POS_COMPLETION_H
#define RES_POS_COMPLETION_H

#include "elemprop.h"
#include "common/ds/array.h"
#include "model/completion.h"
#include "model/step.h"
#include "model/poswell.h"
#include <assert.h>
#include <stdio.h>

class ResPosModel;
class ResPosElementPropertyData;

//* 'ResPosElementPropertyDataArray' Type
// Represents an array of property data
typedef PSArray<ResPosElementPropertyData*> ResPosElementPropertyDataArray;

//* 'ResPosCompletion' Class
// Represents a GRD well completion suitable for viewing.
class ResPosCompletion : public ResCompletion
{
private:
  // step of creation
  int m_step_appear;
  // step when the production began
  int m_step_production_first;
  // step when the production ended
  int m_step_production_last;

  ResPosWell *m_pos_well;
  ResPosElementPropertyDataArray m_properties_values;

  // step constants
  enum {
    ATTR_STEP_APPEAR = 0,
    ATTR_STEP_PRODUCTION_FIRST,
    ATTR_STEP_PRODUCTION_LAST
  };

  // indicates whether the completion is opened or closed at
  // the reference step
  int m_open;

public:
  ResPosCompletion (ResCompletionPosition* pos, int index, ResPosWell *well);
  ~ResPosCompletion();
  ResPosModel * getModel();
  void SetHasProperty (const char* name)
  {
    m_has_prop.Set(name, true);
  }
  
  void SetStepAppear(int s)
  {
    m_step_appear = s;
  }
  
  void SetStepProductionFirst(int s)
  {
    m_step_production_first = s;
  }
  
  void SetStepProductionLast(int s)
  {
    m_step_production_last = s;
  }
  
    //* Step query
    // Returns the corresponding step value.
  int getStep(int step)
  {
    switch(step)
    {
    case ATTR_STEP_APPEAR:
      return m_step_appear;
    case ATTR_STEP_PRODUCTION_FIRST:
      return m_step_production_first;
    case ATTR_STEP_PRODUCTION_LAST:
      return m_step_production_last;
    default:
      return -1;
    }
  }

  ResPosElementPropertyData * loadPropertyData(char *name);

  void unloadPropertyData(char *name);

  //* *ResCompletion*

  int GetCompletionState()
  {
    return m_open;
  }

  ResWell * GetWell()
  {
    return m_pos_well;
  }

  const char* GetName ();
  // virtual methods
  bool HasPropertyData (const char* name)
  {
    return m_has_prop.Find(name);
  }
  /**
   * Informs which time steps are recorded for completion property 'name'.
   * Returns true if successful or false if failed fetching this data.
   */
  bool PropHasRecordedSteps (const char* name, bool* has_recorded_steps);
protected:
  ResPosElementPropertyData * doLoadPropertyData(const char *name)
  {
    return loadPropertyData((char*)name);
  }

  void doUnloadPropertyData(const char *name)
  {
    unloadPropertyData((char*)name);
  }
private:
  DsHash<DsStringKey, bool> m_has_prop;
  char* m_name; // cached completion name (as given by model loaders)
  int m_index; // index on the well's list
};

#endif

