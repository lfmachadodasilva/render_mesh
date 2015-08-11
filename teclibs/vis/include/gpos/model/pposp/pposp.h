// pposp.h
// Tecgraf/PUC-Rio
// fabraham@tecgraf.puc-rio.br
// Jul 2006

#ifndef PPOSP_H
#define PPOSP_H

#ifndef GPOSPPOSP_DLL
# ifndef TEC_DLL
#  define RESPPOSPAPI
# else
#  define RESPPOSPAPI __declspec(dllimport)
# endif
#else
# define RESPPOSPAPI __declspec(dllexport)
#endif

/**
 * Initializes the PPOSP reservoir model file format opener.
 */
RESPPOSPAPI void gpospposp_init ();

#endif
