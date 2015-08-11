//* group.h
// A viewable reservoir group.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef vis_group_h
#define vis_group_h

#include <ds/hash.h>
#include "common/util.h"
#include "elemprop.h"
#include <common/ds/array.h>
#include <model/posmodel.h>
#include <model/group.h>
#include <assert.h>
#include <stdio.h>
#include <gpos/defines.h>

class ResModel;
class ResPosElementPropertyData;

//* 'ResPosElementPropertyDataArray' Type
// Represents an array of property data
typedef PSArray<ResPosElementPropertyData*> ResPosElementPropertyDataArray;

//* 'ResPosGroup' Class
// Represents a group suitable for viewing.
class RES_API ResPosGroup
{
public:
  ResPosGroup(const char *name, ResPosModel *model);
  virtual ~ResPosGroup();
  void Release();
  void SetHasProperty (const char* name)
  {
    m_has_prop.Set(name, true);
  }
    //* Name query
    // Returns the name of the group.
  const char * GetName() const
  {
    return sName;
  }
  /**
   * Informs which time steps are recorded for group property 'name'.
   * Returns true if successful or false if failed fetching this data.
   */
  bool PropHasRecordedSteps (const char* prop_name, bool* has_recorded_steps);
    //* Property data load
    // Loads (if necessary) the data of the given property.
    // Returns the data loaded or NULL in case of an error.
  ResPosElementPropertyData * LoadPropertyData(const char *name);

    //* Property data unload
    // Unloads the data of the given property.
  void UnloadPropertyData(const char *name);

		//* Reference count query
		// Returns the current number of references to the given property
	int GetRefCount(const char *name);
  /**
   * Informs if this group has group property 'name' recorded for at least one
   * time step.
   */
  bool HasPropertyData (const char* name)
  {
    return m_has_prop.Find(name);
  }
private:
  // effectively load property data
  ResPosElementPropertyData * doLoadPropertyData(const char *name);
  void doUnloadPropertyData(const char *name);
  ResPosModel *GetModel() const
  {
    return pResPosModel;
  }
private:
  char *sName;
  ResPosModel *pResPosModel;
  ResPosElementPropertyDataArray vPropertiesValues;
  DsHash<PSUtil::StringKey, int> m_refcount;
  DsHash<DsStringKey, bool> m_has_prop;
};

#endif

