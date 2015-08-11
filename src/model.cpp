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

// Local lib
#include "model.h"
#include "object.h"
#include "object-quad.h"

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cModel::add_object(cObject *object)
{
  m_vec_objects.push_back(object);

  m_vec_render_pick.push_back((cRenderPick*)object);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cModel::add_object(cObjectQuad *quad)
{
  m_vec_quads.push_back(quad);

  m_vec_render_pick.push_back((cRenderPick*)quad);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cModel::clear(void)
{
  for(int i = 0; i < (int) m_vec_objects.size(); i++)
    delete m_vec_objects[i];

  for(int i = 0; i < (int) m_vec_quads.size(); i++)
    delete m_vec_quads[i];

  m_vec_objects.clear();
  m_vec_quads.clear();
  m_vec_render_pick.clear();
}