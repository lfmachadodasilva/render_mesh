/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_CRYPTO_HASH_H_
#define _VR_CRYPTO_HASH_H_

#include "Common.h"
#include "String.h"

namespace vr {

class CryptoHashAlgorithm;

/*!
	\brief The CryptoHash class provides a way to generate cryptographic hashes.

	CryptoHash can be used to generate cryptographic hashes of binary or text data.	Currently MD5 and SHA1 are supported.
 */
class VRBASE_EXPORT CryptoHash
{
public:
	enum Algorithm
	{
		Md5,
		Sha1
	};

	struct VRBASE_EXPORT Result
	{
		Algorithm algorithm;
		int8 numBytes;
		union
		{
			uint8  bytes[20];
			uint32 dwords[5];
		}
		data;

		//! Writes the hash result to 'str' in hexadecimal.
		void toString( String& str );
	};

public:
	//! Constructs an object that can be used to create a cryptographic hash from data using method.
	CryptoHash( Algorithm method );

	//! Destroys the object.
	~CryptoHash();

	//! Adds the first length chars of data to the cryptographic hash.
	void addData( const uint8* data, int length );

	//! This is an overloaded member function, provided for convenience.
	inline void addData( const String& str )
	{ 
		addData( reinterpret_cast<const uint8*>( str.data() ), str.length() );
	}

	//! Resets the object.
	void reset();

	//! Returns the final hash value as a byte array in the given String.
	void getResult( Result& res ) const;

private:
    // forbid copies.
    CryptoHash( const CryptoHash& other );
    CryptoHash& operator=( const CryptoHash& other );

private:
	CryptoHashAlgorithm* _algorithm;
};

} // namespace vr

#endif
