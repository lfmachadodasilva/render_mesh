
#ifndef TOPSVIEWRES_TETRA_GEOMETRY_H
#define TOPSVIEWRES_TETRA_GEOMETRY_H

#include <tops/multimodel.h>
#include <topsviewres/defines.h>
#include <topsview/geometry/tetrageometry3.h>

class TPV_API TpvResTetraGeometry : public TpvTetraGeometry3<TpvResGeometryModel>
{
public:
  typedef TpvTetraGeometry3<TpvResGeometryModel> SuperClass;
  typedef TpvTetrahedronSet Tetrahedra;

  TpvResTetraGeometry();

  virtual ~TpvResTetraGeometry();

  void SetModel (TopMultiModel* m);

  virtual TpvTetrahedronSet* GetTetrahedra(int step_id = TpvGeometry3<TpvResGeometryModel>::NO_REZONE_STEP_ID);

  void SetExtractTetrahedronVertexIncidences (bool flag);

protected:
  virtual void InitGeometry();
  virtual void ClearGeometry();
  virtual void ClearField();
  virtual void ClearDisp();
  virtual void ExtractGeometry();
  virtual void ExtractField();

private:
  void GetTetField(int ti, float* s);
  void AddTet(const TopElement& el);
  void AddElem(const TopElement& el);
  int ExtractTetrahedralIndices (DsArray<int>* tet_ids);
  void ExtractVertexIncidences ();
  void ExtractAdjacencies (const DsArray<int>& tet_ids);
//  void ReOrderTetrahedrons ();

private:
  TpvTetrahedronSet* m_tetra;
  bool m_extract_vertex_incidences;
};

#endif

