// Indices classes
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// vbarata@tecgraf.puc-rio.br
// Dez 2002 - Jul 2007

#ifndef UGL_INDICES_H
#define UGL_INDICES_H

#include "defines.h"
#include "uglmem.h"

/**
 * UGLIndices class.
 * 
 * This class represents an index array.
 * It is used to index vertex arrays, enabling the drawing of multiple
 * primitives of the same type with a single call.
 * Methods are provided to:
 * - create, resize and destroy the array in main or video memory.
 * - query the size of the array and whether it is in main or video memory
 * - call the GL drawing method associated with the index array
 * - set, add and get individual indices values
 * - set and get all indices values at once
 * - set GL buffer object properties
 *
 * This in fact is an abstract class. The concrete classes will use this
 * functionality to implement line/triangle/quad sets/strips, grids, etc.
 */
class UGL_API UGLIndices
{
private:
  int m_ninds_cpu;           // Number of indices in main memory
  int m_ninds_gpu;           // Number of indices in video memory
  unsigned int m_maxVerts;   // Maximum number of vertices indexed
  void *m_indices;           // General pointer to the main memory buffer
  Mem m_mem;                 // Internal data structure (memmanager.h/.cpp)
  int m_type;                // Data type (GL_UNSIGNED_BYTE/SHORT/INT)
  unsigned short m_typesize; // Size of the data type (1,2,4)
  bool m_hasprimrestart;     // Primitive Restart flag
protected:
  /**
   * Copy Constructor
   */
  UGLIndices (const UGLIndices *src);
  /**
   * Calls glDrawElements(mode,...).
   */
  void LoadIndices (int mode);
public:
  /**
   * Constructs a new empty index array indexing at most 'maxVerts' vertices.
   * If 'maxVerts' is 0, array is assumed to index any number of vertices.
   *
   * 'accessHint': expected use of this array as a GL buffer object:
   * - UGL_MEM_USAGE_CPU_TO_GPU
   * - UGL_MEM_USAGE_GPU_TO_CPU
   * - UGL_MEM_USAGE_GPU_ONLY
   * - default: use the setting from ugl_setAutoAccessHint()
   * 'timeHint': expected update rate of this array as a GL buffer object:
   * - UGL_MEM_USAGE_STATIC
   * - UGL_MEM_USAGE_STREAM
   * - UGL_MEM_USAGE_DYNAMIC
   * - default: use the setting from ugl_setAutoTimeHint()
   */
  UGLIndices (unsigned int maxVerts, int accessHint=-1, int timeHint=-1);
  /**
   * Destructor
   */
  virtual ~UGLIndices ();
  /**
   * Is the index array in main memory?
   */
  bool IsInCpu ();
  /**
   * Is the index array in video memory?
   */
  bool IsInGpu ();
  /**
   * Notifies the memory manager that the main memory array has changed
   */
  void FlagCpuChanged ();
  /**
   * Notifies the memory manager that the video memory array has changed
   */
  void FlagGpuChanged ();
  /**
   * Resizes the cpu-based array to 'ni' indices.
   */
  bool Resize (int ni, bool exactSize=true)
  {
    return ResizeCpu(ni, exactSize);
  }
  /**
   * Resizes the cpu-based array to 'ni' indices.
   * - When 'exactSize' is not requested (default), the array's total capacity
   *   will not shrink, and it will grow by multiplying its size by a factor.
   * - When 'copyFromGpu' is true, 'nv' will be ignored, the cpu array size will
   *   match the gpu`s, and the gpu array contents will be copied in.
   * - If a GL buffer object needs to be bound during the operation, setting
   *   'unbind' to false prevents it from being unbound (for performance)
   */
  bool ResizeCpu (int ni, bool exactSize=false, bool copyFromGpu = false, bool unbind=true);
  /**
   * Resizes the gpu-based array to 'ni' indices.
   * - When 'exactSize' is not requested (default), the array's total capacity
   *   will not shrink, and it will grow by multiplying its size by a factor.
   * - When 'copyFromCpu' is true, 'nv' will be ignored, the gpu array size will
   *   match the cpu`s, and the cpu array contents will be copied in.
   * - If a GL buffer object needs to be bound during the operation, setting
   *   'unbind' to false prevents it from being unbound (for performance)
   */
  bool ResizeGpu (int ni, bool exactSize=false, bool copyFromCpu = false, bool unbind=true);
  /**
  * Reserves cpu memory space for at least 'ni' indices (or exactly 'ni' if 'exactsize' is true)
  * The number of actual indices on the array will not be altered, so the user can call
  * "AddIndex" fill up the array.
  * Read notes on "ResizeCpu" for information on other parameters.
  */
  bool ReserveCpu (int ni, bool exactSize=false, bool copyFromGpu = false, bool unbind=true);
  /**
   * Resizes the cpu-based array to 'nelem' elements (lines/triangles/quads).
   */
  bool ResizeElements (int nelem)
  {
    return ResizeElementsCpu(nelem, false);
  }
  /**
   * Resizes the cpu-based array to 'nelem' elements (lines/triangles/quads).
   * See "ResizeCpu()" for a description of 'exactSize', 'copyFromGpu' and 'unbind'
   */
  bool ResizeElementsCpu (int nelem, bool exactSize=false, bool copyFromGpu = false, bool unbind=true)
  {
    return ResizeCpu(GetNumElementIndices(nelem), exactSize, copyFromGpu, unbind);
  }
  /**
   * Resizes the gpu-based array to 'nelem' elements (lines/triangles/quads).
   * See "ResizeGpu()" for a description of 'exactSize', 'copyFromCpu' and 'unbind'
   */
  bool ResizeElementsGpu (int nelem, bool exactSize=false, bool copyFromCpu = false, bool unbind=true)
  {
    return ResizeGpu(GetNumElementIndices(nelem), exactSize, copyFromCpu, unbind);
  }
  /**
   * Copies the array from gpu to cpu
   * 'base' specifies an offset (in bytes) from the start of the GPU buffer
   * 'size' specifies how many bytes to copy, zero = until the end of the array
   */
  bool CopyToCpu (GLintptrARB base=0, GLsizeiptrARB size=0, bool unbind=true);
  /**
   * Copies the array from cpu to gpu
   * 'base' specifies an offset (in bytes) from the start of the GPU buffer
   * 'size' specifies how many bytes to copy, zero = until the end of the array
   */
  bool CopyToGpu (GLintptrARB base=0, GLsizeiptrARB size=0, bool unbind=true);
  /**
   * Maps the GPU index array into main memory
   * 'accessType' must be one of the following:
   * - GL_READ_ONLY[_ARB]
   * - GL_WRITE_ONLY[_ARB]
   * - GL_READ_WRITE[_ARB]
   */
  void* MapIndices (int accessType);
  /**
   * Unmaps the GPU index array from main memory
   * If it returns false, then the array data has
   * become corrupted and must be resubmitted.
   */
  bool UnmapIndices (bool unbind = true);
  /**
   * Frees the array from main memory
   */
  void FreeCpu ();
  /**
   * Frees the array from video memory
   */
  void FreeGpu ();
  /**
   * Sets the automatic dynamic growth rate of the array
   * When resized, if the array needs to grow, its capacity will
   * be multiplied by this constant as many times as necessary.
   */
  void SetGrowRate (float rate);
  /**
   * Gets the automatic dynamic growth rate of the array
   */
  float GetGrowRate (void);
  /**
   * Adds index 'v' to the end of the index array
   */
  void AddIndex (unsigned int v);
  /**
   * Sets index at position 'i' to 'v'.
   */
  bool SetIndex (int i, unsigned int v);
  /**
   * Gets index at position 'i'.
   */
  unsigned int GetIndex (int i) const;
  /**
   * Sets indices from 0 to (ni-1) as the indices on array 'indices'.
   */
  bool SetIndices (int ni, const unsigned int* indices)
  {
    return SetIndicesCpu(ni, indices);
  }
  /**
   * Sets indices from 0 to (ni-1) as the indices on array 'indices'.
   */
  bool SetIndicesCpu (int ni, const unsigned int* indices);
  /**
   * Sets indices from 0 to (ni-1) as the indices on array 'indices'.
   */
  bool SetIndicesCpu (int ni, const unsigned char* indices);
  /**
   * Sets indices from 0 to (ni-1) as the indices on array 'indices'.
   */
  bool SetIndicesCpu (int ni, const unsigned short* indices);
  /**
   * Sets gpu-stored indices from 0 to (ni-1) as the indices on array 'indices'.
   */
  bool SetIndicesGpu (int ni, const unsigned char* indices);
  /**
   * Sets gpu-stored indices from 0 to (ni-1) as the indices on array 'indices'.
   */
  bool SetIndicesGpu (int ni, const unsigned short* indices);
  /**
   * Sets gpu-stored indices from 0 to (ni-1) as the indices on array 'indices'.
   */
  bool SetIndicesGpu (int ni, const unsigned int* indices);
  /**
   * Obtains the indices pointer.
   */
  void* GetIndices () const
  {
    return m_indices;
  }
  /**
   * Obtains the index type: GL_UNSIGNED_BYTE || _SHORT || _INT
   */
  int GetType () const
  {
    return m_type;
  }
  /**
   * Copies all indices on 'src'.
   */
  bool CopyFrom (const UGLIndices *src);
  /**
   * Gets the number of indices in the rendering array.
   */
  int GetNumIndices () const;
  /**
   * Gets the number of indices in the cpu-based array.
   */
  int GetNumIndicesCpu () const
  {
    return m_ninds_cpu; 
  }
  /**
   * Gets the number of indices in the gpu-based array.
   */
  int GetNumIndicesGpu () const
  {
    return m_ninds_gpu; 
  }
  /**
   * Gets the size (in bytes) of the rendering array.
   */
  int GetSize () const;
  /**
   * Gets the size (in bytes) of the cpu-based array.
   */
  int GetSizeCpu () const;
  /**
   * Gets the size (in bytes) of the gpu-based array.
   */
  int GetSizeGpu () const;
  /**
   * Gets the total number of bytes used by the cpu-based array.
   */
  size_t GetMemSizeCpu ();
  /**
   * Gets the total number of bytes used by the gpu-based array.
   */
  size_t GetMemSizeGpu ();
  /**
   * Gets the total number of bytes used by both arrays (CPU and GPU).
   */
  size_t GetTotalMemSize ();
  /**
   * Gets the maximum number of vertices indexed by this array.
   */
  unsigned int GetNumVertices () const
  {
    return m_maxVerts; 
  }
  /**
   * Gets the primitive restart index for this array
   */
  unsigned int GetPrimitiveRestartIndex () const
  {
    return m_maxVerts; 
  }
  /**
   * Gets the indices storage type size (in bytes)
   */
  unsigned short GetTypeSize () const
  {
    return m_typesize;
  }
  /**
   * Gets the id of the GL buffer object, if applicable
   */
  GLuint GetBOId ();
  /**
   * Specifies the usage of the vertex array as a GL buffer object
   */
  void SetBOUsageHints (int accessHint = -1, int timeHint = -1);
  /**
   * What is the expected use of this array as a GL buffer object?
   * - UGL_MEM_USAGE_CPU_TO_GPU
   * - UGL_MEM_USAGE_GPU_TO_CPU
   * - UGL_MEM_USAGE_GPU_ONLY
   */
  int GetBOAccessHint ();
  /**
   * What is the expected use of this array as a GL buffer object?
   * - UGL_MEM_USAGE_STATIC
   * - UGL_MEM_USAGE_STREAM
   * - UGL_MEM_USAGE_DYNAMIC
   */
  int GetBOTimeHint ();
  /**
   * Specifies array usage: Static or dynamic? (backward compatibility)
   */
  void SetStatic (bool f);
  /**
   * Is the vertex array static? (backward compatibility)
   */
  bool GetStatic ();
  /**
   * Forces/forbids the automatic creation of a GL buffer object when bound
   */
  void SetAutoCreateBO (bool state);
  /**
   * Forces the static array to (not) be automatically freed from main memory
   * when copied into a GL buffer object. Only used in static index arrays.
   */
  void SetAutoFreeAfterBO (bool state);
  /**
   * Forces the dynamic GL buffer object to (not) be updated when bound.
   * Only used in non-static index arrays.
   */
  void SetAutoUpdateBO (bool state);
  /**
   * Sets the transform feedback index
   */
  void SetFeedbackIndex (unsigned int index);
  /**
   * Gets the transform feedback index
   */
  unsigned int GetFeedbackIndex (void);
  /**
   * Creates a VBO for the array.
   */
  bool CreateVBO (bool unbind=true);
  /*
   * Obtains the number of indices necessary for 'nelem' elements (lines/triangles/quads)
   */
  virtual int GetNumElementIndices (int nelem) const = 0;
  /*
   * Obtains the number of lines drawn by this index array. 
   */
  virtual int GetLineCount () const = 0;
  /*
   * Obtains the number of triangles drawn by this index array. 
   */
  virtual int GetTriangleCount () const = 0;
  /**
   * Obtains the number of elements (lines, triangles, quads) drawn by this index array.
   */
  virtual int GetElementCount () const = 0;
  /**
   * Gets the element 'i' of the index array.
   */
  virtual void GetElement (int i, int *ni, unsigned int *i0, unsigned int *i1, unsigned int *i2, unsigned int *i3) const = 0;
  /*
   * Issues the draw command, calling glDrawElements or similar.
   */
  virtual void Load () = 0;
  /**
   * Loads the index array for transform feedback mode.
   */
  bool LoadFeedback ();
  /**
   * Unloads the index array from transform feedback mode.
   */
  void UnloadFeedback ();
private:
  void SetUIntIndex (int i, unsigned int v);
  void SetUShortIndex (int i, unsigned int v);
  void SetUCharIndex (int i, unsigned int v);
};

/**
 * Line set class.
 * It indexes a vertex array using GL_LINES. (segment1x segment1y segment1z segment2x ...)
 */
class UGL_API UGLLineSet : public UGLIndices
{
public:
  /*
   * Creates an index array and allocates 'nl' lines in main memory
   * See the UGLIndices class constructor for more information.
   */
  static UGLLineSet* CreateCpu (int nl, unsigned int maxVerts, int accessHint=-1, int timeHint=-1);
  /*
   * Creates an index array and allocates 'nl' lines in video memory
   * See the UGLIndices class constructor for more information.
   */
  static UGLLineSet* CreateGpu (int nl, unsigned int maxVerts, int accessHint=-1, int timeHint=-1);
  /**
   * Constructs a new line set indexing an array of at most 'maxVerts' vertices.
   * See the UGLIndices class constructor for more information.
   */
  UGLLineSet (unsigned int maxVerts, int accessHint=-1, int timeHint=-1) : UGLIndices(maxVerts, accessHint, timeHint)
  {
  }
  /**
   * Copy constructor.
   */
  UGLLineSet (const UGLLineSet *src) : UGLIndices(src)
  {
  }
  /**
   * Destructor
   */
  virtual ~UGLLineSet ()
  {
  }
  /*
   * Adds line 'v0 v1' to the array.
   */
  void AddLine (unsigned int v0, unsigned int v1)
  {
    AddIndex(v0);
    AddIndex(v1);
  }
  /*
   * Sets line on position 'id' as 'v0 v1'.
   */
  void SetLine (int id, unsigned int v0, unsigned int v1)
  {
    SetIndex(2*id,v0);
    SetIndex(2*id+1,v1);
  }
  /*
   * Gets line on position 'id', storing the indices on 'v0 v1'.
   */
  void GetLine (int id, unsigned int*v0, unsigned int*v1) const
  {
    *v0 = GetIndex(2*id);
    *v1 = GetIndex(2*id+1);
  }
  virtual int GetNumElementIndices (int nelem) const
  {
    return nelem*2;
  }
  virtual int GetLineCount () const
  {
    return GetNumIndices()/2;
  }
  virtual int GetTriangleCount () const
  {
    return 0;
  }
  virtual int GetElementCount () const
  {
    return GetNumIndices()/2;
  }
  virtual void GetElement (int i, int *ni, unsigned int *i0, unsigned int *i1, unsigned int *i2, unsigned int *i3) const
  {
    *ni = 2;
    GetLine(i,i0,i1);
  }
  virtual void Load ();
};

/**
 * Line strip class.
 * It indexes a vertex array using GL_LINE_STRIP.
 */
class UGL_API UGLLineStrip : public UGLIndices
{
public:
  /*
   * Creates an index array and allocates 'nl' lines in main memory
   * See the UGLIndices class constructor for more information.
   */
  static UGLLineStrip* CreateCpu (int nl, unsigned int maxVerts, int accessHint=-1, int timeHint=-1);
  /*
   * Creates an index array and allocates 'nl' lines in video memory
   * See the UGLIndices class constructor for more information.
   */
  static UGLLineStrip* CreateGpu (int nl, unsigned int maxVerts, int accessHint=-1, int timeHint=-1);
  /**
   * Constructs a new line strip indexing an array of at most 'maxVerts' vertices.
   * See the UGLIndices class constructor for more information.
   */
  UGLLineStrip (unsigned int maxVerts, int accessHint=-1, int timeHint=-1) : UGLIndices(maxVerts, accessHint, timeHint)
  {
  }
  /**
   * Copy constructor.
   */
  UGLLineStrip (const UGLLineStrip *src) : UGLIndices(src)
  {
  }
  /**
   * Destructor
   */
  virtual ~UGLLineStrip ()
  {
  }
  virtual int GetNumElementIndices (int nelem) const
  {
    return nelem+1;
  }
  virtual int GetLineCount () const
  {
    return GetNumIndices()-1;
  }
  virtual int GetTriangleCount () const
  {
    return 0;
  }
  virtual int GetElementCount () const
  {
    return GetNumIndices()-1;
  }
  virtual void GetElement (int i, int *ni, unsigned int *i0, unsigned int *i1, unsigned int *i2, unsigned int *i3) const
  {
    *ni = 2;
    *i0 = GetIndex(i);
    *i1 = GetIndex(i+1);
  }
  virtual void Load ();
};

/**
 * Triangle set class.
 * It indexes a vertex array using GL_TRIANGLES.
 */
class UGL_API UGLTriangleSet : public UGLIndices
{
public:
  /*
   * Creates an index array and allocates 'nt' triangles in main memory
   * See the UGLIndices class constructor for more information.
   */
  static UGLTriangleSet* CreateCpu (int nt, unsigned int maxVerts, int accessHint=-1, int timeHint=-1);
  /*
   * Creates an index array and allocates 'nt' triangles in video memory
   * See the UGLIndices class constructor for more information.
   */
  static UGLTriangleSet* CreateGpu (int nt, unsigned int maxVerts, int accessHint=-1, int timeHint=-1);
  /**
   * Constructs a new triangle set indexing an array of at most 'maxVerts' vertices.
   * See the UGLIndices class constructor for more information.
   */
  UGLTriangleSet (unsigned int maxVerts, int accessHint=-1, int timeHint=-1) : UGLIndices(maxVerts, accessHint, timeHint)
  {
  }
  /**
   * Copy constructor.
   */
  UGLTriangleSet (const UGLTriangleSet *src) : UGLIndices(src)
  {
  }
  /**
   * Destructor
   */
  virtual ~UGLTriangleSet ()
  {
  }
  /*
   * Adds triangle 'v0 v1 v2' to the array.
   */
  void AddTriangle (unsigned int v0, unsigned int v1, unsigned int v2)
  {
    AddIndex(v0);
    AddIndex(v1);
    AddIndex(v2);
  }
  /*
   * Sets triangle on position 'id' as 'v0 v1 v2'.
   */
  void SetTriangle (int id, unsigned int v0, unsigned int v1, unsigned int v2)
  {
    SetIndex(3*id,v0);
    SetIndex(3*id+1,v1);
    SetIndex(3*id+2,v2);
  }
  /*
   * Gets triangle on position 'id', storing the indices on 'v0 v1 v2'.
   */
  void GetTriangle (int id, unsigned int*v0, unsigned int*v1, unsigned int*v2) const
  {
    *v0 = GetIndex(3*id);
    *v1 = GetIndex(3*id+1);
    *v2 = GetIndex(3*id+2);
  }
  virtual int GetNumElementIndices (int nelem) const
  {
    return nelem*3;
  }
  virtual int GetLineCount () const
  {
    return 0;
  }
  virtual int GetTriangleCount () const
  {
    return GetNumIndices()/3;
  }
  virtual int GetElementCount () const
  {
    return GetNumIndices()/3;
  }
  virtual void GetElement (int i, int *ni, unsigned int *i0, unsigned int *i1, unsigned int *i2, unsigned int *i3) const
  {
    *ni = 3;
    GetTriangle(i,i0,i1,i2);
  }
  virtual void Load ();
};

/**
 * Triangle strip class.
 * It indexes a vertex array using GL_TRIANGLE_STRIP.
 */
class UGL_API UGLTriangleStrip : public UGLIndices
{
public:
  /*
   * Creates an index array and allocates 'nt' triangles in main memory
   * See the UGLIndices class constructor for more information.
   */
  static UGLTriangleStrip* CreateCpu (int nt, unsigned int maxVerts, int accessHint=-1, int timeHint=-1);
  /*
   * Creates an index array and allocates 'nt' triangles in video memory
   * See the UGLIndices class constructor for more information.
   */
  static UGLTriangleStrip* CreateGpu (int nt, unsigned int maxVerts, int accessHint=-1, int timeHint=-1);
  /**
   * Constructs a new triangle strip indexing an array of at most 'maxVerts' vertices.
   * See the UGLIndices class constructor for more information.
   */
  UGLTriangleStrip (unsigned int maxVerts, int accessHint=-1, int timeHint=-1) : UGLIndices(maxVerts, accessHint, timeHint)
  {
  }
  /**
   * Copy constructor.
   */
  UGLTriangleStrip (const UGLTriangleStrip *src) : UGLIndices(src)
  {
  }
  /**
   * Destructor
   */
  virtual ~UGLTriangleStrip()
  {
  }
  virtual int GetNumElementIndices (int nelem) const
  {
    return nelem+2;
  }
  virtual int GetLineCount () const
  {
    return 0; 
  }
  virtual int GetTriangleCount () const
  {
    return GetNumIndices()-2;
  }
  virtual int GetElementCount () const
  {
    return GetNumIndices()-2;
  }
  virtual void GetElement (int i, int *ni, unsigned int *i0, unsigned int *i1, unsigned int *i2, unsigned int *i3) const
  {
    *ni = 3;
    *i0 = GetIndex(i);
    *i1 = GetIndex(i+1);
    *i2 = GetIndex(i+2);
  }
  virtual void Load ();
};

/**
 * Quad set class.
 * It indexes a vertex array using GL_QUADS.
 */
class UGL_API UGLQuadSet : public UGLIndices
{
public:
  /*
   * Creates an index array and allocates 'nq' quads in main memory
   * See the UGLIndices class constructor for more information.
   */
  static UGLQuadSet* CreateCpu (int nq, unsigned int maxVerts, int accessHint=-1, int timeHint=-1);
  /*
   * Creates an index array and allocates 'nq' quads in video memory
   * See the UGLIndices class constructor for more information.
   */
  static UGLQuadSet* CreateGpu (int nq, unsigned int maxVerts, int accessHint=-1, int timeHint=-1);
  /**
   * Constructs a new quad set indexing an array of at most 'maxVerts' vertices.
   * See the UGLIndices class constructor for more information.
   */
  UGLQuadSet (unsigned int maxVerts, int accessHint=-1, int timeHint=-1) : UGLIndices(maxVerts, accessHint, timeHint)
  {
  }
  /**
   * Copy constructor.
   */
  UGLQuadSet (const UGLQuadSet *src) : UGLIndices(src)
  {
  }
  /**
   * Destructor
   */
  virtual ~UGLQuadSet ()
  {
  }
  /*
   * Adds quad 'v0 v1 v2 v3' to the array.
   */
  void AddQuad (unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3)
  {
    AddIndex(v0);
    AddIndex(v1);
    AddIndex(v2);
    AddIndex(v3);
  }
  /*
   * Sets quad on position 'id' as 'v0 v1 v2 v3'.
   */
  void SetQuad (int id, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3)
  {
    SetIndex(4*id,v0);
    SetIndex(4*id+1,v1);
    SetIndex(4*id+2,v2);
    SetIndex(4*id+3,v3);
  }
  /*
   * Gets quad on position 'id', storing the indices on 'v0 v1 v2 v3'.
   */
  void GetQuad (int id, unsigned int*v0, unsigned int*v1, unsigned int*v2, unsigned int*v3) const
  {
    *v0 = GetIndex(4*id);
    *v1 = GetIndex(4*id+1);
    *v2 = GetIndex(4*id+2);
    *v3 = GetIndex(4*id+3);
  }
  virtual int GetNumElementIndices (int nelem) const
  {
    return nelem*4;
  }
  virtual int GetLineCount () const
  {
    return 0;
  }
  virtual int GetTriangleCount () const
  {
    return GetNumIndices()/2; // each quad generates 2 triangles
  }
  int GetQuadCount () const
  {
    return GetNumIndices()/4;
  }
  virtual int GetElementCount () const
  {
    return GetNumIndices()/4;
  }
  virtual void GetElement (int i, int *ni, unsigned int *i0, unsigned int *i1, unsigned int *i2, unsigned int *i3) const
  {
    *ni = 4;
    GetQuad(i,i0,i1,i2,i3);
  }
  virtual void Load ();
};

/**
 * Quad strip class.
 * It indexes a vertex array using GL_QUADSTRIP.
 */
class UGL_API UGLQuadStrip : public UGLIndices
{
public:
  /*
   * Creates an index array and allocates 'nq' quads in main memory
   * See the UGLIndices class constructor for more information.
   */
  static UGLQuadStrip* CreateCpu (int nq, unsigned int maxVerts, int accessHint=-1, int timeHint=-1);
  /*
   * Creates an index array and allocates 'nq' quads in video memory
   * See the UGLIndices class constructor for more information.
   */
  static UGLQuadStrip* CreateGpu (int nq, unsigned int maxVerts, int accessHint=-1, int timeHint=-1);
  /**
   * Constructs a new quad strip indexing an array of at most 'maxVerts' vertices.
   * See the UGLIndices class constructor for more information.
   */
  UGLQuadStrip (unsigned int maxVerts, int accessHint=-1, int timeHint=-1) : UGLIndices(maxVerts, accessHint, timeHint)
  {
  }
  /**
   * Copy constructor.
   */
  UGLQuadStrip (const UGLQuadStrip *src) : UGLIndices(src)
  {
  }
  /**
   * Destructor
   */
  virtual ~UGLQuadStrip ()
  {
  }
  virtual int GetNumElementIndices (int nelem) const
  {
    return (nelem*2)+2;
  }
  virtual int GetLineCount () const
  {
    return 0;
  }
  virtual int GetTriangleCount () const
  {
    return GetNumIndices()-2;
  }
  int GetQuadCount () const
  {
    return (GetNumIndices()-2)/2;
  }
  virtual int GetElementCount () const
  {
    return (GetNumIndices()-2)/2;
  }
  virtual void GetElement (int i, int *ni, unsigned int *i0, unsigned int *i1, unsigned int *i2, unsigned int *i3) const
  {
    *ni = 4;
    *i0 = GetIndex(2*i);
    *i1 = GetIndex(2*i+1);
    *i2 = GetIndex(2*i+2);
    *i3 = GetIndex(2*i+3);
  }
  virtual void Load ();
};
/**
 * Grid strip class.
 * It constructs the topology of a 'm' x 'n' grid using a triangle strip.
 */
class UGL_API UGLGridStrip : public UGLTriangleStrip
{
public:
  /**
   * Constructs a new gridstrip of m x n vertices (automatically allocated in main memory (CPU)).
   * See the UGLIndices class constructor for more information.
   */
  UGLGridStrip (int m, int n, int accessHint=-1, int timeHint=-1);
  /**
   * Destructor.
   */
  virtual ~UGLGridStrip ()
  {
  }
  /**
   * Constructs a gridstrip of m x n vertices on 'strip'.
   */
  static void BuildGridStrip (UGLTriangleStrip *strip, int m, int n);
};

#endif
