/**
 *	Sphere representation. f(p) = ||p - center|| - radius = 0
 *	author: Cesar Palomo <cpalomo@tecgraf.puc-rio.br>
 *	date:   27-Nov-2009
 */
#ifndef GEOMS_SPHERE_H
#define GEOMS_SPHERE_H

#include <alg/vector.h>
#include "defines.h"

namespace geoms {

class GEOMS_API Sphere
{
public:
	AlgVector center; // Center
	AlgVector radius; // Radius
};

} // namespace geoms

#endif // GEOMS_SPHERE_H
