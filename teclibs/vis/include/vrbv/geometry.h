/**
*	Base class for a geometric entity.
*	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
*	date:   3-Mar-2008
*/
#ifndef VRBV_GEOMETRY_H
#define VRBV_GEOMETRY_H

#include "box.h"
#include "defines.h"
#include <vector>

namespace vrbv {

class VRBV_API Geometry
{
public:
	Geometry();

	// Client-side identifier
	void setId( int id );
	int getId() const;

	// Bounding volume
	Box& getBoundingBox();
	const Box& getBoundingBox() const;

private:
	int _id;
	Box _bbox;
};

typedef std::vector< Geometry* > GeometryVector;

} // namespace vrbv

#endif // VRBV_GEOMETRY_H
