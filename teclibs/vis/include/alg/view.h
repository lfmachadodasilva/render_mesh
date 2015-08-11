#ifndef ALG_VIEW_H
#define ALG_VIEW_H

#include "matrix.h"

/**
 * Computes the observer position given the modelview matrix 'mv'.
 * If a modelling transform is present, the coordinate lies on this
 * coordinate system.
 */
AlgVector AlgCalcObsPosition (const AlgMatrix &mv);

#endif

