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

#ifndef ANFLEX_INTERFACE_RENDER_SHADER_PICK_H
#define ANFLEX_INTERFACE_RENDER_SHADER_PICK_H

#include "pick.h"
#include "render.h"

class cRenderPick : public cRender, public cPick
{
private:
protected:
  
  /**
	* @brief Render Attributes 
  *
  * map -> first - attribute type FE_MESH_QUAD, FE_MESH_SPHERE, FE_MESH_POINT
  * map -> second - pointer of object to render
	*/
  map<int, cRender*> m_map_render_obj_att; 

  /*
  * @brief Render using shader
  *
  * @param[in] shader
  * @param[in] render attribute
  */
  virtual void render_shader(const cShader* shader, const cRenderAtt *render_att);

  /*
  * @brief Render using old opengl
  *
  * @param[in] render attribute
  */
  virtual void render_old(const cRenderAtt *render_att);

  /**
	* @brief Pick element
  *
  * @param[in] insert - insert or remove pick
  * @param[in] is_select - select or focus pick
  * @param[in] id - element id
	*/
  virtual void change_element_pick(const bool change, const bool is_select, const int id) = 0;

public:

  /*
  * @brief Constructor
  *
  * @param[in] type - object type eObjectType
  */
  cRenderPick(eObjectType type);

  void operator=(const cRenderPick &render);

  /*
  * @brief Main render
  *
  * @param[in] shader
  * @param[in] render attribute
  */
  virtual void render(const cShader* shader, const cRenderAtt *render_att);

  /**
	* @brief Check if this id is pickable
  *
  * @param[in] id - id of element
  * @param[in] ray_ori - origin ray
  * @param[in] ray_dest - destination ray
  * @param[out] point - collision point 
	*/
  virtual bool check_pick(const int &id, 
                          const AlgVector &ray_ori, 
                          const AlgVector &ray_dest,
                          AlgVector *point) = 0;

};

#endif // ANFLEX_INTERFACE_RENDER_SHADER_PICK_H