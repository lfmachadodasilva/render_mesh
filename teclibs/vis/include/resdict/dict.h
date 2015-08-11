// Reservoir property dictionary
// fabraham@tecgraf.puc-rio.br
// rodesp@tecgraf.puc-rio.br
// Oct 2011
#ifndef RESDICT_H
#define RESDICT_H

#include <ds/array.h>

/**
 * Obtains the property names for a given property identifier.
 *
 * Ex: prop_id: "porosity" -> an array containing 3 strings: "POR", "PORO" and "PHI".
 *
 * Valid property ids:
 *   porosity
 *   permi
 *   permj
 *   permk
 *   volmod
 *   netgross
 *   oil saturation
 */
const DsArray<char*>* ResDictGetNames (const char* prop_id);
/**
 * Obtains, given a property names, its property id, if existing.
 * Returns NULL in case it is not found.
 */
const char* ResDictGetPropertyID (const char* propname);

#endif

