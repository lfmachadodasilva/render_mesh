#ifndef GC_EDGE2D_H
#define GC_EDGE2D_H

#include "defines.h"

// The gcEdge2D class represents a pair of half-edges.
// Given a start and an end vertex, the left half-edge
// goes from start to end, while the right half-edge
// goes from end to start. This ensures that both
// neighboring triangles share the same, counter-clockwise,
// orientation.

class gcVertex2D;
class gcTriangle2D;

class GC_API gcEdge2D
{
public:

  // Constructors and Destructor

  gcEdge2D (gcVertex2D *p12D, gcVertex2D *p22D) :
  p1(p12D),
  p2(p22D),
  tLeft(0),
  tRight(0)
  {}

  virtual ~gcEdge2D (void) {}

  // Getters and Setters

  void SetStartVertex     (gcVertex2D   *pStart2D) {p1     = pStart2D;}
  void SetEndVertex       (gcVertex2D   *pEnd2D)   {p2     = pEnd2D;}
  void SetLeftTriangle    (gcTriangle2D *tLeft2D)  {tLeft  = tLeft2D;}
  void SetRightTriangle   (gcTriangle2D *tRight2D) {tRight = tRight2D;}

  gcVertex2D*   GetStartVertex   (void) const {return p1;}
  gcVertex2D*   GetEndVertex     (void) const {return p2;}
  gcTriangle2D* GetLeftTriangle  (void) const {return tLeft;}
  gcTriangle2D* GetRightTriangle (void) const {return tRight;}
  bool          HasLeftTriangle  (void) const {return tLeft != NULL;}
  bool          HasRightTriangle (void) const {return tRight != NULL;}

  gcVertex2D*   GetLeftStartVertex  (void) const {return p1;}
  gcVertex2D*   GetLeftEndVertex    (void) const {return p2;}
  gcVertex2D*   GetRightStartVertex (void) const {return p2;}
  gcVertex2D*   GetRightEndVertex   (void) const {return p1;}

  // Comparison

  inline bool operator == (const gcEdge2D &e2) const {return (p1==e2.p1 && p2==e2.p2);}
  inline bool operator != (const gcEdge2D &e2) const {return (p1!=e2.p1 || p2!=e2.p2);}

  // Vector Methods

  double  Size     (void) const;
  double  SqrSize  (void) const;

private:

  // Private Internal Data

  gcVertex2D* p1;
  gcVertex2D* p2;

  gcTriangle2D* tLeft;
  gcTriangle2D* tRight;

};

#endif // GC_EDGE2D_H
