#ifndef TPVRES_SECTION_H
#define TPVRES_SECTION_H

#include <topsviewres/defines.h>

/**
 * Choose, in case of reservoir section i/j/k, which facet uses will be tested
 * for adjacency and which do not need.
 *
 * Returns true if the cell has any faces to be drawn, false otherwise.
 */
TPVRES_API bool tpvres_choose_section_adj_test_fus (int i,
                                                    int j,
                                                    int k,
                                                    int section_i,
                                                    int section_j,
                                                    int section_k,
                                                    int& num_no_test_adj_fu,
                                                    int no_test_adj_fu[6],
                                                    int& num_test_adj_fu,
                                                    int test_adj_fu[6]);

#endif

