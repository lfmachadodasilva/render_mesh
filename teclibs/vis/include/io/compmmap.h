#ifndef IO_COMP_MMAP_H
#define IO_COMP_MMAP_H

#include <ds/list.h>
#include <ds/heap2.h>
#include <ds/hash.h>
#include <utl/sort.h>

class IOStream;

class IOCompMemoryMapper
{
public:
  struct Buffer
  {
    int id;
    IOStream* stream;
    size_t offset;
    size_t size;
    float priority;
    double request_time;
    bool awaiting;
    bool ready;
    Buffer ()
    : stream(NULL)
    , request_time(-1.0)
    , awaiting(false)
    , ready(false)
    , heappos(-1)
    {
    }
    ~Buffer ();
    bool IsOnHeap () const
    {
      return heappos >= 0;
    }
  private:
    void SetHeapPosition (int pos)
    {
      heappos = pos;
    }
    int GetHeapPosition () const
    {
      return heappos;
    }
    bool operator> (Buffer* c) const
    {
      return priority < c->priority;
    }
    bool operator< (Buffer* c) const
    {
      return priority > c->priority;
    }
  private:
    int heappos;
  private:
    friend class DsHeap2<Buffer*>;
  };
public:
  IOCompMemoryMapper ();
  ~IOCompMemoryMapper ();
  bool Open (const char* filename);
  bool Close ();
  bool Read (int id, size_t offset, size_t size, float priority);
  void Release (Buffer* b);
  bool Loop ();
  void ReadyIterationBegin ();
  bool ReadyIterationValid ();
  Buffer* ReadyIterationGetCurr ();
  void ReadyIterationNext ();
  /**
   * Informs if the memory mapper is idle or awaiting new buffers to arrive on main memory.
   */
  bool IsIdle ()
  {
    return m_buffers.GetNumberOfKeys() == 0;
  }
private:
  class CompareFunctor 
  {
  public:
    CompareFunctor ()
    : m_sort_data(NULL)
    , m_size(-1)
    {
    }
    UTL_FORCE_INLINE int operator() (const unsigned int i1, const unsigned int i2) const
    {
      assert(0 <= i1 && i1 < m_size);
      assert(0 <= i2 && i2 < m_size);
      if (m_sort_data[i1]->offset > m_sort_data[i2]->offset)
        return 1;
      else if (m_sort_data[i1]->offset < m_sort_data[i2]->offset)
        return -1;
      else
        return 0;
    }
    UTL_FORCE_INLINE void SetSortData (Buffer* const * data, int size)
    { 
      m_sort_data = data;
      m_size = size;
    }
    Buffer* const * m_sort_data;
  private:
    unsigned int m_size;
  };
private:
  int GetPageCount (Buffer* b);
  void* GetRoundedMap (Buffer* b);
  size_t GetRoundedSize (Buffer* b);
  int SortArray (DsArray<Buffer*>* a);
  int GetOrderIndex (int i);
  size_t GetAwaitingSize ();
private:
  DsHeap2<Buffer*> m_read_list;
  DsPList<Buffer> m_awaiting_list;
  DsPList<Buffer> m_ready_list;
  DsPList<Buffer>::Iterator m_ready_it;
  DsHash<int,Buffer*> m_buffers;
  unsigned char* m_map;
  size_t m_map_length;
  char m_filename[1024];
  int m_fd;
  CompareFunctor m_comparefunctor;
  UtlSort<unsigned int, CompareFunctor, UtlSortPivotMiddle<unsigned int> > m_sort;
  DsArray<unsigned int> m_sort_indices;
  DsArray<unsigned char> m_in_core;
  long m_page_size;
  size_t m_prev_awaiting_size;
  size_t m_prev_advised_size;
};

#endif

