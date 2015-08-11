// Grid class
// Tecgraf/PUC-Rio
// Jul 2002

#ifndef SG_GRID_H
#define SG_GRID_H

#include <sg/shape.h>

class SG_API SGGrid : public SGShape
{
  int    m_ns, m_nt;
  int    m_ni;
  unsigned int *m_index;

public:
  static const char* CLASSNAME () { return "Grid"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  SGGrid (int ns, int nt);
  virtual ~SGGrid ();

  virtual int GetFaceCount ();
  virtual int GetLineCount ();

protected:
  void LoadArrayIndices ();
};

#endif

