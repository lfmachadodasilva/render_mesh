// Boundary faces geometry extractor (with sections and layer separation)
// fabraham@tecgraf.puc-rio.br
// Feb 2008
#ifndef TPVRES_BDRY_FACES_SECTION_H
#define TPVRES_BDRY_FACES_SECTION_H

#include "bdryfacessep.h"
#include <topsviewres/defines.h>

class TPVRES_API TpvResBdryFacesSectionGeometry : public TpvResBdryFacesSepGeometry
{
public:
  TpvResBdryFacesSectionGeometry (int num_layers);
  ~TpvResBdryFacesSectionGeometry ();
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
  void ExtractFaces ();
private:
  int m_section_i;
  int m_section_j;
  int m_section_k;
};

#endif

