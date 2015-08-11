#ifndef GC_HALFEDGE2D_H
#define GC_HALFEDGE2D_H

// The gcHalfEdge2D class represents an oriented half-edge.
// Members:
// - The vertex at the end of the halfedge
// - The face to the left of the halfedge
// - The next halfedge around the left face in the counterclockwise direction
// - The previous halfedge around the left face in the counterclockwise direction
// - The symmetrical halfedge
// Methods:
// - Get the vertex at the start of the halfedge
// - Get the vertex at the end of the halfedge
// - Get the face to the left of the halfedge
// - Get the face to the right of the halfedge
// - Get the symmetrical halfedge
// - Get the next halfedge counterclockwise around the left face (previous clockwise)
// - Get the previous halfedge counterclockwise around the left face (next clockwise)
// - Get the next halfedge clockwise around the right face (previous counterclockwise)
// - Get the previous halfedge clockwise around the right face (next counterclockwise)
// - Get the next halfedge counterclockwise around the start vertex (previous clockwise)
// - Get the next halfedge counterclockwise around the end vertex (previous clockwise)
// - Get the previous halfedge counterclockwise around the start vertex (next clockwise)
// - Get the previous halfedge counterclockwise around the end vertex (next clockwise)

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "defines.h"

class gcVertex2D;
class gcTriangle2D;

//------------------//
// Class Definition //
//------------------//

class GC_API gcHalfEdge2D
{
public:

  // Constructors and Destructor

  gcHalfEdge2D ()
  : m_vEnd(0)
  , m_fLeft(0)
  , m_eNext(0)
  , m_ePrev(0)
  , m_eSym(0)
  {}

  virtual ~gcHalfEdge2D (void) {}

  // Setters and Getters

  void SetStartVertex (gcVertex2D*   vStart2D) {GetSymEdge()->SetEndVertex(vStart2D);}
  void SetEndVertex   (gcVertex2D*   vEnd2D)   {m_vEnd  = vEnd2D;}
  void SetLeftFace    (gcTriangle2D* tLeft2D)  {m_fLeft = tLeft2D;}
  void SetRightFace   (gcTriangle2D* tRight2D) {GetSymEdge()->SetLeftFace(tRight2D);}
  void SetLNextEdge   (gcHalfEdge2D* eNext2D)  {m_eNext = eNext2D;}
  void SetLPrevEdge   (gcHalfEdge2D* ePrev2D)  {m_ePrev = ePrev2D;}
  void SetSymEdge     (gcHalfEdge2D* eSym2D)   {m_eSym  = eSym2D;}

  gcVertex2D*   GetStartVertex (void) const {return GetSymEdge()->GetEndVertex();}
  gcVertex2D*   GetEndVertex   (void) const {return m_vEnd;}
  gcTriangle2D* GetLeftFace    (void) const {return m_fLeft;}
  gcTriangle2D* GetRightFace   (void) const {return GetSymEdge()->GetLeftFace();}
  gcHalfEdge2D* GetLNextEdge   (void) const {return m_eNext;}
  gcHalfEdge2D* GetLPrevEdge   (void) const {return m_ePrev;}
  gcHalfEdge2D* GetRNextEdge   (void) const {return GetSymEdge()->GetLPrevEdge()->GetSymEdge();}
  gcHalfEdge2D* GetRPrevEdge   (void) const {return GetSymEdge()->GetLNextEdge()->GetSymEdge();}
  gcHalfEdge2D* GetSymEdge     (void) const {return m_eSym;}

  gcHalfEdge2D* GetSNextEdge (void) const {return GetLPrevEdge()->GetSymEdge();}
  gcHalfEdge2D* GetSPrevEdge (void) const {return GetSymEdge()->GetLNextEdge();}
  gcHalfEdge2D* GetENextEdge (void) const {return GetSymEdge()->GetLPrevEdge();}
  gcHalfEdge2D* GetEPrevEdge (void) const {return GetLNextEdge()->GetSymEdge();}

  // Comparison

  bool operator == (const gcHalfEdge2D &e2) const
  {
    return (m_vEnd  == e2.m_vEnd  &&
            m_fLeft == e2.m_fLeft &&
            m_eNext == e2.m_eNext &&
            m_ePrev == e2.m_ePrev &&
            m_eSym  == e2.m_eSym);
  }

  bool operator != (const gcHalfEdge2D &e2) const
  {
    return (m_vEnd  != e2.m_vEnd  ||
            m_fLeft != e2.m_fLeft ||
            m_eNext != e2.m_eNext ||
            m_ePrev != e2.m_ePrev ||
            m_eSym  != e2.m_eSym);
  }

  // Vector Methods

  double Size    (void) const;
  double SqrSize (void) const;

private:

  // Private Internal Data

  gcVertex2D* m_vEnd;
  gcTriangle2D* m_fLeft;
  gcHalfEdge2D* m_eNext;
  gcHalfEdge2D* m_ePrev;
  gcHalfEdge2D* m_eSym;

};

//------------------//
// Exported Methods //
//------------------//

// Creates a pair of halfedges between the two given vertices
// Returns the halfedge that starts and ends at the respective vertices
gcHalfEdge2D* gcCreateHalfEdges (gcVertex2D* vStart, gcVertex2D* vEnd);

// Connects the end of a halfedge to the start of another
// The two given halfedges must share the same left face
void gcWeldHalfEdges (gcHalfEdge2D* e1, gcHalfEdge2D* e2);

// Connects two halfedges with a new pair of halfedges
// Returns the halfedge from the end of the first to the start of the second
// The two given and the returned halfedges must share the same left face
gcHalfEdge2D* gcConnectHalfEdges (gcHalfEdge2D* eFrom, gcHalfEdge2D* eTo);

// Deletes a pair of halfedges and updates the topology accordingly
void gcDeleteHalfEdges (gcHalfEdge2D* eDel);

#endif // GC_HALFEDGE2D_H
