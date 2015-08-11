// ------------------------------------------------------------------------------------------------- 
// Anflex Project -- Tecgraf/PUC-Rio  CENPES/Petrobras 
// www.tecgraf.puc-rio.br 
// 
// Created by lfmachado in April/2011.
// 
// $URL: $ 
// $Revision: $ 
// $Date: $ 
// 
// $LastChangedBy: $ 
// -------------------------------------------------------------------------------------------------

#ifndef ANFLEX_INTERFACE_OBJECT_H
#define ANFLEX_INTERFACE_OBJECT_H

#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::map;

#include "vdlib\frustumculler.h"
#include "vdlib\occlusionculler.h"

#include "canvas\box.h"
#include "render\render-pick.h"

// Lib im
#include "im.h"
#include "im_image.h"

// Library project
#include "gauge.h"
#include "object-father.h"

class cAppearance;
class cRenderObjectAtt;
struct sRenderAtt;

class cObject : public cRenderPick, public cObjectFather
{
private:

  bool m_pick_object;
  
  // bounding box
  bool m_render_bbox; 

  int m_index_selected;

  // read file
  void read_file(string filename, cAppGauge *gauge);
  void calc_normals(cAppGauge *gauge);
  void create_array(cAppGauge *gauge);
  void read_texture(void);
  void create_scene(void);

  void m_render_shader_fe_mesh(cRender *att, 
                               const cShader *shader, 
                               const cRenderAtt *render_att);

  /**
	* @brief Pick element
  *
  * @param[in] insert - insert or remove pick
  * @param[in] is_select - select or focus pick
  * @param[in] id - element id
	*/
  void change_element_pick(const bool change, const bool is_select, const int id);

 public:

  /*
  * @brief Constructor
  */
  cObject(void);

  /*
  * @brief Destructor
  */
  ~cObject(void) { }

  void create(string filename, cAppGauge *gauge);

  /**
	* @brief Check if this id is pickable
  *
  * @param[in] id - id of element
  * @param[in] ray_ori - origin ray
  * @param[in] ray_dest - destination ray
  * @param[out] point - collision point 
	*/
  bool check_pick(const int &id, 
                  const AlgVector &ray_ori, 
                  const AlgVector &ray_dest,
                  AlgVector *point);

  void add_render_att_fe_mesh_quad(bool enable, cShader *shader);

  void add_render_att_fe_mesh_pts(bool enable, cShader *shader);

  /*
  * @brief Main render
  *
  * @param[in] shader
  * @param[in] render attribute
  */
  void render(const cShader *shader, const cRenderAtt *render_att);

};

#endif
