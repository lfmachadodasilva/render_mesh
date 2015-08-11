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

#include "fps.h"

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cFPS::restart(void)
{
  start = clock();
  frame_counter = 0;
  elapsed_time = 0.0;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
bool cFPS::updateFPS(double &fps, double &ms)
{
  end = clock();
  elapsed_time = difftime(end, start);
  frame_counter++;

  if(elapsed_time >= 1.0e3)
  {
    fps = (double)frame_counter / (elapsed_time / 1000.0);
    ms = (elapsed_time /** 1000.0*/) / frame_counter;

    frame_counter = 0;
    start = clock();
    return true;
  }
  return false;
}