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

#ifndef ANFLEX_INTERFACE_RENDER_FEMESH_PTS_H
#define ANFLEX_INTERFACE_RENDER_FEMESH_PTS_H

#include "render-pick.h"

class cRenderFeMeshPts : public cRenderPick
{
private:

  GLfloat *v_cpy;
  
protected:  

  void create(void);

  /**
	* @brief Pick element
  *
  * @param[in] insert - insert or remove pick
  * @param[in] is_select - select or focus pick
  * @param[in] id - element id
	*/
  virtual void change_element_pick(const bool insert,  const bool is_select, const int id) {}

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
                          AlgVector *point) { return false; }

public:

  cRenderFeMeshPts(GLfloat *vertex, int &size, AlgMatrix &transf_matrix);

  virtual void create_array(cAppGauge *gauge);
  virtual void calc_normals(cAppGauge *gauge);
  virtual void create_scene(void) { /* do anything */ }
};

#endif