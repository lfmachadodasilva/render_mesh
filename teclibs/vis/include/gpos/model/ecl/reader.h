//* reader.h
// ECL data file reading routines.
// earp@tecgraf.puc-rio.br
// Fev 2010

#ifndef ECL_reader_h
#define ECL_reader_h

#include <stdio.h>
#include <gpos/model/posmodel.h>
  
//* 'ECLReader' Class
// Represents an entity capable of reading data from a GRD data file.
class ECLReader
{
public:

  ECLReader (const char* filename, const char* mode);

  ~ECLReader ();

  bool NeedByteConversion () throw(bool);
    //* Status query
    // Checks if the entity has a valid status.
    // Returns non zero if entity is valid, zero otherwise.
  int Valid ();

  /**
   * Obtains the total file size and stores on pointer 'size'.
   * Returns true if the operation was successful, false otherwise.
   */
  void GetFileSize (size_t* size) throw (bool);

    //* Formatted text read
    // Reads in formatted text.
  int Scan (const char* format, void *a=NULL);

    //* Byte skip
    // Skips a specified number of bytes
  void Skip (size_t offset) throw (bool);

    //* Go to a specific location
    // Skips to a specific location in the file.
  void Goto (size_t offset) throw (bool);

  size_t GetCurrentOffset();
    //* Binary data read
    // Reads in binary data
  size_t Read (size_t n,
               size_t size,
               void* buffer,
               const char* progresssection = NULL,
               UpdateSectionProgressCB progresscb = NULL,
               void* progresscbdata = NULL) throw(bool);

    
  FILE *FilePointer ()
  {
    return m_fp;
  }
  
  void SetFilePosition()
  {
    if (!m_fp) return;
        
    m_filepos = GetCurrentOffset();
  }
  
  size_t FilePosition()
  {
    return m_filepos;
  }
  
  void Unget() throw(bool);
  
  
  int ReadProperty(const char *propname, int nphrec, void *buffer);
  
  bool ReadRecord (bool xdr,
                   size_t sizeitem,
                   unsigned int nbufferitems,
                   void *buffer,
                   const char* progresssection = NULL,
                   UpdateSectionProgressCB progresscb = NULL,
                   void* progresscbdata = NULL) throw (bool);

  
  void SetArchitecture(bool is_intel)
  {
    m_is_intel = is_intel;
    //~ printf("SetArchitecture: is_intel=%d\n",m_is_intel);
  }
  
  int Rewind()
  {
    return fseek(m_fp,0,SEEK_SET);
  }

  bool ReadHeader (char*& keyword, int *nelems, char*& dtype);
  bool IgnoreHeader ();
  char* ReadString (int size) throw(bool);
  void ReadInt (int *value) throw (bool);
  void ReadLogical (bool *value) throw (bool);
  void ReadFloat (float *value) throw (bool);
  void ReadDouble (double *value) throw (bool);

  void SkipInt (int n) throw (bool);
  void SkipLogical (int n) throw (bool);
  void SkipDouble (int n) throw (bool);
  void SkipFloat (int n) throw (bool);
  void ReadN (size_t n, size_t size, void* buffer) throw (bool);
private:
  FILE* m_fp;
  bool m_is_intel;
  size_t m_filepos;
  char m_buffer[10000];
  int m_byte_order;
};

class ECLReaderProgressMeter
{
public:
  ECLReaderProgressMeter (ECLReader* reader);
  ~ECLReaderProgressMeter ();
  bool MustReport ();
  float GetProgress ();
private:
  ECLReader* m_reader;
  size_t m_totalsize;
  size_t m_currpos;
  size_t m_lastreportpos;
  size_t m_progressfreq;
};

#endif

