// Mesh class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_MESH_H
#define SG_MESH_H

#include <sg/shape.h>
#include <sg/indices.h>

class SGMeshWriter;

class SG_API SGMesh : public SGShape
{
public:
  typedef DsPList<SGTriangleSet>   TriSetList;
  typedef DsPList<SGTriangleStrip> TriStripList;
  typedef DsPList<SGQuadSet>       QuadSetList;
private:
  TriSetList m_tset;
  TriStripList m_tstrip;
  QuadSetList m_qset;
public:
  static const char* CLASSNAME () { return "Mesh"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  static void SetMeshWriter (SGMeshWriter *writer);
  SGMesh ();
  virtual ~SGMesh ();
  void AddTriangleSet (SGTriangleSet* set)
  {
    set->IncRef();
    m_tset.Append(set);
  }
  void AddTriangleStrip (SGTriangleStrip* strip)
  {
    strip->IncRef();
    m_tstrip.Append(strip);
  }
  void AddQuadSet (SGQuadSet* set)
  {
    set->IncRef();
    m_qset.Append(set);
  }
  TriSetList::Iterator GetTriangleSets ()
  {
    return m_tset.Begin();
  }  
  TriStripList::Iterator GetTriangleStrips ()
  {
    return m_tstrip.Begin();
  }
  QuadSetList::Iterator GetQuadSets ()
  {
    return m_qset.Begin();
  }
  virtual int GetLineCount ();
  virtual int GetTriangleCount ();
  virtual void Draw ();
  virtual void Write (UtlWriter* writer);
};

#endif
