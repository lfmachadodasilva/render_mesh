//* model.h
// A reservoir model in the GRD format.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef pposp_model_h
#define pposp_model_h

#include <gpos/defines.h>
#include <gpos/io/open.h>
#include "elemproporig.h"
#include "loadernew.h"
#include "geometry.h"
#include "model.h"
#include "step.h"
#include <gpos/common/ds/array.h>
#include <assert.h>
#include <stdio.h>
#include <ds/hash.h>
#include <ds/array.h>

class ResPosUnit;
class ResPosTimeStep;
class ResPosIniMapProperty;
class ResPosRecMapProperty;
class ResPosMapProperty;
class ResPosWell;
class ResPosGroup;
class ResPosField;
class ResPosRegion;
class ResPosGeometry;
class ResPosLoader;
class ResPosModel;

struct ResPosLoadError
{
  const char* errormsg;
  const char* errordetails;
  ResPosLoadError (const char* errormsg, const char* errordetails = NULL)
  {
    this->errormsg = errormsg;
    this->errordetails = errordetails;
  }
};

//* 'ResPosUnitArray' Type
// Represents an array of units.
typedef PSArray<ResPosUnit*> ResPosUnitArray;

//* 'ResPosTimeStepArray' Type
// Represents an array of time steps.
typedef PSArray<ResPosTimeStep*> ResPosTimeStepArray;

//* 'ResPosIniPropertyArray' Type
// Represents an array of initial properties.
typedef PSArray<ResPosIniMapProperty*> ResPosIniPropertyArray;

//* 'ResPosRecPropertyArray' Type
// Represents an array of recurrent properties.
typedef PSArray<ResPosRecMapProperty*> ResPosRecPropertyArray;

//* 'ResPosWellArray' Type
// Represents an array of wells.
typedef PSArray<ResPosWell*> ResPosWellArray;

//* 'ResPosWellPropertyArray' Type
// Represents an array of well properties.
typedef PSArray<ResPosElementPropertyOriginal*> ResPosWellPropertyArray;

//* 'ResPosCompletionPropertyArray'
// Represents an array of completion properties.
typedef PSArray<ResPosElementPropertyOriginal*> ResPosCompletionPropertyArray;

//* 'ResPosGroupArray' Type
// Represents an array of groups.
typedef PSArray<ResPosGroup*> ResPosGroupArray;

//* 'ResPosGroupPropertyArray' Type
// Represents an array of group properties.
typedef PSArray<ResPosElementPropertyOriginal*> ResPosGroupPropertyArray;

//* 'ResPosRegionArray' Type
// Represents an array of regions.
typedef PSArray<ResPosRegion*> ResPosRegionArray;

//* 'ResPosRegionPropertyArray' Type
// Represents an array of region properties.
typedef PSArray<ResPosElementPropertyOriginal*> ResPosRegionPropertyArray;

//* 'ResPosFieldPropertyArray' Type
// Represents an array of field properties.
typedef PSArray<ResPosElementPropertyOriginal*> ResPosFieldPropertyArray;

//* 'ResPosEUnitId' enumeration
// Enumerates the valid unit types.
enum ResPosEUnitId {
  GRD_MODSI=0,
  GRD_FIELD,
  GRD_SI,
  GRD_RESERVED,
  GRD_MAX_UNIT
};

//* 'ResPosArchitectureId' enumeration
// Enumerates the valid computer architecture types where the files were saved.
enum ResPosEArchitectureId {
  GRD_INTEL=0,
  GRD_RISC
};

//* 'ResPosUnit' Class
// Represents a measure unit.
class RES_API ResPosUnit
{
  char* d_symbols[GRD_MAX_UNIT];
  float d_factors[GRD_MAX_UNIT]; 

public:
  ResPosUnit (char* const symbols[GRD_MAX_UNIT], const float factors[GRD_MAX_UNIT]);
  ~ResPosUnit ();

    //* Symbol query
    // Returns the unit symbol.
  const char* Symbol (ResPosEUnitId id)
  {
    if (d_symbols)
      return d_symbols[(int)id];
    return "";
  }
  
    //* Factor query
    // Returns the unit factor.
  float Factor (ResPosEUnitId id)
  {
    return d_factors[(int)id];
  }
};

//* 'ResPosSimulation' Class
// Stores general information regarding the simulation.
struct RES_API ResPosSimulation {
  char* title;   
  char* inidate;   // initial date
  ResPosEUnitId unit;

  ResPosSimulation ();
  ~ResPosSimulation ();

  const char *GetDistanceUnit ()
  {
    switch(unit)
    {
      case GRD_MODSI:
      case GRD_SI:
        return "m";
      case GRD_FIELD:
        return "ft";
      default:
        return NULL;
    }
  }
};

//* 'ResPosTimeStep' Class
// Represents a simulation time step, suitable for viewing.
class RES_API ResPosTimeStep : public ResStep
{
  double    d_ndays;             // number of days elapsed since initial time
  int       d_day;               
  int       d_month;             
  int       d_year;              

public:
  ResPosTimeStep (double ndays, int day, int month, int year)
  : d_ndays(ndays)
  , d_day(day)
  , d_month(month)
  , d_year(year)
  {
  }
  virtual ~ResPosTimeStep ()
  {
  }
  double GetNumberOfDays() const
  {
    return d_ndays;
  }
  int GetDay() const
  {
    return d_day;
  }
  int GetMonth() const
  {
    return d_month;
  }
  int GetYear() const
  {
    return d_year;
  }
};

//* 'ResPosModel' Class
// Represents a reservoir model in the GRD format, suitable for viewing.
class RES_API ResPosModel : public ResModel
{
protected:
  char*               d_name;      // model name
  ResPosEArchitectureId  d_arch;      // on which architecture the data files were saved.

  ResPosSimulation       d_simulation;         // simulation data.
  ResPosGeometry*        d_geom;               // grid geometry.
  ResPosUnitArray        d_units;              // array of units.
  ResPosTimeStepArray    d_timesteps;          // array of time steps.
  ResPosTimeStepArray    d_element_timesteps;  // array of element time steps.
  ResPosIniPropertyArray d_iprops;             // array of initial properties.
  ResPosRecPropertyArray d_rprops;             // array of recurrent properties.
  ResPosWellArray        d_wells;              // array of wells.
  ResPosWellPropertyArray d_well_props;        // array of well properties.
  ResPosCompletionPropertyArray d_comp_props;  // array of completion properties.
  ResPosGroupArray       d_groups;             // array of groups.
  ResPosGroupPropertyArray d_group_props;      // array of group properties.
  ResPosRegionArray      d_regions;            // array of regions.
  ResPosRegionPropertyArray d_region_props;    // array of region properties.
  ResPosField            *d_field;             // the reservoir field.
  ResPosFieldPropertyArray d_field_props;      // array of field properties.

  bool d_celldata;                          // cell data presence flag
  bool d_welldata;                          // well data presence flag


  AlgVector d_wellr;  // estimated well radius (the same for all wells)

public:
  ResPosModel (int loader_index, const char *name=NULL);
  virtual ~ResPosModel ();
  void SetMapResultLoader (ResPosMapResultLoader* l)
  {
    // assumes it will only be set once
    m_map_result_loader = l;
    l->IncRef();
  }
  void SetWellResultLoader (ResPosWellResultLoader* l)
  {
    // assumes it will only be set once
    m_well_result_loader = l;
    l->IncRef();
  }
  /**
   * Loads the model geometry from the supplied loader.
   *
   * 'geom_file_suffix', if different than NULL, specifies a suffix for the .geom file.
   * Used when a loader returns multiple models.
   *
   * Returns true if successful and false otherwise.
   */
  bool LoadGeometry (ResPosGeometryLoader* geomloader,
                     const char* filename,
                     const char* geom_file_suffix,
                     ResOpenOptions* options) throw(ResPosLoadError);
  /**
   * Check completions: remove completions at inactive cells when
   * inactive cells geometry is not correct.
   */
  bool CheckCompletions (ResOpenOptions* options);
  bool LoadMapResults (ResOpenOptions* options);
  bool LoadWellResults (ResOpenOptions* options);
  void SetArchitecture (ResPosEArchitectureId arch)
  {
    d_arch = arch;
  }
    //* Architecture query
    // Returns the architecture on which the data files were saved.
  int Architecture () const
  {
    return d_arch;
  }

    //* Geometry query
    // Returns the model geometry.
  ResPosGeometry* Geometry ()
  {
    return d_geom;
  }

    //* Amount of units query
    // Returns the number of units.
  int NumberOfUnits () const
  {
    return d_units.size();
  }

    //* Unit query
    // Returns the ith unit
  ResPosUnit* Unit (int i)
  {
    if (i<0 || i>=d_units.size())
      return NULL;
    
    //assert(i>=0 && i<d_units.size());
    return d_units[i];
  }

    //* Amount of time steps query
    // Returns the number of time steps.
  int NumberOfTimeSteps () const
  {
    return d_timesteps.size();
  }

    //* Amount of element time steps query
    // Returns the number of element time steps.
  int NumberOfElementTimeSteps() const
  {
    return d_element_timesteps.size();
  }

    //* Time step query
    // Returns the ith time step.
  ResPosTimeStep* TimeStep (int i)
  {
    assert(i>=0 && i<d_timesteps.size());
    if (i<0 || i>=d_timesteps.size())
      return 0;
    return d_timesteps[i];
  }

    //* Element time step query
    // Returns the ith element time step.
  ResPosTimeStep* ElementTimeStep(int i)
  {
    assert(i>=0 && i<d_element_timesteps.size());
    if (i<0 || i>=d_element_timesteps.size())
      return 0;
    return d_element_timesteps[i];
  }

    //* Amount of initial properties query
    // Returns the number of initial properties
  int NumberOfIniProperties () const
  {
    return d_iprops.size();
  }

    //* Amount of recurrent properties query
    // Returns the amount of recurrent properties.
  int NumberOfRecProperties () const
  {
    return d_rprops.size();
  }

    // Returns the estimated well radius
  void GetWellRadius(float *i, float *j, float *k) const
  {
    *i = (float)d_wellr.x; *j = (float)d_wellr.x; *k = (float)d_wellr.x;
  }

    //* Property query
    // Returns the ith property (index 0 refers to the first initial property, then the recurrent
    // properties are considered)
    // Returns NULL if an invalid index is given.
  ResPosMapProperty* Property (int i);
    // Returns the property given it's name.
    // Returns NULL if an invalid name is given.
  ResPosMapProperty* Property (const char* name);

    //* Well property query
    // Returns the ith well property.
  ResPosElementPropertyOriginal* WellProperty(int i)
  {
    return d_well_props[i];
  }
    // Returns the well property given it's name.
  ResPosElementPropertyOriginal* WellProperty(const char *name);

    //* Amount of well properties query
    // Returns the amount of well properties.
  int NumberOfWellProperties()
  {
    return d_well_props.size();
  }

    //* Completion property query
    // Returns the ith completion property.
  ResPosElementPropertyOriginal* CompletionProperty(int i)
  {
    return d_comp_props[i];
  }
    // Returns the completion property given it's name.
  ResPosElementPropertyOriginal* CompletionProperty(const char *name);

    //* Amount of completion properties query
    // Returns the number of completion properties.
  int NumberOfCompletionProperties()
  {
    return d_comp_props.size();
  }

    //* Group property query
    // Returns the ith group property.
  ResPosElementPropertyOriginal* GroupProperty(int i)
  {
    return d_group_props[i];
  }
    // Returns the group property given it's name.
  ResPosElementPropertyOriginal* GroupProperty(const char *name);

    //* Amount of group properties query
    // Returns the number of group properties.
  int NumberOfGroupProperties()
  {
    return d_group_props.size();
  }

    //* Region property query
    // Returns the ith region property.
  ResPosElementPropertyOriginal* RegionProperty(int i)
  {
    return d_region_props[i];
  }
    // Returns the region property given it's name.
  ResPosElementPropertyOriginal* RegionProperty(const char *name);

    //* Amount of region properties query
    // Returns the number of region properties.
  int NumberOfRegionProperties()
  {
    return d_region_props.size();
  }

    //* Group property query
    // Returns the ith group property.
  ResPosElementPropertyOriginal* FieldProperty(int i)
  {
    return d_field_props[i];
  }

    //* Field property query
    // Returns the field property given it's name.
  ResPosElementPropertyOriginal* FieldProperty(const char *name);

    //* Amount of field properties query
    // Returns the number of field properties.
  int NumberOfFieldProperties()
  {
    return d_field_props.size();
  }
 
    // Returns the ith well.
  ResPosWell * WellAt(int i)
  {
    assert( (i >= 0) && (i < d_wells.size()) );
    return d_wells[i];
  }
    // Returns the well given it's name.
  ResPosWell * Well(const char *name);

    //* Amount of wells query
    // Returns the number of wells.
  int NumberOfWells()
  {
    return d_wells.size();
  }

    // Returns the ith group.
  ResPosGroup * GroupAt(int i)
  {
    assert( (i >= 0) && (i < d_groups.size()) );
    return d_groups[i];
  }
    // Returns the group given it's name.
  ResPosGroup * Group(char *name);

    //* Amount of groups query
    // Returns the number of groups.
  int NumberOfGroups()
  {
    return d_groups.size();
  }

    // Returns the ith region.
  ResPosRegion * RegionAt(int i)
  {
    assert( (i >= 0) && (i < d_regions.size()) );
    return d_regions[i];
  }
    // Returns the region given it's name.
  ResPosRegion * Region(char *name);

    //* Amount of regions query
    // Returns the number of regions.
  int NumberOfRegions()
  {
    return d_regions.size();
  }

    //* Field query
    // Returns the reservoir field.
  ResPosField * Field()
  {
    return d_field;
  }

  //* *ResModel*

  bool HasCellData() { return d_celldata; }

  bool HasWellData() { return d_welldata; }

  int GetNumberOfSectors() { return 0; }
  int GetNumberOfAreas(int s) { return 0; }
  const char * GetSectorName(int s) { return 0; }
  void GetAreaBoundaries(int s, int a, int *i1, int *j1, int *k1, int *i2, int *j2, int *k2) { };

  ResPosEUnitId GetSimulationUnit()
  {
    return d_simulation.unit;
  }
  const char * GetSimIniDate()
  {
    return d_inidate;
  }

  const char * GetName()
  {
    return d_name;
  }

  const char * GetSimTitle()
  {
    return d_title;
  }

  void SetSimIniDate(const char *date)
  {
    PSUtil::Free(d_inidate);
    d_inidate = PSUtil::StrDup(date);
  }

  void SetSimIniDate (int iday, int imonth, int iyear)
  {
    PSUtil::Free(d_inidate);
    d_inidate = PSUtil::StrDate(iday,imonth,iyear);
  }

  void SetSimTitle(const char *title)
  {
    PSUtil::Free(d_title);
    d_title = PSUtil::StrDup(title);
  }
  const char * GetSimDistanceUnit()
  {
    return GetGeometry()->GetCoordinatesUnit();
  }

  ResGeometry* GetGeometry(int i = 0) const;

  int GetNumberOfIniProperties()
  {
    return NumberOfIniProperties();
  }
 
  int GetNumberOfRecProperties()
  {
    return NumberOfRecProperties();
  }

  ResWell * GetWellAt(int i)
  {
    return (ResWell*)WellAt(i);
  }

  ResWell * GetWell(const char *name)
  {
    return (ResWell*)Well(name);
  }

  int GetNumberOfWells()
  {
    return NumberOfWells();
  }


  ResPosGroup * GetGroupAt(int i)
  {
    return GroupAt(i);
  }

  ResPosGroup * GetGroup(const char *name)
  {
    return Group((char*)name);
  }

  int GetNumberOfGroups()
  {
    return NumberOfGroups();
  }

  ResPosRegion * GetRegionAt(int i)
  {
    return (ResPosRegion*)RegionAt(i);
  }

  ResPosRegion * GetRegion(const char *name)
  {
    return (ResPosRegion*)Region((char*)name);
  }

  int GetNumberOfRegions()
  {
    return NumberOfRegions();
  }

  ResPosField * GetField()
  {
    return (ResPosField*)Field();
  }

  ResStep * GetStep(int i)
  {
    return (ResStep*)TimeStep(i);
  }

  ResStep * GetElementStep(int i)
  {
    return (ResStep*)ElementTimeStep(i);
  }

  int GetNumberOfSteps()
  {
    return NumberOfTimeSteps();
  }
  int GetNumberOfElementSteps()
  {
    return NumberOfElementTimeSteps();
  }
  int IsIntel(void)
  {
    return d_arch == GRD_INTEL;
  }
  int IsRisc(void)
  {
    return d_arch == GRD_RISC;
  }

  ResProperty* RemoveProperty(const char *symbol);
  /**
   * Creates the necessary data structures for an initial map property.
   *
   * 'symbol' is the property symbol.\n
   * 'desc' is the property description.\n
   * 'dtype' is the property value type (RES_TYPE_INTEGER or RES_TYPE_REAL).\n
   * 'unit' is the property unit identifier.\n
   * to store load data (like file offsets).
   * Acessible via ResPosMapProperty::GetHandle().\n
   * 'iscomplete' specifies if the property is defined for all cells (true)
   * or if it is defined only for the active cells (false).
   */
  void CreateIniMapProperty(
    const char* symbol,
    const char* desc,
    ResValueType dtype,
    const char* unit,
    bool iscomplete);
  /**
   * Creates the necessary data structures for a recurrent map property.
   *
   * 'symbol' is the property symbol.\n
   * 'desc' is the property description.\n
   * 'dtype' is the property value type (RES_TYPE_INTEGER or RES_TYPE_REAL).\n
   * 'unit' is the property unit identifier.\n
   * to store load data (like file offsets).
   * Acessible via ResPosMapProperty::GetHandle().
   */
  void CreateRecMapProperty(
    const char* symbol,
    const char* desc,
    ResValueType dtype,
    const char* unit);
  /**
   * Creates a map time step.
   */
  void CreateMapTimeStep (double ndays, int day, int month, int year);
  /**
   * Creates an element time step.
   */
  void CreateElementTimeStep (double ndays, int day, int month, int year);
  void CreateUnit(char * const *symbols, const float *factors);
  /**
   * Creates a well.
   * Returns the new well id.
   */
  int CreateWell (const char* name);
  /**
   * Specifies the well group for time step 'ts'.
   */
  void SetWellGroup (int well, int ts, const char* name);
  /**
   * Specifies the well lgr name.
   */
  void SetWellLGRName (int well, const char* name);
  /**
   * Adds a completion to a well.
   * Returns the completion id.
   */
  int AddCompletion (ResPosWell *well,
                     int depth,
                     const int* i,
                     const int* j,
                     const int* k);
  /**
   * Creates a well group.
   */
  void CreateGroup(const char *name);
  /**
   * Creates a well region.
   */
  void CreateRegion(const char *name);
  /**
   * Creates the reservoir field structure.
   */
  void CreateField();
  void CreateWellProperty (const char* name,
                           const char* desc,
                           ResValueType vtype,
                           const char* unit);
  void CreateCompProperty (const char* name,
                           const char* desc,
                           ResValueType vtype,
                           const char* unit);
  void CreateGroupProperty (const char* name,
                            const char* desc,
                            ResValueType vtype,
                            const char* unit);
  void CreateFieldProperty (const char* name,
                            const char* desc,
                            ResValueType vtype,
                            const char* unit);
  void CreateRegionProperty (const char* name,
                            const char* desc,
                            ResValueType vtype,
                            const char* unit);
  ResPosMapResultLoader* GetMapResultLoader () const
  {
    return m_map_result_loader;
  }
  ResPosWellResultLoader* GetWellResultLoader () const
  {
    return m_well_result_loader;
  }
  ResPosModelNew* GetPosModelNew ()
  {
    return (ResPosModelNew*)GetModelNew();
  }
  /**
   * Obtains the index of this model in the list of its data loader.
   */
  int GetLoaderIndex () const
  {
    return m_loader_index;;
  }
private:
  bool CheckMapFile ();
  bool CheckWellFile ();
    //* Initial property query
    // Returns the ith initial property
  ResPosIniMapProperty* IniProperty (int i)
  {
    assert(i>=0 && i<NumberOfIniProperties());
    return d_iprops[i];
  }
    // Returns the initial property given it's name.
  ResPosIniMapProperty* IniProperty (const char* name);

    //* Recurrent property query
    // Returns the ith recurrent property
  ResPosRecMapProperty* RecProperty (int i)
  {
    assert(i>=0 && i<NumberOfRecProperties());
    return d_rprops[i];
  }
  ResPosRecMapProperty* RecProperty (const char* name);
  void SetRadial (float radial_rw);
  void SetGeometryData (int ni,
                        int nj,
                        int nk,
                        const int* active_cells,
                        const int* packed2complete,
                        bool is_corner_points,
                        bool are_inactive_z_correct,
                        bool zdirdown,
                        bool kdirdown,
                        const char* coords_unit);
  bool CreateGeometry (const char* geometryfile,
                       ResPosGeometryLoader* geomloader,
                       ResGeometry::LoadProgressFunc progressfunc);
  void CreateElementProperty (PSArray<ResPosElementPropertyOriginal*>* array,
                              const char* name,
                              const char* desc,
                              ResValueType vtype,
                              const char* unit);
  static void UpdateGeometryLoadProgress (float progress, void* data);
protected:
  ResProperty * GetIniProperty(int i) { return (ResProperty*)IniProperty(i); }
  ResProperty * GetIniProperty(const char *name) { return (ResProperty*)IniProperty(name); }
  ResProperty * GetRecProperty(int i) { return (ResProperty*)RecProperty(i); }
  ResProperty * GetRecProperty(const char *name) { return (ResProperty*)RecProperty(name); }
  
  ResPosElementProperty * GetWellProp(int i)  { return WellProperty(i);  }
  ResPosElementProperty * GetWellProp(const char *name)  { return WellProperty(name);  }
  int GetNumberOfWellProps()  { return NumberOfWellProperties(); }
  ResPosElementProperty * GetCompProp(int i)  { return CompletionProperty(i);  }
  ResPosElementProperty * GetCompProp(const char *name)  { return CompletionProperty(name);  }
  int GetNumberOfCompProps()  {  return NumberOfCompletionProperties();  }
  ResPosElementProperty * GetGroupProp(int i) {  return GroupProperty(i);  }
  ResPosElementProperty * GetGroupProp(const char *name) {  return GroupProperty(name);  }
  int GetNumberOfGroupProps()  { return NumberOfGroupProperties(); }
  ResPosElementProperty * GetRegionProp(int i) {  return RegionProperty(i);  }
  ResPosElementProperty * GetRegionProp(const char *name) {  return RegionProperty(name);  }
  int GetNumberOfRegionProps()  { return NumberOfRegionProperties(); }
  ResPosElementProperty * GetFieldProp(int i) {  return FieldProperty(i);  }
  ResPosElementProperty * GetFieldProp(const char *name) {  return FieldProperty(name);  }
  int GetNumberOfFieldProps()  { return NumberOfFieldProperties(); }
private:
  void AfterGeometryComputed (ResOpenOptions* options);
  void CreateWellTimeStepsFromWellResultLoader ();
  void CreateWellsFromWellResultLoader ();
  void CreateGroupsFromWellResultLoader ();
  void CreateRegionsFromWellResultLoader ();
  void CreateWellPropertiesFromWellResultLoader ();
  void CreateCompletionPropertiesFromWellResultLoader ();
  void CreateGroupPropertiesFromWellResultLoader ();
  void CreateRegionPropertiesFromWellResultLoader ();
  void CreateFieldPropertiesFromWellResultLoader ();
  void AfterWellOrGeometryLoad (ResOpenOptions* options);
  void AssignTimeStepNumbers ();
private:
  char *d_inidate;
  char *d_title;
private:
  ResPosMapResultLoader* m_map_result_loader;
  ResPosWellResultLoader* m_well_result_loader;
  ResOpenOptions* m_options;
  int m_loader_index; // index of this model in the loaders list
private:
  friend class ResPosModelNew;
  friend class ResPosModelOpener;
};

/**
 * ResPosModelOpener abstract class.
 *
 * Reservoir pos model readers must derive from this class and register an instance
 * of it using gpos_register_res_opener(instance).
 *
 * The "Open" method must be implemented.
 * It must check if the model files match the expected file formats and, if so,
 * must return the pointer to the loaded ResModel.
 *
 * 'GetFilenames' must call, if successful, return AddGeometryFile(rootname, numfiles, filenames).
 */

class RES_API ResPosModelOpener : public ResModelOpener
{
public:
  virtual ~ResPosModelOpener ()
  {
  }
  bool Open (const char *modelname,
             int numfiles,
             const char **filenames,
             ResOpenOptions* options,
             int* o_model_count,
             ResModel*** o_models);
protected:
  virtual ResPosGeometryLoader* BuildGeometryLoader (ResOpenOptions* options) = 0;
  virtual ResPosMapResultLoader* BuildMapResultLoader (ResOpenOptions* options) = 0;
  virtual ResPosWellResultLoader* BuildWellResultLoader (ResOpenOptions* options) = 0;
  /**
   * Appends the geometry file, if existing, to the list of model filenames.
   * 'rootname' will be freed by this method, so callers don't have to.
   */
  bool AddGeometryFile (char* rootname,
                        int *numfiles,
                        char ***filenames);
private:
};

class RES_API ResPosGeometry : public ResGeometry
{
public:
  ResPosGeometry (ResPosModel* model, int nx, int ny, int nz, int ncells, int nact);
  virtual ~ResPosGeometry ();
  ResPosModel *GetPosModel() const
  {
    return (ResPosModel*)GetResModel();
  }
  ResPosModelNew *GetPosModelNew() const
  {
    return GetPosModel()->GetPosModelNew();
  }
  void SetExcludeElementsOutsideBoundingBox (const AlgVector& bbmin, const AlgVector& bbmax);
  void AddGridCellRefinement (int depth,
                              const int* i,
                              const int* j,
                              const int* k,
                              const int* refinement_indices,
                              int nri,
                              int nrj,
                              int nrk)
  {
    m_refinements.Append(new CellRefinement(depth,
                                            i,
                                            j,
                                            k,
                                            refinement_indices,
                                            nri,
                                            nrj,
                                            nrk));
  }
  void AddGridRangeRefinement (int rootistart,
                               int rootiend,
                               int rootjstart,
                               int rootjend,
                               int rootkstart,
                               int rootkend,
                               int nri,
                               int nrj,
                               int nrk)
  {
    m_refinements.Append(new RangeRefinement(rootistart,
                                             rootiend,
                                             rootjstart,
                                             rootjend,
                                             rootkstart,
                                             rootkend,
                                             nri,
                                             nrj,
                                             nrk));
  }
  void RefineBlock (int starti,
                    int endi,
                    int ri,
                    int startj,
                    int endj,
                    int rj,
                    int startk,
                    int endk,
                    int rk);
  void CorrectModelAxes (ResPosGeometryLoader* loader);
  // virtual methods
  virtual int ComputeCells (ResPosGeometryLoader* loader) = 0;
  bool InsertElem (TopMultiModel* model, int i, int j, int k, const float orig_vertex_list[24], float tolerance);
  bool InsertVertex (TopMultiModel* model, int index, float x, float y, float z);
  bool InsertCell (TopMultiModel* model, int i, int j, int k, const int vertex_indices[8]);
protected:
  void AfterMainGridCellsInserted (ResPosGeometryLoader* loader);
  void SetIds (ResPosGeometryLoader* loader);
private:
  struct WaitingCell
  {
    int index;
    int i, j, k;
    float vertex_list[24];
    float tolerance;
    int refcount;
    bool inserted;
  };
  struct ExcludeOutsideBBData
  {
    AlgVector bbmin;
    AlgVector bbmax;
    DsHash<int,DsArray<WaitingCell*>*> waiting_list;
    DsHash<int,WaitingCell*> waiting;
    DsArray<bool> visited;
    DsArray<bool> intersects;
  };
  struct GridHierarchyNode
  {
    int parent_index;
    int nri, nrj, nrk;
    int refinement_index;
    DsArray<GridHierarchyNode*> children;
    GridHierarchyNode* parent;

    ~GridHierarchyNode ()
    {
      int n = children.Size();
      for (int i=0; i<n; ++i)
        delete children[i];
    }
    void InsertChild (GridHierarchyNode* node)
    {
      children.Append(node);
      node->parent = this;
    }
  };
  typedef void (*ProcessWaitingCellFunc) (WaitingCell* cell, void* data);
private:
  void RefineBlock ();
  void RefineCells (ResPosGeometryLoader* loader);
  void FindOutRefinementOrder (DsArray<int>* refinement_order);
  bool InsertElemOutsideBB (TopMultiModel* model, int i, int j, int k, const float orig_vertex_list[24], float tolerance);
  void ElemReadyForInsertion (int i,
                              int j,
                              int k,
                              const float orig_vertex_list[24],
                              float tolerance,
                              bool insert_on_original);
  void VisitedElement (int index, ProcessWaitingCellFunc func=NULL, void* funcdata=NULL);
  void ComputeNumberOfRefinementLevels ();
  void FinishedBuildingLevel (ResPosGeometryLoader* loader,
                              bool smoothmodel,
                              int level);
  /**
   * Obtains the number of refinements.
   */
  int GetNumberOfRefinements () const
  {
    return m_refinements.Size();
  }
  /**
   * Obtains the type of refinement with index 'index'.
   *
   * Requisites:
   * - 0 <= index < GetNumberOfRefinements()
   */
  ResRefinementType GetRefinementType (int index) const
  {
    return m_refinements.Get(index)->type;
  }
  /**
   * Obtains the refinement of index 'index'.
   *
   * Must be returned in the following pointers:
   * *rootistart, *rootiend: range of cells to be refined in the 'i' direction.
   * *rootjstart, *rootjend: range of cells to be refined in the 'j' direction.
   * *rootkstart, *rootkend: range of cells to be refined in the 'k' direction.
   * *nri, *nrj, *nrk:       number of parts in the 'i', 'j' and 'k' directions
   *                         to split each cell.
   *
   * Requisites:
   * - 0 <= index < GetNumberOfRefinements()
   * - GetRefinementType(index) == RANGE
   */
  void GetRangeRefinement (int index,
                           int* rootistart,
                           int* rootiend,
                           int* rootjstart,
                           int* rootjend,
                           int* rootkstart,
                           int* rootkend,
                           int* nri,
                           int* nrj,
                           int* nrk) const
  {
    assert(GetRefinementType(index) == RES_REFINEMENT_RANGE);
    RangeRefinement* r = (RangeRefinement*)m_refinements.Get(index);
    *rootistart = r->rootistart;
    *rootiend   = r->rootiend;
    *rootjstart = r->rootjstart;
    *rootjend   = r->rootjend;
    *rootkstart = r->rootkstart;
    *rootkend   = r->rootkend;
    *nri        = r->nri;
    *nrj        = r->nrj;
    *nrk        = r->nrk;
  }
  /**
   * Given a refinement of index 'index' (type CELL), obtains the refinement
   * depth of a cell: 0 if the cell belongs to the main grid, 1 if on the first
   * refinement level and so on.
   *
   * Requisites:
   * - 0 <= index < GetNumberOfRefinements()
   * - GetRefinementType(index) == CELL
   */
  int GetCellRefinementDepth (int index) const
  {
    assert(GetRefinementType(index) == RES_REFINEMENT_CELL);
    CellRefinement* r = (CellRefinement*)m_refinements.Get(index);
    return r->depth;
  }
  /**
   * Given a refinement of index 'index' (type CELL), obtains the coordinates
   * of the cell to be refined: i[l], j[l] and k[l] are the i, j, k coordinates
   * of the cell on the refinement level 'l-1', where l ranges from 0 (main
   * grid) until GetCellRefinementDepth()-1.
   * Also obtains the indices of refinements: refinement_indices[l] is the index
   * of the refinement containing the cell coordinates i[l], j[l] and k[l].
   *
   * Requisites:
   * - 0 <= index < GetNumberOfRefinements()
   * - GetRefinementType(index) == CELL
   */
  void GetCellRefinementCoords (int index,
                                const int** i,
                                const int** j,
                                const int** k,
                                const int** refinement_indices)
  {
    assert(GetRefinementType(index) == RES_REFINEMENT_CELL);
    CellRefinement* r = (CellRefinement*)m_refinements.Get(index);
    *i = r->i;
    *j = r->j;
    *k = r->k;
    *refinement_indices = r->refinement_indices;
  }
  /**
   * Given a refinement of index 'index' (type CELL), obtains the number of
   * parts to split the refined cell in the 'i', 'j' and 'k' directions.
   *
   * Requisites:
   * - 0 <= index < GetNumberOfRefinements()
   * - GetRefinementType(index) == CELL
   */
  void GetCellRefinementNumParts (int index,
                                  int* nri,
                                  int* nrj,
                                  int* nrk)
  {
    assert(GetRefinementType(index) == RES_REFINEMENT_CELL);
    CellRefinement* r = (CellRefinement*)m_refinements.Get(index);
    *nri = r->nri;
    *nrj = r->nrj;
    *nrk = r->nrk;
  }
  static void InsertWaitingCell (WaitingCell* waitingcell, void* data);
  static int SortHierarchyChildren (const void* a, const void* b);
private:
  struct Refinement {
    ResRefinementType type;
    int nri;
    int nrj;
    int nrk;
    Refinement (ResRefinementType type, int nri, int nrj, int nrk)
  : type(type)
  , nri(nri)
  , nrj(nrj)
  , nrk(nrk)
  {
  }
  };
  struct RangeRefinement : public Refinement {
    int rootistart;
    int rootiend;
    int rootjstart;
    int rootjend;
    int rootkstart;
    int rootkend;
    RangeRefinement (int rootistart,
                     int rootiend,
                     int rootjstart,
                     int rootjend,
                     int rootkstart,
                     int rootkend,
                     int nri,
                     int nrj,
                     int nrk)
    : Refinement(RES_REFINEMENT_RANGE, nri, nrj, nrk)
    , rootistart(rootistart)
    , rootiend(rootiend)
    , rootjstart(rootjstart)
    , rootjend(rootjend)
    , rootkstart(rootkstart)
    , rootkend(rootkend)
    {
    }
  };
  struct CellRefinement : public Refinement {
    int depth;
    int* i;
    int* j;
    int* k;
    int* refinement_indices;
    CellRefinement (int depth,
                    const int* i,
                    const int* j,
                    const int* k,
                    const int* refinement_indices,
                    int nri,
                    int nrj,
                    int nrk);
    ~CellRefinement ();
  };
  DsArray<Refinement*> m_refinements;
  ExcludeOutsideBBData* m_exclude_outside_of_bb_data;
  bool m_refine_block;
  int m_refine_block_starti;
  int m_refine_block_startj;
  int m_refine_block_startk;
  int m_refine_block_endi;
  int m_refine_block_endj;
  int m_refine_block_endk;
  int m_refine_block_ri;
  int m_refine_block_rj;
  int m_refine_block_rk;
  bool m_kdown;
};

#endif

