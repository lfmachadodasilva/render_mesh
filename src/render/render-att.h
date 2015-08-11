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

#ifndef ANFLEX_INTERFACE_RENDER_ATT_H
#define ANFLEX_INTERFACE_RENDER_ATT_H

// Opengl
#include "GL\glew.h"

// Lib vis
#include "vgl\camera.h"
#include "alg\matrix.h"

struct cLightAtt
{
public:
  /*
  * @brief Light position
  */
  GLfloat m_position_light[4];

  /*
  * @brief Light ambient
  */
  GLfloat m_ambient_light[4];

  /*
  * @brief Light diffuse
  */
  GLfloat m_diffuse_light[4];

  /*
  * @brief Light specular
  */
  GLfloat m_specular_light[4];

  /*
  * @brief Light As
  */
  GLfloat m_As[4];
};

class cRenderAtt
{
public:

  /*
  * @brief Model view matrix
  */
  AlgMatrix m_model_view_matrix;

  /*
  * @brief Projection matrix
  */
  AlgMatrix m_projection_matrix;

  /*
  * @brief Normal matrix
  */
  AlgMatrix m_normal_matrix;

  /*
  * @brief Viewport
  */
  int m_viewport[4];

  /*
  * @brief Light attributes
  */
  cLightAtt m_light_att;

  /*
  * @brief Constructor
  *
  * @param[in] camera - used to get render attributes
  */
  cRenderAtt(VglCamera *camera) { set(camera); }
  cRenderAtt(void) { }

  /*
  * @brief Set attributes
  *
  * @param[in] camera - used to get render attributes
  */
  void set(VglCamera *camera) 
  {
    m_model_view_matrix = camera->GetModelview();

    m_projection_matrix = camera->GetProjectionMatrix();

    m_normal_matrix = m_model_view_matrix;
    m_normal_matrix.PrepareScaleToTransformNormals();

    camera->GetUpdatedPosition(&m_light_att.m_position_light[0], 
                               &m_light_att.m_position_light[1], 
                               &m_light_att.m_position_light[2]);
    m_light_att.m_position_light[3] = 1.0;
  }
};


#endif // ANFLEX_INTERFACE_RENDER_ATT_H