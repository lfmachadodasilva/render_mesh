// Boundary faces geometry extractor (with transparency, sections and layer separation)
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_TRANSP_SECTION_H
#define TPVRES_TRANSP_SECTION_H

#include "transpsep.h"
#include <topsviewres/defines.h>

class TPVRES_API TpvResTranspSectionGeometry : public TpvResTranspSepGeometry
{
public:
  TpvResTranspSectionGeometry (int num_layers);
  ~TpvResTranspSectionGeometry ();
  void SetSection (int i, int j, int k);
protected:
  bool HasSection () const
  {
    return
      m_section_i != -1 ||
      m_section_j != -1 ||
      m_section_k != -1;
  }
  bool IsOnSection (int i, int j, int k) const
  {
    return
      (m_section_i == -1 || m_section_i == i) &&
      (m_section_j == -1 || m_section_j == j) &&
      (m_section_k == -1 || m_section_k == k);
  }
private:
  // virtual methods
  void CollectModelElements();
  void ExtractOpaqueFaces ();
  void ExtractTranspFaces ();
private:
  int m_section_i;
  int m_section_j;
  int m_section_k;
};

#endif

