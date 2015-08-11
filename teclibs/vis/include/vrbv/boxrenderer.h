/**
*	An oriented box renderer.
*	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
*	author: Vitor Barata <vbarata@tecgraf.puc-rio.br>
*	date:   3-Mar-2008
*/
#ifndef VRBV_BOXRENDERER_H
#define VRBV_BOXRENDERER_H

#include <vrbv/common.h>

namespace vrbv {

class BoxRenderer
{
public:
  // Renders an oriented bounding box
	static void renderBoundingBox( const Box& box );
};

} // namespace vrbv

#endif // VRBV_BOXRENDERER_H
