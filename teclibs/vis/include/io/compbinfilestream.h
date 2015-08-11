// Compressed binary file stream class
// fabraham@tecgraf.puc-rio.br
// Jul 2008
#ifndef IO_COMP_BIN_FILE_STREAM_H
#define IO_COMP_BIN_FILE_STREAM_H

#include <stdio.h>
#include <pthread.h>
#include <ds/mtqueue.h>
#include <ds/mtpool.h>
#include <ds/mtvar.h>
#include "stream.h"
#include "defines.h"
#include <minilzo/lzoconf.h>

class IOBinFileStream;

/**
 * This class implements a compressed binary file stream.
 * It is able to read and write to a compressed file in a separate thread,
 * allowing concurrent calculations.
 */
class IOLZOAPI IOCompBinFileStream : public IOStream
{
public:
  typedef void (*ProgressFunc)(float progress, void* data);
  IOCompBinFileStream();
  virtual ~IOCompBinFileStream();
  /**
   * Specifies that should use a better compression algorithm, which generates smaller
   * files but takes longer to compress.
   *
   * Default: false
   */
  void SetCompressMore (bool f)
  {
    m_compress_more = f;
  }
  bool Open(const char* filename, Mode mode);
  bool ReadFrom (const void* src, size_t size);
  bool ReachedEnd ();
  bool Close();
  bool Close(bool wait);
  const char* GetFilename() const
  {
    return m_filename;
  }
  void WaitTillDone ()
  {
    while (!IsDone());
  }
  bool IsOpen () const
  {
    return m_isopen;
  }
  void SetReadProgressCB (ProgressFunc func, void* data);
  void Flush();
  Mode GetMode();
  bool WriteBytes(size_t n, const void* v);
  bool ReadBytes(size_t n, void* v);
  static float GetVersion ();
  /**
   * Must be called before exiting the program,
   * guaranteeing that all streams are written and no program threads remain.
   */
  static void AtExit ();
private:
  bool IsDone()
  {
    return m_done.Get();
  }
  bool ReadBytesInt(size_t n, void* v);
  void UpdateProgress (size_t readbytes);
  static void* WriteThread (void* data);
  static void* ReadThread (void* data);
  void WriteThread ();
  void ReadThread (DsArray<unsigned char>* compbuf,
                   lzo_bytep workmem);
  void CreateChunk ();
  void FreeCurrentChunk ();
  void CloseStream ();
  bool StartWrite ();
  bool StartRead ();
private:
  typedef struct
  {
    unsigned char* buf;
    size_t size;
  } Chunk;
  char m_filename[1024];
  Mode m_mode;
  bool m_isopen;
  bool m_close_at_thread_end;
  bool m_error;
  unsigned int m_used_bytes;
  IOStream* m_read_stream;
  IOBinFileStream* m_write_stream;
  Chunk* m_curr_chunk;
  DsMTPool<unsigned char> m_chunk_pool;
  DsMTQueue<Chunk*> m_ready_chunks;
  DsMTVar<bool> m_done;
  ProgressFunc m_read_progress_func;
  void* m_read_progress_data;
  long long m_file_size;
  long m_bytes_read;
  long m_last_progress_update;
  bool m_compress_more;
};

#endif

