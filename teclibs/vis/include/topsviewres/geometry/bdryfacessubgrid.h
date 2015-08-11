// Boundary faces geometry extractor (with subgrid definition)
// fabraham@tecgraf.puc-rio.br
// Nov 2011
#ifndef TPVRES_BDRY_FACES_SUBGRID_H
#define TPVRES_BDRY_FACES_SUBGRID_H

#include "bdryfacessimple.h"
#include <topsviewres/defines.h>

class TPVRES_API TpvResBdryFacesSubGridGeometry : public TpvResBdryFacesSimpleGeometry
{
public:
  TpvResBdryFacesSubGridGeometry ();
  ~TpvResBdryFacesSubGridGeometry ();
  void SetSubGrid (int imin,
                   int imax,
                   int jmin,
                   int jmax,
                   int kmin,
                   int kmax);
private:
  bool ChooseSubGridAdjTestFus (int i,
                                int j,
                                int k,
                                int& num_no_test_adj_fu,
                                int no_test_adj_fu[6],
                                int& num_test_adj_fu,
                                int test_adj_fu[6]);
  // virtual methods
  void ExtractFaces ();
private:
  int m_imin; // sub grid range (inclusive)
  int m_imax;
  int m_jmin;
  int m_jmax;
  int m_kmin;
  int m_kmax;
};

#endif

