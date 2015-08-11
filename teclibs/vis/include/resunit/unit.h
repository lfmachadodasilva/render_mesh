#ifndef RES_UNIT_BASE_H
#define RES_UNIT_BASE_H

/**
 * Obtains, given an input unit and an output unit, the multiplication and
 * addition factors that should be used to convert a value:
 *
 * Vout = mult*Vin + add
 *
 * Ex: if in == C and out == K, mult = 1.8 and add = 32:
 *
 * 100 C = 100*1.8 + 32 = 212 K
 *   0 C =   0*1.8 + 32 =  32 K
 *
 * Returns true if conversion data was found for 'in' and 'out',
 * false otherwise.
 */
bool ResUnitFindConversionFactors (const char* in, const char* out, double* o_factor_mult, double* o_factor_add);
const char* ResUnitTranslate (const char *unit_in);
#endif

