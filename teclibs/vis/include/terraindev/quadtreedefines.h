#ifndef TERRAIN_QUADTREE_DEFINES_H
#define TERRAIN_QUADTREE_DEFINES_H

#define QUADTREE_MAX_LEVELS 16 // 8 = up to 21.845 nodes, 9 = up to 87.381 nodes

#if QUADTREE_MAX_LEVELS < 9
 #define q_index short // up to 32.767 nodes (max 8 levels)
 #define QUADTREE_MAX_NODES 32767
#elif QUADTREE_MAX_LEVELS < 17
 #define q_index long // up to 2.147.483.647 nodes (max 16 levels)
 #define QUADTREE_MAX_NODES 2147483647
#else
 #error "Unsupported number of quadtree levels requested!"
#endif

#endif // TERRAIN_QUADTREE_DEFINES_H
