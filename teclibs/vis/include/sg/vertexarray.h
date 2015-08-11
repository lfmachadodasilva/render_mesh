// Vertex Array class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Sep 2002

#ifndef SG_VERTEXARRAY_H
#define SG_VERTEXARRAY_H

#include <ugl/vertexarray.h>
#include "defines.h"
#include "refcount.h"

/**
 * SGArray Class.
 *
 * This class implements OpenGL vertex arrays using the UGLArray class.
 *
 * Methods are provided to manipulate and query the array (see the UGLArray documentation)
 *
 * This class has automatic memory management. (inherited from SGRefCount),
 * so a single array can be shared between multiple vertex arrays.
 */
class SG_API SGArray : public SGRefCount, public UGLArray
{
public:
  static const char* CLASSNAME () { return "SGArray"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Creates an array. Similar to the constructor.
   */
  static UGLArray* CreateArray (int which, int nelem, int type, int accessHint, int timeHint)
  {
    return new SGArray(which,nelem,type,accessHint,timeHint);
  }
  /*
  * Creates an array and allocates 'nv' vertices in main memory
  */
  static SGArray* CreateCpu (int nv, int which=V_POSITION, int nelem=3, int type=GL_FLOAT, int accessHint=-1, int timeHint=-1);
  /*
  * Creates an array and allocates 'nv' vertices in video memory
  */
  static SGArray* CreateGpu (int nv, int which=V_POSITION, int nelem=3, int type=GL_FLOAT, int accessHint=-1, int timeHint=-1);
  /*
  * Destroys an array created with one of the "Create*" methods
  */
  static void Destroy (SGArray* vArray);
  /**
   * Constructor.
   *
   * Receives number of vertices, which type and the number of elements per vertex.
   * 'which' can be of the following values:
   * - V_POSITION
   * - V_NORMAL
   * - V_COLOR
   * - V_TEXCOORD (same as V_TEXCOORD0)
   * - V_TEXCOORD0
   * - V_TEXCOORD1
   * - V_TEXCOORD2
   * - V_TEXCOORD3
   * - V_TEXCOORD4
   * - V_TEXCOORD5
   * - V_TEXCOORD6
   * - V_TEXCOORD7
   * - V_VPATTRIB
   */
  SGArray (int which=V_POSITION, int nelem=3, int type=GL_FLOAT, int accessHint=-1, int timeHint=-1);
  /**
   * Destructor
   */
  virtual ~SGArray ();
};

/**
 * SGVertexArray Class.
 * 
 * This class is a SGArray container.
 * For more info, see the UGLVertexArray class documentation.
 * 
 */
class SG_API SGVertexArray : public UGLVertexArray
{
public:
  /**
   * Constructor
   */
  SGVertexArray ();
  /**
   * Destructor
   */
  virtual ~SGVertexArray ();
  /**
   * Inserts an array to the list. Returns false if array is already on the list, true otherwise.
   */
  bool Insert (SGArray* array);
  /**
   * Removes an array from the list. Returns false if array not on the list, true otherwise.
   */
  bool Remove (SGArray* array);
  /**
   * Removes all arrays.
   */
  void Clear ();
  /**
   * Gets the first array with type 'which' found, NULL if none found.
   */
  SGArray* GetArray (int which)
  {
    return (SGArray*)UGLVertexArray::GetArray(which);
  }
  /**
   * Copy the arrays from vertex array 'in'.
   */
  virtual bool CopyArrays (UGLVertexArray& in)
  {
    UGLArray::ArrayCreateFunc oldf = UGLArray::GetArrayCreateFunc();
    UGLArray::SetArrayCreateFunc(SGArray::CreateArray);
    bool ret = UGLVertexArray::CopyArrays(in);
    UGLArray::SetArrayCreateFunc(oldf);
    return ret;
  }
};

#endif

