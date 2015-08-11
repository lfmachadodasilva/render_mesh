#ifndef SG_BVTREE_H
#define SG_BVTREE_H

#ifdef _WIN32
# ifdef SGBVTREE_DLL
#  define SGBVTREEAPI __declspec(dllexport)
# else
#  define SGBVTREEAPI
# endif
#else
# define SGBVTREEAPI
#endif

#include <ds/hash.h>
#include <bvtree/bvtree.h>

class SGShape;
typedef DsHash<SGShape*,bv_t*> SGShapeBoundingVolumes;

#include <sgbvtree/bvtreebuilder.h>
#include <sgbvtree/strat/accel/frustum.h>
#include <sgbvtree/strat/accel/slfrustum.h>
#include <sgbvtree/strat/render/bvrender.h>
#include <sgbvtree/strat/render/slrender.h>

#endif
