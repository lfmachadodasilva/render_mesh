#ifndef GC_VERTEX2D_CMP_H
#define GC_VERTEX2D_CMP_H

#include "vertex2d.h"
#include "defines.h"

class GC_API gcVertex2DCompare
{
public:

  // Pontos de referência para ordenação polar

  static gcVertex2D PolarReference;
  static gcVertex2D DirectionReference;

  // Funções de comparação entre pontos 2D

  static int CompareEqual     (gcVertex2D* v1, gcVertex2D* v2); // Equality test only
  static int CompareXY        (gcVertex2D* v1, gcVertex2D* v2); // Tests    X, then    Y
  static int CompareYX        (gcVertex2D* v1, gcVertex2D* v2); // Teste    Y, then    X
  static int CompareRXY       (gcVertex2D* v1, gcVertex2D* v2); // Tests   -X, then    Y
  static int CompareRYX       (gcVertex2D* v1, gcVertex2D* v2); // Tests   -Y, then    X
  static int CompareXRY       (gcVertex2D* v1, gcVertex2D* v2); // Tests    X, then   -Y
  static int CompareYRX       (gcVertex2D* v1, gcVertex2D* v2); // Tests    Y, then   -X
  static int CompareRXRY      (gcVertex2D* v1, gcVertex2D* v2); // Tests   -X, then   -Y
  static int CompareRYRX      (gcVertex2D* v1, gcVertex2D* v2); // Tests   -Y, then   -X
  static int CompareAddSub    (gcVertex2D* v1, gcVertex2D* v2); // Tests  X+Y, then  X-Y
  static int CompareSubAdd    (gcVertex2D* v1, gcVertex2D* v2); // Tests  X-Y, then  X+Y
  static int CompareRAddSub   (gcVertex2D* v1, gcVertex2D* v2); // Tests -Y-X, then  X-Y
  static int CompareRSubAdd   (gcVertex2D* v1, gcVertex2D* v2); // Tests  Y-X, then  X+Y
  static int CompareAddRSub   (gcVertex2D* v1, gcVertex2D* v2); // Tests  X+Y, then  Y-X
  static int CompareSubRAdd   (gcVertex2D* v1, gcVertex2D* v2); // Tests  X-Y, then -Y-X
  static int CompareRAddRSub  (gcVertex2D* v1, gcVertex2D* v2); // Tests -Y-X, then  Y-X
  static int CompareRSubRAdd  (gcVertex2D* v1, gcVertex2D* v2); // Tests  Y-X, then -Y-X
  static int CompareDirection (gcVertex2D* v1, gcVertex2D* v2); // Tests  based on direction reference
  static int ComparePolar     (gcVertex2D* v1, gcVertex2D* v2); // Tests  angle, then  distance (positive x axis = angle 0)
  static int CompareRPolar    (gcVertex2D* v1, gcVertex2D* v2); // Tests -angle, then -distance (positive x axis = angle 0)
  static int CompareGenPolar  (gcVertex2D* v1, gcVertex2D* v2); // Tests  angle, then  distance (direction reference = angle 0)
  static int CompareRGenPolar (gcVertex2D* v1, gcVertex2D* v2); // Tests -angle, then -distance (direction reference = angle 0)

  // Static Configuration Variable

  static int (*CompareFunction)(gcVertex2D* v1, gcVertex2D* v2);

};

#endif // GC_VERTEX2D_CMP_H
