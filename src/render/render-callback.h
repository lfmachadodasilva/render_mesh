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

#ifndef ANFLEX_INTERFACE_RENDER_CALLBACK_H
#define ANFLEX_INTERFACE_RENDER_CALLBACK_H

#include <vector>
using std::vector;

// Lib vis
#include "vrbv\node.h"
#include "vrbv\scenedata.h"
#include "vrbv\treebuilder.h"
#include "vdlib\frustumculler.h"
#include "vdlib\occlusionculler.h"
#include "vgl\camera.h"

// Local
#include "render-att.h"
#include "shader.h"
#include "render-pick.h"

class cRenderCallback : public vdlib::IFrustumCallback, public vdlib::IOcclusionCallback
{
private:
  
  /*
  * @brief Boolean to control if will render or only process vertex in the frustum
  */
  bool m_render;

  /*
  * @brief Vector of selected index 
  */
  vector<int> m_vec_selected;

  /*
  * @brief List of objects. Anflex will be the model.
  */
  cRenderPick **m_vec_objects;

  /*
  * @brief Shader
  */
  const cShader *m_shader;

  /*
  * @brief Render attributes
  */
  const cRenderAtt *m_render_att;

public:

  /*
  * @brief Constructor
  */
  cRenderCallback() : m_render(true) { }

  /*
  * @brief Destructor
  */
  ~cRenderCallback() {}

  /*
  * @brief Set shader
  */
  void set_shader(const cShader *shader) { m_shader = shader; }

  /*
  * @brief Set render attributes
  */
  void set_render_att(const cRenderAtt *render_att) { m_render_att = render_att; }

  /*
  * @brief Prepare to pick
  *
  * Prepare the class to only pick, to process vertex in different frustum
  */
  void set_callbalk_to_pick(void) { m_vec_selected.clear(); m_render = false; }

  /*
  * @brief Prepare to render
  *
  * Prepare the class to render
  */
  void set_callbalk_to_render(void) { m_render = true; }

  /*
  * @brief Get selected
  *
  * @return index of selected 
  */
  vector<int> get_selected(void) { return m_vec_selected; }

  /*
  * @brief Get selected
  *
  * @param[in] objects - vector with objects
  */
  void set_model(cRenderPick **objects) { m_vec_objects = objects; }

  // Frustum culling only
  virtual bool inside(vrbv::Node *node)
  {
    if(m_render)
    {
      // render object
      draw(node);
    }
    else
    {
      // store geometries as selected object
      const vrbv::GeometryVector& geometries = node->getGeometries();
      for( unsigned int i = 0; i < geometries.size(); ++i )
        m_vec_selected.push_back(geometries[i]->getId());
    }

    return true;
  }

  // Occlusion culling
  //virtual void draw(const vdlib::IOcclusionCallback::NodeBatch &nodebatch)
  //{
  //  vdlib::IOcclusionCallback::NodeIterator it;
  //  for(it = nodebatch.begin(); it != nodebatch.end(); ++it)
  //    draw(*it);
  //}

  virtual void draw(const vrbv::Node *node)
  {
    const vrbv::GeometryVector& geometries = node->getGeometries();
    for(unsigned int i = 0; i < geometries.size(); ++i)
      m_vec_objects[geometries[i]->getId()]->render(m_shader, m_render_att);
  }

  // Occlusion culling + frustum culling
  //virtual bool isValid(vrbv::Node *node)
  //{
  //  if(m_frustum_culler != NULL)
  //    return m_frustum_culler->contains(node);
  //  else
  //    return true;
  //}

  // If valid pointer, use frustum culling with occlusion culling
  // Else, disable VFC with occlusion
  //void setFrustumCuller(vdlib::FrustumCuller *frustum)
  //{
  //  m_frustum_culler = frustum;
  //}
  //
  //virtual bool isDrawable(vrbv::Node* node)
  //{
  //  return true;
  //}

};

struct sAccelerationRender
{
  cRenderCallback        m_render_callback;
  vdlib::FrustumCuller   m_frustum_culler;
  vdlib::OcclusionCuller m_occlusion_culler;
  vrbv::Node             *m_scene_root;

  sAccelerationRender(void) : m_scene_root(NULL)
  {}
};

#endif