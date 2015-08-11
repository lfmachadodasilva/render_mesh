#ifndef UTL_WRITER
#define UTL_WRITER

#include "defines.h"

class UTLH_API UtlWriter {
public:
  virtual ~UtlWriter ()
  {
  }
  virtual void WriteFloat (const char* name, float f) = 0;
  virtual void WriteInt (const char* name, int i) = 0;
  virtual void WriteBool (const char* name, bool b) = 0;
  virtual void WriteString (const char* name, const char* s) = 0;
  virtual void WriteMultilineString (const char* name, const char* s) = 0;
  virtual void WriteCode (const char* name, const char* s) = 0;
  virtual void WriteNewBlock (const char* name) = 0;
  virtual void WriteSeparator (const char* str) = 0;
  virtual void WriteCloseBlock () = 0;
  virtual void WriteFloatArray(const char* name, int n, ...) = 0;
};

#endif
