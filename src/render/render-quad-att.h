// ------------------------------------------------------------------------------------------------- 
// Anflex Project -- Tecgraf/PUC-Rio  CENPES/Petrobras 
// www.tecgraf.puc-rio.br 
// 
// Created by lfmachado in April/2012.
// 
// $URL: $ 
// $Revision: $ 
// $Date: $ 
// 
// $LastChangedBy: $ 
// -------------------------------------------------------------------------------------------------

#ifndef ANFLEX_INTERFACE_RENDER_QUAD_ATT_H
#define ANFLEX_INTERFACE_RENDER_QUAD_ATT_H

#include "render-pick.h"

class cRenderQuadAtt : public cRenderPick
{
protected:

  float m_height;
  float m_width;
  float m_lenght;

  void create(void);

  virtual void change_element_pick(const bool select,  const bool is_select, const int id) {}
  virtual bool check_pick(const int &id, 
                          const AlgVector &ray_ori, 
                          const AlgVector &ray_dest,
                          AlgVector *point) { return false; }

public:

  cRenderQuadAtt(void);
  cRenderQuadAtt(float height, float width, float lenght);

  virtual void create_array(cAppGauge *gauge);
  virtual void calc_normals(cAppGauge *gauge);
  virtual void create_scene(void) { /* do anything */ }
};

#endif