//* region.h
// A viewable reservoir region.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef RES_POS_REGION_H
#define RES_POS_REGION_H

#include "posmodel.h"
#include "common/util.h"
#include <ds/hash.h>
#include <gpos/defines.h>

class ResPosModel;
class ResPosElementPropertyData;
typedef PSArray<ResPosElementPropertyData*> ResPosElementPropertyDataArray;

//* 'ResPosRegion' Class
// Represents a region suitable for viewing.
class RES_API ResPosRegion
{
public:
  ResPosRegion(const char *name, ResPosModel *model);
  virtual ~ResPosRegion();
  void Release();
  void SetHasProperty (const char* name)
  {
    m_has_prop.Set(name, true);
  }
    //* Name query
    // Returns the name of the region.
  const char * GetName() const
  {
    return sName;
  }
  /**
   * Informs which time steps are recorded for region property 'name'.
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
   * Informs if this region has region property 'name' recorded for at least one
   * time step.
   */
  bool HasPropertyData (const char* name)
  {
    return m_has_prop.Find(name);
  }
private:
  ResPosModel *GetModel() const
  {
    return m_model;
  }
  ResPosElementPropertyData * loadPropertyData(const char *name);
  void unloadPropertyData(const char *name);
private:
  ResPosModel *m_model;
  ResPosElementPropertyDataArray vPropertiesValues;
  DsHash<PSUtil::StringKey, int> m_refcount;
  DsHash<DsStringKey, bool> m_has_prop;
  char *sName;
};

#endif
