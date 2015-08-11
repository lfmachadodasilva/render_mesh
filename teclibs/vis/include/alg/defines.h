#ifndef ALG_DEFINES_H
#define ALG_DEFINES_H

// define ALG_API (for encapsulated modules) and ALGH_API (for header classes).
#ifndef ALG_DLL
# ifndef TEC_DLL
#  define ALG_API
#  define ALGH_API
# else
#  define ALG_API __declspec(dllimport)
#  define ALGH_API __declspec(dllexport)
# endif
#else
# define ALG_API __declspec(dllexport)
# define ALGH_API __declspec(dllexport)
#endif

#define ALG_TOL 1.0e-7
#define ALG_PI 3.14159f
#define ALG_TO_RAD(a) ((a)*ALG_PI/180)
#define ALG_TO_DEG(a) ((a)*180/ALG_PI)

#if (defined(_WIN32) && !defined(HAS_POSIX))
# include <float.h>
# define ALG_FINITE(a) _finite(a)
#elif defined(__sun)
# include <ieeefp.h>
# define ALG_FINITE(a) finite(a)
#elif defined(__APPLE__)
# include <cmath>
# define ALG_FINITE(a) (std::isfinite(a) != 0 ? 1 : 0)
#else
# include <math.h>
# define ALG_FINITE(a) finite(a)
#endif

#endif
