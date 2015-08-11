// fabraham@tecgraf.puc-rio.br
// Feb 2012
#ifndef IO_FILE_H
#define IO_FILE_H

#include "defines.h"
#include <stdio.h>

/**
 * IOFile: base class for IOBinFile and IOTextFile.
 */
class IOAPI IOFile
{
public:
  virtual bool Open (const char* filename, const char* mode)
  {
    m_f = fopen(filename, mode);
    if (m_f == NULL)
      return false;
    return true;
  }
  virtual bool Close ()
  {
    bool ret = true;
    if (IsOpen()) {
      ret = (fclose(m_f) == 0);
      m_f = NULL;
    }
    return ret;
  }
  bool IsOpen ()
  {
    return m_f != NULL;
  }
  bool EoF ()
  {
    return feof(m_f);
  }
protected:
  void SetFilePointer (FILE* f)
  {
    m_f = f;
  }
  FILE* F ()
  {
    return m_f;
  }
  size_t Seek (size_t offset, int whence)
  {
#ifdef WIN32
    return _fseeki64(F(), offset, whence);
#else
    return fseeko(F(), offset, whence);
#endif
  }
private:
  FILE* m_f;
};

#endif

