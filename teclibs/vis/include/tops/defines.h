/**
  TopS - Topological data structure for mesh representation.
  
  TopS is a software developed by Tecgraf/PUC-Rio & UIUC.
  It is requested that the TopS users provide the appropriate
  credits and references to the work.
  
  References:
  1 -W. Celes, G.H. Paulino, R. Espinha, "A compact adjacency-based
  topological data structure for finite element mesh representation",
  IJNME, 2005 (in press)
  2 - W. Celes, G.H. Paulino, R. Espinha, "Efficient Handling of Implicit
  Entities in Reduced Mesh Representations", JCISE, Special Issue on
  Mesh-Based Geometric Data Processing, 2005 (in press)
  
  Aug 2005
*/

#ifndef _TOP_DEFINES_H
#define _TOP_DEFINES_H

#include <limits.h>

/**
  Defines whether multilevel support will be enabled for entities.
  Default: false
*/
#define TOP_USE_MULTILEVEL

/**
  Defines whether the following optimizations for reservoir meshes 
  are enabled:
    - A single bit, rather than an element handle will be used for structured 
    meshes.
  Notes:
    - Cohesive elements are not supported in this mode.
  Default: false
*/
//#define TOP_USE_RESERVOIR_OPTM

/**
 * Comment this line out in order to disable non-oriented implicit entities
 */
#define TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES

/**
  Defines whether reverse adjacency information will be stored in the model.
*/
#ifndef TOP_USE_RESERVOIR_OPTM
#define TOP_USE_REV_ADJ
#endif

/**
    Defines whether dynamic elements are supported.
*/
//#define TOP_USE_DYNAMIC_ELEMENTS

/**
    Defines whether implicit entity management (e.g. entity locks) is supported.
*/
#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES
# define TOP_IMPLICIT_ENTITY_MANAGEMENT
#endif

/**
    Factor used for resizing arrays in TopS.
*/
#define TOP_ARRAY_RESIZE_FACTOR  1.25

/**
    Initial size for arrays in TopS.
*/
#define TOP_ARRAY_INIT_SIZE  16

/**
    Defines the value considered as an invalid handle.
*/
#define TOP_INVALID_HANDLE        UINT_MAX  // -1

/**
  Generic entity handle.
  Entity-use handle (32 bits): { lid | level | el_type | el_posid }
*/
#define TOP_ENTITY_HANDLE_BITS 32
#define TOP_ENTITY_HANDLE_PAT 0xffffffff // 32 bits
#define TOP_ENTITY_LOCAL_ID_BITS 4
#ifdef TOP_USE_MULTILEVEL
#define TOP_ENTITY_LEVEL_BITS 2
#else
#define TOP_ENTITY_LEVEL_BITS 0
#endif
#if (TOP_ENTITY_LEVEL_BITS > 0)
#define TOP_MAX_NUM_LEVELS (1 << TOP_ENTITY_LEVEL_BITS)
#else
#define TOP_MAX_NUM_LEVELS 1
#endif

/**
  Element handle (32 bits): { X | level | el_type | el_posid }  
*/
#ifdef TOP_USE_MULTILEVEL
#define TOP_ELEMENT_TYPE_BITS 2
#else
#define TOP_ELEMENT_TYPE_BITS 4
#endif
//#define TOP_ELEMENT_POS_ID_BITS 24
#define TOP_ELEMENT_POS_ID_BITS (TOP_ENTITY_HANDLE_BITS - \
    TOP_ENTITY_LOCAL_ID_BITS - TOP_ENTITY_LEVEL_BITS - TOP_ELEMENT_TYPE_BITS)

#define TOP_ELEMENT_HANDLE_BITS (TOP_ENTITY_LEVEL_BITS + TOP_ELEMENT_TYPE_BITS + TOP_ELEMENT_POS_ID_BITS)

/**
  Node handle (32 bits): { X | level | node_type | node_posid }
*/
#define TOP_NODE_TYPE_BITS 2
//#define TOP_NODE_POS_ID_BITS 28
#define TOP_NODE_POS_ID_BITS (TOP_ENTITY_HANDLE_BITS - \
    TOP_ENTITY_LEVEL_BITS - TOP_NODE_TYPE_BITS)
#define TOP_NODE_HANDLE_BITS (TOP_ENTITY_LEVEL_BITS + TOP_NODE_TYPE_BITS + TOP_NODE_POS_ID_BITS)

/**
  Maximum number of nodes of a given type in the model.
*/
#define TOP_MAX_NUM_NODES_OF_TYPE (1 << TOP_NODE_POS_ID_BITS)

/**
  Maximum number of nodes in the model.
*/
#define TOP_MAX_NUM_NODES (1 << TOP_NODE_POS_ID_BITS)

/**
  Maximum number of element types registered in the model.
*/
#define TOP_MAX_ELEMENT_TYPES (1 << TOP_ELEMENT_TYPE_BITS)

/**
  Maximum number of elements of a given type in the model.
*/
#define TOP_MAX_NUM_ELEMENTS_OF_TYPE (1 << TOP_ELEMENT_POS_ID_BITS)

/**
  Maximum number of elements in the model.
*/
#define TOP_MAX_NUM_ELEMENTS (1 << TOP_ELEMENT_POS_ID_BITS)

/** Maximum number of facets of an element. */
#define TOP_MAX_NUM_F   6
/** Maximum number of edges of an element. */
#define TOP_MAX_NUM_E   12
/** Maximum number of vertices of an element. */
#define TOP_MAX_NUM_V   8
/** Maximum number of nodes of an element. */
#define TOP_MAX_NUM_N   24

/** Maximum number of edges of a facet. */
#define TOP_MAX_NUM_F_E 4
/** Maximum number of vertices of a facet. */
#define TOP_MAX_NUM_F_V 4 
/** Maximum number of nodes of a facet. */
#define TOP_MAX_NUM_F_N 9
/** Maximum number of nodes of an edge. */
#define TOP_MAX_NUM_E_N 4
/** Maximum number of vertices of a facet. */
#define TOP_MAX_NUM_V_F 4
/** Maximum number of vertices of an edge. */
#define TOP_MAX_NUM_V_E 4

/** Uncomment this definition to enable additional consistency checks. */
//#define TOP_DEBUG

/** 
  Uncomment this definition to use a hash map (instead of an array) 
  for storing element and node ids.
*/
//#define TOP_USE_HASH_ENTITY_ID_MAP

/********************************************************************
  Internal definitions.
*********************************************************************/
/**
  Patterns used to access element handles. Must be compatible with the
  number of bits set.
*/
#define TOP_ELEMENT_LEVEL_OFFSET (TOP_ELEMENT_POS_ID_BITS + TOP_ELEMENT_TYPE_BITS)
#define TOP_ELEMENT_TYPE_OFFSET (TOP_ELEMENT_POS_ID_BITS)
#define TOP_ELEMENT_POS_ID_PAT (TOP_ENTITY_HANDLE_PAT >> (TOP_ENTITY_HANDLE_BITS - TOP_ELEMENT_POS_ID_BITS))
#define TOP_ELEMENT_TYPE_PAT ((TOP_ENTITY_HANDLE_PAT >> (TOP_ENTITY_HANDLE_BITS - TOP_ELEMENT_TYPE_BITS)) << TOP_ELEMENT_TYPE_OFFSET)
#define TOP_ELEMENT_LEVEL_PAT ((TOP_ENTITY_HANDLE_PAT >> (TOP_ENTITY_HANDLE_BITS - TOP_ENTITY_LEVEL_BITS)) << TOP_ELEMENT_LEVEL_OFFSET)
#define TOP_ELEMENT_HANDLE_PAT (TOP_ENTITY_HANDLE_PAT >> (TOP_ENTITY_HANDLE_BITS - TOP_ELEMENT_HANDLE_BITS))

#define TOP_NODE_LEVEL_OFFSET (TOP_NODE_POS_ID_BITS + TOP_NODE_TYPE_BITS)
#define TOP_NODE_TYPE_OFFSET (TOP_NODE_POS_ID_BITS)
#define TOP_NODE_POS_ID_PAT (TOP_ENTITY_HANDLE_PAT >> (TOP_ENTITY_HANDLE_BITS - TOP_NODE_POS_ID_BITS))
#define TOP_NODE_TYPE_PAT ((TOP_ENTITY_HANDLE_PAT >> (TOP_ENTITY_HANDLE_BITS - TOP_NODE_TYPE_BITS)) << TOP_NODE_TYPE_OFFSET)
#define TOP_NODE_LEVEL_PAT ((TOP_ENTITY_HANDLE_PAT >> (TOP_ENTITY_HANDLE_BITS - TOP_ENTITY_LEVEL_BITS)) << TOP_NODE_LEVEL_OFFSET)
#define TOP_NODE_HANDLE_PAT (TOP_ENTITY_HANDLE_PAT >> (TOP_ENTITY_HANDLE_BITS - TOP_NODE_HANDLE_BITS))

#define TOP_ENTITY_LOCAL_ID_OFFSET (TOP_ELEMENT_HANDLE_BITS)
#define TOP_ENTITY_LOCAL_ID_PAT ((TOP_ENTITY_HANDLE_PAT >> (TOP_ENTITY_HANDLE_BITS - TOP_ENTITY_LOCAL_ID_BITS)) << TOP_ENTITY_LOCAL_ID_OFFSET)

/** 
    Internal definitions to be used only on the implementation 
  of new element types.
  (32 bits): { 1: dynamic | 2:state | 6: fanchors | 12:eanchors | 8:vanchors }
*/
#define TOP_ELEMENT_DYNAMIC_PAT 0x10000000
#define TOP_ELEMENT_STATE_PAT   0xc000000
#define TOP_ELEMENT_FANCHOR_PAT 0x3f00000
#define TOP_ELEMENT_EANCHOR_PAT 0xfff00
#define TOP_ELEMENT_VANCHOR_PAT 0xff
#define TOP_ELEMENT_ANCHOR_PAT  0x3ffffff
#define TOP_ELEMENT_FANCHOR_OFFSET 20
#define TOP_ELEMENT_EANCHOR_OFFSET 8
#define TOP_ELEMENT_VANCHOR_OFFSET 0
#define TOP_ELEMENT_STATE_OFFSET   26
#define TOP_ELEMENT_DYNAMIC_OFFSET 28

#ifndef TOPS_DLL
# ifndef TEC_DLL
#  define TOPS_API
#  define TOPSH_API
# else
#  define TOPS_API __declspec(dllimport)
#  define TOPSH_API __declspec(dllexport)
# endif
#else
# define TOPS_API __declspec(dllexport)
# define TOPSH_API __declspec(dllexport)
#endif

#ifdef __GNUC__
#define	__GNUC_PREREQ__(x, y)						\
	((__GNUC__ == (x) && __GNUC_MINOR__ >= (y)) ||			\
	 (__GNUC__ > (x)))

#if __GNUC_PREREQ__(4, 2)
#pragma GCC diagnostic ignored "-Wwrite-strings"
#endif
#endif

#ifdef _MSC_VER
# define TOPS_FORCE_INLINE  __forceinline
#else
# define TOPS_FORCE_INLINE  inline
#endif

#endif

