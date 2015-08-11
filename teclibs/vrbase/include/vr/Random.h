/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_RANDOM_H_
#define _VR_RANDOM_H_

#include "Common.h"

namespace vr {

/*!
	Pseudo-Random Number Generator based on the Mersenne Twister.
 */
class VRBASE_EXPORT Random
{
public:
    inline static Random* instance()
    {
        if( !sm_instance )
            sm_instance = new Random();
        return sm_instance;
    }

	//! Generates a random uint32 in the interval [0,0xFFFFFFFF].
    inline static uint32 integer32() { return instance()->generateInt32(); }

	//! Generates a random int32 in the interval [0,0x7FFFFFFF] (always positive).
    inline static int32 integer31()	{ return instance()->generateInt31(); }

    //! Generates a random integer in the interval [min, max].
    inline static int32 integer( int32 min, int32 max ) { return instance()->generateInteger( min, max ); }

	//! Generates a random real number in the interval [0,1] (32 bit resolution).
    inline static double realInIn() { return instance()->generateRealInIn(); }

	//! Generates a random real number in the interval [0,1) (32 bit resolution).
	inline static double realInOut() { return instance()->generateRealInOut(); }

	//! Generates a random real number in the interval (0,1) (32 bit resolution).
	inline static double realOutOut() { return instance()->generateRealOutOut(); }

	//! Generates a random real number in the interval [0,1) (53 bit resolution).
	inline static double realHiRes() { return instance()->generateRealHiRes(); }

    //! Generates a random real number in the interval [min, max].
	inline static double real( double min, double max ) { return instance()->generateReal( min, max ); }

public:
    //! Construct and automatically seed a pseudo-Random number generator (using autoSeed()).
    Random();

    //! Construct and seed the PRNG using the specified DWORD.
    Random( uint32 s );

    //! Construct and seed the PRNG using an array of DWORDs.
    Random( uint32 *array, uint32 size );

    //! Generates a random uint32 in the interval [0,0xFFFFFFFF].
    uint32 generateInt32() const;

    //! Generates a random int32 in the interval [0,0x7FFFFFFF] (always positive).
    inline int32 generateInt31() const
    {
        return static_cast<int32>( generateInt32() >> 1 );
    }

    //! Generates a random integer in the interval [min, max].
    int32 generateInteger( int32 min, int32 max ) const;

    //! Generates a random real number in the interval [0,1] (32 bit resolution).
    inline double generateRealInIn() const
    {
        // divided by 2^32-1
        return ( generateInt32() * ( 1.0 / 4294967295.0 ) );
    }

    //! Generates a random real number in the interval [0,1) (32 bit resolution).
    inline double generateRealInOut() const
    {
        // divided by 2^32
        return ( generateInt32() * ( 1.0 / 4294967296.0 ) );
    }

    //! Generates a random real number in the interval (0,1) (32 bit resolution).
    inline double generateRealOutOut() const
    {
        // divided by 2^32
        return ( ( generateInt32() + 0.5 ) * ( 1.0 / 4294967296.0 ) ); 
    }

    //! Generates a random real number in the interval [0,1) (53 bit resolution).
    inline double generateRealHiRes() const
    {
        uint32 a = ( generateInt32() >> 5 );
        uint32 b = ( generateInt32() >> 6 );
        return ( a * 67108864.0 + b ) * ( 1.0 / 9007199254740992.0 );
    }

    //! Generates a random real number in the interval [min, max].
    inline double generateReal( double min, double max ) const
    {
        return ( min + ( max - min ) * generateRealInIn() );
    }

    //! Re-seeds the PRNG using a DWORD.
	void seed( uint32 s );

	//! Re-seeds the PRNG using an array of DWORDs.
	void seed( uint32 *array, uint32 size );

	/*!
		If the PRNG has not been sown yet, seed it automatically using high-entropy
		data sources. If the PRNG has already been sown and you want to re-seed it,
		pass force = true.

		\return true if the auto-seeder has sown the PRNG.
				false if the PRNG had already been sown (and force = false).
	 */
	bool autoSeed( bool force = false );

private:
    static Random* sm_instance;

private:
	// whether either seed() or autoSeed() has been called
	bool _sown;

	// period parameters:
	static const uint32 N = 624;
	static const uint32 M = 397;

	// internal RNG state:
	mutable uint32 _state[N]; // the array for the state vector
	mutable uint32 _index;       // index == N+1 means state[N] is not initialized
};

} // namespace vr

#endif // _VR_RANDOM_H_
