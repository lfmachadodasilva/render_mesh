/*! The MIT License

Copyright( c ) 2008, by Attractive Chaos <attractivechaos@aol.co.uk>

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files( the
"Software" ), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Standalone hash library is a free C++ template library for hash tables.
It implements open-address hashing with the "double hashing" technique,
which makes this library different from most of other implementations,
such as STL and TR1 hash based classes, which are all based on chained
hashing. However, fewer implementations do not mean open-address hashing
is less efficient. As a matter of fact, this hash library is at least as
efficient, in terms of both time and space, as STL and TR1 libraries, and
in some cases outperforms others.
*/

#ifndef _VR_HASHMAP_H_
#define _VR_HASHMAP_H_

#include <string.h>
#include <stdlib.h>
#include "Common.h"

//! Even on 64-bit systems, HashInt should be INT32
typedef vr::uint32 HashInt; 

//! Hash functions

/*! Hash function for strings( char* ) */
HashInt _x31HashString( const char *s )
{
	HashInt h = *s;
	if ( h )
		for ( ++s ; *s; ++s )
			h = ( h << 5 ) - h + *s;
	return h;
}


/*! Jenkins' hash function for 32-bit integers. Not used in this library. */
vr::uint32 _jenkinsHash32( vr::uint32 key )
{
	key += ( key << 12 );
	key ^= ( key >> 22 );
	key += ( key << 4 );
	key ^= ( key >> 9 );
	key += ( key << 10 );
	key ^= ( key >> 2 );
	key += ( key << 7 );
	key ^= ( key >> 12 );
	return key;
}

/*! Jenkins hash function for 64-bit integers.*/
vr::uint64 _jenkinsHash64( vr::uint64 key )
{
	key += ~( key << 32 );
	key ^= ( key >> 22 );
	key += ~( key << 13 );
	key ^= ( key >> 8 );
	key += ( key << 3 );
	key ^= ( key >> 15 );
	key += ~( key << 27 );
	key ^= ( key >> 31 );
	return key;
}

/*! Wang's hash function for 32-bit integers.*/
vr::uint32 _wangHash32( vr::uint32 key )
{
	key += ~( key << 15 );
	key ^=  ( key >> 10 );
	key +=  ( key << 3 );
	key ^=  ( key >> 6 );
	key += ~( key << 11 );
	key ^=  ( key >> 16 );
	return key;
}

/*! Common hash functions */
struct CommonHash
{
	inline HashInt operator () ( vr::uint16 key ) const { return key; }
	inline HashInt operator () ( vr::uint32 key ) const { return key; }
	inline HashInt operator () ( vr::uint64 key ) const { return vr::uint32( key >> 19 ) ^ vr::uint32( key ); }
	inline HashInt operator () ( const char *p ) const { return _x31HashString( p ); }
	inline HashInt operator () ( int key ) const { return key; }
};

/*! Alternative common hash functions */
struct AlternativeHash
{
	inline HashInt operator () ( vr::uint16 key ) const { return _wangHash32( vr::uint32( key ) ); }
	inline HashInt operator () ( vr::uint32 key ) const { return _wangHash32( key ); }
	inline HashInt operator () ( vr::uint64 key ) const { return ( HashInt ) _jenkinsHash64( key ); }
	inline HashInt operator () ( const char *p ) const { return _x31HashString( p ); }
	inline HashInt operator () ( int key ) const { return _wangHash32( key ); }
};

/*! Common key comparisons */
struct KeyComparison
{
	inline bool operator () ( const char *a, const char *b ) const { return strcmp( a, b ) == 0; }
	inline bool operator () ( vr::uint16 a, vr::uint16 b ) const { return a == b; }
	inline bool operator () ( vr::uint32 a, vr::uint32 b ) const { return a == b; }
	inline bool operator () ( vr::uint64 a, vr::uint64 b ) const { return a == b; }
	inline bool operator () ( int a, int b ) const { return a == b; }
};

template<class T1, class T2>
struct pair
{
	T1 first;
	T2 second;
	pair() {};
	pair( const T1 &a, const T2 &b ) : first( a ), second( b ) {};
};

/*! Table for primes */
const int HASH_PRIME_SIZE = 32;
static const vr::uint32 PRIME_LIST[HASH_PRIME_SIZE] =
{
	0ul,          3ul,          11ul,         23ul,         53ul,
	97ul,         193ul,        389ul,        769ul,        1543ul,
	3079ul,       6151ul,       12289ul,      24593ul,      49157ul,
	98317ul,      196613ul,     393241ul,     786433ul,     1572869ul,
	3145739ul,    6291469ul,    12582917ul,   25165843ul,   50331653ul,
	100663319ul,  201326611ul,  402653189ul,  805306457ul,  1610612741ul,
	3221225473ul, 4294967291ul
};

/*! Threshold for rehashing */
const double HASH_UPPER = 0.77;

/*! Constants and macros for retrieve/set flags "_IS_EMPTY" and "_IS_DELETED". */
typedef vr::uint32 FlagHash;

const int FLAG_SHIFT = 4;
const int FLAG_MASK = 0xful;
const FlagHash FLAG_DEFAULT = 0xaaaaaaaaul;

#define _IS_BOTH( flag, i )(( flag[i >> FLAG_SHIFT] >>(( i & FLAG_MASK ) << 1 ) ) & 3 )
#define _IS_EMPTY( flag, i )(( flag[i >> FLAG_SHIFT] >>(( i & FLAG_MASK ) << 1 ) ) & 2 )
#define _IS_DELETED( flag, i )(( flag[i >> FLAG_SHIFT] >>(( i & FLAG_MASK ) << 1 ) ) & 1 )
#define _SET_IS_BOTH_FALSE( flag, i )( flag[i >> FLAG_SHIFT] &=~( 3ul <<(( i & FLAG_MASK ) << 1 ) ) )
#define _SET_IS_EMPTY_FALSE( flag, i )( flag[i >> FLAG_SHIFT] &=~( 2ul <<(( i & FLAG_MASK ) << 1 ) ) )
#define _SET_IS_DELETED_TRUE( flag, i )( flag[i >> FLAG_SHIFT]|= 1ul <<(( i & FLAG_MASK ) << 1 ) )
#define _SET_IS_DELETED_FALSE( flag, i )( flag[i >> FLAG_SHIFT] &=~( 1ul <<(( i & FLAG_MASK ) << 1 ) ) )

/*! Auxiliary functions for search/insert/erase.*/

template <class KeyType, class Hashf, class Hasheq>
HashInt hashSearchAux( const KeyType &key, HashInt m, const KeyType *keys, const FlagHash *flag,
													const Hashf &hashFunction, const Hasheq &hashEq )
{
	if( !m )
		return 0;

	HashInt inc, k, i;

	k = hashFunction( key );
	i = k % m;
	inc = 1 + k %( m - 1 );

	HashInt last = i;

	while( !_IS_EMPTY( flag, i ) && ( _IS_DELETED( flag, i ) || !hashEq( keys[i], key ) ) )
	{
		if( i + inc >= m )
			i = i + inc - m; //! inc < m, and so never write this line as: "i += inc - m;"
		else
			i += inc;

		if( i == last )
			return m; //! fail to find
	}

	return i;
}

template <class KeyType, class Hashf, class Hasheq>
HashInt hashInsertAux( const KeyType &key, HashInt m, const KeyType *keys, const FlagHash *flag, 
													const Hashf &hashFunction, const Hasheq &hashEq )
{
	HashInt inc, k, i, site;

	site = m;
	k = hashFunction( key );
	i = k % m;
	inc = 1 + k %( m - 1 );

	HashInt last = i;

	while( !_IS_EMPTY( flag, i ) && ( _IS_DELETED( flag, i ) || !hashEq( keys[i], key ) ) )
	{
		if( _IS_DELETED( flag, i ) )
			site = i;

		if( i + inc >= m )
			i = i + inc - m;
		else
			i += inc;

		if( i == last )
			return site;
	}

	if( _IS_EMPTY( flag, i ) && site != m )
		return site;
	else
		return i;
}

template <class KeyType, class Hashf, class Hasheq>
HashInt hashEraseAux( const KeyType &key, HashInt m, const KeyType *keys, FlagHash *flag, const Hashf &hashFunction, const Hasheq &hashEq )
{
	if( !m )
		return 0;

	HashInt i = hashSearchAux( key, m, keys, flag, hashFunction, hashEq );

	if( i != m && !_IS_EMPTY( flag, i ) )
	{
		if( _IS_DELETED( flag, i ) )
			return m; //! has been deleted

		_SET_IS_DELETED_TRUE( flag, i );
		return i;
	}
	else
		return m;
}

/*! "HashBaseIterator" class for "hash_set_char" and "HashSet" */
template <class KeyType>
class HashBaseIterator
{
protected:
	HashInt i;
	const KeyType *keys;
	const FlagHash *flags;

public:
	HashBaseIterator() {}
	HashBaseIterator( HashInt _i, const KeyType *_keys, const FlagHash *_flags ): i( _i ), keys( _keys ), flags( _flags ) {};
	inline const KeyType &operator &() const { return keys[i]; } //! Keys should never be changed by an iterator.
	inline const KeyType &key() const { return keys[i]; } //! an alias of the operator "&"
	inline bool operator != ( const HashBaseIterator &iter ) const { return i != iter.i; }
	inline bool operator == ( const HashBaseIterator &iter ) const { return i == iter.i; }
	inline bool operator < ( const HashBaseIterator &iter ) const { return i < iter.i; }
	inline bool operator > ( const HashBaseIterator &iter ) const { return i > iter.i; }
	inline void operator ++ () { ++i; }
	inline void operator ++ ( int ) { ++i; }
	inline void operator -- () { --i; }
	inline void operator -- ( int ) { --i; }
	inline bool isfilled() const { return !_IS_BOTH( flags, i ); }
	inline bool operator + () const { return isfilled(); } //! an alias of "isfilled()"
	inline HashInt pos() const { return i; }
};

/*! "HashValueIterator" class for "hash_map_char" and "hash_map_misc" */
template <class KeyType, class ValueType>
class HashValueIterator : public HashBaseIterator<KeyType>
{
protected:
	ValueType *values;

public:
	HashValueIterator() {}
	HashValueIterator( HashInt _i, const KeyType *_keys, const FlagHash *_flags, ValueType *_values ) 
								: HashBaseIterator<KeyType>( _i, _keys, _flags ), values( _values ) {};
	inline ValueType &operator * () { return values[this->i]; } //! Values can be changed here.
	inline const ValueType &value () const { return values[this->i]; }
	inline void value( const ValueType &v ) { values[this->i] = v; }
};

/*! HashBase class of all hash classes */
template <class KeyType, class Hashf = CommonHash, class Hasheq = KeyComparison>
class HashBase
{
protected:
	HashInt _capacity; /*! < maximum size of the hash table */
	HashInt _size; /*! < number of elements in hash table */
	HashInt _occupied; /*! < number of cells that have not been flaged as "IS_EMPTY"( _capacity >= _occupied >= _size ) */
	HashInt _upperBound; /*! < The upper bound. When _occupied exceeds this, rehashing will be performed. */
	FlagHash *flags; /*! < flag array which stores the status "IS_EMPTY" or "IS_DELETED" of each hash cell. */
	KeyType *keys; /*! < array that stores hash keys */

	//! return 0 for unchanged, 1 for empty, 2 for deleted
	int directInsertAux( const KeyType &key, HashInt m, KeyType *K, FlagHash *F, HashInt *i )
	{
		*i = hashInsertAux( key, m, K, F, Hashf(), Hasheq() );
		if( _IS_EMPTY( F, *i ) )
		{
			K[*i] = key;
			_SET_IS_BOTH_FALSE( F, *i );
			return 1;
		}
		else if( _IS_DELETED( F, *i ) )
		{
			K[*i] = key;
			_SET_IS_BOTH_FALSE( F, *i );
			return 2;
		}
		else
			return 0;
	}

	bool resizeAux1( HashInt *newCapacity, FlagHash **newFlags )
	{
		HashInt t;

		t = HASH_PRIME_SIZE - 1;

		while( PRIME_LIST[t] > *newCapacity )
			--t;

		*newCapacity = PRIME_LIST[t+1];

		if( _size >= HashInt( *newCapacity * HASH_UPPER + 0.5 ) )
			return false;

		keys =( KeyType* )realloc( keys, *newCapacity * sizeof( KeyType ) );

		if( keys == 0 )
			return false;

		*newFlags =( FlagHash* )malloc( ( ( *newCapacity >> FLAG_SHIFT ) + 1 ) * sizeof( FlagHash ) );

		if( *newFlags == 0 )
		{ 
			::free( *newFlags );
			return false;
		}

		for( t = 0; t <(( *newCapacity >> FLAG_SHIFT ) + 1 ); ++t )
			( *newFlags )[t] = FLAG_DEFAULT;
		return true;
	}

	void resizeAux2( HashInt newCapacity, FlagHash *newFlags )
	{
		::free( flags );
		flags = newFlags;
		_capacity = newCapacity;
		_occupied = _size;
		_upperBound = HashInt( _capacity * HASH_UPPER + 0.5 );
	}

	/*! Test whether rehashing is needed and perform rehashing if this is the fact. */
	void rehash()
	{
		if( _occupied >= _upperBound )
		{
			if( _capacity >( _size << 1 ) )
				//! do not enlarge
				resize( _capacity - 1 );
			else
				//! enlarge the capacity
				resize( _capacity + 1 );
		}
	}

public:
	HashBase( void )
	{
		keys = 0;
		flags = 0;
		_capacity = _size = _occupied = _upperBound = 0;;
	}

	~HashBase( void )
	{
		::free( keys );
		::free( flags );
	}

	/*! resize the hash table and perform rehashing */
	bool resize( HashInt newCapacity )
	{
		FlagHash *newFlags;
		if( !resizeAux1( &newCapacity, &newFlags ) )
			return false;
		for( HashInt j = 0; j != _capacity; ++j )
		{
			if( _IS_BOTH( flags, j ) == 0 )
			{
				KeyType key = keys[j]; //! take out the key
				_SET_IS_DELETED_TRUE( flags, j ); //! mark "deleted"
				while( 1 )
				{
					HashInt inc, k, i;
					k = Hashf()( key );
					i = k % newCapacity; //! calculate the new position
					inc = 1 + k %( newCapacity - 1 );
					while( !_IS_EMPTY( newFlags, i ) )
					{
						if( i + inc >= newCapacity )
							i = i + inc - newCapacity;
						else
							i += inc;
					}
					_SET_IS_EMPTY_FALSE( newFlags, i );
					if( i < this->_capacity && _IS_BOTH( flags, i ) == 0 )
					{ 
						//! something is here
						{
							KeyType tmp = keys[i];
							keys[i] = key;
							key = tmp;
						}
						//! take it out
						_SET_IS_DELETED_TRUE( flags, i );
					} 
					else
					{ 
						//! put key and quit the loop
						keys[i] = key;
						break;
					}
				}
			}
		}
		resizeAux2( newCapacity, newFlags );
		return true;
	}

	inline void rehash( HashInt n ) { resize( n ); }

	/*! get _size */
	inline HashInt getSize( void ) const { return _size; };

	/*! get _capacity */
	inline HashInt getCapacity( void ) const { return _capacity; };

	/*! clear the hash table, but do not free the memory */
	void clear( void )
	{
		if( flags )
		{
			for( HashInt t = 0; t <(( _capacity >> FLAG_SHIFT ) + 1 ); ++t )
				flags[t] = FLAG_DEFAULT;
		}
		_size = 0;
	}

	/*! clear the hash table and free the memory */
	void free()
	{
		::free( keys );
		::free( flags );
		keys = 0;
		flags = 0;
		_capacity = _size = _occupied = _upperBound = 0;;
	}
};


/*! HashSet class */
template <class KeyType, class Hashf = CommonHash, class Hasheq = KeyComparison>
class HashSet : public HashBase<KeyType, Hashf, Hasheq>
{
	typedef HashSet<KeyType, Hashf, Hasheq> SelfType;
	typedef pair<HashBaseIterator<KeyType>, bool> InsertPair;

public:
	typedef HashBaseIterator<KeyType> Iterator;

	HashSet( void ) {};
	~HashSet( void ) {};

	/*! clone */
	SelfType *clone() const
	{
		SelfType *h2;
		
		h2 = new SelfType;
		memcpy( h2, this, sizeof( SelfType ) );
		h2->flags =( FlagHash* ) malloc( ( ( this->_capacity >> FLAG_SHIFT ) + 1 ) * sizeof( FlagHash ) );
		memcpy( h2->flags, this->flags, sizeof( FlagHash ) *( ( this->_capacity >> FLAG_SHIFT ) + 1 ) );
		h2->keys =( KeyType* ) malloc( this->_capacity * sizeof( KeyType ) );
		memcpy( h2->keys, this->keys, this->_capacity * sizeof( KeyType ) );

		return h2;
	}

	/*! search a key */
	Iterator find( const KeyType &key )
	{
		HashInt i = hashSearchAux( key, this->_capacity, this->keys, this->flags, Hashf(), Hasheq() );
		return( i == this->_capacity || _IS_BOTH( this->flags, i ) )? this->end() : Iterator( i, this->keys, this->flags );
	}

	/*! insert a key */
	InsertPair insert( const KeyType &key )
	{
		HashBase<KeyType>::rehash();
		HashInt i;
		int ret = directInsertAux( key, this->_capacity, this->keys, this->flags, &i );

		if( ret == 0 )
			return InsertPair( Iterator( i, this->keys, this->flags ), false );

		if( ret == 1 )
		{ 
			++( this->_size );
			++( this->_occupied );
		}
		else
			++( this->_size ); //! then ret == 2

		return InsertPair( Iterator( i, this->keys, this->flags ), true );
	}

	/*! delete a key */
	Iterator erase( const KeyType &key )
	{
		HashInt i = hashEraseAux( key, this->_capacity, this->keys, this->flags, Hashf(), Hasheq() );

		if( i != this->_capacity )
		{
			--( this->_size );
			return Iterator( i, this->keys, this->flags );
		}
		else
			return this->end();
	}

	void erase( Iterator &p )
	{
		if( p != this->end() && !_IS_EMPTY( this->flags, p.pos() ) )
		{
			if( !_IS_DELETED( this->flags, p.pos() ) )
			{
				_SET_IS_DELETED_TRUE( this->flags, p.pos() );
				--( this->_size );
			}
		}
	}

	/*! the first iterator */
	inline Iterator begin() { return Iterator( 0, this->keys, this->flags ); }

	/*! the last iterator */
	inline Iterator end() { return Iterator( this->_capacity, this->keys, this->flags ); }
};

/*! hash_map_misc class */
template <class KeyType, class ValueType, class Hashf = CommonHash, class Hasheq = KeyComparison>
class HashMap : public HashSet<KeyType, Hashf, Hasheq>
{
	ValueType *values;

	/*! a copy of HashBase<keytype>::rehash() */
	void rehash()
	{
		if( this->_occupied >= this->_upperBound )
		{
			if( this->_capacity >( this->_size << 1 ) )
				resize( this->_capacity - 1 );
			else
				resize( this->_capacity + 1 );
		}
	}

	typedef HashMap<KeyType, ValueType, Hashf, Hasheq> SelfType;
	typedef pair<HashValueIterator<KeyType, ValueType>, bool> InsertPair;

public:
	HashMap( void ) { values = 0; };
	~HashMap( void ) { ::free( values ); };

	typedef HashValueIterator<KeyType, ValueType> Iterator;

	inline void rehash( HashInt n ) { resize( n ); }
	inline Iterator begin() { return Iterator( 0, this->keys, this->flags, values ); }
	inline Iterator end() { return Iterator( this->_capacity, this->keys, this->flags, values ); }

	/*! clone */
	SelfType *clone() const
	{
		SelfType *h2;
		h2 = new SelfType;
		memcpy( h2, this, sizeof( SelfType ) );
		h2->flags =( FlagHash* )malloc((( this->_capacity >> FLAG_SHIFT ) + 1 ) * sizeof( FlagHash ) );
		memcpy( h2->flags, this->flags, sizeof( FlagHash ) *(( this->_capacity >> FLAG_SHIFT ) + 1 ) );
		h2->keys =( KeyType* )malloc( this->_capacity * sizeof( KeyType ) );
		memcpy( h2->keys, this->keys, this->_capacity * sizeof( KeyType ) );
		h2->values =( ValueType* )malloc( this->_capacity * sizeof( ValueType ) );
		memcpy( h2->values, this->values, this->_capacity * sizeof( ValueType ) );
		return h2;
	}

	/*! analogy of HashBase<keytype>::resize( khashint_t ) */
	bool resize( HashInt newCapacity )
	{
		FlagHash *newFlags;

		if( !HashBase<KeyType, Hashf, Hasheq>::resizeAux1( &newCapacity, &newFlags ) )
			return false;

		values =( ValueType* )realloc( values, sizeof( ValueType ) * newCapacity );
		
		if( values == 0 )
		{
			//! insufficient enough memory?
			::free( newFlags );
			return false;
		}

		for( HashInt j = 0; j != this->_capacity; ++j )
		{
			if( _IS_BOTH( this->flags, j ) == 0 )
			{
				KeyType key = this->keys[j]; //! take out the key
				ValueType val = values[j];

				_SET_IS_DELETED_TRUE( this->flags, j ); //! mark "deleted"

				while( 1 )
				{
					HashInt inc, k, i;

					k = Hashf()( key );
					i = k % newCapacity; //! calculate the new position
					inc = 1 + k %( newCapacity - 1 );
					while( !_IS_EMPTY( newFlags, i ) )
					{
						if( i + inc >= newCapacity )
							i = i + inc - newCapacity;
						else
							i += inc;
					}

					_SET_IS_EMPTY_FALSE( newFlags, i );

					if( i < this->_capacity && _IS_BOTH( this->flags, i ) == 0 )
					{
						//! something is here
						{
							//! take it out
							KeyType tmp = this->keys[i];
							this->keys[i] = key;
							key = tmp;
						} 
						{
							//! take it out
							ValueType tmp = values[i];
							values[i] = val;
							val = tmp;
						} 

						_SET_IS_DELETED_TRUE( this->flags, i );
					}
					else
					{
						//! clear
						this->keys[i] = key;
						values[i] = val;
						break;
					}
				}
			}
		}

		HashBase<KeyType, Hashf, Hasheq>::resizeAux2( newCapacity, newFlags );

		return true;
	}

	Iterator find( const KeyType &key )
	{
		HashInt i = hashSearchAux( key, this->_capacity, this->keys, this->flags, Hashf(), Hasheq() );

		if( i != this->_capacity && _IS_BOTH( this->flags, i ) == 0 )
		{
			return Iterator( i, this->keys, this->flags, values );
		}
		else
			return this->end();
	}

	InsertPair insert( const KeyType &key, const ValueType &val )
	{
		rehash();
		HashInt i;
		int ret = directInsertAux( key, this->_capacity, this->keys, this->flags, &i );
		values[i] = val;
		if( ret == 0 )
			return InsertPair( Iterator( i, this->keys, this->flags, values ), false );
		if( ret == 1 )
		{
			++( this->_size );
			++( this->_occupied );
		}
		else
			++( this->_size ); //! then ret == 2

		return InsertPair( Iterator( i, this->keys, this->flags, values ), true );
	}

	ValueType &operator[]( const KeyType &key )
	{
		rehash();
		HashInt i;
		int ret = directInsertAux( key, this->_capacity, this->keys, this->flags, &i );
		if( ret == 0 )
			return values[i];
		if( ret == 1 )
		{
			++( this->_size );
			++( this->_occupied );
		}
		else
			++( this->_size ); //! then ret == 2
		values[i] = ValueType();
		return values[i];
	}

	void erase( Iterator &p )
	{
		if( p != this->end() && !_IS_EMPTY( this->flags, p.pos() ) )
		{
			if( !_IS_DELETED( this->flags, p.pos() ) )
			{
				_SET_IS_DELETED_TRUE( this->flags, p.pos() );
				--( this->_size );
			}
		}
	}

	Iterator erase( const KeyType &key )
	{
		HashInt i = hashEraseAux( key, this->_capacity, this->keys, this->flags, Hashf(), Hasheq() );
		if( i != this->_capacity )
		{
			--( this->_size );
			return Iterator( i, this->keys, this->flags, values );
		}
		else
			return this->end();
	}


	void free()
	{
		HashSet<KeyType, Hashf, Hasheq>::free();
		::free( values );
		values = 0;
	}
};
#endif 
