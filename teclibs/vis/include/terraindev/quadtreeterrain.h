#ifndef TERRAIN_UTILS_QUADTREE_TERRAIN_H
#define TERRAIN_UTILS_QUADTREE_TERRAIN_H

#include "defines.h"
#include "typedefs.h"
#include "viewparameters.h"
#include <alg/quatern.h>
#include <alg/vector.h>

q_index quadtreenode_getmatchingtexindex (TrnQuadtreeHeight* qh, TrnQuadtreeTexture* qt, q_index hgtindex);
q_index quadtreenode_getmatchinghgtindex (TrnQuadtreeHeight* qh, TrnQuadtreeTexture* qt, q_index texindex);

bool quadtreenode_shouldbedrawn (TrnQuadtreeHeight* q, q_index n, long currFrame);
bool quadtreenode_shouldbedrawn2 (TrnQuadtreeTexture* q, q_index n, long currFrame);
bool quadtreenode_isvisible (TrnQuadtreeHeight* q, q_index n, const TrnViewParameters& view);
void quadtreenode_getneighbors (TrnQuadtreeHeight* q, q_index n, q_index* north, q_index* south, q_index* east, q_index* west, const TrnViewParameters& view);
void quadtreenode_getdrawnneighbors (TrnQuadtreeHeight* q, q_index n, q_index* north, q_index* south, q_index* east, q_index* west, const TrnViewParameters& view);
void quadtreenode_getloadedneighbors (TrnQuadtreeHeight* q, q_index n, q_index* north, q_index* south, q_index* east, q_index* west, const TrnViewParameters& view);
float aabb_distance_to_point (const float center[3],       // param:  center of aabb
                              const float length[3],       // param:  half-length of aabb sides
                              const float point[3],        // param:  point to measure distance to
                              float where[3]);             // return: aabb corner closest to the point
float aabb_distance_to_point_sqr (const float center[3],   // param:  center of aabb
                                  const float length[3],   // param:  half-length of aabb sides
                                  const float point[3],    // param:  point to measure distance to
                                  float where[3]);         // return: aabb corner closest to the point

#endif // TERRAIN_UTILS_QUADTREE_TERRAIN_H
