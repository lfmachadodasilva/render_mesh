#ifndef _TOP_BIN_FILE_STREAM_H
#define _TOP_BIN_FILE_STREAM_H

#include <stdio.h>
#include "stream.h"

/**
  General interface for data structure I/O.
*/
class IOAPI IOBinFileStream : public IOStream
{
  char m_filename[1024];
  Mode m_mode;
  bool m_isopen;
  FILE* m_fp;

public:
  typedef void (*ProgressFunc)(float progress, void* data);
  IOBinFileStream();
  virtual ~IOBinFileStream();

  bool Open(const char* filename, Mode mode);
  bool Close();
  bool IsOpen();
  bool ReachedEnd ();
  bool Goto (size_t offset);
  /**
   * Obtains the current offset of the file in bytes.
   */
  size_t GetCurrOffset ();
  /**
   * Obtains the file size in bytes (mode == READ).
   */
  size_t GetFileSize () const
  {
    return m_file_size;
  }
  void SetReadProgressCB (ProgressFunc func, void* data);

  virtual void Flush();
  virtual Mode GetMode();

  virtual bool WriteBytes(size_t n, const void* v);
  virtual bool ReadBytes(size_t n, void* v);
private:
  void UpdateProgress (size_t readbytes);
private:
  ProgressFunc m_read_progress_func;
  void* m_read_progress_data;
  size_t m_file_size;
  size_t m_bytes_read;
  size_t m_last_progress_update;
};

#endif

