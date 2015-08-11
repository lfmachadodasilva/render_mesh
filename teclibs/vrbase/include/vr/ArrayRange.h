/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_ARRAY_RANGE_H_
#define _VR_ARRAY_RANGE_H_

#include "Common.h"
#include <cassert>
#include <cstddef>

namespace vr {

/*!
	\brief An encapsulation of iterators for contiguous arrays of elements.
	The range [begin, end) is represented by two pointers.
 
	Example - how to iterate over a range:
	\code
		std::vector<int> myArray;
		myArray.push_back( 3 );
		myArray.push_back( 5 );
		myArray.push_back( 8 );
		myArray.push_back( 13 );

		for( vr::ArrayRange<int> r( myArray ); r; r.popFirst() )
		{
			print( "%i", r.getFirst() );
		}
	\endcode
 */
template<typename T>
class ArrayRange
{
public:
	//! Creates an empty array range.
	ArrayRange() : _begin( 0 ), _end( 0 )
	{;}

	/*!
		Creates the range [begin, end) out of two pointers.
		\param begin pointer to the first element in the range.
		\param end pointer to the location right after the last element in the range.
	 */
	ArrayRange( T* begin, T* end ) : _begin( begin ), _end( end )
	{
		assert( begin <= end );
	}

	//! Creates a range starting at 'array' and containing 'size' elements.
	ArrayRange( T* array, std::size_t size ) : _begin( array ), _end( array + size )
	{;}

	//! Copy constructor.
	ArrayRange( const ArrayRange& other ) : _begin( other._begin ), _end( other._end )
	{;}

	/*!
		General constructor that takes an STL-compatible array-type container and creates a range
		spanning the entire contents of the container.
	
		\warning The container type MUST store all data in a single contiguous block.
	 */
	template<typename C>
	ArrayRange( C& container ) : _begin( 0 ), _end( 0 )
	{
		if( !container.empty() )
		{
			_begin = &( container.front() );
			_end = &( container.back() ) + 1;
		}
	}

	//! Destructor.
	~ArrayRange()
	{;}

	//! Returns true if the range is empty.
	inline bool isEmpty() const { return _begin == _end; }

	//! Returns the number of elements in the range.
	inline std::size_t getSize() const { return _end - _begin; }
	
	//! Testing the range is equivalent to testing if it's not empty.
	inline operator bool() const { return _begin != _end; }

	//! Returns the first element in the range.
	//@{
	inline T& getFirst() { return *_begin; }
	inline const T& getFirst() const { return *_begin; }
	//@}

	//! Returns the last element in the range.
	//@{
	inline T& getLast() { return *( _end - 1 ); }
	inline const T& getLast() const { return *( _end - 1 ); }	
	//@}

	//! Removes the first element from the range, if it's not empty.
	inline void popFirst()
	{
		if( _begin < _end )
			++_begin;
	}

	//! Removes the last element from the range, if it's not empty.
	inline void popLast()
	{
		if( _begin < _end )
			--_end;
	}

private:
	T* _begin;
	T* _end;
};

} // namespace vr

#endif // _VR_ARRAY_RANGE_H_
