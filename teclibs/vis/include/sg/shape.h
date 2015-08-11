// Shape class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// May 2001 

#ifndef SG_SHAPE_H
#define SG_SHAPE_H

#include <alg/matrix.h>
#include "attribute.h"
#include "vertexarray.h"

class UtlWriter;
class SGStrategy;

/**
 * SGShape Class.
 * 
 * This is the base class for all shapes.
 *
 * It provides an interface for concrete classes to:
 * - insert/remove arrays associated with the shape geometry.
 * - load/unload the arrays.
 * - draw the geometry.
 * - write its description.
 * - obtain face/line/vertex count of the shape's geometry.
 * - traverse the shape with a traversal strategy.
 */
class SG_API SGShape : public SGAttribute
{
  SGVertexArray m_verts; 
  int m_id;
protected:
  /**
   * Constructor
   */
  SGShape ();
public:
  static const char* CLASSNAME () { return "Shape"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Obtains the number of shapes in the shape table.
   */
  static int GetTabDimension ();
  /**
   * Obtains the shape with id 'id'.
   */
  static SGShape* GetShape (int id);
  /**
   * Destructor
   */
  virtual ~SGShape ();
  /**
   * Obtains the shape's id.
   */
  int GetId () const
  {
    return m_id;
  }
  /**
   * Inserts an array to the shape.
   */
  void InsertArray (SGArray* array)
  {
    m_verts.Insert(array);
  }
  /**
   * Removes an array from the shape.
   */
  bool RemoveArray (SGArray* array)
  {
    return m_verts.Remove(array);
  }
  /**
   * Obtains the shape's vertex array.
   */
  SGVertexArray* GetVertexArray ()
  {
    return &m_verts;
  }
  /**
   * Obtains the array of type 'which' in the vertex array.
   */
  SGArray *GetArray (int which)
  {
    return m_verts.GetArray(which);
  }
  /**
   * Specifies if the shape vertex arrays are going to be static or dynamic. default=static.
   */
  void SetStatic (bool f)
  {
    SGVertexArray* va = GetVertexArray();
    for (SGVertexArray::Iterator it = va->ITBegin(); va->ITValid(it); va->ITNext(it))
      va->ITCurr(it)->SetStatic(f);
  }
  /**
   * Informs if the shape vertex arrays are in main memory.
   */
  bool IsInMainMemory ()
  {
    return m_verts.IsInMainMemory();
  }
  /**
   * Copies all arrays from a shape.
   */
  bool CopyArrays (SGShape* in) 
  {
    return m_verts.CopyArrays(in->m_verts);
  }
  /**
   * Loads the shape's vertex array.
   */
  void Load ()
  {
    m_verts.Load();
  }
  /**
   * Unloads the shape's vertex array.
   */
  void Unload ()
  {
    m_verts.Unload();
  }
  /**
   * Transforms the shapes vertices according to the matrix 'm'
   */
  virtual void Transform (const AlgMatrix &m);
  /**
   * Specifies if the shape has its own culling algorithm
   */
  virtual bool HasCulling ()
  {
    return false;
  }
  /**
   * Traverses the shape with a traversal strategy.
   * If enabled, this shape will load itself.
   */
  virtual void Traverse(SGStrategy *s);
  /**
   * Obtains the shape vertex count.
   */
  virtual int GetVertexCount ()
  {
    return m_verts.GetSize();
  }
  /**
   * Obtains the shape's triangle of index 'index'.
   * 0 <= index < GetVertexCount().
   * Must be reimplemented for shapes that do not use the included vertex array.
   */
  virtual void GetVertex (int index, float *x, float *y, float *z);
  /**
   * Obtains the shape line count.
   */
  virtual int GetLineCount () = 0;
  /**
   * Obtains the shape triangle count.
   */
  virtual int GetTriangleCount () = 0;
  /**
   * Draws the shape geometry.
   */
  virtual void Draw () = 0;
  /**
   * Writes the shape's description.
   */
  virtual void Write (UtlWriter* writer) = 0;
};

#endif

