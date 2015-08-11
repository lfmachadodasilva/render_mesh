/**
* Algumas constantes de macros uteis
*/

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// constantes 
#define PI		   3.141592653589f
#define PIOVER180  0.017453292519f
#define PIUNDER180 57.29577951308f
#define EPSILON	   1.0e-5
#define SMALL	   1.0e-10f
#define BIG		   1.0e+10f
#define _INFINITE 1.0e+10f

#define MAX_ITERATIONS 30

// Macros Uteis 
#define DEG_TO_RAD( angle )	  ( ( angle )*PIOVER180 )
#define RAD_TO_DEG( radians ) ( ( radians )*PIUNDER180 )
#define SQR( number )		( number*number )
#define CUBE( number )		( number*number*number )
#define SIGN(a,b) ((b)<0 ? -fabsf(a) : fabsf(a))
#define RAND   (((float)rand()-(float)rand())/RAND_MAX)
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

/* Retorna um valor inteiro entre a e b inclusive */
#define RAND_FROM_TO(a,b) (float)((rand()%1000/1000.0)*(b - a) + a)
#endif

