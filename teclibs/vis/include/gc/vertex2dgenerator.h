#ifndef GC_VERTEX2D_GENERATOR
#define GC_VERTEX2D_GENERATOR

#include "defines.h"

class gcVertex2D;

class GC_API gcVertex2DGenerator
{
public:

  // Initialization

  static void Init (void);

  // Random Vertex Generators

  static void OnLine            (gcVertex2D **vertex, const gcVertex2D *LineStart, const gcVertex2D *LineEnd);
  static void RectangleFill     (gcVertex2D **vertex, double MinX, double MinY, double MaxX, double MaxY);
  static void RectangleBorder   (gcVertex2D **vertex, double MinX, double MinY, double MaxX, double MaxY);
  static void CircleCondense    (gcVertex2D **vertex, double MinR, double MinTheta, double MaxR, double MaxTheta);
  static void CircleFill        (gcVertex2D **vertex, double MinR, double MinTheta, double MaxR, double MaxTheta);
  static void CircleBorder      (gcVertex2D **vertex, double Radius, double MinTheta, double MaxTheta);
  static void TriangleCondense  (gcVertex2D **vertex, const gcVertex2D *vertex1, const gcVertex2D *vertex2, const gcVertex2D *vertex3);
  static void TriangleFill      (gcVertex2D **vertex, const gcVertex2D *vertex1, const gcVertex2D *vertex2, const gcVertex2D *vertex3);
  static void TriangleBorder    (gcVertex2D **vertex, const gcVertex2D *vertex1, const gcVertex2D *vertex2, const gcVertex2D *vertex3);

  // Random Vertex Array Generators

  static void ArrayOnLine           (gcVertex2D* Vertices[], int numVertices, const gcVertex2D *LineStart, const gcVertex2D *LineEnd);
  static void ArrayRectangleFill    (gcVertex2D* Vertices[], int numVertices, double MinX, double MinY, double MaxX, double MaxY);
  static void ArrayRectangleBorder  (gcVertex2D* Vertices[], int numVertices, double MinX, double MinY, double MaxX, double MaxY);
  static void ArrayCircleCondense   (gcVertex2D* Vertices[], int numVertices, double MinR, double MinTheta, double MaxR, double MaxTheta);
  static void ArrayCircleFill       (gcVertex2D* Vertices[], int numVertices, double MinR, double MinTheta, double MaxR, double MaxTheta);
  static void ArrayCircleBorder     (gcVertex2D* Vertices[], int numVertices, double Radius, double MinTheta, double MaxTheta);
  static void ArrayTriangleCondense (gcVertex2D* Vertices[], int numVertices, const gcVertex2D *vertex1, const gcVertex2D *vertex2, const gcVertex2D *vertex3);
  static void ArrayTriangleFill     (gcVertex2D* Vertices[], int numVertices, const gcVertex2D *vertex1, const gcVertex2D *vertex2, const gcVertex2D *vertex3);
  static void ArrayTriangleBorder   (gcVertex2D* Vertices[], int numVertices, const gcVertex2D *vertex1, const gcVertex2D *vertex2, const gcVertex2D *vertex3);

};

#endif // GC_VERTEX2D_GENERATOR
