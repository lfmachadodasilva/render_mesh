/**
 *	Main API to store geometric information from client.
 *	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
 *	date:   3-Mar-2008
 *	author: Cesar Palomo <cpalomo@tecgraf.puc-rio.br>
 *	date:   11-Jun-2010
*/
#ifndef VRBV_SCENEDATA_H
#define VRBV_SCENEDATA_H

#include "rawnode.h"
#include "defines.h"

namespace vrbv {

class VRBV_API SceneData
{
public:

	/**
	 * Constructor.
	 * @param store_geometry when true, actual geometry will be added to this class.
	 * Otherwise, pointers to vertices will be used.
	 */
	SceneData(bool store_geometry = true);
	/**
	 * Destructor.
   */
  virtual ~SceneData();

	// Set callback to read vertices' coordinates.
	void setGetCoordsCB( GeomInfoCallback* cb );

	// Get callback to read vertices' coordinates.
	GeomInfoCallback* getGetCoordsCB();

	// Create a new scene node to store all geometries
	void beginScene();

	// Start sending information for a new geometry
	// Takes ownership of geometry pointer and store it
	void beginGeometry( Geometry* geometry );

	// Send geometric information for current geometry
	void addVertices( const float*  vertices, int size );
	void addVertices( const double* vertices, int size );

	// Convenience method to apply given 4x4 transformation to all vertices added thus far
	void transformVertices( const float* matrix );

	// Get vertices for current geometry thus far
	const float* getCurrentVertices() const;

	// Set vertices count for current GeometryInfo being edited.
	// NOTE: should be called between beginGeometry and endGeometry 
	// when storeGeometry==false.
	void setCurGeomVerticesCount( int vertex_count );

	// End current geometry, create bounding box
	void endGeometry();

	// Called once at the end, when all geometries have been added
	// At this point, given sceneRoot is ready for hierarchy construction
	void endScene();

	// Used by TreeBuilder to get initial scene node with all geometries
	RawNode* getSceneNode();

private:
	RawNode* _sceneRoot;
	bool _store_geometry;
	GeomInfoCallback* _getCoords_cb;
};

} // namespace vrbv

#endif // VRBV_SCENEDATA_H
