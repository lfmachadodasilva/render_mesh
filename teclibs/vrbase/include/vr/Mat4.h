/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_MAT4_H_
#define _VR_MAT4_H_

//! \file Mat4.h 4x4 homogeneous matrix class.

#include "Common.h"
#include "Vec3.h"
#include "Quat.h"

namespace vr {

/*! \addtogroup algebra
	@{
 */

/*!
	4x4 Homogeneous Matrix template class.
	You should use the classes vr::Mat4f or vr::Mat4d instead.

	WARNING: This method uses a column major matrix:
	If you want to use it to make Algebra calculations,
	invert columns and rows.
 */
template<typename real>
class Mat4
{
public:
    // Static Functions
    inline static Mat4<real> identity();
    inline static Mat4<real> scale( real x, real y, real z );
    inline static Mat4<real> scale( const Vec3<real>& scale );
    inline static Mat4<real> translation( real x, real y, real z );
    inline static Mat4<real> translation( const Vec3<real>& trans );
    inline static Mat4<real> rotation( real radians, const Vec3<real>& axis );
    inline static Mat4<real> rotation( Vec3<real>& axisX, Vec3<real>& axisY, Vec3<real>& axisZ );

public:
	// Public Fields
	union
	{
		real m[4][4];	//!< Treat the matrix as a matrix.
		real ptr[16];	//!< Treat the matrix as an array.
	};

	// Constructors
	inline Mat4(); // Uninitialized!
	inline Mat4( const Mat4<float>& other );
    inline Mat4( const Mat4<double>& other );
    inline explicit Mat4( float const * const ptr );
    inline explicit Mat4( double const * const ptr );
	inline Mat4( real a00, real a01, real a02, real a03,
				 real a10, real a11, real a12, real a13,
				 real a20, real a21, real a22, real a23,
				 real a30, real a31, real a32, real a33 );

	// Analysis
	inline bool isNaN() const;
	inline bool isIdentity() const;

	// Assignment
    inline Mat4<real>& operator=( const Mat4<float>& other );
    inline Mat4<real>& operator=( const Mat4<double>& other );

	// Getters
	inline real& operator()( int32 row, int32 col );
	inline real  operator()( int32 row, int32 col ) const;

	inline void getTranslation( Vec3<real>& trans ) const;
	inline void getScale( Vec3<real>& getScale ) const;
	void VRBASE_EXPORT getRotation( Quat<real>& q ) const;

	// Setters
	void VRBASE_EXPORT set( const Quat<real>& q_in );
    inline void set( const Mat4<float>& other );
    inline void set( const Mat4<double>& other );
	inline void set( float const * const ptr );
    inline void set( double const * const ptr );
	inline void set( real a00, real a01, real a02, real a03,
					 real a10, real a11, real a12, real a13,
					 real a20, real a21, real a22, real a23,
					 real a30, real a31, real a32, real a33 );

	// Only alter specific parts of the matrix
	inline void setRow( int32 row, real scalar0, real scalar1, real scalar2, real scalar3 );
	inline void setTranslation( const Vec3<real>& trans );
	inline void setTranslation( real x, real y, real z );

	// Makes this a specific kind of matrix
	void VRBASE_EXPORT makeIdentity();

	inline void makeScale( const Vec3<real>& scale );
	void VRBASE_EXPORT makeScale( real x, real y, real z );

	inline void makeTranslation( const Vec3<real>& trans );
	void VRBASE_EXPORT makeTranslation( real x, real y, real z );

	void VRBASE_EXPORT makeRotation( const Vec3<real>& from, const Vec3<real>& to );
	inline void makeRotation( real radians, const Vec3<real>& axis );
	void VRBASE_EXPORT makeRotation( real radians, real x, real y, real z );
	void VRBASE_EXPORT makeRotation( real angle1, const Vec3<real>& axis1, 
									 real angle2, const Vec3<real>& axis2, 
									 real angle3, const Vec3<real>& axis3 );

	//! Creates a rotation matrix that transforms the canonical axes into the given axes.
	inline void makeRotation( Vec3<real>& axisX, Vec3<real>& axisY, Vec3<real>& axisZ );

	// Projection Matrices

	// Set to an orthographic projection.
	void VRBASE_EXPORT makeOrtho( real left, real right, real bottom, real top, real zNear, real zFar );

	// Get the orthographic settings of the orthographic projection matrix.
	// Note, if matrix is not an orthographic matrix then invalid values will be returned.
	bool VRBASE_EXPORT getOrtho( real& left, real& right, real& bottom, real& top, real& zNear, real& zFar ) const;

	// Set to a 2D orthographic projection.
	inline void makeOrtho2D( real left, real right, real bottom, real top );

	// Set to a generic perspective projection.
	void VRBASE_EXPORT makeFrustum( real left, real right, real bottom, real top, real zNear, real zFar );

	// Get the frustum settings of a perspective projection matrix.
	// Note, if matrix is not a perspective matrix then invalid values will be returned.
	bool VRBASE_EXPORT getFrustum( real& left, real& right, real& bottom, real& top, real& zNear, real& zFar ) const;

	// Set to a symmetrical perspective projection.
	// Aspect ratio is defined as width/height.
	void VRBASE_EXPORT makePerspective( real fovy, real aspectRatio, real zNear, real zFar );

	// Get the frustum settings of a symmetric perspective projection matrix.
	// Return false if matrix is not a perspective matrix, where parameter values are undefined. 
	// Note, if matrix is not a symmetric perspective matrix then the shear will be lost.
	// Asymmetric matrices occur when stereo, power walls, caves and reality center display are used.
	// In these configuration one should use the frustum methods instead.
	bool VRBASE_EXPORT getPerspective( real& fovy, real& aspectRatio, real& zNear, real& zFar ) const;

	// Set to be a pick matrix, using the same convention as gluPickMatrix.
	// http://www.mail-archive.com/mesa3d-dev@lists.sourceforge.net/msg03610.html
	void VRBASE_EXPORT makePickMatrix( const real x, const real y, const real width, const real height, const int* viewport );

	// Set the position and orientation to be a view matrix, using the same convention as gluLookAt.
	void VRBASE_EXPORT makeLookAt( const Vec3<real>& eye, const Vec3<real>& center, const Vec3<real>& up );

	// Get to the position and orientation of a modelview matrix, using the same convention as gluLookAt.
	void VRBASE_EXPORT getLookAt( Vec3<real>& eye, Vec3<real>& center, Vec3<real>& up, real lookDistance = 1.0f ) const;

	// Arithmetic operations
	inline Mat4<real> operator*( real scalar ) const;
	inline Mat4<real> operator-() const;

	// Arithmetic updates
	inline Mat4<real>& operator*=( real scalar );

	// Matrix operations
	void VRBASE_EXPORT transpose();
	void VRBASE_EXPORT invert();

	/*!
		Assumes this is a rigid-body transformation (translation * rotation).
		Avoids expensive matrix inversion by transposing 3x3 sub-matrix and inverting the translation vector.
	 */
	void VRBASE_EXPORT invertRBT();

	// Assumes this is a rotation matrix.
	// Ortho-normalize the 3x3 rotation and scale matrix.
	void VRBASE_EXPORT orthoNormalize();

	// Apply this transformation to v
	inline void transform( Vec3<real>& v, real w = 1 ) const;
	inline void transposedTransform( Vec3<real>& v, real w = 1 ) const;

	// Apply only the 3x3 transformation to v
	inline void transform3x3( Vec3<real>& v ) const;
	inline void transposedTransform3x3( Vec3<real>& v ) const;

	//! Receives the result of a * b (this = a * b).
	//! This method follows the inverse order from Algebra.
	//! If you need to combine these two matrices as in Algebra:
	//!    v' = A * B * v
	//! You should use:
	//!    AB.product( B, A )
	void VRBASE_EXPORT product( const Mat4<real>& a, const Mat4<real>& b );
};

template<typename real>
inline std::ostream& operator<<( std::ostream& stream, const vr::Mat4<real>& mat )
{
	stream << "{" << mat(0, 0) << "," << mat(0, 1) << "," << mat(0, 2) << mat(0, 3) << "},";
	stream << "{" << mat(1, 0) << "," << mat(1, 1) << "," << mat(1, 2) << mat(1, 3) << "},";
	stream << "{" << mat(2, 0) << "," << mat(2, 1) << "," << mat(2, 2) << mat(2, 3) << "},";
	stream << "{" << mat(3, 0) << "," << mat(3, 1) << "," << mat(3, 2) << mat(3, 3) << "}";
	
	return stream;
}

/************************************************************************/
/* Mat4<real> Inline Members                                            */
/************************************************************************/

#ifndef DOXYGEN

// Static Functions

template<typename real>
inline Mat4<real> Mat4<real>::identity()
{
    Mat4<real> result;
    result.makeIdentity();
    return result;
}

template<typename real>
inline Mat4<real> Mat4<real>::scale( real x, real y, real z )
{
    return vr::Mat4<real>::scale( vr::Vec3<real>( x, y, z ) );
}

template<typename real>
inline Mat4<real> Mat4<real>::scale( const Vec3<real>& scale )
{
    Mat4<real> result;
    result.makeScale( scale );
    return result;
}

template<typename real>
Mat4<real> Mat4<real>::translation( real x, real y, real z )
{
    return vr::Mat4<real>::translation( vr::Vec3<real>( x, y, z ) );
}

template<typename real>
Mat4<real> Mat4<real>::translation( const Vec3<real>& trans )
{
    Mat4<real> result;
    result.makeTranslation( trans );
    return result;
}

template<typename real>
Mat4<real> Mat4<real>::rotation( real radians, const Vec3<real>& axis )
{
    Mat4<real> result;
    result.makeRotation( radians, axis );
    return result;
}

template<typename real>
Mat4<real> Mat4<real>::rotation( Vec3<real>& axisX, Vec3<real>& axisY, Vec3<real>& axisZ )
{
    Mat4<real> result;
    result.makeRotation( axisX, axisY, axisZ );
    return result;
}

// Constructors

template<typename real>
Mat4<real>::Mat4()
{
	// Not initialized for performance reasons!
}

template<typename real>
Mat4<real>::Mat4( const Mat4<float>& other )
{
	set( other.ptr );
}

template<typename real>
Mat4<real>::Mat4( const Mat4<double>& other )
{
    set( other.ptr );
}

template<typename real>
Mat4<real>::Mat4( float const * const ptr )
{
	set( ptr );
}

template<typename real>
Mat4<real>::Mat4( double const * const ptr )
{
    set( ptr );
}

template<typename real>
Mat4<real>::Mat4( real a00, real a01, real a02, real a03,  
						  real a10, real a11, real a12, real a13,  
						  real a20, real a21, real a22, real a23,  
						  real a30, real a31, real a32, real a33 )
{
	setRow( 0, a00, a01, a02, a03 );
	setRow( 1, a10, a11, a12, a13 );
	setRow( 2, a20, a21, a22, a23 );
	setRow( 3, a30, a31, a32, a33 );
}

// Analysis

template<typename real>
bool Mat4<real>::isNaN() const
{
	return	vr::isNaN( m[0][0] ) ||
			vr::isNaN( m[0][1] ) ||
			vr::isNaN( m[0][2] ) ||
			vr::isNaN( m[0][3] ) ||
			vr::isNaN( m[1][0] ) ||
			vr::isNaN( m[1][1] ) ||
			vr::isNaN( m[1][2] ) ||
			vr::isNaN( m[1][3] ) ||
			vr::isNaN( m[2][0] ) ||
			vr::isNaN( m[2][1] ) ||
			vr::isNaN( m[2][2] ) ||
			vr::isNaN( m[2][3] ) ||
			vr::isNaN( m[3][0] ) ||
			vr::isNaN( m[3][1] ) ||
			vr::isNaN( m[3][2] ) ||
			vr::isNaN( m[3][3] );
}

template<typename real>
bool Mat4<real>::isIdentity() const
{
	return ( m[0][0] == 1 ) && ( m[0][1] == 0 ) && ( m[0][2] == 0 ) && ( m[0][3] == 0 ) &&
		   ( m[1][0] == 0 ) && ( m[1][1] == 1 ) && ( m[1][2] == 0 ) && ( m[1][3] == 0 ) &&
		   ( m[2][0] == 0 ) && ( m[2][1] == 0 ) && ( m[2][2] == 1 ) && ( m[2][3] == 0 ) &&
		   ( m[3][0] == 0 ) && ( m[3][1] == 0 ) && ( m[3][2] == 0 ) && ( m[3][3] == 1 );
}

// Assignment

template<typename real>
Mat4<real>& Mat4<real>::operator=( const Mat4<float>& other )
{
	if( &other == this )
		return *this;
	set( other.ptr );
	return *this;
}

template<typename real>
Mat4<real>& Mat4<real>::operator=( const Mat4<double>& other )
{
    if( &other == this )
        return *this;
    set( other.ptr );
    return *this;
}

// Getters

template<typename real>
real& Mat4<real>::operator()( int32 row, int32 col )
{
	return m[row][col];
}

template<typename real>
real Mat4<real>::operator()( int32 row, int32 col ) const
{
	return m[row][col];
}

template<typename real>
void Mat4<real>::getTranslation( Vec3<real>& trans ) const
{
	trans.set( m[3] );
}

template<typename real>
void Mat4<real>::getScale( Vec3<real>& scale ) const
{
	scale.set( sqrt( m[0][0]*m[0][0] + m[1][0]*m[1][0] + m[2][0]*m[2][0] ),
			   sqrt( m[0][1]*m[0][1] + m[1][1]*m[1][1] + m[2][1]*m[2][1] ),
			   sqrt( m[0][2]*m[0][2] + m[1][2]*m[1][2] + m[2][2]*m[2][2] ) );
}

// Setters

template<typename real>
void Mat4<real>::set( const Mat4<float>& other )
{
	set( other.ptr );
}

template<typename real>
void Mat4<real>::set( const Mat4<double>& other )
{
    set( other.ptr );
}

template<typename real>
void Mat4<real>::set( float const* const ptr )
{
	for( int i = 0; i < 16; ++i )
		this->ptr[i] = static_cast<real>( ptr[i] );
}

template<typename real>
void Mat4<real>::set( double const* const ptr )
{
    for( int i = 0; i < 16; ++i )
        this->ptr[i] = static_cast<real>( ptr[i] );
}

template<typename real>
void Mat4<real>::set( real a00, real a01, real a02, real a03,  
					  real a10, real a11, real a12, real a13,  
					  real a20, real a21, real a22, real a23,  
					  real a30, real a31, real a32, real a33 )
{
	setRow( 0, a00, a01, a02, a03 );
	setRow( 1, a10, a11, a12, a13 );
	setRow( 2, a20, a21, a22, a23 );
	setRow( 3, a30, a31, a32, a33 );
}

// Only alter specific parts of the matrix

template<typename real>
void Mat4<real>::setRow( int32 row, real scalar0, real scalar1, real scalar2, real scalar3 )
{
	m[row][0] = scalar0;
	m[row][1] = scalar1;
	m[row][2] = scalar2;
	m[row][3] = scalar3;
}

template<typename real>
void Mat4<real>::setTranslation( const Vec3<real>& trans )
{
	setTranslation( trans.x, trans.y, trans.z );
}

template<typename real>
void Mat4<real>::setTranslation( real x, real y, real z )
{
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
}

// Makes this a specific kind of matrix

template<typename real>
void Mat4<real>::makeScale( const Vec3<real>& scale )
{
	makeScale( scale.x, scale.y, scale.z );
}

template<typename real>
void Mat4<real>::makeTranslation( const Vec3<real>& trans )
{
	makeTranslation( trans.x, trans.y, trans.z );
}

template<typename real>
void Mat4<real>::makeRotation( real radians, const Vec3<real>& axis )
{
	makeRotation( radians, axis.x, axis.y, axis.z );
}

template<typename real>
void Mat4<real>::makeRotation( Vec3<real>& axisX, Vec3<real>& axisY, Vec3<real>& axisZ )
{
	set( axisX.x, axisX.y, axisX.z, 0,
		 axisY.x, axisY.y, axisY.z, 0,
		 axisZ.x, axisZ.y, axisZ.z, 0,
		       0,       0,       0, 1 );
}

template<typename real>
void Mat4<real>::makeOrtho2D( real left, real right, real bottom, real top )
{
	makeOrtho( left, right, bottom, top, -1, 1 );
}

// Arithmetic operations

template<typename real>
Mat4<real> Mat4<real>::operator*( real scalar ) const
{
	return Mat4<real>( m[0][0]*scalar, m[0][1]*scalar, m[0][2]*scalar, m[0][3]*scalar,
					   m[1][0]*scalar, m[1][1]*scalar, m[1][2]*scalar, m[1][3]*scalar,
					   m[2][0]*scalar, m[2][1]*scalar, m[2][2]*scalar, m[2][3]*scalar,
					   m[3][0]*scalar, m[3][1]*scalar, m[3][2]*scalar, m[3][3]*scalar );
}

template<typename real>
Mat4<real> Mat4<real>::operator-() const
{
	return Mat4<real>( -m[0][0], -m[0][1], -m[0][2], -m[0][3],
					   -m[1][0], -m[1][1], -m[1][2], -m[1][3],
					   -m[2][0], -m[2][1], -m[2][2], -m[2][3],
					   -m[3][0], -m[3][1], -m[3][2], -m[3][3] );
}

template<typename real>
Mat4<real>& Mat4<real>::operator*=( real scalar )
{
	m[0][0] *= scalar;
	m[0][1] *= scalar;
	m[0][2] *= scalar;
	m[0][3] *= scalar;
	m[1][0] *= scalar;
	m[1][1] *= scalar;
	m[1][2] *= scalar;
	m[1][3] *= scalar;
	m[2][0] *= scalar;
	m[2][1] *= scalar;
	m[2][2] *= scalar;
	m[2][3] *= scalar;
	m[3][0] *= scalar;
	m[3][1] *= scalar;
	m[3][2] *= scalar;
	m[3][3] *= scalar;
	return *this;
}

// Matrix operations

template<typename real>
void Mat4<real>::transform( Vec3<real>& v, real w ) const
{
	const real vx = v.x;
	const real vy = v.y;
	const real vz = v.z;
	const real d = 1.0f / ( m[0][3]*vx + m[1][3]*vy + m[2][3]*vz + m[3][3]*w ) ;

	v.x = ( m[0][0]*vx + m[1][0]*vy + m[2][0]*vz + m[3][0]*w ) * d;
	v.y = ( m[0][1]*vx + m[1][1]*vy + m[2][1]*vz + m[3][1]*w ) * d;
	v.z = ( m[0][2]*vx + m[1][2]*vy + m[2][2]*vz + m[3][2]*w ) * d;
}

template<typename real>
void Mat4<real>::transposedTransform( Vec3<real>& v, real w ) const
{
	const real vx = v.x;
	const real vy = v.y;
	const real vz = v.z;
	const real d = 1.0f / ( m[3][0]*vx + m[3][1]*vy + m[3][2]*vz + m[3][3]*w ) ;

	v.x = ( m[0][0]*vx + m[0][1]*vy + m[0][2]*vz + m[0][3]*w ) * d;
	v.y = ( m[1][0]*vx + m[1][1]*vy + m[1][2]*vz + m[1][3]*w ) * d;
	v.z = ( m[2][0]*vx + m[2][1]*vy + m[2][2]*vz + m[2][3]*w ) * d;
}

template<typename real>
void Mat4<real>::transform3x3( Vec3<real>& v ) const
{
	const real vx = v.x;
	const real vy = v.y;
	const real vz = v.z;
	v.x = m[0][0]*vx + m[1][0]*vy + m[2][0]*vz;
	v.y = m[0][1]*vx + m[1][1]*vy + m[2][1]*vz;
	v.z = m[0][2]*vx + m[1][2]*vy + m[2][2]*vz;
}

template<typename real>
void Mat4<real>::transposedTransform3x3( Vec3<real>& v ) const
{
	const real vx = v.x;
	const real vy = v.y;
	const real vz = v.z;
	v.x = m[0][0]*vx + m[0][1]*vy +m[0][2]*vz;
	v.y = m[1][0]*vx + m[1][1]*vy +m[1][2]*vz;
	v.z = m[2][0]*vx + m[2][1]*vy +m[2][2]*vz;
}

#endif // DOXYGEN

/************************************************************************/
/* Matrix Functions                                                     */
/************************************************************************/

template<typename real>
inline Mat4<float> toFloat( const Mat4<real>& a )
{
	return Mat4<float>(
		a( 0, 0 ), a( 0, 1 ), a( 0, 2 ), a( 0, 3 ),
		a( 1, 0 ), a( 1, 1 ), a( 1, 2 ), a( 1, 3 ),
		a( 2, 0 ), a( 2, 1 ), a( 2, 2 ), a( 2, 3 ),
		a( 3, 0 ), a( 3, 1 ), a( 3, 2 ), a( 3, 3 ) );
}

template<typename real>
inline Mat4<double> toDouble( const Mat4<real>& a )
{
	return Mat4<double>(
		a( 0, 0 ), a( 0, 1 ), a( 0, 2 ), a( 0, 3 ),
		a( 1, 0 ), a( 1, 1 ), a( 1, 2 ), a( 1, 3 ),
		a( 2, 0 ), a( 2, 1 ), a( 2, 2 ), a( 2, 3 ),
		a( 3, 0 ), a( 3, 1 ), a( 3, 2 ), a( 3, 3 ) );
}

/************************************************************************/
/* Mat4<real> Instantiations                                            */
/************************************************************************/

//! 4x4 homogeneous matrix using float precision.
typedef Mat4<float> Mat4f;

//! 4x4 homogeneous matrix using double precision.
typedef Mat4<double> Mat4d;

/*! @} */ // end of group algebra

} // namespace vr

#endif // _VR_MAT4_H_
