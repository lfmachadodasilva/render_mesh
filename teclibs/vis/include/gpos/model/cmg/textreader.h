//* reader.h
// CMG data file reading routines.
// earp@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jun 2007

#ifndef cmg_text_reader_h
#define cmg_text_reader_h

#include <io/textfile.h>
#include <stdio.h>
#include <gpos/model/posmodel.h>
  
//* 'CMGTextReader' Class
// Represents an entity capable of reading data from a GRD data file.
class CMGTextReader
{
public:

  CMGTextReader (const char* filename, const char* mode, bool is_intel);

  ~CMGTextReader ();

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

    //* Formatted text read
    // Reads in formatted text.
  int Scan (const char* format, void *a=NULL);

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

  bool EoF ()
  {
    return m_f.EoF();
  }

  int GetC ()
  {
    return m_f.GetC();
  }

  IOTextFile* GetFile ()
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
  
  int FormattedInt();
  bool SkipFormattedInt ();
  bool SkipRestOfLine ()
  {
    return Scan("%*[^\n]\n") != EOF; // discard the rest of the line
  }
  const char* ReadUntil(char s,bool skip);
private:
  IOTextFile m_f;
  size_t m_filepos;
  char m_buffer[10000];
};

class CMGReaderProgressMeter
{
public:
  CMGReaderProgressMeter (CMGTextReader* reader);
  ~CMGReaderProgressMeter ();
  bool MustReport ();
  float GetProgress ();
private:
  CMGTextReader* m_reader;
  size_t m_totalsize;
  size_t m_currpos;
  size_t m_lastreportpos;
  size_t m_progressfreq;
};

#endif

