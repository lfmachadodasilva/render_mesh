#ifndef SND_DEFINES_H
#define SND_DEFINES_H

#ifdef SND_DLL
 #define SND_API __declspec(dllexport)
#else
 #define SND_API
#endif

#endif
