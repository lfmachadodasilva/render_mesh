/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_VEC3_H_
#define _VR_VEC3_H_

//! \file Vec3.h 3D vector class.

#include <ostream>

#include "Common.h"
#include "Math.h"
#include "Platform.h"

namespace vr {

/*! \addtogroup algebra
	@{
 */

/*!
	3D Vector template class.
	You should use the classes vr::Vec3f or vr::Vec3d instead.
 */
template<typename real>
class
VRBASE_HEXPORT
Vec3
{
public:
	// Public members
	union
	{
		struct { real x, y, z; };	//!< Treat the vector as a position or direction.
		struct { real r, g, b; };	//!< Treat the vector as a color.
		struct { real s, t, p; };	//!< Treat the vector as a parametric coordinate.
		real ptr[3];				//!< Treat the vector as an array.
	};

	// Constants
	inline static Vec3<real> UNIT_X();  // ( 1, 0, 0 )
	inline static Vec3<real> UNIT_Y();  // ( 0, 1, 0 )
	inline static Vec3<real> UNIT_Z();  // ( 0, 0, 1 )
	inline static Vec3<real> ZERO();    // ( 0, 0, 0 )

	// Construction
	inline Vec3(); // Uninitialized!
	inline Vec3( real scalar1, real scalar2, real scalar3 );
	inline explicit Vec3( real scalar ); // x = y = z = scalar
	inline explicit Vec3( real const * const tuple );

	// Getters
	inline real  operator[]( int32 i ) const;
	inline real& operator[]( int32 i );

	// Setters
	inline void set( real scalar );
	inline void set( real scalar1, real scalar2, real scalar3 );
	inline void set( real const * const tuple );

	// Arithmetic operations
	inline Vec3<real> operator+( const Vec3<real>& other ) const;
	inline Vec3<real> operator-( const Vec3<real>& other ) const;
	inline Vec3<real> operator*( const Vec3<real>& other ) const; // Componentwise
	inline Vec3<real> operator*( real scalar ) const;
	inline Vec3<real> operator-() const;

	// Arithmetic updates
	inline Vec3<real>& operator+=( const Vec3<real>& other );
	inline Vec3<real>& operator-=( const Vec3<real>& other );
	inline Vec3<real>& operator*=( const Vec3<real>& other ); // Componentwise
	inline Vec3<real>& operator*=( real scalar );

	// Equality test (with no tolerance)
	inline bool operator==( const Vec3<real>& other ) const;

	// Inequality test (with no tolerance)
	inline bool operator!=( const Vec3<real>& other ) const;

	// Vector operations
	inline real length() const;
	inline real length2() const;

	// Used when previous length is needed
	inline real normalize();

	// Only normalizes if needed, saves unnecessary sqrt
	inline void tryNormalize();

	inline real dot( const Vec3<real>& other ) const;
	inline Vec3<real> cross( const Vec3<real>& other ) const;

	inline void makeInvalid();

	inline bool isValid() const;

	inline static Vec3<real> invalid();

	/*!
		Assuming this is an unit vector, computes the other two vectors
		that form an orthonormal
	 */
	void orthonormalBasis( Vec3<real>& u, Vec3<real>& v ) const;
};

template<typename real>
inline std::ostream& operator<<( std::ostream& stream, const vr::Vec3<real>& vec )
{
	return stream << vec.x << "," << vec.y << "," << vec.z;
}

/************************************************************************/
/* Vec3<real> Inline Members                                            */
/************************************************************************/

#ifndef DOXYGEN

// Constants

template<typename real>
Vec3<real> Vec3<real>::UNIT_X()
{
	return Vec3<real>( 1, 0, 0 );
}

template<typename real>
Vec3<real> Vec3<real>::UNIT_Y()
{
	return Vec3<real>( 0, 1, 0 );
}

template<typename real>
Vec3<real> Vec3<real>::UNIT_Z()
{
	return Vec3<real>( 0, 0, 1 );
}

template<typename real>
Vec3<real> Vec3<real>::ZERO()
{
	return Vec3<real>( 0, 0, 0 );
}

// Construction

template<typename real>
Vec3<real>::Vec3()
{
	// Not initialized for performance reasons!
}

template<typename real>
Vec3<real>::Vec3( real scalar1, real scalar2, real scalar3 )
	: x( scalar1 ), y( scalar2 ), z( scalar3 )
{
}

template<typename real>
Vec3<real>::Vec3( real scalar )
: x( scalar ), y( scalar ), z( scalar )
{
}

template<typename real>
Vec3<real>::Vec3( real const * const tuple )
	: x( tuple[0] ), y( tuple[1] ), z( tuple[2] )
{
}

// Getters

template<typename real>
real Vec3<real>::operator[]( int32 i ) const
{
	return ptr[i];
}

template<typename real>
real& Vec3<real>::operator[]( int32 i )
{
	return ptr[i];
}

// Setters

template<typename real>
void Vec3<real>::set( real scalar )
{
	x = scalar;
	y = scalar;
	z = scalar;
}

template<typename real>
void Vec3<real>::set( real scalar1, real scalar2, real scalar3 )
{
	x = scalar1;
	y = scalar2;
	z = scalar3;
}

template<typename real>
void Vec3<real>::set( real const * const tuple )
{
	x = tuple[0];
	y = tuple[1];
	z = tuple[2];
}

// Arithmetic operations

template<typename real>
Vec3<real> Vec3<real>::operator+( const Vec3<real>& other ) const
{
	return Vec3<real>( x + other.x, y + other.y, z + other.z );
}

template<typename real>
Vec3<real> Vec3<real>::operator-( const Vec3<real>& other ) const
{
	return Vec3<real>( x - other.x, y - other.y, z - other.z );
}

template<typename real>
Vec3<real> Vec3<real>::operator*( const Vec3<real>& other ) const
{
	return Vec3<real>( x * other.x, y * other.y, z * other.z );
}

template<typename real>
Vec3<real> Vec3<real>::operator*( real scalar ) const
{
	return Vec3<real>( x * scalar, y * scalar, z * scalar );
}

template<typename real>
Vec3<real> Vec3<real>::operator-() const
{
	return Vec3<real>( -x, -y, -z );
}

// Arithmetic updates

template<typename real>
Vec3<real>& Vec3<real>::operator+=( const Vec3<real>& other )
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

template<typename real>
Vec3<real>& Vec3<real>::operator-=( const Vec3<real>& other )
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

template<typename real>
Vec3<real>& Vec3<real>::operator*=( const Vec3<real>& other )
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

template<typename real>
Vec3<real>& Vec3<real>::operator*=( real scalar )
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

// Equality test (with no tolerance)

template<typename real>
bool Vec3<real>::operator==( const Vec3<real>& other ) const
{
	return x == other.x && y == other.y && z == other.z;
}

// Inequality test (with no tolerance)

template<typename real>
bool Vec3<real>::operator!=( const Vec3<real>& other ) const
{
	return x != other.x || y != other.y || z != other.z;
}

// Vector operations

template<typename real>
real Vec3<real>::length() const
{
	return sqrt( length2() );
}

template<typename real>
real Vec3<real>::length2() const
{
	return x*x + y*y + z*z;
}

template<typename real>
real Vec3<real>::normalize()
{
	real len = length2();
	if( len > Math<real>::ZERO_TOLERANCE * Math<real>::ZERO_TOLERANCE )
	{
		len = sqrt( len );
		real invLen = static_cast<real>( 1.0 ) / len;
		x *= invLen;
		y *= invLen;
		z *= invLen;
		return len;
	}
	else
	{
		x = 0;
		y = 0;
		z = 0;
		return 0;
	}
}

template<typename real>
void Vec3<real>::tryNormalize()
{
	real len2 = length2();
	if( !vr::isEqual<real>( len2, 1 ) && !vr::isEqual<real>( len2, 0 ))
	{
		real invLen = static_cast<real>( 1.0 ) / sqrt( len2 );
		x *= invLen;
		y *= invLen;
		z *= invLen;
	}
}

template<typename real>
real Vec3<real>::dot( const Vec3<real>& other ) const
{
	return x*other.x + y*other.y + z*other.z;
}

template<typename real>
Vec3<real> Vec3<real>::cross( const Vec3<real>& other ) const
{
	return Vec3<real>(	y*other.z - z*other.y,
					    z*other.x - x*other.z,
					    x*other.y - y*other.x );
}

template<typename real>
inline void Vec3<real>::makeInvalid()
{
	set( vr::Math<real>::NAN_VALUE );
}

template<typename real>
inline bool Vec3<real>::isValid() const
{
	return !vr::isNaN( x ) && !vr::isNaN( y ) && !vr::isNaN( z );
}

template<typename real>
inline Vec3<real> Vec3<real>::invalid()
{
	Vec3<real> result( vr::Math<real>::NAN_VALUE );
	return result;
}

#endif // DOXYGEN

/************************************************************************/
/* Vectorized Math Functions                                            */
/************************************************************************/

//! A vectorized version of isEqual() for vr::Vec3.
template<typename real>
inline bool isEqual( const Vec3<real>& a, const Vec3<real>& b, real tolerance = Math<real>::EPSILON )
{
	return isEqual<real>( a.x, b.x, tolerance ) &&
		   isEqual<real>( a.y, b.y, tolerance ) &&
		   isEqual<real>( a.z, b.z, tolerance );
}

template<typename real>
inline Vec3<float> toFloat( const Vec3<real>& a )
{
	return Vec3<float>( (float)a.x, (float)a.y, (float)a.z );
}

template<typename real>
inline Vec3<double> toDouble( const Vec3<real>& a )
{
	return Vec3<double>( (double)a.x, (double)a.y, (double)a.z );
}

/************************************************************************/
/* Vec3<real> Instantiations                                            */
/************************************************************************/

//! 3D vector using float precision.
typedef Vec3<float>  Vec3f;

//! 3D vector using double precision.
typedef Vec3<double> Vec3d;

/*! @} */ // end of group algebra

} // namespace vr

#endif // _VR_VEC3_H_
