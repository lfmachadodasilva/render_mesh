#ifndef TPVVFL_VECTORFIELD_H
#define TPVVFL_VECTORFIELD_H

//----------//
// Includes //
//----------//

#include "defines.h"

#include <vfl/basevectorfield.h>
#include <tops/model.h>
#include <alg/vector.h>

//----------------------//
// Forward Declarations //
//----------------------//

class TpvProperty;

//--------------------------------------//
// Class Definition - TpvVflVectorField //
//--------------------------------------//

class TPVVFL_API TpvVflVectorField : public VflBaseVectorField
{
public:

  enum InterpolationMode
  {
    INTERPOLATION_IDW         = 0,  // Use inverse distance weighting (hyperbolic non-homogeneous interpolation)
    INTERPOLATION_BARYCENTRIC = 1   // Use barycentric coordinates as weights (linear homogeneous interpolation)
  };

  // Constructors and Destructor

  TpvVflVectorField (TopModel* topModel = 0, InterpolationMode interpolation = INTERPOLATION_IDW);
  virtual ~TpvVflVectorField (void);

  // Getters and Setters

  TopModel*     GetTopModel       (void) {return m_topModel;}
  float         GetLimit          (void) {return m_limit;}
  unsigned int  GetInterpolation  (void) {return m_interpolation;}
  TopElement    GetCurrentElement (void) {return m_element;}
  TpvProperty*  GetProperty       (void) {return m_property;}

  void SetTopModel       (TopModel*         topModel)       {m_topModel       = topModel;}
  void SetActiveElements (const bool*       activeElements) {m_activeElements = activeElements;}
  void SetLimit          (float             limit)          {m_limit          = limit;}
  void SetInterpolation  (InterpolationMode interpolation)  {m_interpolation  = interpolation;}
  void SetCurrentElement (const TopElement& element);

  bool SetProperty (TpvProperty* property, bool invertZ = false, bool takePropertyOwnership = false);
  bool SetProperty (const float* propertyX, const float* propertyY, const float* propertyZ, bool invertZ = false, bool takeOwnership = false);
  void SetNullProperty (float nullX, float nullY, float nullZ);

  // Element Activeness

  bool IsElementActive ();
  bool IsElementActive (const TopElement& topElement);

  // Field Value

  virtual AlgVector GetFieldValue (const AlgVector& pos);

protected:

  // Auxiliary functions

  void ReleaseElementData (void);

  void LimitVector (AlgVector& vec);

  void SetIncidenceHex8 (int v0, int v1, int v2, int v3, int v4, int v5, int v6, int v7);
  void SetIncidenceHex8Res (int v0, int v1, int v2, int v3, int v4, int v5, int v6, int v7);

  AlgVector GetNodeProperty (const TopNode& topNode);

  AlgVector GetFieldValueIDW     (const AlgVector& pos);
  AlgVector GetFieldValueHex8    (const AlgVector& pos, int incidence[8]);
  AlgVector GetFieldValueTet4    (const AlgVector& pos, int vertexId0, int vertexId1, int vertexId2, int vertexId3);

private:

  TopModel*    m_topModel;

  TpvProperty* m_property;
  const float* m_propertyX;
  const float* m_propertyY;
  const float* m_propertyZ;

  TopElement   m_element;
  TopNode*     m_elementVertexNodes;
  AlgVector*   m_elementVertexPos;
  unsigned int m_elementVertexCount;

  const bool*  m_activeElements;

  int m_incidenceHex8[8];
  int m_incidenceHex8Res[8];

  InterpolationMode m_interpolation;
  AlgVector m_nullProperty;
  float m_limit;
  float m_signZ;

  bool m_ownProperty;
  bool m_ownPropertyXYZ;

};

#endif // TPVVFL_VECTORFIELD_H
