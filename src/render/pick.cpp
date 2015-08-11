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
 // ------------------------------------------------------------------------------------------------

 #include "pick.h"

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cPick::focus_element(int id)
{
  if(id < 0)
    return;

  cPick::set_focus(true);
  cPick::set_focus(id);

  change_element_pick(true, false, cPick::get_focus());
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cPick::unfocus_element(void)
{
  change_element_pick(false, false, cPick::get_focus());

  cPick::set_focus(false);
  cPick::set_focus(-1);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cPick::select_element(int id)
{
  if(id < 0)
    return;

  cPick::set_selected(true);
  cPick::add_selected(id);

  change_element_pick(true, true, id);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cPick::unselect_element(int id)
{
  change_element_pick(false, true, id);

  cPick::set_selected(false);
  cPick::remove_selected(id);
}