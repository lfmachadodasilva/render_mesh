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

#ifndef ANFLEX_INTERFACE_OBJECT_QUAD_H
#define ANFLEX_INTERFACE_OBJECT_QUAD_H

#include <map>
using std::map;

// Lib vis
#include "render\render-quad-att.h"
//#include "libvis\render-pick.h"

// Local
#include "object-father.h"

class cObjectQuad : public cRenderQuadAtt, public cObjectFather
{
private:

  map<int, cRender*> m_map_render_obj_att;

  void create_array_pick(void);
  void create_scene(void);

  void change_element_pick(const bool select, const bool is_select, const int id);

protected:

  
public:

  cObjectQuad(void);
  cObjectQuad(float height, float width, float lenght);

  void add_render_att_fe_mesh_quad(bool enable, cShader *shader);
  
  bool check_pick(const int &id, 
                  const AlgVector &ray_ori, 
                  const AlgVector &ray_dest,
                  AlgVector *point);
};

#endif // ANFLEX_INTERFACE_OBJECT_QUAD_H