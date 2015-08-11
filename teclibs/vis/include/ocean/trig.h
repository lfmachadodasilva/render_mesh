#ifndef TRIG_H
#define TRIG_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Define this however your compiler likes it. */
#define INLINE      __inline 


/* INTORFLOAT union for easy access to bits of a float. */
typedef union
{
    int     i;          // as integer
    float   f;          // as float
    struct              // as bit fields
    {
        unsigned int    sign:1;
        unsigned int    biasedexponent:8;
        unsigned int    significand;
    }
            bits;
}
INTORFLOAT;

/* Bias constant used for fast conversions between int and float. First element
   in INTORFLOAT union is integer -- we are storing biased exponent 23, mantissa .1, which
   is equivalent to 1.5 x 2^23. */
INTORFLOAT  bias = {((23 + 127) << 23) + (1 << 22)};

/**************************************************************
    Linear lookup for sine and cosine

    This section implements a lookup table version of sin
    and cos, both using the same table.
 **************************************************************/

#define SINTABLESIZE    4096
#define TWOPISCALE      ((float)SINTABLESIZE / (2.0f * 3.14159265f))

static float    sintable[SINTABLESIZE];

/*
    Initialize the lookup table.
*/

void    triginit(void)
{
    int     i;
    double  theta;

    /* Integer range 0 to SINTABLESIZE is converted to floating
       point 0 to 2 pi range (radians for a full circle). */
    for (i = 0; i < SINTABLESIZE; ++i)
    {
        theta = (double)i/TWOPISCALE;
        sintable[i] = (float)sin(theta);
    }
}

/*
    fsin - sin calculation with lookup table.
*/

INLINE float    fsin(float theta)
{
    unsigned int    i;

#if 1   /* Use biasing trick for fast float to int conversion. */
    INTORFLOAT  fi;
    fi.f = theta * TWOPISCALE + bias.f; /* Scale to table index range and add conversion bias. */
    i = fi.i & (SINTABLESIZE - 1);         /* Mask off lower bits, assuming SINTABLESIZE is power of 2. */
#else   /* Use typecasting for slow float to int conversion. */
    i = ((unsigned int)(theta * TWOPISCALE)) & (SINTABLESIZE - 1);
#endif

    /* Return sine from table. */
    return sintable[i];
}

/*
    fcos - cos calculation with lookup table.
*/

INLINE float    fcos(float theta)
{
    unsigned int    i;

    INTORFLOAT  fi;
    fi.f = theta * TWOPISCALE + bias.f;             /* Scale to table index range and add conversion bias. */

    /* Note how adding SINTABLESIZE/4 lets us compute cos instead of sin,
       since cos(theta) = sin(theta + Pi/4). */
    i = (fi.i + (SINTABLESIZE/4)) & (SINTABLESIZE - 1);   /* Mask off lower bits, assuming SINTABLESIZE is power of 2. */

    return sintable[i];
}



#endif

