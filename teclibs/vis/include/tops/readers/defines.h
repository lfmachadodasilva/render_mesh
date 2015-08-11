
#ifndef TOP_READERS_DEFINES_H
#define TOP_READERS_DEFINES_H

#ifndef TOPSRD_DLL
# ifndef TEC_DLL
#  define TOPSRD_API
#  define TOPSRDH_API
//#define TOPS_AAAA
# else
#  define TOPSRD_API __declspec(dllimport)
#  define TOPSRDH_API __declspec(dllexport)
//#define TOPS_BBBB
# endif
#else
# define TOPSRD_API __declspec(dllexport)
# define TOPSRDH_API __declspec(dllexport)
//#define TOPS_CCCC
#endif

#endif
