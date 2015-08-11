#ifndef TOP_MEM_STREAM_H
#define TOP_MEM_STREAM_H

#include <stdio.h>
#include "stream.h"

class IOAPI IOMemStream : public IOStream
{
public:
  typedef void (*ProgressFunc)(float progress, void* data);
  IOMemStream();
  virtual ~IOMemStream();

  /**
   * Sets the memory location where serialized data will be
   * read from. This implicitly set stream mode as READ and opens it.
   */
  void SetSource (const void* src, size_t size);
  /**
   * Sets the memory location where serialized data will be
   * written to. This implicitly set stream mode as WRITE and opens it.
   */
  void SetDestination (void* src, size_t size);
  bool Close();
  bool ReachedEnd();
  bool IsOpen();
  void SetReadProgressCB (ProgressFunc func, void* data);

  void Flush();
  Mode GetMode();

  bool WriteBytes(size_t n, const void* v);
  bool ReadBytes(size_t n, void* v);
private:
  const void* m_src;
  void* m_dest;
  Mode m_mode;
  bool m_isopen;
  ProgressFunc m_read_progress_func;
  void* m_read_progress_data;
  size_t m_data_size;
  size_t m_bytes_done;
  size_t m_last_progress_update;
};

#endif

