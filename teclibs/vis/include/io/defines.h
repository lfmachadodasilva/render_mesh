#ifndef IO_DEFINES_H
#define IO_DEFINES_H

#ifndef IO_DLL
# ifndef TEC_DLL
#  define IOAPI
#  define IOHAPI
# else
#  define IOAPI __declspec(dllimport)
#  define IOHAPI __declspec(dllexport)
# endif
#else
# define IOAPI  __declspec(dllexport)
# define IOHAPI __declspec(dllexport)
#endif

#ifndef IOLZO_DLL
# ifndef TEC_DLL
#  define IOLZOAPI
#  define IOLZOHAPI
# else
#  define IOLZOAPI __declspec(dllimport)
#  define IOLZOHAPI __declspec(dllexport)
# endif
#else
# define IOLZOAPI  __declspec(dllexport)
# define IOLZOHAPI __declspec(dllexport)
#endif

#endif

