/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_VEC2_H_
#define _VR_VEC2_H_

//! \file Vec2.h 2D vector class.

#include <ostream>

#include "Common.h"
#include "Math.h"

namespace vr {

/*! \addtogroup algebra
	@{
 */

/*!
	2D Vector template class.
	You should use the classes vr::Vec2f or vr::Vec2d instead.
 */
template<typename real>
class Vec2
{
public:
	// Public members
	union
	{
		struct { real x, y; };	//!< Treat the vector as a position or direction.
		struct { real s, t; };	//!< Treat the vector as a parametric coordinate.
		real ptr[2];			//!< Treat the vector as an array.
	};

	// Constants
	inline static Vec2<real> UNIT_X();  // ( 1, 0 )
	inline static Vec2<real> UNIT_Y();  // ( 0, 1 )

	// Construction
	inline Vec2(); // Uninitialized
	inline Vec2( real scalar1, real scalar2 );
	inline explicit Vec2( real const * const pair );

	// Getters
	inline real  operator[]( int32 i ) const;
	inline real& operator[]( int32 i );

	// Setters
	inline void set( real scalar1, real scalar2 );
	inline void set( real const * const pair );

	// Arithmetic operations
	inline Vec2<real> operator+( const Vec2<real>& other ) const;
	inline Vec2<real> operator-( const Vec2<real>& other ) const;
	inline Vec2<real> operator*( const Vec2<real>& other ) const; // Componentwise
	inline Vec2<real> operator/( const Vec2<real>& other ) const; // Componentwise
	inline Vec2<real> operator*( real scalar ) const;
	inline Vec2<real> operator-() const;

	// Arithmetic updates
	inline Vec2<real>& operator+=( const Vec2<real>& other );
	inline Vec2<real>& operator-=( const Vec2<real>& other );
	inline Vec2<real>& operator*=( const Vec2<real>& other ); // Componentwise
	inline Vec2<real>& operator*=( real scalar );

	// Equality test (with no tolerance)
	inline bool operator==( const Vec2<real>& other ) const;

	// Vector operations
	inline real length() const;
	inline real length2() const;

	// Used when previous length is needed
	inline real normalize();

	// Only normalizes if needed, saves unnecessary sqrt
	inline void tryNormalize();

	// Dot Test
	inline real dot( const Vec2<real>& other ) const;
};

template<typename real>
inline std::ostream& operator<<( std::ostream& stream, const vr::Vec2<real>& vec )
{
	return stream << vec.x << "," << vec.y;
}

/************************************************************************/
/* Vec2<real> Inline Members                                            */
/************************************************************************/

#ifndef DOXYGEN

// Constants

template<typename real>
Vec2<real> Vec2<real>::UNIT_X()
{
	return Vec2<real>( 1, 0 );
}

template<typename real>
Vec2<real> Vec2<real>::UNIT_Y()
{
	return Vec2<real>( 0, 1 );
}

// Construction

template<typename real>
Vec2<real>::Vec2()
{
	// Do not initialize for performance!
}

template<typename real>
Vec2<real>::Vec2( real scalar1, real scalar2 )
	: x( scalar1 ), y( scalar2 )
{
}

template<typename real>
Vec2<real>::Vec2( real const * const pair )
	: x( pair[0] ), y( pair[1] )
{
}

// Getters

template<typename real>
real Vec2<real>::operator[]( int32 i ) const
{
	return ptr[i];
}

template<typename real>
real& Vec2<real>::operator[]( int32 i )
{
	return ptr[i];
}

// Setters

template<typename real>
void Vec2<real>::set( real scalar1, real scalar2 )
{
	x = scalar1;
	y = scalar2;
}

template<typename real>
void Vec2<real>::set( real const * const pair )
{
	x = pair[0];
	y = pair[1];
}

// Arithmetic operations

template<typename real>
Vec2<real> Vec2<real>::operator+( const Vec2<real>& other ) const
{
	return Vec2<real>( x + other.x, y + other.y );
}

template<typename real>
Vec2<real> Vec2<real>::operator-( const Vec2<real>& other ) const
{
	return Vec2<real>( x - other.x, y - other.y );
}

template<typename real>
Vec2<real> Vec2<real>::operator*( const Vec2<real>& other ) const
{
	return Vec2<real>( x * other.x, y * other.y );
}

template<typename real>
Vec2<real> Vec2<real>::operator/( const Vec2<real>& other ) const
{
	return Vec2<real>( x / other.x, y / other.y );
}

template<typename real>
Vec2<real> Vec2<real>::operator*( real scalar ) const
{
	return Vec2<real>( x * scalar, y * scalar );
}

template<typename real>
Vec2<real> Vec2<real>::operator-() const
{
	return Vec2<real>( -x, -y );
}

// Arithmetic updates

template<typename real>
Vec2<real>& Vec2<real>::operator+=( const Vec2<real>& other )
{
	x += other.x;
	y += other.y;
	return *this;
}

template<typename real>
Vec2<real>& Vec2<real>::operator-=( const Vec2<real>& other )
{
	x -= other.x;
	y -= other.y;
	return *this;
}

template<typename real>
Vec2<real>& Vec2<real>::operator*=( const Vec2<real>& other )
{
	x *= other.x;
	y *= other.y;
	return *this;
}

template<typename real>
Vec2<real>& Vec2<real>::operator*=( real scalar )
{
	x *= scalar;
	y *= scalar;
	return *this;
}

// Equality test (with no tolerance)

template<typename real>
bool Vec2<real>::operator==( const Vec2<real>& other ) const
{
	return x == other.x && y == other.y;
}

// Vector operations

template<typename real>
real Vec2<real>::length() const
{
	return sqrt( length2() );
}

template<typename real>
real Vec2<real>::length2() const
{
	return x*x + y*y;
}

// Used when previous length is needed

template<typename real>
real Vec2<real>::normalize()
{
	real len = length();
	if( len > Math<real>::ZERO_TOLERANCE )
	{
		real invLen = static_cast<real>(1.0) / len;
		x *= invLen;
		y *= invLen;
		return len;
	}
	else
	{
		x = 0;
		y = 0;
		return 0;
	}
}

// Only normalizes if needed, saves unnecessary sqrt

template<typename real>
void Vec2<real>::tryNormalize()
{
	real len2 = length2();
	if( !vr::isEqual<real>( len2, 1 ) )
	{
		real invLen = static_cast<real>(1.0) / sqrt( len2 );
		x *= invLen;
		y *= invLen;
	}
}

template<typename real>
real Vec2<real>::dot( const Vec2<real>& other ) const
{
	return x*other.x + y*other.y;
}

#endif // DOXYGEN

/************************************************************************/
/* Vec2<real> Instantiations                                            */
/************************************************************************/

//! 2D vector using float precision.
typedef Vec2<float>  Vec2f;

//! 2D vector using double precision.
typedef Vec2<double> Vec2d;

//! 2D vector using integer.
typedef Vec2<int> Vec2i;

/*! @} */ // end of group algebra

} // namespace vr

#endif // _VR_VEC2_H_
