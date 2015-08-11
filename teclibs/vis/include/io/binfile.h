// fabraham@tecgraf.puc-rio.br
// Feb 2012
#ifndef IO_BIN_FILE_H
#define IO_BIN_FILE_H

#include "file.h"
#include <assert.h>
#include <stdio.h>

/**
 * IOBinFile: binary file reader.
 *
 * TODO:
 * - implement RAII techniques (resource allocation is instantiation)
 */
class IOAPI IOBinFile : public IOFile
{
public:
  bool Open (const char* filename, const char* mode)
  {
    bool ret = IOFile::Open(filename, mode);
    if (ret) {
      m_co = 0;
      //TestCurrentOffset();
    }
    return ret;
  }
  bool Close ()
  {
    bool ret = IOFile::Close();
    m_co = 0;
    return ret;
  }
  size_t GetCurrentOffset ()
  {
    return m_co;
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
    if (Seek(0L, SEEK_END) != 0)
      return false;
    QueryCurrentOffset();
    return true;
  }
  bool Goto (size_t offset)
  {
    size_t ret = Seek(m_co = offset, SEEK_SET);
    //TestCurrentOffset();
    return ret == 0;
  }
  bool Skip (size_t offset)
  {
    m_co += offset;
    size_t ret = Seek(offset, SEEK_CUR);
    //TestCurrentOffset();
    return ret == 0;
  }
  int GetC ()
  {
    int ret = fgetc(F());
    if (ret != EOF)
      ++m_co;
    //TestCurrentOffset();
    return ret;
  }
  int UnGetC (int c)
  {
    int ret = ungetc(c, F());
    if (ret != EOF)
      --m_co;
    //TestCurrentOffset();
    return ret;
  }
  size_t Read (void* p, size_t memb_size, size_t nmemb)
  {
    size_t ret = fread(p, memb_size, nmemb, F());
    m_co += ret*memb_size;
    //TestCurrentOffset();
    return ret;
  }
private:
  void QueryCurrentOffset ()
  {
#ifdef WIN32
    m_co = (size_t)_ftelli64(F());
#else
    m_co = (size_t)ftello(F());
#endif
  }
  void TestCurrentOffset ()
  {
#ifdef WIN32
    assert(m_co == (size_t)_ftelli64(F()));
#else
    assert(m_co == (size_t)ftello(F()));
#endif
  }
private:
  size_t m_co; // current offset
};

#endif

