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

#ifndef ANFLEX_INTERFACE_MODEL_H
#define ANFLEX_INTERFACE_MODEL_H

#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::map;

class cObject;
class cObjectQuad;
class cRenderPick;

class cModel
{
public:
  // Objects, Line - Stinger - Bargrid ...
  vector<cObject*> m_vec_objects;
  vector<cObjectQuad*> m_vec_quads;

  // Render classes
  vector<cRenderPick*> m_vec_render_pick;
  vector<cRenderPick*> m_vec_render_pick2;

  void clear(void);
  int get_size(void) { return (int) m_vec_render_pick.size(); }
  void add_object(cObject *object);
  void add_object(cObjectQuad *object);
};

#endif