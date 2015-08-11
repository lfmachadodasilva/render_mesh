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

#ifndef ANFLEX_INTERFACE_GAUGE_H
#define ANFLEX_INTERFACE_GAUGE_H

#include <iup.h>
#include "string"
using std::string;

class cAppGauge
{
 private:
  int num_steps, step;
  string title, text;
  Ihandle *dialog, *gauge;

  void init(void);

 public:
  cAppGauge(void) : num_steps(0), step(0), dialog(0), gauge(0) {init();}
  cAppGauge(int n) : num_steps(n), step(0), dialog(0), gauge(0) {init();}
  ~cAppGauge(void) { if(dialog) kill(); }

  Ihandle* get_gauge(void) { return gauge; }

  void set_num_steps(int n) {if(n > 0) num_steps = n;}
  void set_step(int n) {if(n >= 0 && n <= num_steps) step = n;}
  void inc_step(void) { if(step < num_steps) step++; }
  void set_title(string);
  void set_text(string);

  void show(void) { IupShowXY(dialog, IUP_CENTER, IUP_CENTER); }
  void update(void);
  void update(float) const;
  void kill(void);
};

#endif