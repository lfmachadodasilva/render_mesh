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

#ifndef ANFLEX_INTERFACE_FPS_H
#define ANFLEX_INTERFACE_FPS_H

#include <time.h>

class cFPS
{
private:
 time_t start;
 time_t end;
 int frame_counter;
 double elapsed_time;

public:

 cFPS() : frame_counter(0), elapsed_time(0.0) {}
 ~cFPS() {}

 void restart(void);
 bool updateFPS(double& fps, double& ms);
};

#endif // ANFLEX_INTERFACE_FPS_H