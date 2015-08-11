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

#ifndef ANFLEX_INTERFACE_PICK_H
#define ANFLEX_INTERFACE_PICK_H

#include <set>
using namespace std;

#include "alg\vector.h"

class cPick
{
public:

  enum eObjectType { OBJECT, QUAD, NONE };

  enum ePickType{ NO_PICK, PICK_BY_OBJECT, PICK_BY_ELEMET }; 

  /**
	* @brief Pick type - NO_PICK, PICK_BY_OBJECT, PICK_BY_ELEMET
	*/
  static ePickType m_pick_type;

protected:

  /**
	* @brief object type - OBJECT, QUAD, NONE
	*/
  eObjectType m_object_type;

  bool m_has_focus, m_has_selected;

  /**
	* @brief Element focus id
	*/
  int m_focus;

  /**
	* @brief Set of select elements
	*/
  set<int> m_set_selected;

  /**
	* @brief Array of select element. Used only to send to shader
	*/
  int *m_vec_selec;
  
  /**
	* @brief Constructor
	*/
  cPick(void) : 
    m_object_type(NONE), 
    m_has_focus(false),
    m_has_selected(false),
    m_focus(-1)
  {
    m_vec_selec = new int[50];

    for(int i = 0; i < 50; i++)
      m_vec_selec[i] = -1;
  }

  /**
	* @brief Constructor
	*/
  cPick(eObjectType type) : 
    m_object_type(type), 
    m_has_focus(false),
    m_has_selected(false),
    m_focus(-1)
  {
    m_vec_selec = new int[50];

    for(int i = 0; i < 50; i++)
      m_vec_selec[i] = -1;
  }

public:

  /**
	* @brief Get object type
  *
  * @return object type - OBJECT, QUAD, NONE
	*/
  int get_object_type(void) { return m_object_type; }

#pragma region FOCUS
  void set_focus(bool focus) { m_has_focus = focus; }
  bool is_focus(void) { return m_has_focus; }
  void set_focus(int id) { m_focus = id; } 
  int get_focus(void) { return m_focus; }

  void focus_object(void) { cPick::set_focus(true); cPick::set_focus(-1); }
  void unfocus_object(void) { cPick::set_focus(false); cPick::set_focus(-1); }

  void focus_element(int id);
  void unfocus_element(void);

  /**
	* @brief Pick element
  *
  * @param[in] insert - insert or remove pick
  * @param[in] is_select - select or focus pick
  * @param[in] id - element id
	*/
  virtual void change_element_pick(const bool insert, // insert or remove pick
                                   const bool is_select, // select or focus pick
                                   const int id) = 0; // 
#pragma endregion

#pragma region SELECTED
  void set_selected(bool selected) { m_has_selected = selected; }
  void add_selected(int id) { m_set_selected.insert(id); }
  bool is_selected(int id) { return (m_set_selected.find(id) != m_set_selected.end()); }
  set<int> get_selected(void) { return m_set_selected; }
  bool is_selected(void) { return m_has_selected; }
  void remove_selected(int id) { if(is_selected(id)) m_set_selected.erase(id); }
  void remove_all_selected(void) { m_set_selected.clear(); cPick::m_vec_selec[0] = 0; }

  void select_object(void) { cPick::set_selected(true); }
  void unselect_object(void) { cPick::set_selected(false); }

  void select_element(int id);
  void unselect_element(int id);

#pragma endregion

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

#endif // ANFLEX_INTERFACE_RENDER_PICK_H