/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_STL_UTILS_H_
#define _VR_STL_UTILS_H_

#include <vr/Common.h>
#include <map>
#include <set>
#include <vector>
#include <ostream>

/*!
	\file STLUtils.h Contains utility functions to manipulate objects from the Standard Template Library.
 */

namespace vr {

/*!
	Sets new capacity equal to new size, do not grow vector by half.
	Used when exact number of elements is previously known, optimizing memory allocation.
 */
template<typename T>
inline static void vectorExactResize( std::vector<T>& v, uint32 newSize )
{
	v.reserve( newSize );
	v.resize( newSize );
}

/*!
	Sets new capacity equal to new size, do not grow vector by half.
	Used when exact number of elements is previously known, optimizing memory allocation.
	Parameter <tt>pad</tt> is used for new elements added if the new size is larger that the original size.
 */
template<typename T>
inline static void vectorExactResize( std::vector<T>& v, uint32 newSize, T pad )
{
	v.reserve( newSize );
	v.resize( newSize, pad );
}

/*!
	The following need to temporarily duplicate the vectors.
	They are not recommended for very large vectors.
 */

//! Sets vector to interval [<tt>first</tt>, <tt>last</tt>], erases all other data
template<typename T>
inline static void vectorClip( std::vector<T>& v, uint32 first, uint32 last )
{
	std::vector<T>( v.begin() + first, v.begin() + last ).swap( v );
}

//! Sets capacity equal to current size. Free unused memory.
template<typename T>
inline static void vectorTrim( std::vector<T>& v )
{
	std::vector<T>( v ).swap( v );
}

//! Sets size and capacity to zero. Free all memory.
template<typename T>
inline static void vectorFreeMemory( std::vector<T>& v )
{
	std::vector<T>().swap( v );
}

} // namespace vr

//! Operator to make std::vectors compatible with streams.
template<typename T>
inline static std::ostream& operator<<( std::ostream& stream, const std::vector<T>& v )
{
	if( v.empty() )
		return (stream << "vector: empty");
	
	if( v.size() == 1 )
		return (stream << "vector: 1 element");
	
	return (stream << "vector: " << v.size() << " elements");
}

//! Operator to make std::maps compatible with streams.
template<typename K, typename T>
inline static std::ostream& operator<<( std::ostream& stream, const std::map<K, T>& m )
{
	if( m.empty() )
		return (stream << "map: empty");
	
	if( m.size() == 1 )
		return (stream << "map: 1 element");
	
	return (stream << "map: " << m.size() << " elements");
}

//! Operator to make std::multisets compatible with streams.
template<typename T>
inline static std::ostream& operator<<( std::ostream& stream, const std::multiset<T>& ms )
{
	if( ms.empty() )
		return (stream << "multiset: empty");
	
	if( ms.size() == 1 )
		return (stream << "multiset: 1 element");
	
	return (stream << "multiset: " << ms.size() << " elements");
}

#endif // _VR_STL_UTILS_H_
