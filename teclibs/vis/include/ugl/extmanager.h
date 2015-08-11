#ifndef UGL_EXT_MANAGER_H
#define UGL_EXT_MANAGER_H

#include "defines.h"

class UGL_API UGLExtManager
{
public:
  static bool  SupportsExtension  (const char* name);
  static void* GetExtensionFuncPtr(const char* name);
};

#endif
