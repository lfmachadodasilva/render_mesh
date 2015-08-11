//* reader.h
// CMG data file reading routines.
// earp@tecgraf.puc-rio.br
// Jun 2007

#ifndef cmg_reader_h
#define cmg_reader_h

#include <stdio.h>
#include <gpos/model/posmodel.h>
  
//* 'CMGReader' Class
// Represents an entity capable of reading data from a GRD data file.
class CMGReader
{
public:

  CMGReader (const char* filename, const char* mode, bool is_intel);

  ~CMGReader ();

    //* Status query
    // Checks if the entity has a valid status.
    // Returns non zero if entity is valid, zero otherwise.
  int Valid ();

  /**
   * Obtains the total file size and stores on pointer 'size'.
   * Returns true if the operation was successful, false otherwise.
   */
  bool GetFileSize (size_t* size);

    //* Formatted text read
    // Reads in formatted text.
  int Scan (const char* format, void *a=NULL);

    //* Byte skip
    // Skips a specified number of bytes
  bool Skip (size_t offset);

    //* Go to a specific location
    // Skips to a specific location in the file.
  int Goto (size_t offset);

  size_t GetCurrentOffset();
    //* Binary data read
    // Reads in binary data
  size_t Read (size_t n,
               size_t size,
               void* buffer,
               const char* progresssection = NULL,
               UpdateSectionProgressCB progresscb = NULL,
               void* progresscbdata = NULL);

    //* String read
    // Reads in the specified number of bytes as string
  const char* String (int nbytes);
    // Reads next string removing quotes
  const char* QuotedString(void);
    // Reads a word (stops at first blank)
  const char* Word ();
  bool SkipWord ();
    //* Integer read
    // Reads the next 4 bytes as text and converts the result to an integer
  int Short ();
    // Reads the next 8 bytes as text and converts the result to an integer
  int Int ();
  bool SkipInt ();

    //* Float read
    // Reads the next word as text and converts the result to a float
  float Float ();
  bool SkipFloat ();

    //* Double read
    // Reads the next word as text and converts the result to a double
  double Double ();

    //* Line read
  const char* Line();
  
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

  int FormattedInt();
  bool SkipFormattedInt ();
  bool SkipRestOfLine ()
  {
    return Scan("%*[^\n]\n") != EOF; // discard the rest of the line
  }
  const char* ReadUntil(char s,bool skip);
  
  void SetArchitecture(bool is_intel)
  {
    m_is_intel = is_intel;
    //~ printf("SetArchitecture: is_intel=%d\n",m_is_intel);
  }
  
  int Rewind()
  {
    return fseek(m_fp,0,SEEK_SET);
  }
private:
  FILE* m_fp;
  bool m_is_intel;
  size_t m_filepos;
  char m_buffer[10000];
  int m_byte_order;
};

class CMGReaderProgressMeter
{
public:
  CMGReaderProgressMeter (CMGReader* reader);
  ~CMGReaderProgressMeter ();
  bool MustReport ();
  float GetProgress ();
private:
  CMGReader* m_reader;
  size_t m_totalsize;
  size_t m_currpos;
  size_t m_lastreportpos;
  size_t m_progressfreq;
};

#endif

