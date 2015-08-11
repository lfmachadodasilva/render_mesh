#ifndef GC_TRIANGLE2D_H
#define GC_TRIANGLE2D_H

#include "defines.h"

class gcVertex2D;

class GC_API gcTriangle2D
{
public:

  // Special Values

  static gcTriangle2D* GC_TRIANGLE2D_INVALID;

  // Constructors and Destructor

  gcTriangle2D (gcVertex2D* p1, gcVertex2D* p2, gcVertex2D* p3) :
  p1(p1),
  p2(p2),
  p3(p3),
  t1(NULL),
  t2(NULL),
  t3(NULL)
  {}
  
  virtual ~gcTriangle2D (void) {}

  // Getters and Setters

  gcTriangle2D* GetTriangle1        (void) const {return t1;}
  gcTriangle2D* GetTriangle2        (void) const {return t2;}
  gcTriangle2D* GetTriangle3        (void) const {return t3;}
  gcTriangle2D* GetTriangleOpposite (const gcVertex2D   *reference) const;
  gcTriangle2D* GetTriangleCW       (const gcTriangle2D *reference) const;
  gcTriangle2D* GetTriangleCW       (const gcVertex2D   *reference) const;
  gcTriangle2D* GetTriangleCCW      (const gcTriangle2D *reference) const;
  gcTriangle2D* GetTriangleCCW      (const gcVertex2D   *reference) const;

  gcVertex2D* GetVertex1            (void) const {return p1;}
  gcVertex2D* GetVertex2            (void) const {return p2;}
  gcVertex2D* GetVertex3            (void) const {return p3;}
  gcVertex2D* GetVertexOpposite     (const gcTriangle2D *reference) const;
  gcVertex2D* GetVertexOpposite     (const gcVertex2D   *reference) const;
  gcVertex2D* GetVertexCW           (const gcVertex2D   *reference) const;
  gcVertex2D* GetVertexCCW          (const gcVertex2D   *reference) const;

  void SetTriangle1         (gcTriangle2D *triangle) {t1 = triangle;}
  void SetTriangle2         (gcTriangle2D *triangle) {t2 = triangle;}
  void SetTriangle3         (gcTriangle2D *triangle) {t3 = triangle;}
  void SetTriangleOpposite  (const gcVertex2D   *reference, gcTriangle2D *triangle);
  void SetTriangleCW        (const gcTriangle2D *reference, gcTriangle2D *triangle);
  void SetTriangleCCW       (const gcTriangle2D *reference, gcTriangle2D *triangle);

  void SetVertex1           (gcVertex2D *vertex) {p1 = vertex;}
  void SetVertex2           (gcVertex2D *vertex) {p2 = vertex;}
  void SetVertex3           (gcVertex2D *vertex) {p3 = vertex;}
  void SetVertexOpposite    (const gcTriangle2D *reference, gcVertex2D *vertex);
  void SetVertexCW          (const gcVertex2D   *reference, gcVertex2D *vertex);
  void SetVertexCCW         (const gcVertex2D   *reference, gcVertex2D *vertex);

  // Geometric Methods

  gcVertex2D FindOutcircleCenter (void) const; // If points are colinear, returns p1

private:

  // Private Internal Data

  gcVertex2D* p1;
  gcVertex2D* p2;
  gcVertex2D* p3;

  gcTriangle2D *t1;
  gcTriangle2D *t2;
  gcTriangle2D *t3;

};

#endif // GC_TRIANGLE2D_H
