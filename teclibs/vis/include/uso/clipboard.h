#ifndef USO_CLIPBOARD_H_
#define USO_CLIPBOARD_H_

#include "defines.h"

USO_API bool uso_clipboard_writetext(char* text);
USO_API bool uso_clipboard_readtext(char** text);

#endif

