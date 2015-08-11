#ifndef RES_DEFINES_H
#define RES_DEFINES_H

#ifndef GPOS_DLL
# ifndef TEC_DLL
#  define RES_API
#  define RESH_API
# else
#  define RES_API __declspec(dllimport)
#  define RESH_API __declspec(dllexport)
# endif
#else
# define RES_API __declspec(dllexport)
# define RESH_API __declspec(dllexport)
#endif

/**
 * Operation profile callback type.
 * Usually used to specify the type of operation.
 * This type will define which sub-operations must be
 * completed in order to finish the operation.
 * These sub-operations are called 'sections'.
 */
typedef void (*SetOpenProfileCB)(const char *name, void* data);
/**
 * Section progress update callback type.
 * Updates the progress of the current profile's section named 'section'.
 * 'progress' is a number between 0 and 1, where 0 means "section 'section'
 * is 0% completed" and 1 means "section 'section' is 100% completed".
 */
typedef void (*UpdateSectionProgressCB)(const char *section, float p, void* data);

#define RES_NULL_VALUE 97654321.0f
/**
 * Returns, given the indices 'i', 'j' and 'k' and grid dimensions
 * 'ni', 'nj' and 'nk', a linear index.
 * This is similar to:
 *
 * index = 0
 * for k=1,nk
 *   for j=1,nj
 *     for i=1,ni
 *       index++
 */
#define RES_LINEAR_INDEX(i,j,k,ni,nj,nk) ((((k)*(nj))+(j))*(ni)+(i))

enum ResWellType {
  RES_WELL_PRODUCER = 0,
  RES_WELL_INJECTOR,
  RES_WELL_UNDEFINED,
};

/**
 * Value type for properties.
 */
enum ResValueType {
  RES_TYPE_INTEGER = 0,
  RES_TYPE_REAL,
  RES_TYPE_MAX,
};

/**
 * Grid refinement options.
 */
enum ResRefinementType {
  // refines a range of cells (only valid for the root grid)
  RES_REFINEMENT_RANGE=0,
  // refines a cell (valid on all refinement levels)
  RES_REFINEMENT_CELL,
  RES_REFINEMENT_MAX,
};

/**
 * Returns, given an index 'index' and grid dimensions 'ni', 'nj' and 'nk,
 * the 'i', 'j' and 'k' coordinates of a cell.
 * This function is the inverse of RES_LINEAR_INDEX.
 */
inline void ResReverseIndex (int index, int ni, int nj, int nk, int* i, int* j, int* k);
/**
 * Same as above, but faster (above method computed ni*nj. Useful if this value can be reused among multiple calls.
 */
inline void ResReverseIndex (int index, int ni, int nj, int nk, int ninj, int* i, int* j, int* k);
/**
 * Returns, given an index 'index' and grid dimension 'ni',
 * the 'i' coordinate of a cell.
 */
inline int ResReverseIndexI (int index, int ni);
/**
 * Returns, given an index 'index' and grid dimensions 'ni', 'nj',
 * the 'j' coordinate of a cell.
 */
inline int ResReverseIndexJ (int index, int ni, int nj);
inline int ResReverseIndexJ (int index, int ni, int nj, int ninj);
/**
 * Returns, given an index 'index' and grid dimensions 'ni', 'nj',
 * the 'k' coordinate of a cell.
 */
inline int ResReverseIndexK (int index, int ni, int nj);
inline int ResReverseIndexK (int index, int ninj);
/**
 * Obtains the maximum number of allowed refinement levels.
 */
int ResGetMaximumRefinementLevels ();

#include "defines.inl"

#endif

