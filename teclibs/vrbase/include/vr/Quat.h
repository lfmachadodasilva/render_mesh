/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_QUAT_H_
#define _VR_QUAT_H_

//! \file Quat.h Quaternion class.

#include <ostream>

#include "Common.h"
#include "Vec3.h"

namespace vr {

/*! \addtogroup algebra
	@{
 */

/*!
	Quaternion template class.
	You should use the classes vr::Quatf or vr::Quatd instead.
 */
template<typename real>
class Quat
{
public:
    // Public members
    union
    {
        struct { real x, y, z, w; };	//!< Access to individual components.
        real ptr[4];                    //!< Treat the quaternion as an array.
    };

	// Constructors
    inline Quat(); // Uninitialized!
    inline Quat( const Quat<real>& other );
	inline Quat( real x, real y, real z, real w );
	inline Quat( real radians, const Vec3<real>& axis );
	inline Quat( real radians1, const Vec3<real>& axis1, 
				 real radians2, const Vec3<real>& axis2, 
				 real radians3, const Vec3<real>& axis3 );

	// Getters
	void VRBASE_EXPORT getRotation( real& radians, real& x, real& y, real& z ) const;
	inline void getRotation( real& radians, Vec3<real>& axis ) const;

	/// Euler rotation using Tait-Bryan rotation order:
	/// yaw-pitch-roll (around local object axis)
	/// yaw rotates around Z axis (which points up)
	/// pitch rotates around X axis (which points to the right)
	/// roll rotates around Y axis (which points forward)
	/// More information available on http://en.wikipedia.org/wiki/Tait-Bryan_angles
	void VRBASE_EXPORT getEuler( real& yaw, real& pitch, real& roll ) const;

	inline real  operator[]( int32 i ) const;
	inline real& operator[]( int32 i );

	// Setters
	inline void set( real x, real y, real z, real w );
	inline void set( const Vec3<real>& v, real w );

	// Zero Rotation
	inline bool isZeroRotation() const;
	inline void makeZeroRotation();

	// Assignment operators
	inline const Quat<real>& operator=( const Quat<real>& other );

	// Arithmetic operations
	inline Quat<real> operator+( const Quat<real>& other ) const;
	inline Quat<real> operator-( const Quat<real>& other ) const;

	//! Multiply two quaternions.
	//! This method does not follow Algebra notation. If applied on
	//! a vector, the quaternion on the left rotates first, followed by the
	//! quaternion on the right.
	inline Quat<real> operator*( const Quat<real>& other ) const;
	inline Quat<real> operator*( real scalar ) const;
	inline Quat<real> operator-() const;
	inline Quat<real> operator/( const Quat<real>& denom ) const;

	//! Rotate a vector by this Quat.
	inline Vec3<real> operator*( const Vec3<real>& v ) const;

	// Arithmetic operations (with self assignment)
	inline Quat<real>& operator+=( const Quat<real>& other );
	inline Quat<real>& operator-=( const Quat<real>& other );
	inline Quat<real>& operator*=( const Quat<real>& other );
	inline Quat<real>& operator*=( real scalar );

	// Comparison operations
	inline bool operator==( const Quat<real>& other ) const;
	inline bool operator!=( const Quat<real>& other ) const;

	// Quaternion operations
	inline real length() const;
	inline real length2() const;
	inline Quat<real> conjugate() const;
	inline Quat<real> inverse() const;

	static inline Quat<real> rotate( real radians, Vec3<real> vec );

	//! Create a rotation around an axis.
	//! This method overrides the Quaternion's current value.
	void VRBASE_EXPORT makeRotation( real radians, real x, real y, real z );

	//! Create a rotation around an axis.
	//! This method overrides the Quaternion's current value.
	inline void makeRotation( real radians, const Vec3<real>& vec );

	/// Compose a rotation around 3 axes.
	/// First applied axis is axis3, followed by axis2 in local
	/// object coordinates, followed by axis1 in local object coordinates
	inline void makeRotation( real radians1, const Vec3<real>& axis1,
							  real radians2, const Vec3<real>& axis2,
							  real radians3, const Vec3<real>& axis3 );

	/*!
		Make a rotation Quat which will rotate vec1 to vec2. Generally take a dot product to get 
		the radians between these and then use a cross product to get the rotation axis.
		Watch out for the two special cases when the vectors are co-incident or opposite in direction.
	 */
	void VRBASE_EXPORT makeRotation( const Vec3<real>& from, const Vec3<real>& to );

	/*!
		Spherical Linear Interpolation.
		As t goes from 0 to 1, the Quat object goes from "from" to "to".
	 */
	void VRBASE_EXPORT slerp( real t, const Quat<real>& from, const Quat<real>& to );

	//! Rotate a vector by this Quat.
	void VRBASE_EXPORT transform( Vec3<real>& v ) const;
};

template<typename real>
inline std::ostream& operator<<( std::ostream& stream, const vr::Quat<real>& quat )
{
	return stream << quat.x << "," << quat.y << "," << quat.z << "," << quat.w;
}

/************************************************************************/
/* Quat<real> Inline Members                                            */
/************************************************************************/

#ifndef DOXYGEN

template<typename real>
Quat<real>::Quat()
{
	// Not initialized for performance reasons!
}

template<typename real>
Quat<real>::Quat( const Quat<real>& other )
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
}

template<typename real>
Quat<real>::Quat( real x, real y, real z, real w )
{
	set( x, y, z, w );
}

template<typename real>
Quat<real>::Quat( real radians, const Vec3<real>& axis )
{
	makeRotation( radians, axis );
}

template<typename real>
Quat<real>::Quat( real radians1, const Vec3<real>& axis1,  
				  real radians2, const Vec3<real>& axis2,  
				  real radians3, const Vec3<real>& axis3 )
{
	makeRotation( radians1, axis1, radians2, axis2, radians3, axis3 );
}

template<typename real>
void Quat<real>::getRotation( real& radians, Vec3<real>& axis ) const
{
	getRotation( radians, axis.x, axis.y, axis.z );
}

template<typename real>
real Quat<real>::operator[]( int32 i ) const
{
	return ptr[i];
}

template<typename real>
real& Quat<real>::operator[]( int32 i )
{
	return ptr[i];
}

template<typename real>
void Quat<real>::set( real x, real y, real z, real w )
{
	ptr[0] = x;
	ptr[1] = y;
	ptr[2] = z;
	ptr[3] = w;
}

template<typename real>
void Quat<real>::set( const Vec3<real>& v, real w )
{
	ptr[0] = v.x;
	ptr[1] = v.y;
	ptr[2] = v.z;
	ptr[3] = w;
}

template<typename real>
bool Quat<real>::isZeroRotation() const
{
	return	vr::isEqual<real>( ptr[0], 0 ) && 
			vr::isEqual<real>( ptr[1], 0 ) && 
			vr::isEqual<real>( ptr[2], 0 ) && 
			vr::isEqual<real>( ptr[3], 1 );
}

template<typename real>
void Quat<real>::makeZeroRotation()
{
	set( 0, 0, 0, 1 );
}

// Assignment operators

template<typename real>
const Quat<real>& Quat<real>::operator=( const Quat<real>& other )
{
	ptr[0] = other.ptr[0];
	ptr[1] = other.ptr[1];
	ptr[2] = other.ptr[2];
	ptr[3] = other.ptr[3];
	return other;
}

template<typename real>
Quat<real> Quat<real>::operator+( const Quat<real>& other ) const
{
	return Quat<real>( ptr[0] + other.ptr[0], ptr[1] + other.ptr[1], ptr[2] + other.ptr[2], ptr[3] + other.ptr[3] );
}

template<typename real>
Quat<real> Quat<real>::operator-( const Quat<real>& other ) const
{
	return Quat<real>( ptr[0] - other.ptr[0], ptr[1] - other.ptr[1], ptr[2] - other.ptr[2], ptr[3] - other.ptr[3] );
}

template<typename real>
Quat<real> Quat<real>::operator*( const Quat<real>& other ) const
{
	return Quat<real>( other.ptr[3]*ptr[0] + other.ptr[0]*ptr[3] + other.ptr[1]*ptr[2] - other.ptr[2]*ptr[1],
					   other.ptr[3]*ptr[1] - other.ptr[0]*ptr[2] + other.ptr[1]*ptr[3] + other.ptr[2]*ptr[0],
					   other.ptr[3]*ptr[2] + other.ptr[0]*ptr[1] - other.ptr[1]*ptr[0] + other.ptr[2]*ptr[3],
					   other.ptr[3]*ptr[3] - other.ptr[0]*ptr[0] - other.ptr[1]*ptr[1] - other.ptr[2]*ptr[2] );
}

template<typename real>
Quat<real> Quat<real>::operator*( real scalar ) const
{
	return Quat<real>( ptr[0] * scalar, ptr[1] * scalar, ptr[2] * scalar, ptr[3] * scalar );
}

template<typename real>
Quat<real> Quat<real>::operator-() const
{
	return Quat<real>( -ptr[0], -ptr[1], -ptr[2], -ptr[3] );
}

template<typename real>
inline Quat<real> Quat<real>::operator/( const Quat<real>& denom ) const
{
	return ( denom.inverse() * ( *this ) );
}

template<typename real>
inline Vec3<real> Quat<real>::operator*( const Vec3<real>& v ) const
{
	Vec3<real> result = v;	
	transform( result );
	return result;
}


template<typename real>
Quat<real>& Quat<real>::operator+=( const Quat<real>& other )
{
	ptr[0] += other.ptr[0];
	ptr[1] += other.ptr[1];
	ptr[2] += other.ptr[2];
	ptr[3] += other.ptr[3];
	return *this;
}

template<typename real>
Quat<real>& Quat<real>::operator-=( const Quat<real>& other )
{
	ptr[0] -= other.ptr[0];
	ptr[1] -= other.ptr[1];
	ptr[2] -= other.ptr[2];
	ptr[3] -= other.ptr[3];
	return *this;
}

template<typename real>
Quat<real>& Quat<real>::operator*=( const Quat<real>& other )
{
	real x = other.ptr[3]*ptr[0] + other.ptr[0]*ptr[3] + other.ptr[1]*ptr[2] - other.ptr[2]*ptr[1];
	real y = other.ptr[3]*ptr[1] - other.ptr[0]*ptr[2] + other.ptr[1]*ptr[3] + other.ptr[2]*ptr[0];
	real z = other.ptr[3]*ptr[2] + other.ptr[0]*ptr[1] - other.ptr[1]*ptr[0] + other.ptr[2]*ptr[3];
	ptr[3]  = other.ptr[3]*ptr[3] - other.ptr[0]*ptr[0] - other.ptr[1]*ptr[1] - other.ptr[2]*ptr[2];
	ptr[2] = z;
	ptr[1] = y;
	ptr[0] = x;

	return *this;
}

template<typename real>
Quat<real>& Quat<real>::operator*=( real scalar )
{
	ptr[0] *= scalar;
	ptr[1] *= scalar;
	ptr[2] *= scalar;
	ptr[3] *= scalar;
	return *this;
}

// Comparison operations

template<typename real>
bool Quat<real>::operator==( const Quat<real>& other ) const
{
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

template<typename real>
bool Quat<real>::operator!=( const Quat<real>& other ) const
{
	return x != other.x || y != other.y || z != other.z || w != other.w;
}

// Quaternion operations

template<typename real>
real Quat<real>::length() const
{
	return sqrt( length2() );
}

template<typename real>
real Quat<real>::length2() const
{
	return ptr[0]*ptr[0] + ptr[1]*ptr[1] + ptr[2]*ptr[2] + ptr[3]*ptr[3];
}

template<typename real>
Quat<real> Quat<real>::conjugate() const
{
	return Quat<real>( -ptr[0], -ptr[1], -ptr[2], ptr[3] );
}

template<typename real>
Quat<real> Quat<real>::inverse() const
{
	return conjugate() * ( static_cast<real>(1.0) / length2() );
}

template<typename real>
Quat<real> Quat<real>::rotate( real radians, Vec3<real> vec )
{
	Quat<real> q;
	q.makeRotation( radians, vec );
	return q;
}

template<typename real>
void Quat<real>::makeRotation( real radians, const Vec3<real>& vec )
{
	makeRotation( radians, vec.x, vec.y, vec.z );
}

template<typename real>
void Quat<real>::makeRotation( real radians1, const Vec3<real>& axis1,
							   real radians2, const Vec3<real>& axis2,
							   real radians3, const Vec3<real>& axis3 )
{
	*this = Quat<real>( radians1, axis1 ) * Quat<real>( radians2, axis2 ) * Quat<real>( radians3, axis3 );
}

#endif // DOXYGEN

/************************************************************************/
/* Vectorized Math Functions                                            */
/************************************************************************/

//! A vectorized version of isEqual() for vr::Quat.
template<typename real>
inline bool isEqual( const Quat<real>& a, const Quat<real>& b, real tolerance = Math<real>::EPSILON )
{
	return isEqual<real>( a.x, b.x, tolerance ) && isEqual<real>( a.y, b.y, tolerance ) &&
		   isEqual<real>( a.z, b.z, tolerance ) && isEqual<real>( a.w, b.w, tolerance );
}

template<typename real>
inline Quat<float> toFloat( const Quat<real>& a )
{
	return Quat<float>( (float)a.x, (float)a.y, (float)a.z, (float)a.w );
}

template<typename real>
inline Quat<double> toDouble( const Quat<real>& a )
{
	return Quat<double>( (double)a.x, (double)a.y, (double)a.z, (float)a.w );
}

/************************************************************************/
/* Quat<real> Instantiations                                            */
/************************************************************************/

//! Quaternion using float precision.
typedef Quat<float> Quatf;

//! Quaternion using double precision.
typedef Quat<double> Quatd;

/*! @} */ // end of group algebra

} // namespace vr

#endif // _VR_QUAT_H_
