//* model.h
// A viewable reservoir model.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef vis_model_h
#define vis_model_h

#include <gpos/defines.h>
#include <gpos/common/ds/array.h>
#include <gpos/common/util.h>
#include <alg/vector.h>
#include <gpos/model/property.h>

#include <ds/array.h>
#include <ds/queue.h>
#include <limits.h>
#include <float.h>
//#include <stdio.h>

class ResGeometry;
class ResProperty;
class ResPosElementProperty;
class ResPosElementPropertyData;
class ResWell;
class ResPosGroup;
class ResPosField;
class ResPosRegion;
class ResStep;
class ResModel;
class ResModelNew;

//* 'ResGrid' Class
//Represents a Grid.A grid has the geometry and properties
class RES_API ResGrid
{
public:
  /**
   * Breadth-first search iterator on refined grids.
   *
   * Utility class designed to simplify iterating on a breadth-first manner
   * on the hierarchy of refined grids.
   *
   * Typical usage:
   *
   * for (ResGrid::BFSIterator it = ResGrid::BeginBFS(rootgrid); it.Valid(); ++it)
   * {
   *   ResGrid* resgrid = it.Self();
   *   ...
   * }
   */
  class BFSIterator
  {
  public:
    BFSIterator (const BFSIterator& iterator);
    BFSIterator (ResGrid* rootgrid);
    bool Valid () const
    {
      return m_curr != NULL;
    }
    ResGrid* operator-> () const
    {
      return m_curr;
    }
    ResGrid* Self () const
    {
      return m_curr;
    }
    BFSIterator& operator++ ();
  private:
    DsQueue<ResGrid*> m_bfs_queue;
    ResGrid* m_curr;
  };
public:
  ResGrid (int nir,
           int njr,
           int nkr,
           int starti,
           int endi,
           int startj,
           int endj,
           int startk,
           int endk)
  : m_children()
  , m_parent(NULL)
  {
    d_size[0] = nir;
    d_size[1] = njr;
    d_size[2] = nkr;
    d_start[0] = starti;
    d_start[1] = startj;
    d_start[2] = startk;
    d_end[0] = endi;
    d_end[1] = endj;
    d_end[2] = endk;
  }   
	~ResGrid ()
  {
    int n = m_children.Size();
    for (int i=0; i<n; ++i)
      delete m_children[i];
  }
  int GetISubdivision() const { return d_size[0]; }
  int GetJSubdivision() const { return d_size[1]; }
  int GetKSubdivision() const { return d_size[2]; }
  int GetStartI() const { return d_start[0]; }
  int GetStartJ() const { return d_start[1]; }
  int GetStartK() const { return d_start[2]; }
  int GetEndI() const { return d_end[0]; }
  int GetEndJ() const { return d_end[1]; }
  int GetEndK() const { return d_end[2]; }
  void AddChild (ResGrid* model, int at=-1);
  /**
   * Removes a child grid from the children list.
   */
  bool RemoveChild (ResGrid* grid);
  int GetNumberOfChildren() const
  {
    return m_children.Size();
  }
  ResGrid* GetChild (int i) const
  {
    return m_children.Get(i);
  }
  /**
   * Obtains the entire hierarchy in an array structure, where grids->Get(index) equals
   * GetGridAllHierarchy(index).
   */
  void GetFlatGridHierarchy (DsArray<ResGrid*>* grids);
  /**
   * Obtains the child model of index 'index' between all models below this
   * model (including it).
   *
   * Be aware that this is an O(n) operation (where n is the number of grids in
   * the hierarchy).
   */
  ResGrid* GetGridAllHierarchy (int index);
  /**
   * Obtains the index of this model in the root model hierarchy
   * (see GetTotalNumberOfGrids/GetGridAllHierarchy).
   * Returns -1 in case this model is not found in the hierarchy.
   */
  int GetGridIndexAllHierarchy ();
  ResGrid* GetParent() const
  {
    return m_parent;
  }
  ResGrid* GetRootParent()
  {
    if (m_parent == NULL)
      return this;
    else
      return m_parent->GetRootParent();
  }
  int GetLevel () const
  {
    if (m_parent == NULL)
      return 0;
    return 1 + m_parent->GetLevel();
  }
  void GetParentCell (int i, int j, int k, int* pi, int* pj, int* pk) const
  {
    GetParentCell(0,i,pi);
    GetParentCell(1,j,pj);
    GetParentCell(2,k,pk);
  }
  void GetParentCell (int which, int index, int *pindex) const;
  static BFSIterator BeginBFS (ResGrid* rootgrid)
  {
    return BFSIterator(rootgrid);
  }
private:
  static ResGrid* GetGridAllHierarchyRec (ResGrid *mdl, int index, int &counter);
  static int GetGridIndexAllHierarchyRec (ResGrid *mdl, ResGrid *findmodel, int &counter);
  void GetFlatGridHierarchyRec (DsArray<ResGrid*>* grids);
private:
  DsArray<ResGrid*> m_children;
  ResGrid* m_parent;
  int d_size[3];  // Numero de divisoes por celula   ([0]=i [1]=j [2]=k)
  int d_start[3]; // Celula de inicio do refinamento ([0]=i [1]=j [2]=k)
  int d_end[3];   // Celula de fim do refinamento    ([0]=i [1]=j [2]=k)
};

//* 'ResModel' Class
// Represents a model suitable for viewing.
class RES_API ResModel
{
  PSArray<ResProperty*> m_xtramprops; // extra map properties
  PSArray<ResPosElementProperty*> m_xtrawprops; // extra well properties
  PSArray<ResPosElementProperty*> m_xtracprops; // extra completion properties
  PSArray<ResPosElementProperty*> m_xtragprops; // extra group properties
  PSArray<ResPosElementProperty*> m_xtrarprops; // extra region properties
  PSArray<ResPosElementProperty*> m_xtrafprops; // extra field properties
  PSArray<char*> m_xtraenames; // extra elements' names
  PSArray<char*> m_xtraedescs; // extra elements' descriptions
  PSArray<char*> m_xtraeunits; // extra elements' units
  PSArray<ResPosElementPropertyData*> m_xtraeprops; // extra elements' property data
  
  const char **m_mpnames; // the actual map property list (sorted)
  char **m_wpnames; // the actual well property list (sorted)
  char **m_cpnames; // the actual completion property list (sorted)
  char **m_gpnames; // the actual group property list (sorted)
  char **m_fpnames; // the actual field property list (sorted)
  char **m_rpnames; // the actual region property list (sorted)

  int m_refcount;
  float m_grid_rw;
  bool m_is_grid_radial;
protected:

  void updatepnames();
  void updatewpnames();
  void updatecpnames();
  void updategpnames();
  void updaterpnames();
  void updatefpnames();


  ResModel ();
  virtual ~ResModel ();
public:
    //* Reference counting routines

  void AddRef()
  {
    m_refcount++;
  }

  void Release();
  /**
   * Obtains the new api object for this model.
   */
  ResModelNew* GetModelNew () const
  {
    return m_mdlnew;
  }
    //* Cell data presence
    // Returns if this model has cell data
  virtual bool HasCellData() = 0;

    //* Well data presence
    // Returns if this model has well data
  virtual bool HasWellData() = 0;
  /**
   * Is the model grid radial?
   */
  virtual bool IsGridRadial () const
  {
    return m_is_grid_radial;
  }
  virtual float GetGridRW () const
  {
    return m_grid_rw;
  }
  void SetGridRW (float rw)
  {
    m_is_grid_radial = true;
    m_grid_rw = rw;
  }
    //* Cell sectors routines
  virtual int GetNumberOfSectors() = 0;
  virtual int GetNumberOfAreas(int s) = 0;
  virtual const char * GetSectorName(int s) = 0;
  virtual void GetAreaBoundaries(int s, int a, int *i1, int *j1, int *k1, int *i2, int *j2, int *k2) = 0;
  /**
   * Marks all cells of sectors 'sectors'.
   * 'numsectors' is the number of sectors given.
   * A special sector with value -1 requests cells that are in no sector.
   * Returns a boolean array 'indices', such that
   * indices[geom->Index(i,j,k)] = true for the requested sectors.
   * Note: memory is allocated with malloc/calloc.
   */
  bool* MarkCellsOfSectors(int numsectors, const int *sectors);

    //* Simulation initial date query
  virtual const char * GetSimIniDate() = 0;

    //* Name query
    // Returns the model name.
  virtual const char * GetName() = 0;
  
    //* Simulation title query
    // Returns the simulation title.
  virtual const char * GetSimTitle() = 0;

  /**
   * Returns the simulations distance unit.
   */
  virtual const char * GetSimDistanceUnit() = 0;

    //* Grid geometry query
    // Returns the given grid geometry.
  virtual ResGeometry * GetGeometry (int i = 0) const = 0;
  
  //* Cell activeness query
  // Returns if the given cell is active.
  bool IsActiveCell (int index) const;

    //* Amount of initial properties query
    // Returns the number of initial properties.
  virtual int GetNumberOfIniProperties() = 0;

    //* Amount of recurrent properties query
    // Returns the number of recurrent properties.
  virtual int GetNumberOfRecProperties() = 0;

    //* Amount of extra properties query
    // Returns the number of properties that were added after the model has been loaded.
  int GetNumberOfExtraProperties()
  {
    return m_xtramprops.size();
  }

    //* Amount of properties query
    // Returns the total number of map properties.
  int GetNumberOfProperties();

    //* Amount of well properties query
    // Returns the number of well properties.
  int GetNumberOfWellProperties();

  int GetNumberOfExtraWellProperties() { return m_xtrawprops.size(); }

    //* Amount of completion properties query
    // Returns the number of completion properties.
  int GetNumberOfCompletionProperties();

  int GetNumberOfExtraCompletionProperties() { return m_xtracprops.size(); }

    //* Amount of group properties query
    // Returns the number of group properties.
  int GetNumberOfGroupProperties();

  int GetNumberOfExtraGroupProperties() { return m_xtragprops.size(); }

    //* Amount of field properties query
    // Returns the number of field properties.
  int GetNumberOfFieldProperties();
  
  int GetNumberOfExtraFieldProperties() { return m_xtrafprops.size(); }

    //* Amount of region properties query
    // Returns the number of region properties.
  int GetNumberOfRegionProperties();

  int GetNumberOfExtraRegionProperties() { return m_xtrarprops.size(); }

    //* Amount of extra elements query
    // Returns the number of extra elements (1D data).
  int GetNumberOfExtraElements()
  {
    return m_xtraenames.size();
  }

    //* Amount of geometries query
    // Returns the number of geometries.
  virtual int GetNumberOfGeometries()
  {
    return 1;
  }

  float GetPropertyMinValue(char* name);
  float GetPropertyMaxValue(char* name);

    //* Model property query
    // Returns the model property given it's name.
    // Returns NULL if there is no such property.
  ResProperty * GetProperty(const char *name);
    // Returns the ith model property.
    // Returns NULL if there is no such property.
    // The order is initial, recurrent, then extra.
  ResProperty * GetProperty(int i);

    //* Map Property addition
    // Adds a map property to the model.
    // Returns non zero in case of success, zero otherwise.
  virtual int AddMapProperty(ResProperty *p)
  {
    m_xtramprops.insert(p);
    updatepnames();
    return 1;
  }
  virtual ResProperty* RemoveProperty(const char *symbol);

    //* Extra element addition
    // Adds an extra element to the model
  void AddExtraElement(const char *name, const char *desc, const char *unit, ResPosElementPropertyData *d);

    //* Well property query
    // Returns the well property given it's name.
    // Returns NULL if there is no such property.
  ResPosElementProperty * GetWellProperty(const char *name);
    // Returns the ith well property.
    // Returns NULL if there is no such property.
  ResPosElementProperty * GetWellProperty(int i);

  ResPosElementProperty * GetExtraWellProperty(int i)
  {
    if (i<0 || i>=GetNumberOfExtraWellProperties())
      return 0;
    return m_xtrawprops[i];
  }

    //* Well Property addition
    // Adds a well property to the model.
    // Returns non zero in case of success, zero otherwise.
  int AddWellProperty(ResPosElementProperty *p)
  {
    m_xtrawprops.insert(p);
    updatewpnames();
    return 1;
  }

    //* Completion property query
    // Returns the completion property given it's name.
    // Returns NULL if there is no such property.
  ResPosElementProperty * GetCompletionProperty(const char *name);
    // Returns the ith completion property.
    // Returns NULL if there is no such property.
  ResPosElementProperty * GetCompletionProperty(int i);

  ResPosElementProperty * GetExtraCompletionProperty(int i)
  {
    if (i<0 || i>=GetNumberOfExtraCompletionProperties())
      return 0;
    return m_xtracprops[i];
  }

    //* Completion Property addition
    // Adds a completion property to the model.
    // Returns non zero in case of success, zero otherwise.
  int AddCompletionProperty(ResPosElementProperty *p)
  {
    m_xtracprops.insert(p);
    updatecpnames();
    return 1;
  }

    //* Group property query
    // Returns the group property given it's name.
    // Returns NULL if there is no such property.
  ResPosElementProperty * GetGroupProperty(const char *name);
    // Returns the ith group property.
    // Returns NULL if there is no such property.
  ResPosElementProperty * GetGroupProperty(int i);

  ResPosElementProperty * GetExtraGroupProperty(int i)
  {
    if (i<0 || i>=GetNumberOfExtraGroupProperties())
      return 0;
    return m_xtragprops[i];
  }

    //* Group Property addition
    // Adds a group property to the model.
    // Returns non zero in case of success, zero otherwise.
  int AddGroupProperty(ResPosElementProperty *p)
  {
    m_xtragprops.insert(p);
    updategpnames();
    return 1;
  }

    //* Region property query
    // Returns the region property given it's name.
    // Returns NULL if there is no such property.
  ResPosElementProperty * GetRegionProperty(const char *name);
    // Returns the ith region property.
    // Returns NULL if there is no such property.
  ResPosElementProperty * GetRegionProperty(int i);

  ResPosElementProperty * GetExtraRegionProperty(int i)
  {
    if (i<0 || i>=GetNumberOfExtraRegionProperties())
      return 0;
    return m_xtrarprops[i];
  }
  
    //* Region Property addition
    // Adds a region property to the model.
    // Returns non zero in case of success, zero otherwise.
  int AddRegionProperty(ResPosElementProperty *p)
  {
    m_xtrarprops.insert(p);
    updaterpnames();
    return 1;
  }

    //* Field property query
    // Returns the field property given it's name.
    // Returns NULL if there is no such property.
  ResPosElementProperty * GetFieldProperty(const char *name);
    // Returns the ith field property.
    // Returns NULL if there is no such property.
  ResPosElementProperty * GetFieldProperty(int i);

  ResPosElementProperty * GetExtraFieldProperty(int i)
  {
    if (i<0 || i>=GetNumberOfExtraFieldProperties())
      return 0;
    return m_xtrafprops[i];
  }

    //* Field Property addition
    // Adds a field property to the model.
    // Returns non zero in case of success, zero otherwise.
  int AddFieldProperty(ResPosElementProperty *p)
  {
    m_xtrafprops.insert(p);
    updatefpnames();
    return 1;
  }

    //* Extra property query
    // Returns the ith extra property
    // Returns NULL if there is no such property.
  ResProperty * GetExtraProperty(int i)
  {
    if ((i<0)||(i>m_xtramprops.size()))
      return 0;
    return m_xtramprops[i];
  }

    //* Extra element name query
    // Returns the name of the ith extra element.
    // Returns NULL if there is no such element.
  const char * GetExtraElementName(int i)
  {
    if ((i<0)||(i>=m_xtraenames.size()))
      return 0;
    return m_xtraenames[i];
  }

    //* Extra element description query
    // Returns the description of the ith extra element.
    // Returns NULL if there is no such element.
  const char * GetExtraElementDesc(int i)
  {
    if ((i<0)||(i>=m_xtraedescs.size()))
      return 0;
    return m_xtraedescs[i];
  }

    //* Extra element unit query
    // Returns the unit of the ith extra element.
    // Returns NULL if there is no such element.
  const char * GetExtraElementUnit(int i)
  {
    if ((i<0)||(i>=m_xtraeunits.size()))
      return 0;
    return m_xtraeunits[i];
  }

    //* Extra element property data query
    // Returns the property data of the ith extra element.
    // Returns NULL if there is no such element.
  ResPosElementPropertyData * GetExtraElementPropertyData(int i)
  {
    if ((i<0)||(i>=m_xtraeprops.size()))
      return 0;
    return m_xtraeprops[i];
  }

    // Returns the ith well.
    // Returns NULL if there is no such well.
  virtual ResWell * GetWellAt(int i) = 0;
    // Returns the well given it's name.
    // Returns NULL if there is no such well.
  virtual ResWell * GetWell(const char *name) = 0;
  
    //* Amount of wells query
    // Returns the number of wells.
  virtual int GetNumberOfWells() = 0;


    //* Group query
    // Returns the ith group.
    // Returns NULL if there is no such group.
  virtual ResPosGroup * GetGroupAt(int i) = 0;
    // Returns the group given it's name.
    // Returns NULL if there is no such group.
  virtual ResPosGroup * GetGroup(const char *name) = 0;

    //* Amount of groups query
    // Returns the number of groups.
  virtual int GetNumberOfGroups() = 0;

    //* Region query
    // Returns the ith region.
    // Returns NULL if there is no such region.
  virtual ResPosRegion * GetRegionAt(int i) = 0;
    // Returns the region given it's name.
    // Returns NULL if there is no such region.
  virtual ResPosRegion * GetRegion(const char *name) = 0;

    //* Amount of regions query
    // Returns the number of regions.
  virtual int GetNumberOfRegions() = 0;

    //* Field query
    // Returns the field.
  virtual ResPosField * GetField() = 0;

    //* Step query
    // Returns the ith step.
  virtual ResStep * GetStep(int i) = 0;

    //* Element Step query
    // Returns the ith element step.
  virtual ResStep * GetElementStep(int i) = 0;

    //* Amount of steps query
    // Returns the number of steps.
  virtual int GetNumberOfSteps() = 0;

    //* Amount of element steps query
    // Returns the number of element steps.
  virtual int GetNumberOfElementSteps() = 0;
  /**
   * Specifies the value to be associated to an undefined grid value.
   */
  void SetGridNullValue (float v)
  {
    m_grid_null_value = v;
  }
  /**
   * Obtains the value associated with an undefined grid value.
   */
  float GetGridNullValue () const
  {
    return m_grid_null_value;
  }
  /**
   * Specifies the value to be associated to an undefined grid value.
   */
  void SetWellNullValue (float v)
  {
    m_well_null_value = v;
  }
  /**
   * Obtains the value associated with an undefined well value.
   */
  float GetWellNullValue () const
  {
    return m_well_null_value;
  }
  /**
  * Gets the map step matching the given element step
  */
  int GetClosestStepNumber(int elementStepNumber);

  /**
   * Gets the element step matching the given map step.
   * Returns -1 in case the model does not have any element time steps.
   */
  int GetClosestElementStepNumber(int mapStepNumber);

  /** 
   * Find a element step given a date
   */
  int FindElemStep(int dd,int mm,int yy,double dtol);
   
  /**
   *  Find a closest element step given a date
   */
  int FindClosestElemStep(int dd,int mm,int yy,double dtol);

  /** 
   * Find a map step given a date
   */
  int FindMapStep(int dd,int mm,int yy,double dtol);
   
  /**
   * Computes the radius to be used in the rendering of all wells.
   */
  void ComputeWellRadius ( void );
  
  /**
   * Obtains the radius used in the rendering of all wells.
   */
  void GetWellsRadius ( float *oi, float *oj, float *ok ) const
  {
    *oi = m_well_radius_i;
    *oj = m_well_radius_j;
    *ok = m_well_radius_k;
  }
  virtual ResProperty * GetIniProperty(int i) = 0;
  virtual ResProperty * GetIniProperty(const char *name) = 0;
  virtual ResProperty * GetRecProperty(int i) = 0;
  virtual ResProperty * GetRecProperty(const char *name) = 0;
  /**
   * Exports the model into an ASCII file.
   * 'filename' is the file to export to.
   * 'propname' is the name of the property exported along.
   * 'stepindex' is the index of the desired time step.
   *
   * Returns 'true' if successful, 'false' otherwise.
   *
   * File format (in portuguese):
   *
   * Na primeira linha:
   * NI NJ NK NUMACTIVE NUMVERTICES NUMSTEPS:
   * - numero de celulas em i, j, k (inteiros)
   * - numero de celulas ativas (inteiro)
   * - numero de vertices (inteiro)
   * - numero de time steps gravados (inteiro)
   *
   * Em seguida, NUMSTEPS linhas, com o formato:
   * dia/mes/ano
   *
   * Em seguida, NUMVERTICES linhas, com o formato:
   * X Y Z
   * - coordenadas x, y e z do vertice 'i' (float)
   *
   * Em seguida, NI*NJ*NK linhas, com o formato:
   * ACTIVE I J K N1 N2 N3 N4 N5 N6 N7 N8 AD1 AD2 AD3 AD4 AD5 AD6 PROPS
   * - ACTIVE: 1 se celula eh ativa, 0 se celula eh inativa
   * - I J e K: indices i, j e k da celula (inteiro, base 0)
   * - Ni: indice do 'i'esimo vertice da celula (inteiros, base 0)
   * - ADi: indice da celula adjacente pela face 'i' do hexaedro, se houver. se nao houver, -1 (inteiros, base 0)
   * - PROPS: valor do campo escalar no time step 't' (NUMSTEPS floats)
   */
  bool ExportASCII (const char* filename, const char* propname, int stepindex);
protected:
  bool WasGridNullValueInitialized () const;
  bool WasWellNullValueInitialized () const;
  // Removes all current extra elements from the model,
  // freeing the memory used by them as well
  // this method should me called manually on each subclass destructor
  // since it calls virtual methods
  void FreeExtraElements();
  virtual ResProperty * GetExtraProperty(const char *name);
  virtual ResPosElementProperty * GetExtraWellProperty(const char *name);
  virtual ResPosElementProperty * GetExtraCompletionProperty(const char *name);
  virtual ResPosElementProperty * GetExtraGroupProperty(const char *name);
  virtual ResPosElementProperty * GetExtraRegionProperty(const char *name);
  virtual ResPosElementProperty * GetExtraFieldProperty(const char *name);
  virtual ResPosElementProperty * GetWellProp(int i) = 0;
  virtual ResPosElementProperty * GetWellProp(const char *name) = 0;
  virtual int GetNumberOfWellProps() = 0;
  virtual ResPosElementProperty * GetCompProp(int i) = 0;
  virtual ResPosElementProperty * GetCompProp(const char *name) = 0;
  virtual int GetNumberOfCompProps() = 0;
  virtual ResPosElementProperty * GetGroupProp(int i) = 0;
  virtual ResPosElementProperty * GetGroupProp(const char *name) = 0;
  virtual int GetNumberOfGroupProps() = 0;
  virtual ResPosElementProperty * GetRegionProp(int i) = 0;
  virtual ResPosElementProperty * GetRegionProp(const char *name) = 0;
  virtual int GetNumberOfRegionProps() = 0;
  virtual ResPosElementProperty * GetFieldProp(int i) = 0;
  virtual ResPosElementProperty * GetFieldProp(const char *name) = 0;
  virtual int GetNumberOfFieldProps() = 0;
  /**
   * Builds the TOPO, BASE and H properties based on the geometry
   * information.
   * 'is_rebuilding' signals if this method has already been called once.
   */
  void CompleteGeometryProperties (bool is_rebuilding);
private:
  void ComputeWellRadius ( float maxRadius[3] );

  void SetWellsRadius (float i, float j, float k);

  float m_well_radius_i;
  float m_well_radius_j;
  float m_well_radius_k;
  float m_grid_null_value;
  float m_well_null_value;
  ResModelNew* m_mdlnew;
};

#endif

