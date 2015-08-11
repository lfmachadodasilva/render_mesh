// Boundary faces geometry extractor (with transparency)
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_TRANSP_H
#define TPVRES_TRANSP_H

#include "bdryfaces.h"
#include <stdio.h>
#include <ds/array.h>
#include <utl/sort.h>
#include <alg/vector.h>
#include <topsview/colorscale/colorscale.h>
#include <topsviewres/defines.h>

class UGLQuadSet;
class TpvResRadialTriangulator;

class TPVRES_API TpvResTranspGeometry : public TpvResBdryFacesGeometry
{
public:
  TpvResTranspGeometry();
  ~TpvResTranspGeometry();
  void SetColorScale (TpvColorScale *color_scale);
  void SetEyePos(float x, float y, float z)
  {
    if (x == m_ex && y == m_ey && z == m_ez)
      return;
    m_ex = x; m_ey = y; m_ez = z;
    m_eye_norm = m_mdl_scale * (AlgVector(m_ex, m_ey, m_ez) - m_mdl_center);
    m_sorted = false;
  }
  void GetEyePos(float* x, float* y, float* z) const
  {
    *x = m_ex; *y = m_ey; *z = m_ez;
  }
  void EnableSorting()
  {
    m_enable_sorting = true;
  }
  void DisableSorting()
  {
    m_enable_sorting = false;
  }
  bool IsSortingEnabled () const
  {
    return m_enable_sorting;
  }
  TpvQuadSet* GetQuadSetOpaque ();
  TpvQuadSet* GetQuadSetTransp ();
  void SetColorScaleChanged ();
  // virtual methods
  virtual void SetGeometryOutdated ();
  virtual void SetModel (TopMultiModel* m, bool is_radial, float radial_rw);
  virtual bool SetActiveElements (const bool* active_elems);
  virtual void SetPerElemField (TpvProperty* p);
  virtual void SetPerElemColors (TpvProperty* p);
  virtual void SetFieldOutdated ();
  virtual void SetPerElemColorsOutdated ();
  virtual void SetVBOEnabled (bool flag);
  void SetModelBB (const AlgVector& bbmin, const AlgVector& bbmax);
protected:
  TpvColorScale* GetColorScale () const
  {
    return m_color_scale;
  }
  void Sort();
  void UpdateCollect ();
  int GetColorIndex (TpvColorScale *color_scale, int elem_id);
  void SetCentroidsOutdated ()
  {
    m_centroids_updated = false;
  }
  TpvQuadSet* GetQuadSetTranspInt () const
  {
    return m_geom_set_transp;
  }
  void SetTranspElemDataCount (int num_elems)
  {
    m_transp_elem_data.Resize(num_elems);
  }
  void SetTranspElemData (int index, int first_face_index, int num_faces)
  {
    assert(m_transp_elem_data.ValidIndex(index));
    m_transp_elem_data[index].first_face = first_face_index;
    m_transp_elem_data[index].num_faces = num_faces;
  }
  void InitSortData (int count)
  {
    if (count != m_sort_data.Size()) {
      m_sort_data.Resize(count);
      // initialize sorting structures
      m_comparefunctor.SetSortData((const SortData*)m_sort_data.GetArray());
      m_sort.SetCompareFunctor(m_comparefunctor);

      m_sort_indices.Resize(count);
      for (int i=0; i<count; i++)
        m_sort_indices[i] = i;
    }
  }
  void SetSortData (int index, float cx, float cy, float cz)
  {
    assert(m_sort_data.ValidIndex(index));
    m_sort_data[index].cx = cx;
    m_sort_data[index].cy = cy;
    m_sort_data[index].cz = cz;
    m_sort_data[index].elem = index;
  }
  void InitOpaqueElemArray ()
  {
    m_opaque_elem_array.Resize(0);
  }
  void InitTranspElemArray ()
  {
    m_transp_elem_array.Resize(0);
  }
  int GetOpaqueElemCount () const
  {
    return m_opaque_elem_array.Size();
  }
  int GetTranspElemCount () const
  {
    return m_transp_elem_array.Size();
  }
  void AddOpaqueElem (TopElement elem)
  {
    m_opaque_elem_array.Append(elem);
  }
  void AddTranspElem (TopElement elem)
  {
    m_transp_elem_array.Append(elem);
  }
  TopElement GetOpaqueElem (int index)
  {
    return m_opaque_elem_array.Get(index);
  }
  TopElement GetTranspElem (int index)
  {
    return m_transp_elem_array.Get(index);
  }
  int AddElemCS (
    TopElement element,
    TopModel* elem_model,
    TpvQuadSet *destset,
    TpvColorScale* cs,
    int elem_id,
    int color_id,
    int num_no_test_adj_fu,
    const int *no_test_adj_fu,
    int num_test_adj_fu,
    const int *test_adj_fu);
private:
  static int QSortCb(const void* a, const void* b);
  void ExtractFacesFromElemArray (DsArray<TopElement> *array, TpvQuadSet *destset, bool transparent);
  void SetColorsChanged ();
  static int GetElementCount (TopMultiModel* m);
  // virtual methods
  virtual void ComputeCentroids();
  virtual void CollectModelElements();
  virtual void ExtractFaces ();
private:
  struct SortData {
    int elem;
    float cx, cy, cz;
    double dist; 
  };
  struct TranspElemData {
    int first_face;
    int num_faces;
  };
  class CompareFunctor 
  {
  public:
    UTL_FORCE_INLINE int operator() (const unsigned int i1, const unsigned int i2) const
    {
      if (m_sortData[i1].dist < m_sortData[i2].dist)
        return 1;
      else if (m_sortData[i1].dist > m_sortData[i2].dist)
        return -1;
      else
        return 0;
    }
    UTL_FORCE_INLINE void SetSortData (const SortData* data)
    { 
      m_sortData = data;
    }
  private:
    const SortData* m_sortData;
  };
private:
  void UpdateIndicesFromSortData (DsArray<SortData>* sortdata,
                                  unsigned int* ind);
private:
  TpvQuadSet* m_geom_set_opaque;
  TpvQuadSet* m_geom_set_transp;
  TpvResRadialTriangulator* m_radial_triangulator;
  UGLQuadSet* m_geom_set_transp_indices;
  TpvColorScale *m_color_scale;
  DsArray<TopElement> m_transp_elem_array;
  DsArray<TopElement> m_opaque_elem_array;
  float m_ex, m_ey, m_ez;
  AlgVector m_eye_norm;
  AlgVector m_mdl_center, m_mdl_scale;
  DsArray<SortData> m_sort_data;
  DsArray<TranspElemData> m_transp_elem_data;
  // array indices: sorting this array instead of SortData*:
  // this is faster since sizeof(SortData) > sizeof(unsigned int).
  DsArray<unsigned int> m_sort_indices;
  CompareFunctor m_comparefunctor;
  UtlSort<unsigned int, CompareFunctor, UtlSortPivotMiddle<unsigned int> > m_sort;
  // flags
  bool m_enable_sorting;
  bool m_sorted;
  bool m_update_collect;
  bool m_centroids_updated;
};

#endif

