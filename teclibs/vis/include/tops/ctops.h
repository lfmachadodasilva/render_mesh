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


  C binding for Top FEM Data Structure
*/

#ifndef _C_TOPS_H
#define _C_TOPS_H

#include <stdio.h>
#include "defines.h"

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES

#ifdef __cplusplus
extern "C" {
#endif

/**
    A model is basically a container for elements and nodes, which are 
  the only explicitly represented entities. All the others (TopFacet,
  TopEdge and TopVertex) and their uses (TopFacetUse, TopEdgeUse and TopVertexUse) 
  can be indirectly retrieved from those entities.
  
    The model may represents a finite elements mesh, or other type of cell complex.

    Currently, only manifold models are supported. Although some non-manifold 
  intermediate conditions may arise during edition of the model, the final model 
  must be manifold.
*/ 
typedef struct topmodel TopModel;

/**
    Node handle (32bits): { node_id }

    Nodes are the lowest order entities represented in a model. When attached to
  an element, a node can be a corner or mid-side node, and always holds a reference
  to at least one of the elements which contains it. (For a manifold model, which 
  is the case of this data structure, only one element pointer is actually required).
*/
typedef unsigned TopNode;

/**
    Element handle (32 bits): { 4: 0 | 4:el_type | 24:el_id }

    Elements are the highest order entities represented in a model. Along
  with nodes, they are explicitly represented and are the "building blocks"
  of a finite element model. There are, basically, two types of 
  elements: cohesive and non-cohesive.
  
    In current implementation, the following constraints are assumed for
  an element:
    - its boundary is manifold;
    - normals of facet-uses must point away from the element;
    - element's entities are locally oriented;
    - it has at most: 
      * 6  facet-uses,
      * 12 edge-uses,
      * 8  vertex-uses;
    - if it's not cohesive, then it's a closed polyhedron and it has no more 
    than a single reference to each of its nodes. Non-cohesive elements
    can have at most one use of a facet, edge or vertex. Cohesive elements can 
    have up to two uses of an edge or vertex (in this case, the element has
    what is called either a "shared" edge-use or vertex-use).
*/ 
typedef unsigned TopElement;

/**
    Facet handle.

    For a d-dimensional element, a facet is the (d-1)-dimensional non-oriented entity
  which defines the element's boundary and is bounded by a set of edges. In a 
  manifold model, facets can be "used" by one element (boundary facets) or two 
  adjacent elements (interior facets), and
  are uniquely defined by one of the two possible facet-uses. The facet-use which
  defines the facet is the one of the only element holding the "anchor" bit for the
  facet.
*/
typedef unsigned TopFacet;

/**
    Face handle.

    For a d-dimensional element, a face is the (d-1)-dimensional non-oriented entity
  which defines the element's boundary and is bounded by a set of edges. In a 
  manifold model, faces can be "used" by one element (boundary faces) or two 
  adjacent elements (interior faces), and
  are uniquely defined by one of the two possible face-uses. The face-use which
  defines the face is the one of the only element holding the "anchor" bit for the
  face.
*/
typedef unsigned TopFace;

/**
    Edge handle.
  
    An edge is the 1-dimensional entity which is bounded by two vertices. Non-linear 
  edges can also have mid-side nodes, besides the corner nodes.
  It may be radialy "used" by several elements and is uniquely defined by one
  of its edge-uses. The edge-use which defines the edge is the one of the only 
  element holding the "anchor" bit for the edge. The edge is considered a boundary 
  edge if one of its uses is on the model's boundary.
  
    For an element, an edge-use is locally incident to two facet-uses.
  If the element is cohesive, then these two facet-uses are the same. A non-cohsive 
  element can have at most one use of a given edge, while a cohesive one can have 
  up to two uses of the edge.

    Non-linear edges can contain one or more mid-side nodes, in addition to the
  corner nodes related to the vertices which bound the edge.
*/
typedef unsigned TopEdge;

/**
    Vertex handle.
  
    A vertex is the 0-dimensional entity which bounds an edge. It may be unorderly
  "uses" by several elements and is uniquely defined by one of its vertex-uses. The 
  vertex-use which defines the vertex is the one of the only element holding the 
  "anchor" bit for the vertex. The vertex is considered a boundary vertex if one of 
  its uses is on the model's boundary.
*/
typedef unsigned TopVertex;

/**
    FacetUse handle (32 bits): { 4:lid | 4:el_type | 24:el_id }

    Represents the use of a facet by an element.
*/
typedef unsigned TopFacetUse;

/**
    FaceUse handle (32 bits): { 4:lid | 4:el_type | 24:el_id }

    Represents the use of a face by an element.
*/
typedef unsigned TopFaceUse;

/**
    EdgeUse handle (32 bits): { 4:lid | 4:el_type | 24:el_id }
    
    Represents the use of a edge by an element.
*/
typedef unsigned TopEdgeUse;

/**
    VertexUse handle (32 bits): { 4:lid | 4:el_type | 24:el_id }

    Represents the use of a vertex by an element.
*/
typedef unsigned TopVertexUse;


/** C binding structure for TopNodeItr class. */
typedef struct topnodeitr TopNodeItr;

/** C binding structure for TopElemItr class. */
typedef struct topelemitr TopElemItr;

/** C binding structure for TopNodeElemItr class. */
typedef struct topnodeitr TopNodeElemItr;

/** C binding structure for TopFacetItr class. */
typedef struct topfacetitr TopFacetItr;

/** C binding structure for TopFaceItr class. */
typedef struct topfaceitr TopFaceItr;

/** C binding structure for TopEdgeItr class. */
typedef struct topedgeitr  TopEdgeItr;

/** C binding structure for TopVertexItr class. */
typedef struct topvertexitr  TopVertexItr;

/** C binding structure for TopEdgeUseItr class. */
typedef struct topedgeuseitr  TopEdgeUseItr;

/** C binding structure for TopEdgeElemItr class. */
typedef struct topedgeelemitr  TopEdgeElemItr;

/** C binding structure for TopVertexUseItr class. */
typedef struct topvertexuseitr  TopVertexUseItr;

/** C binding structure for TopVertexFacetItr class. */
typedef struct topvertexfacetitr  TopVertexFacetItr;

/** C binding structure for TopVertexEdgeItr class. */
typedef struct topvertexedgeitr  TopVertexEdgeItr;

/** C binding structure for TopVertexElemItr class. */
typedef struct topvertexelemitr  TopVertexElemItr;


/** 
    Element types. 
    Element templates can be found in "elem/concrete[type].h".
*/
enum {
  TOP_ELEMENT_T3 = 0,
  TOP_ELEMENT_T6,
  TOP_ELEMENT_Q4,
  TOP_ELEMENT_Q8,
  TOP_ELEMENT_TET4,
  TOP_ELEMENT_TET10,
  TOP_ELEMENT_HEX8,
  TOP_ELEMENT_HEX8_RESERVOIR,
  TOP_ELEMENT_HEX20,
  TOP_ELEMENT_WEDGE15,
  TOP_ELEMENT_COH2E2,
  TOP_ELEMENT_COH2E3,
  TOP_ELEMENT_COH3T3,
  TOP_ELEMENT_COH3T6,
  TOP_ELEMENT_COH3Q4,
  TOP_ELEMENT_COH3Q8,
  TOP_ELEMENT_WEDGE6,
  TOP_ELEMENT_INF2E2,
  TOP_ELEMENT_INF2E3,
  TOP_ELEMENT_INF2V2,
  TOP_ELEMENT_INF3Q4,
  TOP_ELEMENT_INF3Q8,
  TOP_ELEMENT_Q9,
  TOP_ELEMENT_POLY2D,
  TOP_ELEMENT_LINE2,
  TOP_ELEMENT_MAX
};

/**
    Creates a new empty model.
*/
TOPS_API TopModel* topModel_Create();

/**
    Destroys the model. 
    User attributes are not freed. They must be deallocated 
    explicitly by the user.
*/
TOPS_API void topModel_Destroy(TopModel* m);

/*****************
** TopNode
******************/
/**
   Inserts a new node to the model, given its position in space, and returns 
 a handle for the created node.
*/
TOPS_API TopNode topModel_InsertNode(TopModel* m, double x, double y, double z);

/**
    Inserts a node at the empty position with the given id. If the position 
  is not empty, an invalid node is returned.
*/
//TopNode topModel_InsertNodeAt(TopModel* m, unsigned id, 
//                           double x, double y, double z);

/** 
  Sets the global id associated to the node (id >= 0). 
*/
TOPS_API void topNode_SetId(TopModel* m, TopNode n, int id);

/**
    Gets the user id associated to the node.
  Returns id or -1.
*/
TOPS_API int topNode_GetId(TopModel* m, TopNode n);

/** 
    Gets the node associated to the given user id.
  Returns an invalid node if there is no node with the given id.
*/
TOPS_API TopNode topModel_GetNodeAtId(TopModel* m, int id);

TOPS_API void topModel_RemNode(TopModel* m, TopNode n);
 
TOPS_API int topModel_GetNNodes(TopModel* m);

TOPS_API unsigned topNode_GetHandle(TopModel* m, TopNode node);

TOPS_API int topNode_IsValid(TopModel* m, TopNode n);
  
TOPS_API void topNode_SetPosition(TopModel* m, TopNode n, 
                           double x, double y, double z);

TOPS_API void topNode_GetPosition(TopModel* m, TopNode n, 
                           double* x, double* y, double* z);

/**
    Sets the pointer of an user-defined attribute for the node.
*/
TOPS_API void topNode_SetAttrib(TopModel* m, TopNode n, void* data);

TOPS_API void* topNode_GetAttrib(TopModel* m, TopNode n);

/**
    Gets the reference vertex for the node. If the node is not a vertex, 
  then returns an invalid vertex.
*/
TOPS_API TopVertex topNode_GetVertex(TopModel* m, TopNode n);

/**
    If the node is a mid-side node of an edge, returns the 
  reference edge for the node. Else, an invalid edge is returned.
*/
TOPS_API TopEdge topNode_GetEdge(TopModel* m, TopNode n);


/*****************
** TopElement
******************/

/**
    Inserts a new element to the model, updating its adjacencies. 
  Although this method handles non-manifold intermediate conditions that 
  may arise during model edition, the final mesh must be manifold.
*/  
TOPS_API TopElement topModel_InsertElem(TopModel* m, 
    unsigned type, TopNode* nodes);

/**
    Creates and inserts a cohesive element between the two non-cohesive 
  elements incident to the given facet. A cohesive (also called "interface") 
  element is an especial element which consists of exactly two facets and may
  only be inserted between two non-cohesive elements. 
  
    When the cohesive element is inserted, some nodes in its second facet 
  may need to be duplicated (new nodes are automatically created and inserted 
  into the model). The duplicated nodes are always on the second facet of the 
  cohesive element and the user MUST explicitly set new attributes for them. This
  node duplication implies that, although the respective edges and vertices 
  of the facet do not change, their incidence does. The nodes of the first facet 
  of the cohesive element are identical to the given facet.

    The node duplications are notified by the TopDuplicateNodeCb().
  
    In order to make node duplication easier, the nodes of a cohesive
  element are internally stored in a fixed order correspondence between its
  two facets. 
  
    Let's consider following example: a cohesive element has just been
  inserted. Given that node "ni"
  is a reference to node with id "i" in the model, and that elem[j] is
  a reference to the jth node of an element, then elem[0] is associated 
  to elem[6], elem[1] is associated to elem[6+1], and so on. The first 6
  nodes belongs to the first facet and the others to the second. Although
  the nodes are directly associated by an increment of 6, their local 
  facet-use orientation order is reversed (as shown by the element template ahead),
  in order to maintain consistency on the facet-use normals.
 
  @verbatim 

                  v2
                   n2 
                  /  \
                 /    \         v5
                /      \ ^      n8
               /        \ \e1  /  \
         e2 / /          \    /    \
           V n5          n4  /      \   normal
        normal             \/    ....\--------->
      <---------  f0       .\        n10 \
          /           e3^ .  \         \  V e4 
         /             / n11  \  f1     \
        /               .      \         \
       n0----------n3----------n1         \
       v0    -->      /        v1          \
             e0      /                      \
                    n6----------n9----------n7
                    v3         <--          v4
                               e5

  
    Element's nodes order: n0 n1 n2 n3 n4 n5 | n6 n7 n8 n9 n10 n11 
    f0: n0, n3, n1, n4, n2, n5
    f1: n3, n11, n5, n10, n7, n9
  @endverbatim 
 
    Therefore, to find out which nodes were duplicated after a cohesive
  element insertion between two non-cohesive elements, one would write:
  
  @verbatim
   n = model->GetNNodes(coh)/2;
   for (i = 0; i < n; i++) {
      if (model->GetNode(coh, i) != model->GetNode(coh, n+i)) {
        *** coh->GetNode(n+i) is new!!!! 
        ***
        *** So, we MUST set new attributes for the node, by 
        *** allocating new space in memory for attribute data type 
        *** and initializing it. 
        
        node_data = Create new userdata...
        newnode   = model->GetNode(coh, n+i);
        model->SetAttrib(newnode, node_data);
      }
   }
 @endverbatim
      
    On success, it returns the cohesive element inserted. On failure, it
  returns and invalid element.
 */ 
TOPS_API TopElement topModel_InsertCohesiveAtFacet(TopModel* m, 
    unsigned type, TopFacet facet);

/** 
  Sets the global id associated to the element (id >= 0). 
*/
TOPS_API void topElement_SetId(TopModel* m, TopElement n, int id);

/**
    Gets the user id associated to the element.
  Returns id or -1.
*/
TOPS_API int topElement_GetId(TopModel* m, TopElement n);

/** 
    Gets the element associated to the given user id.
  Returns an invalid element if there is no element with the given id.
*/
TOPS_API TopElement topModel_GetElemAtId(TopModel* m, int id);

/**
    Removes an element from the model, updating its adjacency information. 
  Although this method handles non-manifold intemediate conditions that 
  may appear during model edition, the final mesh must be manifold.
*/  
TOPS_API void topModel_RemElem(TopModel* m, TopElement el);

/**
    Gets the number of elements of a given type in the model.
*/
TOPS_API int topModel_GetNElemOfType(TopModel* m, int type); 

/**
    Gets the total number of elements in the model.
*/
TOPS_API int topModel_GetNElem(TopModel* m); 

TOPS_API unsigned topElement_GetHandle(TopModel* m, TopElement el);

/**
    Gets the type of the element.
*/
TOPS_API unsigned topElement_GetType(TopModel* m, TopElement el);

TOPS_API int topElement_IsValid(TopModel* m, TopElement el);

/**
    Gets element's dimension: 2 for 2D elements or 3 for 3D elements.
*/
TOPS_API int topElement_GetDimension(TopModel* m, TopElement el); 

TOPS_API int topElement_IsCohesive(TopModel* m, TopElement el); 

/**
    Gets the element order: 1 for linear elements, 2 for quadratic elements,
  and so on.
*/
TOPS_API int topElement_GetOrder(TopModel* m, TopElement el); 

/**
    Sets the pointer of an user-defined attribute for the element.
*/
TOPS_API void topElement_SetAttrib(TopModel* m, TopElement el, void* data); 

/**
    Gets the user-defined attribute set for the element.
    Returns Attribute or NULL.
*/
TOPS_API void* topElement_GetAttrib(TopModel* m, TopElement el); 

/************************
** TopElement - Adjacencies
*************************/
TOPS_API int topElement_GetNAdj(TopModel* m, TopElement el);

TOPS_API TopElement topElement_GetAdj(TopModel* m, TopElement el, int fi);

/*********************
** TopElement - Facets 
**********************/
TOPS_API int topElement_GetNFacets(TopModel* m, TopElement el);

TOPS_API TopFacetUse topElement_GetFacetUse(TopModel* m, TopElement el, int i);

TOPS_API TopFacet topElement_GetFacet(TopModel* m, TopElement el, int fi);
  
TOPS_API TopFacet topModel_GetFacet(TopModel* m, TopElement el1, TopElement el2);

/*********************
** TopElement - Faces 
**********************/
TOPS_API int topElement_GetNFaces(TopModel* m, TopElement el);

TOPS_API TopFaceUse topElement_GetFaceUse(TopModel* m, TopElement el, int i);

TOPS_API TopFace topElement_GetFace(TopModel* m, TopElement el, int fi);

/*********************
** TopElement - Edges 
**********************/
TOPS_API int topElement_GetNEdges(TopModel* m, TopElement el);

TOPS_API TopEdgeUse topElement_GetEdgeUse(TopModel* m, TopElement el, int i);

TOPS_API TopEdge topElement_GetEdge(TopModel* m, TopElement el, int ei);

/*********************
** TopElement - Vertices
**********************/
TOPS_API int topElement_GetNVertices(TopModel* m, TopElement el);

TOPS_API TopVertexUse topElement_GetVertexUse(TopModel* m, 
    TopElement el, int i);

TOPS_API TopVertex topElement_GetVertex(TopModel* m, TopElement el, int vi);

/************************
** TopElement - Nodes 
*************************/
TOPS_API int topElement_GetNNodes(TopModel* m, TopElement el);

TOPS_API TopNode topElement_GetNode(TopModel* m, TopElement el, int i);

TOPS_API int topElement_GetNCornerNodes(TopModel* m, TopElement el);
  
TOPS_API TopNode topElement_GetCornerNode(TopModel* m, TopElement el, int vi);

TOPS_API int topElement_IsCornerNode(TopModel* m, TopElement el, int ni);

TOPS_API int topElement_IsMidSideNode(TopModel* m, TopElement el, int ni);

/***********************
** TopFacetUse
************************/
TOPS_API unsigned topFacetUse_GetHandle(TopModel* m, TopFacetUse fu);

TOPS_API unsigned topFacetUse_GetLocalId(TopModel* m, TopFacetUse fu);

TOPS_API int topFacetUse_IsValid(TopModel* m, TopFacetUse fu);

TOPS_API void topFacetUse_SetAttrib(TopModel* m, TopFacetUse fu, void* attrib);

TOPS_API void* topFacetUse_GetAttrib(TopModel* m, TopFacetUse fu);

TOPS_API TopElement topFacetUse_GetElem(TopModel* m, TopFacetUse fu);

/**
    Gets the corresponding facet-use of the element adjacent to the
  fi'th facet-use of the current element. If there is no adjacent element,
  it returns an invalid facet-use. 
    This method uses adjacency information stored in the data structure 
  to determine the mate facet-use.
*/
TOPS_API TopFacetUse topFacetUse_GetMate(TopModel* m, TopFacetUse fu);

TOPS_API TopFacet topFacetUse_GetFacet(TopModel* m, TopFacetUse fu);

TOPS_API int topFacetUse_GetNEdgeUses(TopModel* m, TopFacetUse fu); 

TOPS_API TopEdgeUse topFacetUse_GetEdgeUse(TopModel* m, 
    TopFacetUse fu, int ei); 

TOPS_API int topFacetUse_GetNVertexUses(TopModel* m, TopFacetUse fu); 

TOPS_API TopVertexUse topFacetUse_GetVertexUse(TopModel* m, 
    TopFacetUse fu, int vi);

TOPS_API int topFacetUse_GetNNodes(TopModel* m, TopFacetUse fu); 

TOPS_API TopNode topFacetUse_GetNode(TopModel* m, TopFacetUse fu, int ni);

TOPS_API int topFacetUse_GetNCornerNodes(TopModel* m, TopFacetUse fu); 
  
TOPS_API TopNode topFacetUse_GetCornerNode(TopModel* m, TopFacetUse fu, int vi);

/***********************
** TopFaceUse
************************/
TOPS_API unsigned topFaceUse_GetHandle(TopModel* m, TopFaceUse fu);

TOPS_API unsigned topFaceUse_GetLocalId(TopModel* m, TopFaceUse fu);

TOPS_API int topFaceUse_IsValid(TopModel* m, TopFaceUse fu);

TOPS_API void topFaceUse_SetAttrib(TopModel* m, TopFaceUse fu, void* attrib);

TOPS_API void* topFaceUse_GetAttrib(TopModel* m, TopFaceUse fu);

TOPS_API TopElement topFaceUse_GetElem(TopModel* m, TopFaceUse fu);

/**
    Gets the corresponding facet-use of the element adjacent to the
  fi'th facet-use of the current element. If there is no adjacent element,
  it returns an invalid facet-use. 
    This method uses adjacency information stored in the data structure 
  to determine the mate facet-use.
*/
TOPS_API TopFaceUse topFaceUse_GetMate(TopModel* m, TopFaceUse fu);

TOPS_API TopFace topFaceUse_GetFace(TopModel* m, TopFaceUse fu);

TOPS_API int topFaceUse_GetNEdgeUses(TopModel* m, TopFaceUse fu); 

TOPS_API TopEdgeUse topFaceUse_GetEdgeUse(TopModel* m, TopFaceUse fu, int ei); 

TOPS_API int topFaceUse_GetNVertexUses(TopModel* m, TopFaceUse fu); 

TOPS_API TopVertexUse topFaceUse_GetVertexUse(TopModel* m, 
    TopFaceUse fu, int vi);

TOPS_API int topFaceUse_GetNNodes(TopModel* m, TopFaceUse fu); 

TOPS_API TopNode topFaceUse_GetNode(TopModel* m, TopFaceUse fu, int ni);

TOPS_API int topFaceUse_GetNCornerNodes(TopModel* m, TopFaceUse fu); 
  
TOPS_API TopNode topFaceUse_GetCornerNode(TopModel* m, TopFaceUse fu, int vi);

/***********************
** TopEdgeUse
************************/
TOPS_API unsigned topEdgeUse_GetHandle(TopModel* m, TopEdgeUse eu);

TOPS_API unsigned topEdgeUse_GetLocalId(TopModel* m, TopEdgeUse eu);

TOPS_API int topEdgeUse_IsValid(TopModel* m, TopEdgeUse eu);

TOPS_API void topEdgeUse_SetAttrib(TopModel* m, TopEdgeUse eu, void* attrib);

TOPS_API void* topEdgeUse_GetAttrib(TopModel* m, TopEdgeUse eu);

TOPS_API TopElement topEdgeUse_GetElem(TopModel* m, TopEdgeUse eu);

/**
    Gets the number of element's facet-uses incident to the ei'th edge-use.
  In general, the number of edge-use's incident facet-uses is:
    - 2 for 3D non-cohesive elements, or
    - 1 for cohesive elements or 2D non-cohesive elements.
*/
TOPS_API int topEdgeUse_GetNFacetUses(TopModel* m, TopEdgeUse eu);

/**
    Gets the i'th facet-use incident to the ei'th edge-use of the element. 
  By convention, we have: 0: "left" and 1: "right". The "left" one 
  corresponds to the facet-use with the same local orientation of the 
  edge-use, while the "right" one corresponds to the facet-use with opposite 
  local orientation.
*/
TOPS_API TopFacetUse topEdgeUse_GetFacetUse(TopModel* m, TopEdgeUse eu, int i);

/**
    Gets the number of element's face-uses incident to the ei'th edge-use.
  In general, the number of edge-use's incident face-uses is:
    - 2 for 3D non-cohesive elements, or
    - 1 for cohesive elements or 2D non-cohesive elements.
*/
TOPS_API int topEdgeUse_GetNFaceUses(TopModel* m, TopEdgeUse eu);

/**
    Gets the i'th face-use incident to the ei'th edge-use of the element. 
  By convention, we have: 0: "left" and 1: "right". The "left" one 
  corresponds to the face-use with the same local orientation of the 
  edge-use, while the "right" one corresponds to the face-use with opposite 
  local orientation.
*/
TOPS_API TopFaceUse topEdgeUse_GetFaceUse(TopModel* m, TopEdgeUse eu, int i);

TOPS_API TopEdge topEdgeUse_GetEdge(TopModel* m, TopEdgeUse eu);

/**
    Gets the corresponding edge-use of the element adjacent to the
  i'th facet-use adjacent to the ei'th edge of the current element. If there 
  is no adjacent element, it returns an invalid edge-use. 
    This method uses adjacency information stored in the data structure 
  to determine the mate edge-use.

  @param i 0: left, 1: right.
*/
TOPS_API TopEdgeUse topEdgeUse_GetMate(TopModel* m, TopEdgeUse eu, int i);

TOPS_API TopVertexUse topEdgeUse_GetVertexUse(TopModel* m, 
    TopEdgeUse eu, int vi);

TOPS_API int topEdgeUse_GetNNodes(TopModel* m, TopEdgeUse eu); 

TOPS_API TopNode topEdgeUse_GetNode(TopModel* m, TopEdgeUse eu, int ni);

TOPS_API TopNode topEdgeUse_GetCornerNode(TopModel* m, TopEdgeUse eu, int vi);

/***********************
** TopVertexUse
************************/
TOPS_API unsigned topVertexUse_GetHandle(TopModel* m, TopVertexUse vu);

TOPS_API unsigned topVertexUse_GetLocalId(TopModel* m, TopVertexUse vu);

TOPS_API int topVertexUse_IsValid(TopModel* m, TopVertexUse vu);

TOPS_API void topVertexUse_SetAttrib(TopModel* m, 
    TopVertexUse vu, void* attrib);

TOPS_API void* topVertexUse_GetAttrib(TopModel* m, TopVertexUse vu);
  
TOPS_API TopElement topVertexUse_GetElem(TopModel* m, TopVertexUse vu);

TOPS_API int topVertexUse_GetNFacetUses(TopModel* m, TopVertexUse vu);

TOPS_API TopFacetUse topVertexUse_GetFacetUse(TopModel* m, 
    TopVertexUse vu, int i);

TOPS_API int topVertexUse_GetNFaceUses(TopModel* m, TopVertexUse vu);

TOPS_API TopFaceUse topVertexUse_GetFaceUse(TopModel* m, 
    TopVertexUse vu, int i);

TOPS_API int topVertexUse_GetNEdgeUses(TopModel* m, TopVertexUse vu);

TOPS_API TopEdgeUse topVertexUse_GetEdgeUse(TopModel* m, 
    TopVertexUse vu, int ei);

/**
    Gets the corresponding vertex-use of the element adjacent to the
  i'th facet-use adjacent to the vi'th vertex of the current element. 
  If there is no adjacent element, it returns an invalid vertex-use. 
    This method uses adjacency information stored in the data structure 
  to determine the mate vertex-use.
*/
TOPS_API TopVertexUse topVertexUse_GetMate(TopModel* m, 
    TopVertexUse vu, int i);

TOPS_API TopVertex topVertexUse_GetVertex(TopModel* m, TopVertexUse vu);

TOPS_API TopNode topVertexUse_GetNode(TopModel* m, TopVertexUse vu);

/***********************
  TopFacet
************************/
TOPS_API unsigned topFacet_GetHandle(TopModel* m, TopFacet f);

TOPS_API int topFacet_IsValid(TopModel* m, TopFacet f);
  
TOPS_API void topFacet_AddLock(TopModel* m, TopFacet f);

TOPS_API void topFacet_RemLock(TopModel* m, TopFacet f);

TOPS_API void topFacet_ResetLock(TopModel* m, TopFacet f);

TOPS_API TopFacetUse  topFacet_GetFacetUse(TopModel* m, TopFacet f, int i);

TOPS_API void topFacet_SetAttrib(TopModel* m, TopFacet f, void* attrib);

TOPS_API void* topFacet_GetAttrib(TopModel* m, TopFacet f);

/**
    Gets one of the two possible elements using the facet.
*/
TOPS_API TopElement topFacet_GetElem(TopModel* m, TopFacet f, int i);

TOPS_API int topFacet_IsBoundary(TopModel* m, TopFacet f);

TOPS_API int topFacet_GetNEdges(TopModel* m, TopFacet f);

TOPS_API TopEdge topFacet_GetEdge(TopModel* m, TopFacet f, int i);

TOPS_API int topFacet_GetNVertices(TopModel* m, TopFacet f);

TOPS_API TopVertex topFacet_GetVertex(TopModel* m, TopFacet f, int i);

TOPS_API int topFacet_GetNNodes(TopModel* m, TopFacet f);

TOPS_API TopNode topFacet_GetNode(TopModel* m, TopFacet f, int i);

/***********************
  TopFace
************************/
TOPS_API unsigned topFace_GetHandle(TopModel* m, TopFace f);

TOPS_API int topFace_IsValid(TopModel* m, TopFace f);
  
TOPS_API void topFace_AddLock(TopModel* m, TopFace f);

TOPS_API void topFace_RemLock(TopModel* m, TopFace f);

TOPS_API void topFace_ResetLock(TopModel* m, TopFace f);

TOPS_API TopFaceUse  topFace_GetFaceUse(TopModel* m, TopFace f, int i);

TOPS_API void topFace_SetAttrib(TopModel* m, TopFace f, void* attrib);

TOPS_API void* topFace_GetAttrib(TopModel* m, TopFace f);

/**
    Gets one of the two possible elements using the face.
*/
TOPS_API TopElement topFace_GetElem(TopModel* m, TopFace f, int i);

TOPS_API int topFace_IsBoundary(TopModel* m, TopFace f);

TOPS_API int topFace_GetNEdges(TopModel* m, TopFace f);

TOPS_API TopEdge topFace_GetEdge(TopModel* m, TopFace f, int i);

TOPS_API int topFace_GetNVertices(TopModel* m, TopFace f);

TOPS_API TopVertex topFace_GetVertex(TopModel* m, TopFace f, int i);

TOPS_API int topFace_GetNNodes(TopModel* m, TopFace f);

TOPS_API TopNode topFace_GetNode(TopModel* m, TopFace f, int i);

/***********************
  TopEdge
************************/
TOPS_API unsigned topEdge_GetHandle(TopModel* m, TopEdge e);

TOPS_API int topEdge_IsValid(TopModel* m, TopEdge e);

TOPS_API void topEdge_AddLock(TopModel* m, TopEdge e);

TOPS_API void topEdge_RemLock(TopModel* m, TopEdge e);

TOPS_API void topEdge_ResetLock(TopModel* m, TopEdge e);

TOPS_API void topEdge_SetAttrib(TopModel* m, TopEdge e, void* attrib);

TOPS_API void* topEdge_GetAttrib(TopModel* m, TopEdge e);

TOPS_API int topEdge_IsBoundary(TopModel* m, TopEdge e); 

TOPS_API TopVertex topEdge_GetVertex(TopModel* m, TopEdge e, int i);

TOPS_API int topEdge_GetNNodes(TopModel* m, TopEdge e);

TOPS_API TopNode topEdge_GetNode(TopModel* m, TopEdge e,int i);

/***********************
  TopVertex
************************/
TOPS_API unsigned topVertex_GetHandle(TopModel* m, TopVertex e);

TOPS_API int topVertex_IsValid(TopModel* m, TopVertex v);

TOPS_API void topVertex_AddLock(TopModel* m, TopVertex v);

TOPS_API void topVertex_RemLock(TopModel* m, TopVertex v);

TOPS_API void topVertex_ResetLock(TopModel* m, TopVertex v);

TOPS_API void topVertex_SetAttrib(TopModel* m, TopVertex v, void* attrib);

TOPS_API void* topVertex_GetAttrib(TopModel* m, TopVertex v);

TOPS_API int topVertex_IsBoundary(TopModel* m, TopVertex v);

TOPS_API TopNode topVertex_GetNode(TopModel* m, TopVertex v); 

/***********************
  Edition
************************/

/**
    Callback functions for some mesh modification events. 
    When on of these events happen (e.g., when a cohesive element is inserted), 
  the appropriate function, if registered, is called to notify of a change in the 
  model.
    To register a callback to handle an event, the topModel_Set*Cb functions 
  below are used. At most one callback of each type may be registered in the 
  model.
    The events generated by the mesh edition functions are indicated in the 
  documentation of the functions.
    The data parameter is a pointer to an optional user data which is passed 
  every time the callback is invoked.
*/
typedef void (*TopSplitElemCb)(TopModel* m, TopElement old_el, TopElement new_el[2], void* data);
typedef void (*TopSwapElemCb)(TopModel* m, TopElement old_el[2], TopElement new_el[2], void* data);
typedef void (*TopMergeElemCb)(TopModel* m, TopElement old_el[2], TopElement new_el, void* data);
typedef void (*TopInsertNodeCb)(TopModel* m, TopNode node, void* data);
typedef void (*TopRemoveNodeCb)(TopModel* m, TopNode node, void* data);
typedef void (*TopDuplicateNodeCb)(TopModel* m, TopNode old_n, TopNode new_n, void* data);

TOPS_API void topModel_SetSplitElemCb(TopModel* m, TopSplitElemCb cb, void* data);
TOPS_API void topModel_SetSwapElemCb(TopModel* m, TopSwapElemCb cb, void* data);
TOPS_API void topModel_SetMergeElemCb(TopModel* m, TopMergeElemCb cb, void* data);
TOPS_API void topModel_SetInsertNodeCb(TopModel* m, TopInsertNodeCb cb, void* data);
TOPS_API void topModel_SetRemoveNodeCb(TopModel* m, TopRemoveNodeCb cb, void* data);
TOPS_API void topModel_SetDuplicateNodeCb(TopModel* m, TopDuplicateNodeCb cb, void* data);

/**  
    Splits an edge of a 4-8 mesh (T3 or T6 elements). 
    When one of the edge-use local ids of the split edge is different from zero,
  the algorithm will proceed recursively.
    During the split process, some new entities (nodes, vertices, edges, elements)
  may be inserted into the model. 
    The mesh modifications are notified by the callbacks: TopSplitElemCb(), 
  TopInsertNodeCb(). 
    When TopSplitElemCb() are called, the old element is 
  already disconnect from the model. Thus, only the local entities of this 
  element (facet-use, edge-use and vertex-use) can be retrieved. Facets, edges 
  and vertices are not guaranteed. 
    The main uses for the above callbacks are to move attributes from the old 
  entities to the new ones.
  
    Split node order:
  @verbatim
                2                                        2 
              /   \                                    / | \
            /       \                                /   |   \
          5    El0'   4                            5     8     4
        /               \                        /  El0  |  El1  \
      /                   \                    /         |         \
      0----------3----------1                  0----6-----3----7-----1
      .......................---> e            .......................---> e
      *----------*----------*                  *----*----* *---*-----*
              El2'                 ====>         El4         El5
      *----------*----------*                  *----*----* *---*-----*
                                              
      10---------12---------9                  10---16----12---15----9
      \                   /                    \         |         /
        \               /                        \  El2  |  El3  /
          13    El1'   14                           13    17    14
            \        /                               \   |    /
              \    /                                   \ |  /
                11                                       11 
  @endverbatim 
*/
TOPS_API void topModel_SplitEdge4K8(TopModel* m, TopEdge e);

/**
    Swaps an edge of a 4-8 mesh (T3 or T6 elements).
    When one of the edge-use local ids of the swap edge is different from zero,
  the algorithm will split other edges recursively, by calling 
  topModel_SplitEdge4K8(). Swaps are only allowed in internal edges shared by
  two non-cohesive elements.
    The swap modifications are notified by the callbacks: TopSwapElemCb().
    When TopSwapElemCb() is called, the old element is 
  already disconnect from the model. Thus, only the local entities of this 
  element (facet-use, edge-use and vertex-use) can be retrieved. Facets, edges 
  and vertices are not guaranteed.
    The main uses for the above callbacks are to move attributes from the old 
  entities to the new ones.
  
    Swap node order:
  @verbatim
                  2                                    2           
                /   \                                / | \
              /       \                            /   |   \
            6    El0'   5                        6     |     5
          /               \                    /       |       \
        /                   \                /         |         \
      0----------4----------1    ====>     0    El0   4   El1    1
        \                   /                \         |         / 
          \               /                    \       |       /   
          7     El1'   8                       7      |     8     
            \        /                           \    |   /       
              \    /                               \  | /         
                3                                     3            
  @endverbatim 
*/
TOPS_API void topModel_SwapEdge4K8(TopModel* m, TopEdge e);

/***********************
  Consistency 
************************/

/**
    Checks whether model is consistent.
*/
TOPS_API int topModel_CheckConsistency(TopModel* m);

/***********************
  Iterators
************************/

/**
    Creates and initializes an iterator for traversing all elements of a model. 
  After been used, the iterator must be properly destroyed.
*/
TOPS_API TopElemItr*   topModel_CreateElemItr(TopModel* m);
TOPS_API void          topElemItr_Begin(TopElemItr* itr);
TOPS_API void          topElemItr_Next(TopElemItr* itr);
TOPS_API int           topElemItr_IsValid(TopElemItr* itr);
TOPS_API TopElement    topElemItr_GetCurr(TopElemItr* itr);
TOPS_API void          topElemItr_Destroy(TopElemItr* itr);

/**
    Creates and initializes an iterator for traversing all nodes of a model. 
  After been used, the iterator must be properly destroyed.
*/
TOPS_API TopNodeItr*   topModel_CreateNodeItr(TopModel* m);
TOPS_API void          topNodeItr_Begin(TopNodeItr* itr);
TOPS_API void          topNodeItr_Next(TopNodeItr* itr);
TOPS_API int           topNodeItr_IsValid(TopNodeItr* itr);
TOPS_API TopNode       topNodeItr_GetCurr(TopNodeItr* itr);
TOPS_API void          topNodeItr_Destroy(TopNodeItr* itr);

/**
    Creates and initializes an iterator for traversing all facets of a model. 
  After been used, the iterator must be properly destroyed.
*/
TOPS_API TopFacetItr*  topModel_CreateFacetItr(TopModel* m);
TOPS_API void          topFacetItr_Begin(TopFacetItr* itr);
TOPS_API void          topFacetItr_Next(TopFacetItr* itr);
TOPS_API int           topFacetItr_IsValid(TopFacetItr* itr);
TOPS_API TopFacet      topFacetItr_GetCurr(TopFacetItr* itr);
TOPS_API void          topFacetItr_Destroy(TopFacetItr* itr);

/**
    Creates and initializes an iterator for traversing all faces of a model. 
  After been used, the iterator must be properly destroyed.
*/
TOPS_API TopFaceItr*  topModel_CreateFaceItr(TopModel* m);
TOPS_API void          topFaceItr_Begin(TopFaceItr* itr);
TOPS_API void          topFaceItr_Next(TopFaceItr* itr);
TOPS_API int           topFaceItr_IsValid(TopFaceItr* itr);
TOPS_API TopFace      topFaceItr_GetCurr(TopFaceItr* itr);
TOPS_API void          topFaceItr_Destroy(TopFaceItr* itr);

/**
    Creates and initializes  an iterator for traversing all edges of a model. 
  After been used, the iterator must be properly destroyed.
*/
TOPS_API TopEdgeItr*   topModel_CreateEdgeItr(TopModel* m);
TOPS_API void          topEdgeItr_Begin(TopEdgeItr* itr);
TOPS_API void          topEdgeItr_Next(TopEdgeItr* itr);
TOPS_API int           topEdgeItr_IsValid(TopEdgeItr* itr);
TOPS_API TopEdge       topEdgeItr_GetCurr(TopEdgeItr* itr);
TOPS_API void          topEdgeItr_Destroy(TopEdgeItr* itr);

/**
    Creates and initializes  an iterator for traversing all vertices of a model. 
  After been used, the iterator must be properly destroyed.
*/
TOPS_API TopVertexItr* topModel_CreateVertexItr(TopModel* m);
TOPS_API void          topVertexItr_Begin(TopVertexItr* itr);
TOPS_API void          topVertexItr_Next(TopVertexItr* itr);
TOPS_API int           topVertexItr_IsValid(TopVertexItr* itr);
TOPS_API TopVertex     topVertexItr_GetCurr(TopVertexItr* itr);
TOPS_API void          topVertexItr_Destroy(TopVertexItr* itr);


/**
    Creates and initializes  an iterator for traversing all uses of an edge. 
  After being used, the iterator must be properly destroyed.  
*/
TOPS_API TopEdgeUseItr* topModel_CreateEdgeUseItr(TopModel* m, TopEdge e);
TOPS_API void           topEdgeUseItr_Begin(TopEdgeUseItr* itr);
TOPS_API void           topEdgeUseItr_Next(TopEdgeUseItr* itr);
TOPS_API int            topEdgeUseItr_IsValid(TopEdgeUseItr* itr);
TOPS_API TopEdgeUse     topEdgeUseItr_GetCurr(TopEdgeUseItr* itr);
TOPS_API void           topEdgeUseItr_Destroy(TopEdgeUseItr* itr);

/**
    Creates and initializes  an iterator for traversing all elements that use an 
  edge. After being used, the iterator must be properly destroyed.
*/
TOPS_API TopEdgeElemItr* topModel_CreateEdgeElemItr(TopModel* m, TopEdge e);
TOPS_API void            topEdgeElemItr_Begin(TopEdgeElemItr* itr);
TOPS_API void            topEdgeElemItr_Next(TopEdgeElemItr* itr);
TOPS_API int             topEdgeElemItr_IsValid(TopEdgeElemItr* itr);
TOPS_API TopElement      topEdgeElemItr_GetCurr(TopEdgeElemItr* itr);
TOPS_API void            topEdgeElemItr_Destroy(TopEdgeElemItr* itr);

/**
    Creates and initializes  an iterator for traversing all uses of a vertex. 
  After being used, the iterator must be properly destroyed.  
*/
TOPS_API TopVertexUseItr* topModel_CreateVertexUseItr(TopModel* m, TopVertex v);
TOPS_API void             topVertexUseItr_Begin(TopVertexUseItr* itr);
TOPS_API void             topVertexUseItr_Next(TopVertexUseItr* itr);
TOPS_API int              topVertexUseItr_IsValid(TopVertexUseItr* itr);
TOPS_API TopVertexUse     topVertexUseItr_GetCurr(TopVertexUseItr* itr);
TOPS_API void             topVertexUseItr_Destroy(TopVertexUseItr* itr);

/**
    Creates and initializes  an iterator for traversing all elements that use a 
  vertex. After being used, the iterator must be properly destroyed.
*/
TOPS_API TopVertexElemItr* topModel_CreateVertexElemItr(TopModel* m, TopVertex v);
TOPS_API void               topVertexElemItr_Begin(TopVertexElemItr* itr);
TOPS_API void               topVertexElemItr_Next(TopVertexElemItr* itr);
TOPS_API int                topVertexElemItr_IsValid(TopVertexElemItr* itr);
TOPS_API TopElement         topVertexElemItr_GetCurr(TopVertexElemItr* itr);
TOPS_API void               topVertexElemItr_Destroy(TopVertexElemItr* itr);

/**
    Creates and initializes  an iterator for traversing all the facets incident to a 
  vertex. After being used, the iterator must be properly destroyed.
*/
TOPS_API TopVertexFacetItr* topModel_CreateVertexFacetItr(TopModel* m, TopVertex v);
TOPS_API void               topVertexFacetItr_Begin(TopVertexFacetItr* itr);
TOPS_API void               topVertexFacetItr_Next(TopVertexFacetItr* itr);
TOPS_API int                topVertexFacetItr_IsValid(TopVertexFacetItr* itr);
TOPS_API TopFacet           topVertexFacetItr_GetCurr(TopVertexFacetItr* itr);
TOPS_API void               topVertexFacetItr_Destroy(TopVertexFacetItr* itr);

/**
    Creates and initializes  an iterator for traversing all the edges incident to a 
  vertex. After being used, the iterator must be properly destroyed.
*/
TOPS_API TopVertexEdgeItr*  topModel_CreateVertexEdgeItr(TopModel* m, TopVertex v);
TOPS_API void               topVertexEdgeItr_Begin(TopVertexEdgeItr* itr);
TOPS_API void               topVertexEdgeItr_Next(TopVertexEdgeItr* itr);
TOPS_API int                topVertexEdgeItr_IsValid(TopVertexEdgeItr* itr);
TOPS_API TopEdge            topVertexEdgeItr_GetCurr(TopVertexEdgeItr* itr);
TOPS_API void               topVertexEdgeItr_Destroy(TopVertexEdgeItr* itr);

/**
    Creates and initializes  an iterator for traversing all elements that are 
  incident to a node. After being used, the iterator must be properly destroyed.
*/
TOPS_API TopNodeElemItr*    topModel_CreateNodeElemItr(TopModel* m, TopNode n);
TOPS_API void               topNodeElemItr_Begin(TopNodeElemItr* itr);
TOPS_API void               topNodeElemItr_Next(TopNodeElemItr* itr);
TOPS_API int                topNodeElemItr_IsValid(TopNodeElemItr* itr);
TOPS_API TopElement         topNodeElemItr_GetCurr(TopNodeElemItr* itr);
TOPS_API void               topNodeElemItr_Destroy(TopNodeElemItr* itr);


/***********************
  Utilities
************************/

/**
  DEPRECATED
  Creates a square grid of the given element type into the given empty model.
  For Q4, Q8, HEX8, HEX20 and HEX8_RESERVOIR element types, a regular grid
  is created. For T3 and T6 element types, a 4-8 mesh is created. For TET4 
  and TET10 element types, a mesh of HEX elements each decomposed into 6 TET
  elements is created. For two-dimensional elements, the z coordinate 
  parameters are ignored.
  If the grid cannot be created, returns false.
*/
TOPS_API int topBuildGrid(TopModel* m, int el_type, int nx, int ny, int nz, 
  double xmin, double ymin, double zmin, double xmax, double ymax, double zmax);

typedef struct topgridbuilder TopGridBuilder;

typedef enum {
  TOP_GRID_BUILDER_HEXAHEDRON_TRIANG_SIX_TETRA = 0,
  TOP_GRID_BUILDER_HEXAHEDRON_TRIANG_PYRAMID_TETRA
} TopGridBuilderTriangType;

/**
  Creates a new grid builder object. The builder constructs a square grid 
  of the given element type and outputs it to an empty model.
  For Q4, Q8, HEX8, HEX20 and HEX8_RESERVOIR element types, a regular grid
  is created. For T3 and T6 element types, a regular grid is created and 
  decomposed into a 4-8 triangular mesh. For TET4 and TET10 element types, 
  the regular grid of hexahedral cells is decomposed into 6 tetrahedra (default) of
  the corresponding type per cell.
  In two-dimensional grids, the z coordinate parameters are ignored.
  Basic usage: 
    TopGridBuilder* b = topGridBuilder_Create(); // create a builder
    topGridBuilder_SetOutputModel(b, model);
    topGridBuilder_SetElemType(b, TOP_ELEMENT_TET4);
    topGridBuilder_SetDiscretization(b, 3, 4, 4);
    topGridBuilder_SetBoundingBox(b, 0.0, 0.0, 0.0, 30.0, 40.0, 40.0);
    if (!topGridBuilder_Build(b))
      printf("Errror!\n");
    topGridBuilder_Destroy(b);
    
*/
TOPS_API TopGridBuilder* topGridBuilder_Create();

TOPS_API void topGridBuilder_Destroy(TopGridBuilder* builder);

TOPS_API void topGridBuilder_SetOutputModel(TopGridBuilder* builder, TopModel* m);

/**
  Sets the element type into which the regular grid will be decomposed.
*/
TOPS_API void topGridBuilder_SetElemType(TopGridBuilder* builder, int elemtype);

/**
  Defines the way grid cells will be triangulate if the grid element type is 
  triangle or tetrahedron.

  By default, hexahedral cells are decomposed into 6 tetrahedra per cell.

  Parameters:
    triang  Triangulation type (see enum TopGridBuilderTriangType)
*/
TOPS_API void topGridBuilder_SetTriangulationType(TopGridBuilder* builder, int triang);

/**
  Defines the discretization (nx x ny x nz) of the regular grid.
*/
TOPS_API void topGridBuilder_SetDiscretization(TopGridBuilder* builder, int nx, int ny, int nz);

/**
  Sets the bounding box used to define the size of the regular grid in the
  Cartesian coordinate space.
*/
TOPS_API void topGridBuilder_SetBoundingBox(TopGridBuilder* builder,
    double xmin, double ymin, double zmin, double xmax, double ymax, double zmax);

/**
  Builds a regular grid based on the grid parameters previously set.
  Returns 1 if the grid can be created or 0 otherwise.
*/
TOPS_API int topGridBuilder_Build(TopGridBuilder* builder);

/**
    Jitters internal nodes of the model.
  Assumes that mesh has not been modified yet.
*/
TOPS_API void topJitterInternalNodes(TopModel* m, double factor);

/**
    Checks the orientation of all the faces of the model.
  Assumes that faces are planar.
*/
TOPS_API int topCheckFaceOrientations(TopModel* m);


/**
  Computes the quality factor of a triangular or tetrahedral element.
  Uses Lo´s quality factor metric.
  
  - Planar T3 and T6, with vertices A, B, C:

    alpha = 4 * sqrt(3) * area / sum[i=1,3](edge_length(i)^2)

  Higher values mean better quality triangles. Equilateral triangles have
  alpha = 1. alpha = 0 corresponds to A, B and C being co-linear.

  - TET4 and TET10

    gamma = 72 * sqrt(3) * volume / ((sum[i=1,6](edge_length(i)^2))^(3/2)),
      (0 <= gamma <= 1)
*/
TOPS_API double topComputeElemQuality(TopModel* m, TopElement el);

/**
    Smooths triangular or tetrahedral meshes using Laplacian filter and
  Lo's quality factor, with weight factor equal to 1 for every edge incident to each of the
  smoothed vertices.
    The algorithm will converge if every element in the mesh has quality
  grater required quality factor.
  @param maxsteps Maximum number of smooth steps.
  @param factor Nodal movement multiplication factor.
  @param qmin Minimum required quality factor.
  @param constrained Nodal constraint array. If constrained[i] != 0,
  node will not be moved. The size of this array must be at least the
  number of nodes.
  @return Whether the algorithm has converged (1) or not (0).
*/
TOPS_API int topSmoothMesh(
  TopModel* m, int maxsteps, double factor, double qmin, int* constrained);

/**
  Refines the facet arond the given vertex for a tolerance value.
  Parameters:
    v: A vertex in the model.
    f: One of the facets incident to the vertex v.
    tol: Tolerance factor. The facet is repeatedly split until it reaches
    a size that is less than the given tolerance.
*/
TOPS_API TopFacet topRefineVertexFacet4K8(TopModel* m, TopVertex v, TopFacet f, double tol);


/**************************************
 * Two-dimensional 4K mesh adaptivity
 **************************************/ 
typedef struct toprefinement4k TopRefinement4K;

/**
    Creates a refinement manager for 4K triangular meshes. It permits refined 
  portions of the mesh to be coarsen back, up to the original mesh shape.
    Upon construction, the manager will set and manage attributes to
  all the edges of the model.
    By the current implementation, the manager will only work if the client 
  application does not set or use any edge attributes.
    All the refinement or coarsening operation must be done through the interface
  of TopRefinement4K, rather than TopModel, and the initial mesh cannot have
  edges that have been previously split, swapped, or under any refinement operations.
    The refinement manager must be destructed when it is not needed anymore, in order
  that edge attributes can be freed.    
*/
TOPS_API TopRefinement4K* topCreateRefinement4K(TopModel* m);

/**
    Destroys a refinement manager for 4K triangular meshes.
*/
TOPS_API void topDestroyRefinement4K(TopRefinement4K* r);

/**
    Splits an edge of a 4K mesh. 
    It executes the same procedure of topModel_SplitEdge4K8, but a history
  of refinement operations is kept so that the mesh can be coarsened back.
    The mesh modifications are notified by the callbacks: TopSplitElemCb(), 
  TopInsertNodeCb().
*/
TOPS_API void topRefinement4K_SplitEdge(TopRefinement4K* r, TopEdge e);

/**
    Refines the facet around the given vertex for a tolerance value.
    Parameters:
      v: A vertex in the model.
      f: One of the facets incident to the vertex v.
      tol: Tolerance factor. The facet is repeatedly split until it reaches
      a size that is less than the given tolerance.
    The mesh modifications are notified by the callbacks: TopSplitElemCb(), 
  TopInsertNodeCb().
*/
TOPS_API TopFacet topRefinement4K_RefineVertexFacet(TopRefinement4K* r, TopVertex cv, TopFacet cf, double tol);

/**
    Splits a vertex at the center of a 4-face (or 2-face, if the vertex is on the
  boundary of the mesh) pattern of a refined 4K mesh. 
    This method is used to undo a split edge operation (see 
  topRefinement4K_SplitEdge). 
    Cohesive elements along the edges to collapse are not supported. No consistency
  checks are performed by this method.
    This method is non-recursive.
    Entity orders:

                  *                                        * 
                /   \                                    / | \
              /       \                                /   |   \
            *    El0'   *                            *     *     *
          /               \                        /  El0  |  El1  \
        /                   \                    /         |         \
       *----------*----------*    <========     *----*-----X----*-----*
        \                   /                    \         |         /
          \               /                        \  El2  |  El3  /
            *    El1'   *                            *     *      *
              \        /                               \   |    /
                \    /                                   \ |  /
                  *                                        *  
                                  
       X = colv
       Either of the two vertical edges (in this example) = cole
    Mesh modifications are notified by the callbacks: 
  TopRemoveEdgeCb(), TopRemoveVertexCb(), TopRemoveNodeCb(), TopMergeEdgeCb(),
  and TopMergeElemCb().
*/
TOPS_API void topRefinement4K_SplitVertex(TopRefinement4K* r, TopVertex v);

/**
    Returns whether the given vertex can be split.
*/
TOPS_API int topRefinement4K_CanSplitVertex(TopRefinement4K* r, TopVertex v);

/**
    Get the depth of the edge in the refinement tree.
*/
TOPS_API int topRefinement4K_GetEdgeDepth(TopRefinement4K* r, TopEdge e);

/**
    Refines all the edges which centroids are within the disc 
    <(x0,y0,z0), radius>, up to 'maxdepth' level of refinement.
*/
TOPS_API void topRefinement4K_RefineInRegion(TopRefinement4K* r, double x0, double y0, double z0, double radius, int maxdepth);

/**
    Coarsens the triangles surrounding all the vertices which positions are
    out of the disc <(x0, y0, z0), radius>, back to the initial level of refinement,
    whenever possible.
*/
TOPS_API void topRefinement4K_CoarsenOutRegion(TopRefinement4K* r, double x0, double y0, double z0, double radius);

/**********************************************
 * Three-dimensional 4K mesh adaptivity
 **********************************************/ 
typedef struct toprefinement4k3d TopRefinement4K3D;

typedef enum {
  /** Six tetrahedra per hexahedral cell. */
  TOP_REFINEMENT_4K_3D_6_TETRA_PER_CELL = 0,
  /** Six pyramids per hexaedral cell, each decomposed into 4 tetrahedra. */
  TOP_REFINEMENT_4K_3D_24_TETRA_PER_CELL
} TopRefinement4K3DTriangType;

/**
  Adaptive mesh refinement fo 3D 4K tetrahedral meshes.
  Refinement data is recorded so that the mesh can be coarsened back. 

  Currently, only regular meshes composed of linear tetrahedra (Tet4) are 
  supported. Meshes created by using the TopGridBuilder utility are
  guaranteed to be consistent for use with this refinement process.

  This object attaches itself to a model (TopModel) in order to manage 
  the refinement process. After refinement process is done
  the destructor must be called in order to release the model 
  attachment and other recorded data.
  
  Parameters:
    m      Model to be refined
    triang Initial grid triangulation type (see TopRefinement4K3DTriangType)
*/
TOPS_API TopRefinement4K3D* topCreateRefinement4K3D(TopModel* m, int triang);

/**
  Destroys the refinement manager and free allocated resources.
*/
TOPS_API void topDestroyRefinement4K3D(TopRefinement4K3D* r);

/**
  Sets a callback function for element split.
*/
TOPS_API void topRefinement4K3D_SetSplitElemCb(TopRefinement4K3D* r, TopSplitElemCb cb, void* userdata);

/**
  Sets a callback function for element merging.
*/
TOPS_API void topRefinement4K3D_SetMergeElemCb(TopRefinement4K3D* r, TopMergeElemCb cb, void* userdata);

/**
  Refines a set of elements until the given maximum level of refinement
  is reached for all of the descendant elements.
*/
TOPS_API void topRefinement4K3D_RefineElements (TopRefinement4K3D* r,
                                       int num_elems, 
                                       const TopElement* elems, 
                                       int maxlevel);

/**
  Coarsens a set of elements back until the given minimum level of 
  refinement is reached.
*/
TOPS_API void topRefinement4K3D_CoarsenElements (TopRefinement4K3D* r,
                                        int num_elems, 
                                        const TopElement* elems, 
                                        int minlevel);

#ifdef __cplusplus
}
#endif

#endif
#endif
