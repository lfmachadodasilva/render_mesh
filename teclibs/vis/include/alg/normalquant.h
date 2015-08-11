// Implements unit normal quantization
// fabraham@tecgraf.puc-rio.br
// Mar 2010
#ifndef ALG_NORMAL_QUANT_H
#define ALG_NORMAL_QUANT_H

#include "defines.h"
#include "vector.h"

/**
 * Packs unit normal 'vec' into an unsigned short value.
 */
ALG_API unsigned short AlgUnitNormalPack (const AlgVector& vec);
/**
 * Unpacks an unit normal 'vec' stored in an unsigned short value.
 */
ALG_API AlgVector AlgUnitNormalUnpack (unsigned short pvec);
/**
 * Initializes this module.
 */
ALG_API void AlgUnitNormalInit ();
/**
 * Test function.
 */
ALG_API bool AlgUnitNormalTest ();

#endif

