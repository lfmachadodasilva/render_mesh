//* colorscale.h
// An active color scale (with IUP menu).
// Tecgraf/PUC-Rio
// Mar 2008

#ifndef SCI_ACOLORSCALE_IUP_H
#define SCI_ACOLORSCALE_IUP_H

#include "acolorscalelua.h"
#include <sciutils/lua/sciutilsiuplua.h>
#include <iup.h>

class SCIUTILSIUPAPI SciActiveElementColorScaleIUP : public SciActiveElementColorScaleLua
{
public:
  SciActiveElementColorScaleIUP(const char *name);
  virtual ~SciActiveElementColorScaleIUP();
protected:
  virtual void cbButton(float x, float y, int mbt, int mst, VglNotifier *ntf);
private:
  static int MenuItemCB (Ihandle *self);
  void MenuItem (const char *title);
  Ihandle *m_percentages[11];
  Ihandle *m_switch_orientation;
  Ihandle *m_switch_orientation_noalpha;
  Ihandle *m_popupmenu;
  Ihandle *m_popupmenu_noalpha;
};

#endif

