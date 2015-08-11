#ifndef SG_UTILS_H
#define SG_UTILS_H

#include "defines.h"

#define SG_MORPH_LINEAR 0
#define SG_MORPH_EASE   1
#define SG_MORPH_MAX    2

class UtlWriter;
class SGNode;
class SGScene;
class SGMeshWriter;

/**
 * Writes the scene's description lua file using writer 'writer' and meshwriter 'meshwriter'.
 */
SG_API void sg_writeluascenefile (SGScene* scene, UtlWriter* writer, SGMeshWriter *meshwriter);
/**
 * Writes an hierarchy's description lua file using writer 'writer' and meshwriter 'meshwriter'.
 */
SG_API void sg_writeluahierarchyfile (SGNode* node, UtlWriter* writer, SGMeshWriter *meshwriter);
/**
 * Duplicates a hierarchy, sharing all attributes (thus improving performance and
 * reducing memory usage).
 */
SG_API SGNode* sg_duplicate (SGNode *node);
/**
 * Flattens an hierarchy.
 * There can be no nodes of type SGWorldSpace/SGEyeSpace/SGClipSpace below 'node'.
 * There can be no shares shapes below 'node'.
 * Returns the success in flattening the hierarchy.
 */
SG_API bool sg_flatten (SGNode *node);
/**
 * Specifies if vertex and index arrays should be freed from
 * main memory after transferred to the video memory. Default=false.
 * Only used in static vertex and index arrays.
 */
SG_API void sg_setfreeaftervbo (bool freeaftervbo);
/**
 * Specifies if VBOs (vertex buffer objects) must be used automatically. Default=false.
 */
SG_API void sg_setautovbo (bool autovbo);
/**
 * Obtains the auto VBO flag.
 */
SG_API bool sg_getautovbo ();
SG_API void sg_setstaticdefault (bool f);
SG_API bool sg_getstaticdefault ();
/**
 * Interpolates between two shapes. dest_shape is an interpolated Shape of src_shp1 and src_shp2.
 */
SG_API void sg_morph(SGShape* src_shp_1, SGShape* src_shp_2, SGShape* dest_shp, float factor, int interpolate_type = SG_MORPH_LINEAR);

#endif

