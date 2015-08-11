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

#include <iup.h>
#include "gauge.h"

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cAppGauge :: set_title(string s)
{
 if(dialog)
  IupSetAttribute(dialog, IUP_TITLE, (char*)s.c_str());
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cAppGauge :: set_text(string s)
{
 if(gauge)
  IupSetAttribute(gauge, IUP_TEXT, (char*)s.c_str());
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cAppGauge :: init(void)
{
  gauge = IupSetAtt(NULL, IupProgressBar(),
    IUP_TEXT, text.c_str(),
    NULL);

  dialog = IupSetAtt(NULL, 
    IupDialog( IupVbox(gauge, NULL) ),
    IUP_ICON, "",
    IUP_EXPAND, IUP_NO,
    IUP_TITLE, "Application Gauge",
    IUP_ICON, "IUP_Tecgraf",
    IUP_MINBOX, IUP_NO,
    IUP_MENUBOX, IUP_NO,
    IUP_MAXBOX, IUP_NO,
  NULL);

  IupMap(dialog);
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cAppGauge :: update(void)
{
 char att[20];
 inc_step();
 sprintf(att, "%.3f", (float)step / (float)num_steps);
 if(gauge)
  IupStoreAttribute(gauge, IUP_VALUE, att);
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cAppGauge :: update(float val) const
{
 char att[20];
 sprintf(att, "%.3f", val);
 if(gauge)
  IupStoreAttribute(gauge, IUP_VALUE, att);
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void cAppGauge :: kill(void)
{
 if(dialog)
 {
  IupDestroy(dialog);
  dialog = 0;
  gauge = 0;
 }
}