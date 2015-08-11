#ifndef GC_AUXMATH_H
#define GC_AUXMATH_H

#include <math.h>

// Constants

#define GC_Pi  3.1415926535897932384626433832795

#define GC_DET_LUDECOMPOSITION 0
#define GC_DET_COFACTORS       1

// Globals Class

class gcGlobals
{
public:
  static float  epsilonf;
  static double epsilond;

  static bool   debugMode;
};

// Defined Functions

#ifndef max
#define max(a,b) (((a) > (b)) ? (a):(b))
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a):(b))
#endif

#ifndef round
#define round(_) (int)floor( (_)+0.5 )
#endif

#ifndef valswap
#define valswap(a,b,temp) {temp = a; a = b; b = temp;}
#endif

// Functions

float  gcAbs  (float  number);
double gcAbs  (double number);

bool gcIsZero (float  number);
bool gcIsZero (double number);

bool gcEqual  (float  a, float  b);
bool gcEqual  (double a, double b);

int  gcCmpZero (float  number);
int  gcCmpZero (double number);

int gcCompare (float  a, float  b);
int gcCompare (double a, double b);

double gcDeterminant4x4 (double *matrix, const int Method = GC_DET_LUDECOMPOSITION);

#endif // GC_AUXMATH_H
