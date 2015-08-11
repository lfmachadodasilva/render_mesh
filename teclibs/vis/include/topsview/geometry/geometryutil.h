/**
* Modulo de definicao da classe TpvGeometry, para ser usado como geometria extraida para a TopsView
*/

#ifndef TPV_GEOMETRY_UTIL_H
#define TPV_GEOMETRY_UTIL_H

#include <tops/tops.h>
#include <topsview/defines.h>
#include "../property/property.h"

#include <stdio.h>
#include <math.h>

/**  
*/
class TPV_API TpvGeometryUtil
{
public:
  /** Available face types. */
  enum FaceType {
    FACE_T3,
    FACE_T6,
    FACE_Q4,
    FACE_Q5,
    FACE_Q8,
    FACE_MAX_TYPE,
  };

  /** Available edge types. */
  enum EdgeType {
    EDGE_E2,
    EDGE_E3,
    EDGE_MAX_TYPE,
  };

private:
  static int m_elem_face_types[TopModel::ELEMENT_MAX][TOP_MAX_NUM_F];
  static int m_elem_edge_types[TopModel::ELEMENT_MAX][TOP_MAX_NUM_E];
  static float m_elem_node_params[TopModel::ELEMENT_MAX][3*TOP_MAX_NUM_N];
  static float m_face_node_params[FACE_MAX_TYPE][2*TOP_MAX_NUM_F_N];
  static float m_face2d_node_params[FACE_MAX_TYPE][2*TOP_MAX_NUM_F_N];
  static float m_edge_node_params[FACE_MAX_TYPE][TOP_MAX_NUM_E_N];

  static void InitElemFaceTypes();
  static void InitElemEdgeTypes();
  static void InitElemNodeParams();
  static void InitFaceNodeParams();
  static void InitFace2DNodeParams();
  static void InitEdgeNodeParams();

  template <class T>
  static void GetEntityPositions(TopModel* m, 
                                 const T& fu, 
                                 TpvProperty* disp, 
                                 float disp_factor, 
                                 float* pos)
  {
    int nnodes = m->GetNNodes(fu);
    for (int i = 0; i < nnodes; i++) {
      GetNodePosition(m, m->GetNode(fu, i), disp, disp_factor, pos);
      pos += 3;
    }
  }

  template<class T>
  static void GetEntityField(TopModel* m, const T& fu, 
    TpvProperty* field, float* s)
  {
    int nnodes = m->GetNNodes(fu);
    if (field) {
      int elid;
      float v;
      switch (field->GetType()) {
        case TpvProperty::PROP_ELEMENT_NODE:
          elid = m->GetId(m->GetElem(fu));
          for (int i = 0; i < nnodes; i++)
            s[i] = field->GetValue(elid, m->GetNodeLocalId(fu, i))[0];
          break;
        case TpvProperty::PROP_ELEMENT:
          elid = m->GetId(m->GetElem(fu));
          v = field->GetValue(elid)[0];
          for (int i = 0; i < nnodes; i++) 
            s[i] = v;
          break;
        case TpvProperty::PROP_NODE:
          for (int i = 0; i < nnodes; i++)
            s[i] = field->GetValue(m->GetId(m->GetNode(fu, i)))[0];
          break;
        default:
          assert(false);
          for (int i = 0; i < nnodes; i++) 
            s[i] = 0.0f;
          break;
      }
    } else {
      for (int i = 0; i < nnodes; i++) 
        s[i] = 0.0f;
    }
  }

public:

  static void Init();

  static int GetElemFaceType(int el_type, int fi);

  static int GetElemEdgeType(int el_type, int ei);

  static void GetElemPositions(TopModel* m, 
                               const TopElement& elem, 
                               TpvProperty* disp, 
                               float disp_factor, 
                               float* o_pos)
  {
    GetEntityPositions<TopElement>(m, elem, disp, disp_factor, o_pos);
  }

  /**
      Gets the positions (x,y,z) of the nodes of the face.
  */
  static void GetFacetPositions(TopModel* m, const TopFacetUse& fu, 
    TpvProperty* disp, float disp_factor, float* pos)
  {
    GetEntityPositions<TopFacetUse>(m, fu, disp, disp_factor, pos);
  }
   
  static void GetFacePositions(TopModel* m, const TopFaceUse& fu, 
    TpvProperty* disp, float disp_factor, float* pos)
  {
    GetEntityPositions<TopFaceUse>(m, fu, disp, disp_factor, pos);
  }    

  static void GetEdgePositions(TopModel* m, const TopEdgeUse& fu, 
    TpvProperty* disp, float disp_factor, float* pos)
  {
    GetEntityPositions<TopEdgeUse>(m, fu, disp, disp_factor, pos);
  }

  static void GetNodePosition(TopModel* m, const TopNode& n, 
    TpvProperty* disp, float disp_factor, float* pos)
  {
    m->GetPosition(n, &pos[0], &pos[1], &pos[2]);
    if (disp) {
      float* pdisp = disp->GetValue(m->GetId(n));
      pos[0] += disp_factor*pdisp[0];
      pos[1] += disp_factor*pdisp[1];
      pos[2] += disp_factor*pdisp[2];
    }  
  }

  static void GetElemField(TopModel* m, 
                           const TopElement& el, 
                           TpvProperty* field, 
                           float* s)
  {
    int nnodes = m->GetNNodes(el);
    if (field) {
      int elid = m->GetId(el);
      switch (field->GetType()) {
        case TpvProperty::PROP_ELEMENT_NODE:
          for (int i = 0; i < nnodes; i++)
            s[i] = field->GetValue(elid, i)[0];
          break;
        case TpvProperty::PROP_ELEMENT:
          for (int i = 0; i < nnodes; i++) 
            s[i] = field->GetValue(elid)[0];
          break;
        case TpvProperty::PROP_NODE:
          for (int i = 0; i < nnodes; i++)
            s[i] = field->GetValue(m->GetId(m->GetNode(el, i)))[0];
          break;
        default:
          assert(false);
          for (int i = 0; i < nnodes; i++) 
            s[i] = 0.0f;
          break;
      }
    } else {
      for (int i = 0; i < nnodes; i++) 
        s[i] = 0.0f;
    }
  }

  /**
      Gets the scalar field of the nodes of the face.
  */
  static void GetFacetField(TopModel* m, const TopFacetUse& e, 
    TpvProperty* field, float* s)
  {
    GetEntityField<TopFacetUse>(m, e, field, s);
  }  
 
  static void GetFaceField(TopModel* m, const TopFaceUse& e, 
    TpvProperty* field, float* s)
  {
    GetEntityField<TopFaceUse>(m, e, field, s);
  }  

  static void GetEdgeField(TopModel* m, const TopEdgeUse& e, 
    TpvProperty* field, float* s)
  {
    GetEntityField<TopEdgeUse>(m, e, field, s);
  }

  /**
    Gets the value of the field linearly interpolated between the
    two edge's vertices.
  */
  static void GetInterpolatedEdgeField(TopModel* m,
    const TopEdgeUse& eu, TpvProperty* field, float t, float* s_out)
  {
    float s[2];
    if (field) {
      int ft = field->GetType();
      if (ft == TpvProperty::PROP_ELEMENT_NODE) {
        int elid = m->GetId(m->GetElem(eu));
        int nid = m->GetVertexNodeLocalId(eu, 0);
        s[0] = field->GetValue(elid, nid)[0];
        nid = m->GetVertexNodeLocalId(eu, 1);
        s[1] = field->GetValue(elid, nid)[0];
      } else if (ft == TpvProperty::PROP_ELEMENT) {
        int elid = m->GetId(m->GetElem(eu));
        s[0] = s[1] = field->GetValue(elid)[0];
      } else if (ft == TpvProperty::PROP_NODE) {
        int nid = m->GetId(m->GetVertexNode(eu, 0));
        s[0] = field->GetValue(nid)[0];
        nid = m->GetId(m->GetVertexNode(eu, 1));
        s[1] = field->GetValue(nid)[0];
      } else {
        s[0] = s[1] = 0.0f;
      }
    } else {
      s[0] = s[1] = 0.0f;
    }
    *s_out = (1.0f-t)*s[0] + t*s[1];
  }

  /** Natural (parametric) coordinates (r,s,t) of the nodes of the given element type. */
  static const float* GetElemNodeParams(int elem_type);
  /** Natural (parametric) coordinates (r,s) of the nodes of the given face type. */
  static const float* GetFaceNodeParams(int face_type);
  static const float* GetFace2DNodeParams(int face_type);
  /** Natural (parametric) coordinate (r) of the nodes of the given edge type. */
  static const float* GetEdgeNodeParams(int edge_type);
  static bool ComputeTriNormal(float* v0, float* v1, float* v2, float* n)
  {
    float va[3], vb[3];
    va[0] = v1[0] - v0[0]; va[1] = v1[1] - v0[1]; va[2] = v1[2] - v0[2];
    vb[0] = v2[0] - v0[0]; vb[1] = v2[1] - v0[1]; vb[2] = v2[2] - v0[2];
    // Cross product: (P1-P0)x(P2-P0)
    n[0] = va[1]*vb[2] - va[2]*vb[1];
    n[1] = va[2]*vb[0] - va[0]*vb[2];
    n[2] = va[0]*vb[1] - va[1]*vb[0];
    float d = n[0]*n[0] + n[1]*n[1] + n[2]*n[2];
    if (d > 0.0f)
      d = (float) sqrt(d);
    if (d > 0.0f) {
      n[0] /= d; n[1] /= d; n[2] /= d;
      return true;
    } else {
      //printf("Degenerated face. Cannot compute normal.\n");
      n[0] = n[1] = n[2] = 0;
      return false;
    }
  }
};

#endif
