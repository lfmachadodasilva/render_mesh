#ifndef SGTERRAIN_EDITABLE_SPLINE_FLOOR_H
#define SGTERRAIN_EDITABLE_SPLINE_FLOOR_H

#include "defines.h"
#include "qterrain.h"
#include <sgvgl/shp/editablesplinepipe.h>

/**
 * Terrain Pipe Floor class.
 *
 * Uses the Quadtree terrain as floor for the editable pipes.
 */
class SGTERRAINAPI SGTerrainPipeFloor : public SGEditableSplinePipeFloor
{
public:
  SGTerrainPipeFloor (SGQTerrain* terrain);
  virtual ~SGTerrainPipeFloor ();
  float GetHeight (float x, float z);
private:
  SGQTerrain* m_terrain;
};

#endif // SGTERRAIN_EDITABLE_SPLINE_FLOOR_H
