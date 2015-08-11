//* reader.h
// CMG data file reading routines.
// earp@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jun 2007

#ifndef cmg_bin_reader_h
#define cmg_bin_reader_h

#include <io/binfile.h>
#include <stdio.h>
#include <gpos/model/posmodel.h>
  
//* 'CMGBinReader' Class
// Represents an entity capable of reading data from a GRD data file.
class CMGBinReader
{
public:

  CMGBinReader (const char* filename, const char* mode, bool is_intel);

  ~CMGBinReader ();

    //* Status query
    // Checks if the entity has a valid status.
    // Returns non zero if entity is valid, zero otherwise.
  int Valid ()
  {
    return m_f.IsOpen();
  }

  /**
   * Obtains the total file size and stores on pointer 'size'.
   * Returns true if the operation was successful, false otherwise.
   */
  bool GetFileSize (size_t* size)
  {
    return m_f.GetSize(size);
  }

    //* Byte skip
    // Skips a specified number of bytes
  bool Skip (size_t offset)
  {
    return m_f.Skip(offset);
  }

    //* Go to a specific location
    // Skips to a specific location in the file.
  int Goto (size_t offset)
  {
    return m_f.Goto(offset);
  }

  size_t GetCurrentOffset()
  {
    return m_f.GetCurrentOffset();
  }
    //* Binary data read
    // Reads in binary data
  size_t Read (size_t n,
               size_t size,
               void* buffer,
               const char* progresssection = NULL,
               UpdateSectionProgressCB progresscb = NULL,
               void* progresscbdata = NULL);

  bool EoF ()
  {
    return m_f.EoF();
  }

  int GetC ()
  {
    return m_f.GetC();
  }

  IOBinFile* GetFile ()
  {
    return &m_f;
  }
private:
  void SetFilePosition()
  {
    if (!Valid()) return;
        
    m_filepos = GetCurrentOffset();
  }
  
  size_t FilePosition()
  {
    return m_filepos;
  }
public:
  void Unget();
  
  int TableType1 (DsArray<char *> *table);
  
  int TableType2 (int *nphrec, DsArray<char *> *table);
  int SkipTableType2 ();
  
  int TableType3 (DsArray<char *> *table);
  
  int TableType4 (int *nphrec, DsArray<int> *table);
  
  int TableType5(int *nphrec,int *nreals,int *nint,
                 int *nlogic,int *nchar, int *lchar);
  
  int TableType6 (int *num_rows, int *nphrec, DsArray<char *> *table);
  
  int ReadProperty(const char *propname, int nphrec, void *buffer);
  
  bool SkipHeader(bool xdr);
  bool SkipMark(bool xdr);
  bool SkipRecord(bool xdr);
  bool SkipRecord (size_t recordsize, bool xdr);
  bool ReadRecord (bool xdr,
                   size_t sizeitem,
                   unsigned int nbufferitems,
                   void *buffer,
                   const char* progresssection = NULL,
                   UpdateSectionProgressCB progresscb = NULL,
                   void* progresscbdata = NULL);

  void SetArchitecture(bool is_intel)
  {
    m_is_intel = is_intel;
    //~ printf("SetArchitecture: is_intel=%d\n",m_is_intel);
  }
private:
  IOBinFile m_f;
  bool m_is_intel;
  size_t m_filepos;
  char m_buffer[10000];
  int m_byte_order;
};

#endif

