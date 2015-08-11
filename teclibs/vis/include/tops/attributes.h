/**
  TopS - Topological data structure for mesh representation.
  
  TopS is a software developed by Tecgraf/PUC-Rio & UIUC.
  It is requested that the TopS users provide the appropriate
  credits and references to the work.
  
  References:
  1 -W. Celes, G.H. Paulino, R. Espinha, "A compact adjacency-based
  topological data structure for finite element mesh representation",
  IJNME, 2005 (in press)
  2 - W. Celes, G.H. Paulino, R. Espinha, "Efficient Handling of Implicit
  Entities in Reduced Mesh Representations", JCISE, Special Issue on
  Mesh-Based Geometric Data Processing, 2005 (in press)
  
  Aug 2005
*/

#ifndef TOP_ATTRIBUTES_H
#define TOP_ATTRIBUTES_H

class TopModel;

/**
  Dense attributes (array)
*/
class TOPS_API TopDenseAttrib
{
public:
  TopDenseAttrib(int datasize) 
    : m_datasize(datasize)
  {
    m_packsize = 0;
    m_pack_func = NULL;
    m_unpack_func = NULL;
    m_pack_data = NULL;
  }
  ~TopDenseAttrib() 
  {
  }
  const char* GetName() 
  { 
    return m_v.GetName(); 
  }
  int GetDataSize() const 
  { 
    return m_datasize; 
  }
  void* GetArray() 
  { 
    return m_v.GetArray(); 
  }

  typedef void (*PackFunc) (void* attrib, unsigned char* buffer, void* data);

  void SetPackFunc (
      int packsize, PackFunc pack_func, PackFunc unpack_func, void* data)
  {
    m_packsize = packsize;
    m_pack_func = pack_func;
    m_unpack_func = unpack_func;
    m_pack_data = data;
  }

  void Set(const TopNode& node, void* data) 
  { 
    memcpy(m_v.GetAddress(m_datasize*node.GetPosId()), data, m_datasize);
  }
  void* Get(const TopNode& node) 
  {
    return m_v.GetAddress(m_datasize*node.GetPosId());
  }
  void Set(const TopElement& elem, void* data) 
  { 
    memcpy(m_v.GetAddress(m_datasize*elem.GetPosId()), data, m_datasize);
  }
  void* Get(const TopElement& elem) 
  {
    return m_v.GetAddress(m_datasize*elem.GetPosId());
  }

  /** Internal use */
  bool IsEmpty() const
  {
    return m_datasize == 0;
  }
  bool Resize(int nvalues)
  {
    return m_v.Resize(nvalues*m_datasize);
  }
  bool TrimToSize()
  {
    return m_v.TrimToSize();
  }
  int PackSize()
  {
    return m_packsize;  
  }
  void Pack(int i, unsigned char* dest)
  {
    if (m_pack_func != NULL)
      m_pack_func(m_v.GetAddress(i*m_datasize), dest, m_pack_data);  
    else
      memcpy(dest, m_v.GetAddress(i*m_datasize), m_datasize);  
   
  }
  void Unpack(int i, unsigned char* src)
  {
    if (m_unpack_func != NULL)
      m_unpack_func(m_v.GetAddress(i*m_datasize), src, m_pack_data);  
    else
      memcpy(m_v.GetAddress(i*m_datasize), src, m_datasize);  
  }
  bool SetName(const char* name)
  {
    return m_v.SetName(name);
  }
private:
  int m_datasize;
  int m_packsize;
  PackFunc m_pack_func;
  PackFunc m_unpack_func;
  void* m_pack_data;
  TopRawArray<unsigned char> m_v;
};

typedef TopDenseAttrib TopElementDenseAttrib;
typedef TopDenseAttrib TopNodeDenseAttrib;

/**
  Sparse attributes (hash)

  WARNING: After setting a new value (see Set()), all the current pointers 
  to attributes in the table (returned by Get()) may be invalidated. Therefore, 
  it is necessary to retrieve them again.
*/
class TOPS_API TopSparseAttrib
{
public:
  TopSparseAttrib(TopModel* model, int datasize)
    : m_model(model), m_datasize(datasize), m_name(0), m_v(datasize)
  {
    m_packsize = 0;
    m_pack_func = NULL;
    m_unpack_func = NULL;
    m_pack_data = NULL;
  }
  ~TopSparseAttrib() 
  {
  }
  const char* GetName() 
  { 
    return m_name;
  }
  int GetDataSize() const 
  { 
    return m_datasize; 
  }

  typedef void (*PackFunc) (void* attrib, unsigned char* buffer, void* data);

  void SetPackFunc (
      int packsize, PackFunc pack_func, PackFunc unpack_func, void* data)
  {
    m_packsize = packsize;
    m_pack_func = pack_func;
    m_unpack_func = unpack_func;
    m_pack_data = data;
  }

  void Set(const TopNode& node, void* data);

  void* Get(const TopNode& node);

  void Set(const TopElement& elem, void* data);

  void* Get(const TopElement& elem);

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES   
  void Set(const TopFacet& facet, void* data);

  void* Get(const TopFacet& facet);

  void Set(const TopFace& face, void* data);

  void* Get(const TopFace& face);

  void Set(const TopEdge& edge, void* data);

  void* Get(const TopEdge& edge);

  void Set(const TopVertex& vertex, void* data);

  void* Get(const TopVertex& vertex);
#endif

private:
  friend class TopModel;

  /** Internal use */
  bool TrimToSize()
  {
    return m_v.TrimToSize();
  }
  int PackSize()
  {
    return m_packsize;  
  }
  void Pack(int i, unsigned char* dest)
  {
    m_pack_func(m_v.Get(i), dest, m_pack_data);  
  }
  void Unpack(int i, unsigned char* src)
  {
    m_unpack_func(m_v.Get(i), src, m_pack_data);  
  }
  bool SetName (const char* name)
  {
    if (m_name) {
      free(m_name);
      m_name = NULL;
    }
    if (name) {
      m_name = (char*)malloc(strlen(name)+1);
      if (!m_name)
        return false;
      strcpy(m_name,name);
    }
    return true;
  }
  TopAttribHash<unsigned int>& GetHash()
  {
    return m_v;
  }
  int GetNumberOfKeys()
  {
    return m_v.GetNumberOfKeys();
  }

private:
  TopModel* m_model;
  int m_datasize;
  int m_packsize;
  PackFunc m_pack_func;
  PackFunc m_unpack_func;
  void* m_pack_data;
  char* m_name;
  TopAttribHash<unsigned int> m_v;
};

typedef TopSparseAttrib TopElementSparseAttrib;
typedef TopSparseAttrib TopNodeSparseAttrib;
typedef TopSparseAttrib TopFacetSparseAttrib;
typedef TopSparseAttrib TopFaceSparseAttrib;
typedef TopSparseAttrib TopEdgeSparseAttrib;
typedef TopSparseAttrib TopVertexSparseAttrib;

#endif
