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

#ifndef ANFLEX_INTERFACE_OBJECT_FATHER_H
#define ANFLEX_INTERFACE_OBJECT_FATHER_H

#include <string>
using std::string;

class cObjectFather
{
private:

  int m_id;
  string m_label;

public:

  cObjectFather(void) {}
  cObjectFather(int id, string label) { m_id = id; m_label = label; }

  /*
  * @brief Get id
  *
  * @return id
  */
  int get_id(void) { return m_id; }
  /*
  * @brief Set id
  *
  * @param[in] id
  */
  void set_id(int id) { m_id = id; } 

  /*
  * @brief Get label
  *
  * @return label
  */
  string get_label(void) { return m_label; }
  /*
  * @brief Set label
  *
  * @param[in] label
  */
  void set_label(string label) { m_label = label; }

  string new_label(void) { return m_label; }
};

#endif // ANFLEX_INTERFACE_OBJECT_FATHER_H