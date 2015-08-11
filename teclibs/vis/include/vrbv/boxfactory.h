/**
*	Factory pattern for building different types of boxes.
*	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
*	date:   3-Mar-2008
*/
#ifndef VRBV_BOXFACTORY_H
#define VRBV_BOXFACTORY_H

#include "common.h"
#include "box.h"
#include "defines.h"

namespace vrbv {

class VRBV_API BoxFactory
{
public:
	enum BoxType
	{
		Type_Aabb,
		Type_Obb
	};

	// Set default box type to be built
	static void setDefaultBoxType( BoxType type );

	// Create box according to default type
	static void createBox( Box& result, const float* vertices, int size );

	// Create box according to default type, using pointers to vertices.
	static void createBox( Box& result, int geominfo_id, GeomInfoCallback* cb );
	static void createBox( Box& result, int* geominfo_ids, int geominfo_ids_count, GeomInfoCallback* cb );

	// Create box of a specific type
	static void createBox( Box& result, const float* vertices, int size, BoxType BoxType );

	// Create box of a specific type, using pointers to vertices.
	static void createBox( Box& result, int geominfo_id, GeomInfoCallback* cb, BoxType BoxType );

	// Create box of a specific type, using pointers to vertices.
	static void createBox( Box& result, int* geominfo_ids, int geominfo_count, GeomInfoCallback* cb, BoxType BoxType );

private:
	static BoxType s_defaultType;
};

} // namespace vrbv

#endif // VRBV_BOXFACTORY_H
