#ifndef RES_FAULT_DATA_H
#define RES_FAULT_DATA_H

#include <stdlib.h>
#include <alg/matrix.h>
#include <alg/vector.h>
#include <ds/array.h>
#include <ds/hash.h>
#include <ds/stringkey.h>

class ResModelNew;

/**
 * Fault property class definition: contains property's name and values.
 */
class ResFaultProperty
{
public:
  enum PropName
  {
    PORE,
    COHESION,
    PHI,
    NONE
  };
public:
  ResFaultProperty ();
  virtual ~ResFaultProperty ();
  DsArray<float>& GetValues ();
  const DsArray<float>& GetValuesConst () const;
  void ComputeValuesLimits ();
  void GetValuesLimits (float& vmin, float& vmax) const;
  static const char* PropNameString[3];
  static const char* PropNameDesc[3];
  static const int PropNameCount = 3; // must follow changes in enum PropName
private:
  DsArray<float> m_scalars;
  float m_vmin, m_vmax;
};

/**
 * Fault class definition: encapsulates geometry and properties.
 */
class ResFault
{
public:

public:
  ResFault ();
  virtual ~ResFault ();
  const char* ClassName () const { return "ResFault"; };

  /**
   * Access to a given property.
   */
  const ResFaultProperty* GetProperty (ResFaultProperty::PropName n) const;
  /**
   * Set a specific property.
   */
  void SetProperty (ResFaultProperty::PropName n, const ResFaultProperty* p);

  /**
   * Access to fault's vertices array.
   */
  DsArray<float>& GetVertices ()
  {
    return m_vertices;
  }
  /**
   * Access to fault's triangles array.
   */
  DsArray<unsigned int>& GetTriangles ()
  {
    return m_triangles;
  }

  /**
   * Access to const fault's vertices array.
   */
  const DsArray<float>& GetVerticesConst () const
  {
    return m_vertices;
  }
  /**
   * Access to const fault's triangles array.
   */
  const DsArray<unsigned int>& GetTrianglesConst () const
  {
    return const_cast<DsArray<unsigned int>&>(m_triangles);
  }
  /**
   * Get property values limits of a given property.
   */
  void GetPropertyValuesLimits (ResFaultProperty::PropName prop,
                                float& vmin, 
                                float& vmax) const;
private:
  DsArray<float> m_vertices;
  DsArray<unsigned int> m_triangles;
  DsHash<DsStringKey, const ResFaultProperty*> m_properties;
  ResFaultProperty::PropName m_active_property;
};

/**
 * Fault data class definition: able to load faults file,
 * store faults and their properties.
 */
class ResFaultData
{
public:
  ResFaultData ();
  virtual ~ResFaultData ();
  const char* ClassName () const { return "ResFaultData"; };
  
  /**
   * Load faults data from input file.
   * @param input_file complete path to input file with faults data.
   * @param mdl reservoir model
   * @return success in operation.
   */
  bool LoadFromFile (const char* input_file, ResModelNew* mdl);
  /*********************** Faults operations. *********************************/
  /**
   * Return a given fault.
   * @return fault_i fault's index.
   */
  const ResFault* GetFault (int fault_i) const
  {
    return m_fault.Get(fault_i);
  }

  /**
   * Return faults count.
   * @return faults count.
   */
  int GetFaultCount () const
  {
    return m_fault.Size();
  }

  /**
   * Add fault.
   * @param f fault to be added
   */
  void AddFault (ResFault* f);

  /**
   * Reset faults data.
   */
  void Clear ();

  /**
   * Get bounding box limits.
   */
  void GetBoundingBox (AlgVector& bbmin, AlgVector& bbmax) const
  {
    bbmin = m_bbmin;
    bbmax = m_bbmax;
  }

private:
  AlgVector m_bbmin, m_bbmax;        /**< Faults bounding box limits.       */
  DsArray<ResFault*> m_fault;        /**< Faults elements.                  */
};

#endif  // RES_FAULT_DATA_H
