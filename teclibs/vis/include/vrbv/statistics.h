/**
*	Statistical analysis of geometric information.
*	author: Paulo Ivson <psantos@tecgraf.puc-rio.br>
*	date:   3-Mar-2008
*/
#ifndef _VDLIB_STATISTICS_H_
#define _VDLIB_STATISTICS_H_

#include "common.h"
#include "defines.h"
#include <vr/Vec3.h>

namespace vrbv {

// Return struct for Min-Max operations.
// Stores computed minimum and maximum vertex values for each axis.
class VRBV_API MinMax
{
public:
	vr::Vec3f minValues;
	vr::Vec3f maxValues;
};

// Main algorithms
class VRBV_API Statistics
{
public:
	// Geometric mean of vertices.
	// Average equation:
	// Average = 1/n * SUM( all vertices )
	static void average( vr::Vec3f& average, const float* vertices, int size );
	// This version receives pointers to vertices and a callback to get vertices coords.
	static void average( vr::Vec3f& average, 
	                     int* geominfo_ids,
	                     int geominfo_ids_count,
	                     GeomInfoCallback* getCoords_cb );

	// Covariance around average parameter.
	// Elements of the Covariance matrix have the following closed form:
	// C[i][j] = 1/n * SUM( vm[i] * vm[j] )
	// m = average
	// vm = v - m
	static void covariance( float covariance[3][3], const vr::Vec3f& average, const float* vertices, int size );
	// This version receives pointers to vertices and a callback to get vertices coords.
	static void covariance( float covariance[3][3], 
	                        const vr::Vec3f& average, 
	                        int* geominfo_ids,
	                        int geominfo_ids_count,
	                        GeomInfoCallback* getCoords_cb );

	// Computes the minimum and maximum vertex values, along each axis X, Y and Z.
	static void minMaxVertices( MinMax& result, const float* vertices, int size );
	// This version receives pointers to vertices and a callback to get vertices coords.
	static void minMaxVertices( MinMax& result, 
	                            int* geominfo_ids,
	                            int geominfo_ids_count,
	                            GeomInfoCallback* getCoords_cb );

	// Computes the minimum and maximum vertex values along three specified axis, using center as reference point.
	static void axisMinMaxValues( MinMax& result, 
	                              const vr::Vec3f axis[3], 
	                              const vr::Vec3f& center, 
	                              const float* vertices, 
	                              int size );
	// This version receives pointers to vertices and a callback to get vertices coords.
	static void axisMinMaxValues( MinMax& result, 
	                              const vr::Vec3f axis[3], 
	                              const vr::Vec3f& center, 
	                              int* geominfo_ids,
	                              int geominfo_ids_count, 
	                              GeomInfoCallback* getCoords_cb );
};

} // namespace vdlib

#endif // _VDLIB_STATISTICS_H_
