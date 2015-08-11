// Cut planes geometry extractor (with sections and layer separation)
// fabraham@tecgraf.puc-rio.br
// Feb 2008
// cpalomo@tecgraf.puc-rio.br
// May 2010
#ifndef TPVRES_CUT_H
#define TPVRES_CUT_H

#include <ds/array.h>
#include <ds/hash.h>
#include <alg/vector.h>
#include <geoms/intersect.h>
#include <topsgeoms/polyhedramodel.h>
#include <topsviewres/defines.h>
#include "bdryfaces.h"

// forward declarations
class TpvTriangleSet;
class TpvResCutTriangulator;

class TPVRES_API TpvResCutGeometry : public TpvResBdryFacesGeometry
{
public:
  TpvResCutGeometry ();
  virtual ~TpvResCutGeometry ();

  void SetPerElemField (TpvProperty* p);
  void SetPerElemColors (TpvProperty* p);
  void SetGeometryOutdated ();
  void SetFieldOutdated ();
  void SetPerElemColorsOutdated ();
  void SetVBOEnabled (bool flag);

  void resetPlanes ();
  bool hasIntersection (TopElement el, int planeID, float* middlePoint = NULL);
  /**
  * Indica os limites dos planos.
  * Use esta funcao quando o plano for finito.
  * @param nplanes é o número de planos especificados.
  * @param limits é o vetor que contém os limites dos planos no formato
  * XminP0 YminP0 ZminP0 XmaxP0 YmaxP0 ZmaxP0 XminP1 YminP1 ZminP1 XmaxP1 YmaxP1 ZmaxP1...
  * @param direction é a direcao de crescimento do plano. Deve ser paralelo a todos os segmentos formados por limits
  */
  bool setPlaneLimits ( int nplanes, float* limits, float direction[3]=NULL);
  /**
  * Indica a equacao do plano.
  * Use apenas para um plano infinito.
  * @param nx, ny, nz, d são as variaveis da equação do plano.
  */
  bool setPlaneEquation (float nx, float ny, float nz, float d);
  bool getPlaneLimits (int plane, float limits[6], float direction[3]=NULL);
  void getPlaneEquation (float vetEquation[4]) const
  {
    memcpy(vetEquation, m_planeEquation, 4 * sizeof(float));
  }
  /**
   * Get planes count.
   */
  int GetPlanesCount ();
  /**
   * Return whether a certain plane is active for draw.
   * @return true when plane active for draw.
   */
  bool IsPlaneEnabled (int plane_i) const;
  /**
   * Active a certain plane for draw.
   * @param plane_i must be 0..planes count-1.
   * @param flag activate/deactivate plane draw.
   */
  void SetPlaneEnabled (int plane_i, bool flag);
  bool getPlaneEquation (float planeLimits[6], float planeEquation[4]);
  bool GetPlaneNormal (const float planeLimits[6], float normal[3]);
  void getZLimits (float* zmin, float* zmax);
  void SetPlaneNormal (int plane_i, const float* vetNormal)
  {
    m_normal.SetConst(plane_i, AlgVector(vetNormal));
  }
  AlgVector GetPlaneNormal (int plane_i) const
  {
    return m_normal.Get(plane_i);
  }
# if DEBUG_TESTED_ELEMS
  void SetTestedElems (DsHash<int, bool>* tested_elems)
  {
    m_tested_elems = tested_elems;
  }
# endif

private:
  bool HasCutPlaneChanged (const float* limits1, 
                           const float* eq1, 
                           const float* limits2, 
                           const float* eq2) const;
  void calculateCut ();
  // virtual methods
  void ExtractFaces ();

  bool ReallocVectors (int planeID, int num_total_intersections);
  void ProcessIntersections (int planeID, int num_total_intersections);
  /**
   * Checa a intersecao dos elementos do modelo com um plano.
   *
   * @param planeLimits são os dois pontos que delimitam o plano.
   * @param planeEquation é a equacao 3D do plano.
   * @param planeID um identificador do plano.
   */
  bool checkIntersection(float* planeLimits, float* planeEquation, int planeID);
  static float normalize(float* vector);
  static void  cross(const float* v1, const float* v2, float* v);

  void AllocGeomSets (int plane_i);

  // pure virtual methods
  virtual int GetGeomCount () = 0;
  virtual TpvTriangleSet* GetGeom (int i) = 0;
  virtual TpvTriangleSet** AllocPlaneGeoms (int plane_i, int* count) = 0;
  virtual TpvTriangleSet** GetPlaneGeoms (int plane_i, int* count) = 0;
  virtual bool SkipFaceExtraction (int si, int sj, int sk) = 0;
  virtual void AddFace (int plane_i,
                        int k, 
                        DsArray<AlgVector>& polygon, 
                        TopElement el) = 0;
  virtual void ResetGeomsets (int plane_i) = 0;
  virtual int GetIntersectCount () = 0;
  virtual TOP_INTERSECT* GetIntersect (int i) = 0;
  virtual TOP_INTERSECT* GetIntersectByEl (TopElement el) = 0;
  virtual topsgeoms::PolyhedraModelRes* GetPolyModel (int i) = 0;
  virtual bool CheckIntersection (TopElement el, 
                                  float planeLimits[6],
                                  float planeEquation[4],
                                  const float direction[3],
                                  bool isInfinitePlane) = 0;
  virtual int CalculateIntersection (float* planeLimits,
                                     float* planeEquation, 
                                     const float direction[3], 
                                     bool isInfinitePlane) = 0;
  bool allocVectors(int nplanes, float *limits, float* planeEquation);
  void resetPlane(int planeNumber);

protected:
  void GetElemEdgesAndFaces(TopElement el,
                            int* edge_count,
                            float** edges,
                            int* face_count,
                            float** faces,
                            int** faces_v_count);

private:
  TpvResCutTriangulator* m_triangulator;
  DsArray<bool> m_update_plane_geom;
  TpvProperty* m_per_elem_field;
  TpvProperty* m_per_elem_colors;
  int m_allocatedPlanes;
  int m_nPlanes;          /**< Numero de planos de corte. */
  int m_totalPoints;      /**< Numero total de pontos gerados. */
  int* m_nPoints;         /**< Vetor de numero de pontos gerados pelo corte de cada plano. */
  bool* m_calculateCut;   /**< Vetor que determina os planos cujos cortes devem ser recalculados. */
  float* m_planeLimits;   /**< Vetor com os limites dos planos no formato [xi1 yi1 zi1 xf1 yf1 zf1 xi2 yi2 ... ]. */
  float** m_points;       /**< Vetor com os pontos gerados pelo corte. */
  TopElement** m_elements;/**< Vetor com os elementos relacionados aos pontos. */
  DsArray<bool> m_plane_active;
  float** m_zlimits;
  float m_planeEquation[4];
  bool m_isInfinitePlane;
  DsArray<AlgVector> m_normal;  /**< Array with planes' normals. */
  float m_direction[3];
# if DEBUG_TESTED_ELEMS
  DsHash<int, bool>* m_tested_elems;
# endif
};

#endif  // TPVRES_CUT_H

