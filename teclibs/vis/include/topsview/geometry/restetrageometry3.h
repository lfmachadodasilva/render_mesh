#ifndef TPV_RES_TETRA_GEOMETRY_3_H
#define TPV_RES_TETRA_GEOMETRY_3_H

#include "tetrageometry3.h"
#include <tops/multimodel.h>
#include <topsview/defines.h>

class TPV_API TpvResTetraGeometry3 : public TpvTetraGeometry3<TpvResGeometryModel>
{
public:
  typedef TpvTetraGeometry3<TpvResGeometryModel> SuperClass;
  typedef TpvTetrahedronSet Tetrahedra;

  TpvResTetraGeometry3();

  virtual ~TpvResTetraGeometry3();

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
//  void ReOrderTetrahedrons ();

private:
  TpvTetrahedronSet* m_tetra;
  bool m_extract_vertex_incidences;
};

#endif

