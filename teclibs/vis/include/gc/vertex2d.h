#ifndef GC_VERTEX2D_H
#define GC_VERTEX2D_H

// Vertex in 2 dimensions
//------------------------
// A vertex is not a vector. Its "position" property is given by a vector.
// Two position vectors can be added, for example, but it is meaningless
// to add vertices themselves.

#include "defines.h"
#include "dvector2d.h"

class GC_API gcVertex2D
{
public:

  // Constructors and Destructor

  gcVertex2D (void)                       : m_position()           {}
  gcVertex2D (double newAll)              : m_position(newAll)     {}
  gcVertex2D (double newX, double   newY) : m_position(newX,newY)  {}
  gcVertex2D (const double       *vtx2dv) : m_position(vtx2dv)     {}
  gcVertex2D (const gcDVector2D  &vtx2D)  : m_position(vtx2D)      {}

  virtual ~gcVertex2D (void) {}

  // Setters and Getters

  void SetPosition (double newX, double   newY) {m_position.Set(newX,newY);}
  void SetPosition (const double       *vtx2dv) {m_position.Set(vtx2dv);}
  void SetPosition (const gcDVector2D  &vtx2D)  {m_position = vtx2D;}

  gcDVector2D GetPosition (void) const {return m_position;}
  double      GetX        (void) const {return m_position.x;}
  double      GetY        (void) const {return m_position.y;}

  // Comparison
  // (to operate on vertices (not pointers) directly instead of their positions)

  bool operator == (gcVertex2D &v2) {return (CompareTo(&v2) == 0);}
  bool operator != (gcVertex2D &v2) {return (CompareTo(&v2) != 0);}
  bool operator >  (gcVertex2D &v2) {return (CompareTo(&v2) >  0);}
  bool operator >= (gcVertex2D &v2) {return (CompareTo(&v2) >= 0);}
  bool operator <  (gcVertex2D &v2) {return (CompareTo(&v2) <  0);}
  bool operator <= (gcVertex2D &v2) {return (CompareTo(&v2) <= 0);}

  virtual int CompareTo (gcVertex2D *v2);

  // Basic vector dot operations and scalar multiplication and division
  // (to operate on vertices (not pointers) directly instead of their positions)

  gcVertex2D operator + (const gcVertex2D &v2) const {return gcVertex2D(m_position + v2.GetPosition());}
  gcVertex2D operator - (const gcVertex2D &v2) const {return gcVertex2D(m_position - v2.GetPosition());}
  gcVertex2D operator * (const gcVertex2D &v2) const {return gcVertex2D(m_position * v2.GetPosition());}
  gcVertex2D operator / (const gcVertex2D &v2) const {return gcVertex2D(m_position / v2.GetPosition());}

  gcVertex2D operator * (double Sc) const {return gcVertex2D(GetPosition() * Sc);}
  gcVertex2D operator / (double Sc) const {return gcVertex2D(GetPosition() * Sc);}

  // Basic self-assignment vector dot operations
  // (to operate on vertices (not pointers) directly instead of their positions)

  void operator += (const gcVertex2D &v2)   {m_position += v2.GetPosition();}
  void operator -= (const gcVertex2D &v2)   {m_position -= v2.GetPosition();}
  void operator *= (const gcVertex2D &v2)   {m_position *= v2.GetPosition();}
  void operator /= (const gcVertex2D &v2)   {m_position /= v2.GetPosition();}

  void operator *= (double Sc) {m_position *= Sc;}
  void operator /= (double Sc) {m_position /= Sc;}

  // Vector Product Operators
  // (to operate on vertices (not pointers) directly instead of their positions)

  double operator ^ (const gcVertex2D &v2) const {return Dot(&v2);}
  double operator % (const gcVertex2D &v2) const {return Cross(&v2);}

  // Vector methods
  // - vector parameters whose name begin with "unit" must be normalized
  // - all angles are in radians

  // (to operate on vertex object pointers directly)

  double       Norm       (void) const                 {return m_position.Norm();}
  double       SqrNorm    (void) const                 {return m_position.SqrNorm();}
  double       Dot        (const gcVertex2D *v2) const {return m_position.Dot  (v2->GetPosition());}
  double       Cross      (const gcVertex2D *v2) const {return m_position.Cross(v2->GetPosition());} // z coordinate of cross product
  double       Angle      (const gcVertex2D *v2) const {return m_position.Angle(v2->GetPosition());}

  double       Dot        (const gcVertex2D &v2) const {return m_position.Dot  (v2.GetPosition());}
  double       Cross      (const gcVertex2D &v2) const {return m_position.Cross(v2.GetPosition());} // z coordinate of cross product
  double       Angle      (const gcVertex2D &v2) const {return m_position.Angle(v2.GetPosition());}

  void         Normalize  (void)                                         {m_position.Normalize();}
  void         Project    (const gcVertex2D *unitV2)                     {m_position.Project (unitV2->GetPosition());}
  void         OProject   (const gcVertex2D *unitV2)                     {m_position.OProject(unitV2->GetPosition());}
  void         Reflect    (const gcVertex2D *unitV2)                     {m_position.Reflect (unitV2->GetPosition());}
  void         RotateZ    (double angleRad)                              {m_position.RotateZ (angleRad);}
  void         RotateZ    (double angleRad, const gcVertex2D *refPoint)  {m_position.RotateZ (angleRad, refPoint->GetPosition());}

  void         Project    (const gcVertex2D &unitV2)                     {m_position.Project (unitV2.GetPosition());}
  void         OProject   (const gcVertex2D &unitV2)                     {m_position.OProject(unitV2.GetPosition());}
  void         Reflect    (const gcVertex2D &unitV2)                     {m_position.Reflect (unitV2.GetPosition());}
  void         RotateZ    (double angleRad, const gcVertex2D &refPoint)  {m_position.RotateZ (angleRad, refPoint.GetPosition());}

  // (to operate on vertices (not pointers) directly instead of their positions)

  gcVertex2D  Normalized (void) const                                         {return gcVertex2D(m_position.Normalized());}
  gcVertex2D  Projected  (const gcVertex2D &unitV2) const                     {return gcVertex2D(m_position.Projected (unitV2.GetPosition()));}
  gcVertex2D  OProjected (const gcVertex2D &unitV2) const                     {return gcVertex2D(m_position.OProjected(unitV2.GetPosition()));}
  gcVertex2D  Reflected  (const gcVertex2D &unitV2) const                     {return gcVertex2D(m_position.Reflected (unitV2.GetPosition()));}
  gcVertex2D  RotatedZ   (double angleRad) const                              {return gcVertex2D(m_position.RotatedZ  (angleRad));}
  gcVertex2D  RotatedZ   (double angleRad, const gcVertex2D &refPoint) const  {return gcVertex2D(m_position.RotatedZ  (angleRad, refPoint.GetPosition()));}
  gcVertex2D  Lerp       (const gcVertex2D &v2, double weight2) const         {return gcVertex2D(m_position.Lerp(v2.GetPosition(), weight2));}

  // Basic Geometric Primitives involving Vertices

  double  Cross               (const gcVertex2D *posRight,  const gcVertex2D *posLeft)    const;
  int     LocateAboutLine     (const gcVertex2D *lineStart, const gcVertex2D *lineEnd)    const;
  bool    OnSegment           (const gcVertex2D *segStart,  const gcVertex2D *segEnd)     const;
  int     LocateAboutSegment  (const gcVertex2D *segStart,  const gcVertex2D *segEnd)     const;
  int     TurningSide         (const gcVertex2D *lastPoint, const gcVertex2D *nextPoint)  const;

  int     InCircleDeterminant (const gcVertex2D *v1, const gcVertex2D *v2, const gcVertex2D *v3) const;
  int     InCircleExplicit    (      gcVertex2D *v1,       gcVertex2D *v2,       gcVertex2D *v3) const;

private:

  // Private Internal Data

  gcDVector2D m_position;

};

#endif // GC_VERTEX2D_H
