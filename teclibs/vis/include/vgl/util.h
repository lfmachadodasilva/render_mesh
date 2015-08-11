//* util.h
// Graphics utility functions
// celes@tecgraf.puc-rio.br
// Feb 2003

#ifndef VGL_UTIL_H
#define VGL_UTIL_H

#include "defines.h"
#include <alg/matrix.h>

class VGL_API VglUtil
{
public:
  static void XorBegin (bool useFrontBuffer = true);
  static void XorEnd ();
   /**
    * Draws a box. Useful for VglCamera box debugging.
    * xmin, xmax, ymin, ymax, zmin, zmax = box definition.
    * l(r,g,b,a) are the line colors (default=white)
    * q(r,g,b,a) are the quad colors (default=transparent yellow)
    */
   static void DrawBox (float xmin, float xmax, float ymin, float ymax, float zmin, float zmax, float lr=1.0f, float lg=1.0f, float lb=1.0f, float qr=1.0f, float qg=1.0f, float qb=0.0f, float qa=0.3f);
  static float GetZBufferValue (float x, float y);
  static AlgMatrix GetModelview ();
  static AlgMatrix GetProjection ();
  static void Project 
    (float x, float y, float z, float* winx, float* winy, float* winz);
  static void Unproject 
    (float winx, float winy, float winz, float* x, float* y, float* z);
};

#endif
