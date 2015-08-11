#ifndef TERRAIN_DEFINES_H
#define TERRAIN_DEFINES_H

#ifndef TERRAINDEV_DLL
# ifndef TEC_DLL
#  define TERRAINAPI
# else
#  define TERRAINAPI __declspec(dllimport)
# endif
#else
# define TERRAINAPI __declspec(dllexport)
#endif

#include "quadtreedefines.h"

#include <GL/glew.h>

// Mathematical defines

#define TRN_PI        3.14159265358979f
#define TRN_LN2       0.693147180559945f
#define TRN_LN2I      1.44269504088896f
#define TRN_DEG2RAD   0.0174532925199433f
#define TRN_RAD2DEG  57.2957795130823f

#define DEG2RAD(x)      (TRN_DEG2RAD * (x))
#define RAD2DEG(x)      (TRN_RAD2DEG * (x))
#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#define MAX(a, b)       ((a) > (b) ? (a) : (b))
#define ISPOW2(x)       (!((x) & ((x) - 1)) && !!(x))
#define SQR(x)          ((x) * (x))
#define ABS(x)          (((x) < 0) ? (-(x)) : (x))
#define SIGN(x)         (((x) < 0) ? (-1) : (1))

#define DISTANCE_SQR(p, q)            (SQR((p)->x-(q)->x) + SQR((p)->y-(q)->y) + SQR((p)->z-(q)->z))
#define DISTANCE_SQR2(p, qx, qy, qz)  (SQR((p)->x-(qx)) + SQR((p)->y-(qy)) + SQR((p)->z-(qz)))
#define DISTANCE_SQR3(p, qx, qy, qz)  (SQR((p)->x-(qx)) + SQR((p)->height-(qy)) + SQR((p)->z-(qz)))
#define DISTANCE(p, q)                (sqrtf(DISTANCE_SQR(p, q)))

#define CROSS_PRODUCT(x, y, z)\
  ((void)((x)[0] = (y)[1]*(z)[2] - (y)[2]*(z)[1],\
          (x)[1] = (y)[2]*(z)[0] - (y)[0]*(z)[2],\
          (x)[2] = (y)[0]*(z)[1] - (y)[1]*(z)[0]))

#define ADD(x, y) ((void)((x)[0] += (y)[0], (x)[1] += (y)[1], (x)[2] += (y)[2]))
#define SUB(x, y) ((void)((x)[0] -= (y)[0], (x)[1] -= (y)[1], (x)[2] -= (y)[2]))

// Terrain defines

#define RECENTLY_USED_FRAME_COUNT 100
#define TILEINFO_FILENAME_MAXLEN  100
#define MIN_LEVEL 2

// Debug messages (hide = 0, show = 1)

static const int TRN_DEBUG_SERVICES       = 0; // Service execution (tile management, view prediction, rendering)
static const int TRN_DEBUG_TILEMANAGER    = 0; // Tile management service internal execution
static const int TRN_DEBUG_PREDICTOR      = 0; // View predictor service internal execution
static const int TRN_DEBUG_RENDERER       = 0; // Renderer service internal execution
static const int TRN_DEBUG_DEADLOCK       = 0; // Potentially deadlocking operations
static const int TRN_DEBUG_TILE_LOAD      = 0; // Tile loading and unloading
static const int TRN_DEBUG_TILE_RENDER    = 0; // Tile rendering
static const int TRN_DEBUG_PREPROCESS     = 0; // Preprocessing
static const int TRN_DEBUG_HANDLERS       = 0; // Camera handlers
static const int TRN_DEBUG_VIEWPARAMETERS = 0; // View parameters

// Selection objects

enum TrnObjectType
{
  TRN_OBJECT_NONE    = 0,
  TRN_OBJECT_TERRAIN = 1,
  TRN_OBJECT_BORDER  = 2,
  TRN_OBJECT_GROUND  = 3,
  TRN_OBJECT_CAMERA  = 4,
};

// View planes

enum TrnViewPlanes
{
  TRN_VIEW_PLANE_NEAR   = 0,
  TRN_VIEW_PLANE_FAR    = 1,
  TRN_VIEW_PLANE_LEFT   = 2,
  TRN_VIEW_PLANE_RIGHT  = 3,
  TRN_VIEW_PLANE_BOTTOM = 4,
  TRN_VIEW_PLANE_TOP    = 5,
};

enum TrnViewPlaneMask
{
  TRN_PLANE_MASK_NONE   = 0x0000u,
  TRN_PLANE_MASK_NEAR   = 0x0001u,
  TRN_PLANE_MASK_FAR    = 0x0002u,
  TRN_PLANE_MASK_LEFT   = 0x0004u,
  TRN_PLANE_MASK_RIGHT  = 0x0008u,
  TRN_PLANE_MASK_BOTTOM = 0x0010u,
  TRN_PLANE_MASK_TOP    = 0x0020u,
  TRN_PLANE_MASK_ALL    = 0x003Fu,
};

// Directions

enum TrnDirection
{
  TRN_DIRECTION_SOUTHWEST = 1,
  TRN_DIRECTION_SOUTH     = 2,
  TRN_DIRECTION_SOUTHEAST = 3,
  TRN_DIRECTION_WEST      = 4,
  TRN_DIRECTION_CENTER    = 5,
  TRN_DIRECTION_EAST      = 6,
  TRN_DIRECTION_NORTHWEST = 7,
  TRN_DIRECTION_NORTH     = 8,
  TRN_DIRECTION_NORTHEAST = 9,
};

// Files

enum TrnFileLocation
{
  TRN_FILE_LOCAL = 0,
  TRN_FILE_FTC = 1,
};

enum TrnFileAccess
{
  TRN_FILE_READ = 0,
  TRN_FILE_WRITE = 1,
  TRN_FILE_APPEND = 2,
};

// Height tiles

enum TrnTileHeightType
{
  TRN_HEIGHT_TILE_BASIC,
  TRN_HEIGHT_TILE_LIND_STATIC,
  TRN_HEIGHT_TILE_LIND_DYNAMIC,
  TRN_HEIGHT_TILE_SHADER,
};

enum TrnTileHeightBounding
{
  TRN_HEIGHT_BOUNDING_SPHERE,
  TRN_HEIGHT_BOUNDING_AABOX,
};

enum TrnTileHeightDataType
{
  TRN_HEIGHT_DATA_SHORT,
  TRN_HEIGHT_DATA_INT,
  TRN_HEIGHT_DATA_FLOAT,
  TRN_HEIGHT_DATA_DOUBLE,
};

enum TrnTileTextureDataType
{
  TRN_TEXTURE_DATA_BYTE,
  TRN_TEXTURE_DATA_UBYTE,
  TRN_TEXTURE_DATA_SHORT,
  TRN_TEXTURE_DATA_USHORT,
  TRN_TEXTURE_DATA_INT,
  TRN_TEXTURE_DATA_UINT,
  TRN_TEXTURE_DATA_FLOAT,
};

// Standard Defines

#ifndef NULL
# ifdef __cplusplus
#  define NULL    0
# else
#  define NULL    ((void *)0)
# endif
#endif

#endif // TERRAIN_DEFINES_H
