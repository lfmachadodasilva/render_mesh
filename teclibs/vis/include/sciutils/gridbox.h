// gridbox.cpp
// malf@tecgraf.puc-rio.br
// Feb 2010

#ifndef SCIUTILS_GRID_BOX_H
#define SCIUTILS_GRID_BOX_H

#include "defines.h"
#include <stdlib.h>

class SCIH_API SciGridBox
{
public:

 /**
  * Constructs a new SciGridBox object.
  */
  SciGridBox ();  
 /**
  * Destroys a SciGridBox object.
  */
  ~SciGridBox ();
 /**
  * Sets the bounding box offset in percentage related to the model.
  */ 
  void SetBoxOffset (float percentage);
 /**
  * Sets the numbers of intervals for the grid.
  */
  int GetNumOfIntervals ();
  void SetNumOfIntervals (int count);
 /**
  * Sets the grid's bounding box.
  */
  void SetBoundingBox (float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
 /**
  * Gets the grid's bounding box coordinates.
  */
  void GetGridBoundingBox (float* xmin, float* xmax, float* ymin, float* ymax, float* zmin, float* zmax);
 /**
  * Gets the object's bounding box coordinates.
  */
  void GetObjectBoundingBox (float* xmin, float* xmax, float* ymin, float* ymax, float* zmin, float* zmax);


  void RecalculateGridBoundingBox ();
  void GetFaceSize (int id, int *face_w, int *face_h);
  float GetGridSqSize();
  float GetGridScaleX();
  float GetGridScaleY();
  float GetGridScaleZ();

private:
  void SetObjectBoundingBox (float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
  void SetGridBoundingBox (float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);

private:
  float m_bbox_offsetperc;    // Offset in % related to the object's Bounding box.
  float m_bbox_offset;        // Offset in pixels related to the object's Bounding box.
  int m_num_intervals;        // Number of intervals of the grid.
  float m_gridscale_x;
  float m_gridscale_y;
  float m_gridscale_z;
  float m_grid_sqsize;
  float m_obj_bbox[6];        // Object Bounding Box (xmin, xmax, ymin, ymax, zmin, zmax).
  float m_grid_bbox[6];       // Bounding Box xmin, xmax, ymin, ymax, zmin, zmax.

};

#endif
