// fabraham@tecgraf.puc-rio.br
// Feb 2012
#ifndef IO_TEXT_FILE_H
#define IO_TEXT_FILE_H

#include "file.h"
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

/**
 * IOTextFile: text file reader.
 *
 * TODO:
 * - implement RAII techniques (resource allocation is instantiation)
 * - implement text file parsing utilities, such as reading an entire line, etc.
 */
class IOAPI IOTextFile : public IOFile
{
public:
  size_t GetCurrentOffset ()
  {
#ifdef WIN32
    return (size_t)_ftelli64(F());
#else
    return (size_t)ftello(F());
#endif
  }
  bool GetSize (size_t* size)
  {
    size_t curr = GetCurrentOffset();
    if (!GotoEnd()) {
      (void)Goto(curr);
      return false;
    }
    *size = GetCurrentOffset(); // file size
    return Goto(curr) != 0;
  }
  bool GotoStart ()
  {
    return Goto(0);
  }
  bool GotoEnd ()
  {
    return Seek(0L, SEEK_END) == 0;
  }
  bool Goto (size_t offset)
  {
    return Seek(offset, SEEK_SET) == 0;
  }
  bool Skip (size_t offset)
  {
    return Seek(offset, SEEK_CUR) == 0;
  }
  int GetC ()
  {
    return fgetc(F());
  }
  int UnGetC (int c)
  {
    return ungetc(c, F());
  }
#ifdef WIN32
  int Scan (const char* format, void* a = NULL)
  {
    return fscanf(F(), format, a);
  }
#else
  int Scan (const char* format, ...)
  {
    va_list ap;
    va_start(ap, format);
    int ret = vfscanf(F(), format, ap);
    va_end(ap);
    return ret;
  }
#endif
};

#endif

