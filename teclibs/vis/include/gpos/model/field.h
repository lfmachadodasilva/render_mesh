//* field.h
// A viewable reservoir field.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef vis_field_h
#define vis_field_h

#include <ds/hash.h>
#include <gpos/defines.h>
#include "common/util.h"
#include "common/ds/array.h"

class ResPosModel;
class ResPosElementPropertyData;

//* 'ResPosElementPropertyDataArray' Type
// Represents an array of property data
typedef PSArray<ResPosElementPropertyData*> ResPosElementPropertyDataArray;

//* 'ResPosField' Class
// Represents a field suitable for viewing.
class RES_API ResPosField
{
  DsHash<PSUtil::StringKey, int> m_refcount;
public:
  ResPosField(ResPosModel *model) :
    d_model(model)
  {
  }
  virtual ~ResPosField();
  void Release();

  /**
   * Informs which time steps are recorded for field property 'name'.
   * Returns true if successful or false if failed fetching this data.
   */
  bool PropHasRecordedSteps (const char* name, bool* has_recorded_steps);

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
private:
  // effectively load property data
  ResPosElementPropertyData * doLoadPropertyData(const char *name);
  void doUnloadPropertyData(const char *name);
  ResPosModel* GetModel() const
  {
    return d_model;
  }
private:
  ResPosElementPropertyDataArray d_propv;
  ResPosModel *d_model;
};

#endif

