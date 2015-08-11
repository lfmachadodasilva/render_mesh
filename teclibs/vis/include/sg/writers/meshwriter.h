#ifndef SG_MESH_WRITER
#define SG_MESH_WRITER

#include <sg/defines.h>
#include <sg/shp/mesh.h>
#include <string.h>
#include <stdlib.h>

class SG_API SGMeshWriter
{
  int m_index;
  char *m_filenamebase, *m_path;
public:
  SGMeshWriter () :
    m_index(0),
    m_filenamebase(0),
    m_path(0)
  {
    SetFilenameBase("mesh");
  }
  virtual ~SGMeshWriter ()
  {
  }
  void IncIndex ()
  {
    m_index++;
  }
  int GetIndex ()
  {
    return m_index;
  }
  void SetFilenameBase (const char *base)
  {
    m_filenamebase = (char*)realloc(m_filenamebase,(strlen(base)+1)*sizeof(char));
    strcpy(m_filenamebase,base);
  }
  void SetPath (char *path)
  {
    m_path = (char*)realloc(m_path,(strlen(path)+1)*sizeof(char));
    strcpy(m_path,path);
  }
  const char *GetFilenameBase () const
  {
    return m_filenamebase;
  }
  const char *GetPath () const
  {
    return m_path;
  }
  virtual void Write (SGMesh *mesh, UtlWriter *writer) = 0;
};

#endif
