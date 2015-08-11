// Stream interface
// rodesp@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
#ifndef IO_STREAM_H
#define IO_STREAM_H

#include "defines.h"
#include <stdio.h>

/**
  General interface for data structure I/O.
*/
class IOHAPI IOStream
{
public:
  enum Mode {
    READ = 0,
    WRITE
  };

  virtual ~IOStream() {}
  virtual void Flush() = 0;
  virtual Mode GetMode() = 0;
  /**
   * Closes the stream. Returns 'true' on success, false otherwise.
   */
  virtual bool Close() = 0;
  /**
   * Returns 'true' if there is no more data to be read (Mode=READ only),
   * 'false' otherwise.
   */
  virtual bool ReachedEnd () = 0;

  virtual bool WriteBytes(size_t n, const void* v) = 0;
  virtual bool WriteUChars (int n, const unsigned char* v)
  {
    return WriteBytes(n*sizeof(unsigned char),v);
  }
  virtual bool WriteInts (int n, const int* v)
  {
    return WriteBytes(n*sizeof(int),v);
  }
  virtual bool WriteUInts (int n, const unsigned int* v)
  {
    return WriteBytes(n*sizeof(unsigned int),v);
  }
  virtual bool WriteShorts (int n, const short* v)
  {
    return WriteBytes(n*sizeof(short),v);
  }
  virtual bool WriteUShorts (int n, const unsigned short* v)
  {
    return WriteBytes(n*sizeof(unsigned short),v);
  }
  virtual bool WriteFloats (int n, const float* v)
  {
    return WriteBytes(n*sizeof(float),v);
  }
  virtual bool WriteDoubles (int n, const double* v)
  {
    return WriteBytes(n*sizeof(double),v);
  }
  virtual bool WriteBools (int n, const bool* v)
  {
    return WriteBytes(n*sizeof(bool),v);
  }
  virtual bool WriteLongs (int n, const long* v)
  {
    return WriteBytes(n*sizeof(long),v);
  }
  virtual bool WriteLongLongs (int n, const long long* v)
  {
    return WriteBytes(n*sizeof(long long),v);
  }

  virtual bool ReadBytes (size_t n, void* v) = 0;
  virtual bool ReadUChars (int n, unsigned char* v)
  {
    return ReadBytes(n*sizeof(unsigned char), v);
  }
  virtual bool ReadInts (int n, int* v)
  {
    return ReadBytes(n*sizeof(int), v);
  }
  virtual bool ReadUInts (int n, unsigned int* v)
  {
    return ReadBytes(n*sizeof(unsigned int), v);
  }
  virtual bool ReadShorts (int n, short* v)
  {
    return ReadBytes(n*sizeof(short), v);
  }
  virtual bool ReadUShorts (int n, unsigned short* v)
  {
    return ReadBytes(n*sizeof(unsigned short), v);
  }
  virtual bool ReadFloats (int n, float* v)
  {
    return ReadBytes(n*sizeof(float), v);
  }
  virtual bool ReadDoubles (int n, double* v)
  {
    return ReadBytes(n*sizeof(double), v);
  }
  virtual bool ReadBools (int n, bool* v)
  {
    return ReadBytes(n*sizeof(bool), v);
  }
  virtual bool ReadLongs (int n, long* v)
  {
    return ReadBytes(n*sizeof(long), v);
  }
  virtual bool ReadLongLongs (int n, long long* v)
  {
    return ReadBytes(n*sizeof(long long), v);
  }
  virtual bool WriteUChar (unsigned char v)
  {
    return WriteUChars(1, &v);
  }
  virtual bool WriteInt (int v)
  {
    return WriteInts(1, &v);
  }
  virtual bool WriteUInt (unsigned int v)
  {
    return WriteUInts(1, &v);
  }
  virtual bool WriteShort (short v)
  {
    return WriteShorts(1, &v);
  }
  virtual bool WriteUShort (unsigned short v)
  {
    return WriteUShorts(1, &v);
  }
  virtual bool WriteFloat (float v)
  {
    return WriteFloats(1, &v);
  }
  virtual bool WriteDouble (double v)
  {
    return WriteDoubles(1, &v);
  }
  virtual bool WriteBool (bool v)
  {
    return WriteBools(1, &v);
  }
  virtual bool WriteLong (long v)
  {
    return WriteLongs(1, &v);
  }
  virtual bool WriteLongLong (long long v)
  {
    return WriteLongLongs(1, &v);
  }
};

#endif

