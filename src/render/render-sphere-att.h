//// ------------------------------------------------------------------------------------------------- 
//// Anflex Project -- Tecgraf/PUC-Rio  CENPES/Petrobras 
//// www.tecgraf.puc-rio.br 
//// 
//// Created by lfmachado in April/2012.
//// 
//// $URL: $ 
//// $Revision: $ 
//// $Date: $ 
//// 
//// $LastChangedBy: $ 
//// -------------------------------------------------------------------------------------------------
//
//#ifndef ANFLEX_INTERFACE_RENDER_SPHERE_ATT_H
//#define ANFLEX_INTERFACE_RENDER_SPHERE_ATT_H
//
//#include "render-object-att.h"
//
//#include <vector>
//using std::vector;
//
//class cRenderSphereAtt : public cRenderObjectAtt
//{
//private:
//
//  float m_radius;
//  float m_slices;
//  float m_stacks;
//
//  void create(void);
//
//public:
//
//  cRenderSphereAtt(void);
//  cRenderSphereAtt(float m_radius, float m_slices, float m_stacks);
//
//  virtual void create_array(cAppGauge *gauge);
//  virtual bool check_pick(const int &id, 
//                          const AlgVector &ray_ori, 
//                          const AlgVector &ray_dest,
//                          AlgVector *point);
//  virtual void calc_normals(cAppGauge *gauge);
//};
//
//#endif