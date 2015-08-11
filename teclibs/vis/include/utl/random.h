#ifndef UTL_RANDOM_H
#define UTL_RANDOM_H

#include "defines.h"

//--------//
// Random //
//--------//

UTL_API void    utlRandomize     (void);
UTL_API int     utlRandomInt     (int Min, int Max);
UTL_API float   utlRandomFloat   (float Min, float Max);
UTL_API double  utlRandomDouble  (double Min, double Max);

#endif // UTL_RANDOM_H
