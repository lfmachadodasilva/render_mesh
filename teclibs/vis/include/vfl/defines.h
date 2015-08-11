#ifndef VFL_DEFINES_H
#define VFL_DEFINES_H

//-----------------//
// DLL Definitions //
//-----------------//

#ifndef VFL_DLL
# ifndef TEC_DLL
#  define VFL_API
#  define VFLH_API
# else
#  define VFL_API __declspec(dllimport)
#  define VFLH_API __declspec(dllexport)
# endif
#else
# define VFL_API __declspec(dllexport)
# define VFLH_API __declspec(dllexport)
#endif

//----------------------//
// Standard Definitions //
//----------------------//

#ifndef NULL
# ifdef __cplusplus
#  define NULL    0
# else
#  define NULL    ((void *)0)
# endif
#endif

//------------//
// Value swap //
//------------//

template <class TYPE>
void vflSwap (TYPE* field1, TYPE* field2)
{
  TYPE tempfield = *field1;
  *field1 = *field2;
  *field2 = tempfield;
}

template <class TYPE>
void vflSwap (TYPE& field1, TYPE& field2)
{
  TYPE tempfield = field1;
  field1 = field2;
  field2 = tempfield;
}

#endif // VFL_DEFINES_H
