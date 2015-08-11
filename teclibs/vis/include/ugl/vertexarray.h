// Vertex Array class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// vbarata@tecgraf.puc-rio.br
// Sep 2002 - Jul 2007

#ifndef UGL_VERTEXARRAY_H
#define UGL_VERTEXARRAY_H

#include "defines.h"
#include "uglmem.h"
#include <alg/matrix.h>
#include <ds/list.h>
#include <assert.h>

/**
 * UGLArray Class.
 *
 * This class implements OpenGL vertex arrays that can be:
 * - position array.
 * - normal array.
 * - color array.
 * - texture coordinates array.
 * - generic vertex attributes array
 *
 * Methods are provided to:
 * - create, resize and destroy the array in main or video memory.
 * - query the size of the array and whether it is in main or video memory
 * - load and unload the array.
 * - set, add and get individual vertices values
 * - set and get all vertices values at once
 * - set GL buffer object properties
 */
class UGL_API UGLArray
{
public:
  typedef UGLArray* (*ArrayCreateFunc) (
    int which,
    int nelem,
    int type,
    int accessHint,
    int timeHint);
protected:
  int m_which;        // Usage of the array. See constructor for more info.
  int m_nelem;        // Number of elements in each vertex (e.g. (x,y,z) = 3)
  int m_nverts_cpu;   // Number of vertices in main memory
  int m_nverts_gpu;   // Number of vertices in video memory
  Mem m_mem;          // Internal data structure (memmanager.h/.cpp)
  void *m_values;     // General  pointer to the main memory buffer
  short *m_svalues;   // 'short'  pointer to the main memory buffer
  int *m_ivalues;     // 'int'    pointer to the main memory buffer
  float *m_fvalues;   // 'float'  pointer to the main memory buffer
  double *m_dvalues;  // 'double' pointer to the main memory buffer
  int m_type;         // Data type (GL_SHORT, GL_INT, GL_FLOAT, GL_DOUBLE)
  unsigned int m_typesize;      // Size of the data type (1,2,4...)
  unsigned int m_vpattribindex; // Index for vertex program attribute bindings
  bool m_vpattribnormalize;     // Normalization flag for VP attributes
public:
  enum {
    /**
     * Vertex position array
     */
    V_POSITION=0,
    /**
     * Vertex normal array
     */
    V_NORMAL=1,
    /**
     * Vertex color array
     */
    V_COLOR=2,
    /**
    * Vertex secondary color array
    */
    V_COLOR2=3,
    /**
    * Vertex indexed color array
    */
    V_INDEX=4,
    /**
    * Vertex fog coordinates array
    */
    V_FOGCOORD=5,
    /**
     * Vertex texture coordinates array (same as V_TEXCOORD0)
     */
    V_TEXCOORD=6,
    /**
     * Vertex texture coordinates 0 array
     */
    V_TEXCOORD0=6,
    /**
     * Vertex texture coordinates 1 array
     */
    V_TEXCOORD1=7,
    /**
     * Vertex texture coordinates 2 array
     */
    V_TEXCOORD2=8,
    /**
     * Vertex texture coordinates 3 array
     */
    V_TEXCOORD3=9,
    /**
     * Vertex texture coordinates 4 array
     */
    V_TEXCOORD4=10,
    /**
     * Vertex texture coordinates 5 array
     */
    V_TEXCOORD5=11,
    /**
     * Vertex texture coordinates 6 array
     */
    V_TEXCOORD6=12,
    /**
     * Vertex texture coordinates 7 array
     */
    V_TEXCOORD7=13,
    /**
     * Vertex program attribute
     */
    V_VPATTRIB=14
  };
  /**
   * Sets the function responsible for creating arrays.
   * Used in the 'CopyArrays' function.
   */
  static void SetArrayCreateFunc (ArrayCreateFunc func);
  /**
   * Gets the function responsible for creating arrays.
   */
  static ArrayCreateFunc GetArrayCreateFunc ();
  /**
   * Creates an array identical to 'src'.
   */
  static UGLArray* CreateFromArray (UGLArray* src);
  /**
   * Creates an array and allocates 'nv' vertices in main memory, each with
   * 'nelem' elements of type 'type'. See constructor for more information.
   */
  static UGLArray* CreateCpu (
    int nv,
    int which = V_POSITION,
    int nelem = 3,
    int type = GL_FLOAT,
    int accessHint = -1,
    int timeHint = -1);
  /**
   * Creates an array and allocates 'nv' vertices in video memory, each with
   * 'nelem' elements of type 'type'. See constructor for more information.
   */
  static UGLArray* CreateGpu (
    int nv,
    int which = V_POSITION,
    int nelem = 3,
    int type = GL_FLOAT,
    int accessHint = -1,
    int timeHint = -1);
  /**
   * Constructor.
   *
   * 'which': type of vertex information, one of the following values:
   * - V_POSITION
   * - V_NORMAL
   * - V_COLOR
   * - V_COLOR2
   * - V_INDEX
   * - V_FOGCOORD
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
   * 'nelem': number of elements per vertex (coordinates usually) (2<=nelem<=4)
   * 'type': GL_SHORT || GL_INT || GL_FLOAT || GL_DOUBLE
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
  UGLArray (
    int which = V_POSITION,
    int nelem = 3,
    int type = GL_FLOAT,
    int accessHint = -1,
    int timeHint = -1);
  /**
   * Destructor
   */
  virtual ~UGLArray ();
  /**
   * Is the vertex array in main memory? (backward compatibility)
   */
  bool IsInMainMemory ();
  /**
   * Is the vertex array in main memory?
   */
  bool IsInCpu ();
  /**
   * Is the vertex array in video memory (VBO)?
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
   * Resizes the cpu-based array to 'nv' vertices.
   * This method and the default value for 'exactSize' are intended for backward compatibility
   */
  bool Resize (int nv, bool exactSize=true)
  {
    return ResizeCpu(nv, exactSize);
  }
  /**
   * Resizes the cpu-based array to 'nv' vertices.
   * - When 'exactSize' is not requested (default), the array's total capacity
   *   will not shrink, and it will grow by multiplying its size by a factor.
   * - When 'copyFromGpu' is true, 'nv' will be ignored, the cpu array size will
   *   match the gpu`s, and the gpu array contents will be copied in.
   * - If a GL buffer object needs to be bound during the operation, setting
   *   'unbind' to false prevents it from being unbound (for performance)
   */
  bool ResizeCpu (int nv, bool exactSize=false, bool copyFromGpu = false, bool unbind=true);
  /**
   * Resizes the gpu-based array to 'nv' vertices.
   * - When 'exactSize' is not requested (default), the array's total capacity
   *   will not shrink, and it will grow by multiplying its size by a factor.
   * - When 'copyFromCpu' is true, 'nv' will be ignored, the gpu array size will
   *   match the cpu`s, and the cpu array contents will be copied in.
   * - If a GL buffer object needs to be bound during the operation, setting
   *   'unbind' to false prevents it from being unbound (for performance)
   */
  bool ResizeGpu (int nv, bool exactSize=false, bool copyFromCpu = false, bool unbind=true);
  /**
   * Reserves cpu memory space for at least 'nv' vertices (or exactly 'nv' if 'exactsize' is true)
   * The number of actual vertices on the array will not be altered, so the user can call
   * "AddValue*" fill up the array.
   * Read notes on "ResizeCpu" for information on other parameters.
   */
  bool ReserveCpu (int nv, bool exactSize=false, bool copyFromGpu = false, bool unbind=true);
  /**
   * Creates a VBO containing the vertex values.
   */
  bool CreateVBO (bool unbind=true);
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
   * Maps the GPU vertex array into main memory
   * Must be using the 'float' data type in GPU.
   * 'accessType' must be one of the following:
   * - GL_READ_ONLY[_ARB]
   * - GL_WRITE_ONLY[_ARB]
   * - GL_READ_WRITE[_ARB]
   */
  float* MapArray (int accessType);
  /**
   * Maps the GPU vertex array into main memory
   * Must be using the 'float' data type in GPU.
   * See MapArray() for a description of 'accessType'
   */
  float* MapArrayf (int accessType);
  /**
   * Maps the GPU vertex array into main memory
   * Must be using the 'double' data type in GPU.
   * See MapArray() for a description of 'accessType'
   */
  double* MapArrayd (int accessType);
  /**
   * Maps the GPU vertex array into main memory
   * Must be using the 'int' data type in GPU.
   * See MapArray() for a description of 'accessType'
   */
  int* MapArrayi (int accessType);
  /**
   * Maps the GPU vertex array into main memory
   * Must be using the 'short' data type in GPU.
   * See MapArray() for a description of 'accessType'
   */
  short* MapArrays (int accessType);
  /**
   * Unmaps the GPU vertex array from main memory
   * If it returns false, then the array data has
   * become corrupted and must be resubmitted.
   */
  bool UnmapArray (bool unbind = true);
  /**
   * Frees the array from main memory
   */
  void FreeCpu ();
  /**
   * Frees the array from video memory
   */
  void FreeGpu ();
  /**
   * Returns true if the next Load() call will use the array data on GPU, false otherwise.
   */
  bool WillUseGpu ();
  /**
   * Updates the vertex array (do everything that is done before setting it as
   * the current vertex array for its type).
   */
  void Update (bool unbind=true);
  /**
   * Loads the vertex array, setting vertex pointer and enabling it.
   * 'unbind' signals if the used VBO must be unbound.
   */
  void Load (bool unbind=true);
  /**
  * Unloads the vertex array.
  */
  void Unload ();
  /**
   * Loads the vertex array for transform feedback mode.
   */
  bool LoadFeedback ();
  /**
  * Unloads the vertex array from transform feedback mode.
  */
  void UnloadFeedback ();
  /**
   * Sets the type of the array, which can be of the following values:
   * - V_POSITION
   * - V_NORMAL
   * - V_COLOR
   * - V_COLOR2
   * - V_INDEX
   * - V_FOGCOORD
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
  void SetWhich (int which)
  {
    m_which = which;
  }
  /**
   * Gets the type of the array.
   */
  int GetWhich () const
  {
    return m_which;
  }
  /**
   * Sets the automatic dynamic growth rate of the array.
   * When resized, if the array needs to grow, its capacity will
   * be multiplied by this constant as many times as necessary.
   */
  void SetGrowRate (float rate);
  /**
   * Gets the automatic dynamic growth rate of the array.
   */
  float GetGrowRate (void);
  /**
   * Which data representation? GL_SHORT || GL_INT || GL_FLOAT || GL_DOUBLE.
   */
  int GetType () const
  {
    return m_type;
  }
  /**
   * Returns the number of vertices in the rendering array.
   */
  int GetSize () const;
  /**
   * Returns the number of vertices in the cpu-based array.
   */
  int GetSizeCpu () const
  {
    return m_nverts_cpu; 
  }
  /**
   * Returns the number of vertices in the gpu-based array.
   */
  int GetSizeGpu () const
  {
    return m_nverts_gpu; 
  }
  /**
   * Returns the total number of bytes used by the cpu-based array.
   */
  size_t GetMemSizeCpu ();
  /**
   * Returns the total number of bytes used by the gpu-based array.
   */
  size_t GetMemSizeGpu ();
  /**
   * Returns the total number of bytes used by both arrays (CPU and GPU).
   */
  size_t GetTotalMemSize ();
  /**
   * Returns the number of elements per vertex (1 to 4).
   */
  int GetNumElements () const
  {
    return m_nelem; 
  }
  /**
   * Obtains the actual vertex array.
   * Returns NULL in case the vertex array is not in main memory.
   * Returns NULL in case the element data type is not 'float'.
   */
  const float* GetArray () const
  {
    return m_fvalues;
  }
  /**
   * Obtains the actual vertex array.
   * Returns NULL in case the vertex array is not in main memory.
   * Returns NULL in case the element data type is not 'float'.
   */
  const float* GetArrayf () const
  {
    return m_fvalues;
  }
  /**
   * Obtains the actual vertex array.
   * Returns NULL in case the vertex array is not in main memory.
   * Returns NULL in case the element data type is not 'double'.
   */
  const double* GetArrayd () const
  {
    return m_dvalues;
  }
  /**
   * Obtains the actual vertex array.
   * Returns NULL in case the vertex array is not in main memory.
   * Returns NULL in case the element data type is not 'int'.
   */
  const int* GetArrayi () const
  {
    return m_ivalues;
  }
  /**
   * Obtains the actual vertex array.
   * Returns NULL in case the vertex array is not in main memory.
   * Returns NULL in case the element data type is not 'short'.
   */
  const short* GetArrays () const
  {
    return m_svalues;
  }
  /**
   * Sets value of vertex 'i'. (0 <= i). Must be using the 'float' data type.
   */
  void SetValue (int i, float x, float y=0.0f, float z=0.0f, float w=0.0f)
  {
    SetValuef(i,x,y,z,w);
  }
  /**
   * Sets value of vertex 'i'. (0 <= i). Must be using the 'float' data type.
   */
  void SetValuef (int i, float x, float y=0.0f, float z=0.0f, float w=0.0f)
  {
    if (i >= m_nverts_cpu) ResizeCpu(i+1, false);
    assert(0<=i && m_fvalues);
    switch (m_nelem) 
    {
    case 4: m_fvalues[m_nelem*i+3] = w;
    case 3: m_fvalues[m_nelem*i+2] = z;
    case 2: m_fvalues[m_nelem*i+1] = y;
    case 1: m_fvalues[m_nelem*i+0] = x;
    }
    if (IsInGpu())
      FlagCpuChanged();
  }
  /**
   * Sets value of vertex 'i'. (0 <= i). Must be using the 'short' data type.
   */
  void SetValues (int i, short x, short y=0, short z=0, short w=0)
  {
    if (i >= m_nverts_cpu) ResizeCpu(i+1, false);
    assert(0<=i && m_svalues);
    switch (m_nelem) 
    {
    case 4: m_svalues[m_nelem*i+3] = w;
    case 3: m_svalues[m_nelem*i+2] = z;
    case 2: m_svalues[m_nelem*i+1] = y;
    case 1: m_svalues[m_nelem*i+0] = x;
    }
    if (IsInGpu())
      FlagCpuChanged();
  }
  /**
   * Sets value of vertex 'i'. (0 <= i). Must be using the 'int' data type.
   */
  void SetValuei (int i, int x, int y=0, int z=0, int w=0)
  {
    if (i >= m_nverts_cpu) ResizeCpu(i+1, false);
    assert(0<=i && m_ivalues);
    switch (m_nelem) 
    {
    case 4: m_ivalues[m_nelem*i+3] = w;
    case 3: m_ivalues[m_nelem*i+2] = z;
    case 2: m_ivalues[m_nelem*i+1] = y;
    case 1: m_ivalues[m_nelem*i+0] = x;
    }
    if (IsInGpu())
      FlagCpuChanged();
  }
  /**
   * Sets value of vertex 'i'. (0 <= i). Must be using the 'double' data type.
   */
  void SetValued (int i, double x, double y=0.0, double z=0.0, double w=0.0)
  {
    if (i >= m_nverts_cpu) ResizeCpu(i+1, false);
    assert(0<=i && m_dvalues);
    switch (m_nelem) 
    {
    case 4: m_dvalues[m_nelem*i+3] = w;
    case 3: m_dvalues[m_nelem*i+2] = z;
    case 2: m_dvalues[m_nelem*i+1] = y;
    case 1: m_dvalues[m_nelem*i+0] = x;
    }
    if (IsInGpu())
      FlagCpuChanged();
  }
  /**
   * Appends a new vertex at the end of the array. For 'float' data type only.
   */
  void AddValue (float x, float y=0.0f, float z=0.0f, float w=0.0f)
  {
    SetValue(m_nverts_cpu,x,y,z,w);
  }
  /**
   * Appends a new vertex at the end of the array. For 'float' data type only.
   */
  void AddValuef (float x, float y=0.0f, float z=0.0f, float w=0.0f)
  {
    SetValuef(m_nverts_cpu,x,y,z,w);
  }
  /**
   * Appends a new vertex at the end of the array. For 'short' data type only.
   */
  void AddValues (short x, short y=0, short z=0, short w=0)
  {
    SetValues(m_nverts_cpu,x,y,z,w);
  }
  /**
   * Appends a new vertex at the end of the array. For 'int' data type only.
   */
  void AddValuei (int x, int y=0, int z=0, int w=0)
  {
    SetValuei(m_nverts_cpu,x,y,z,w);
  }
  /**
   * Appends a new vertex at the end of the array. For 'double' data type only.
   */
  void AddValued (double x, double y=0.0, double z=0.0, double w=0.0)
  {
    SetValued(m_nverts_cpu,x,y,z,w);
  }
  /**
   * Resizes the cpu  array to 'nv' vertices and copies them from 'values'.
   * 'nv*GetNumElements()' elements will be copied.
   * Element data types must match.
   */
  void SetValues (int nv, const void* values)
  {
    SetValuesCpu(nv, values);
  }
  /**
   * Resizes the cpu  array to 'nv' vertices and copies them from 'values'.
   * 'nv*GetNumElements()' elements will be copied.
   * Element data types must match.
   */
  bool SetValuesCpu (int nv, const void* values);
  /**
   * Resizes the gpu  array to 'nv' vertices and copies them from 'values'.
   * 'nv*GetNumElements()' elements will be copied.
   * Element data types must match.
   */
  bool SetValuesGpu (int nv, const void* values);
  /**
   * Gets value of vertex 'i'. (0 <= i < nverts_cpu). 'float' data type only.
   */
  void GetValue (int i, float* x, float* y=0, float* z=0, float* w=0) const
  {
    GetValuef(i,x,y,z,w);
  }
  /**
   * Gets value of vertex 'i'. (0 <= i < nverts_cpu). 'float' data type only.
   */
  void GetValuef (int i, float* x, float* y=0, float* z=0, float* w=0) const
  {
    assert(0<=i && i<m_nverts_cpu && m_fvalues);
    switch (m_nelem)
    {
    case 4: *w = m_fvalues[m_nelem*i+3];
    case 3: *z = m_fvalues[m_nelem*i+2];
    case 2: *y = m_fvalues[m_nelem*i+1];
    case 1: *x = m_fvalues[m_nelem*i+0];
    }
  }
  /**
   * Gets value of vertex 'i'. (0 <= i < nverts_cpu). 'short' data type only.
   */
  void GetValues (int i, short* x, short* y=0, short* z=0, short* w=0) const
  {
    assert(0<=i && i<m_nverts_cpu && m_svalues);
    switch (m_nelem)
    {
    case 4: *w = m_svalues[m_nelem*i+3];
    case 3: *z = m_svalues[m_nelem*i+2];
    case 2: *y = m_svalues[m_nelem*i+1];
    case 1: *x = m_svalues[m_nelem*i+0];
    }
  }
  /**
   * Gets value of vertex 'i'. (0 <= i < nverts_cpu). 'int' data type only.
   */
  void GetValuei (int i, int* x, int* y=0, int* z=0, int* w=0) const
  {
    assert(0<=i && i<m_nverts_cpu && m_ivalues);
    switch (m_nelem)
    {
    case 4: *w = m_ivalues[m_nelem*i+3];
    case 3: *z = m_ivalues[m_nelem*i+2];
    case 2: *y = m_ivalues[m_nelem*i+1];
    case 1: *x = m_ivalues[m_nelem*i+0];
    }
  }
  /**
   * Gets value of vertex 'i'. (0 <= i < nverts_cpu). 'double' data type only.
   */
  void GetValued (int i, double* x, double* y=0, double* z=0, double* w=0) const
  {
    assert(0<=i && i<m_nverts_cpu && m_dvalues);
    switch (m_nelem)
    {
    case 4: *w = m_dvalues[m_nelem*i+3];
    case 3: *z = m_dvalues[m_nelem*i+2];
    case 2: *y = m_dvalues[m_nelem*i+1];
    case 1: *x = m_dvalues[m_nelem*i+0];
    }
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
   * Specifies the array usage: Static or dynamic? (backward compatibility)
   */
  void SetStatic (bool f);
  /**
   * Is the vertex array static? (backward compatibility)
   */
  bool GetStatic ();
  /**
   * Forces/forbids the automatic creation of a GL buffer object when bound.
   */
  void SetAutoCreateBO (bool state);
  /**
   * Forces the static array to (not) be automatically freed from main memory
   * when copied into a GL buffer object. Only used in static vertex arrays.
   */
  void SetAutoFreeAfterBO (bool state);
  /**
   * Forces the GL buffer object to (not) be updated when bound
   */
  void SetAutoUpdateBO (bool state);
  /**
   * Specifies the vertex program generic attribute index.
   * Set normalize as 'true' if the values should be normalized when accessed.
   */
  void SetVPAttribIndex (unsigned int index, bool normalize = false)
  {
    m_vpattribindex = index;
    m_vpattribnormalize = normalize;
  }
  /**
   * Sets the transform feedback index
   */
  void SetFeedbackIndex (unsigned int index);
  /**
   * Gets the vertex program generic attribute index
   */
  unsigned int GetVPAttribIndex (void)
  {
    return m_vpattribindex;
  }
  /**
   * Should the vertex program generic attribute be normalized when accessed?
   */
  bool GetVPAttribNormalize (void)
  {
    return m_vpattribnormalize;
  }
  /**
   * Gets the transform feedback index
   */
  unsigned int GetFeedbackIndex (void);
  /**
   * Transforms the vertices according to the matrix 'm'
   */
  void Transform (const AlgMatrix &m);
private:
  /**
  * Gets the general void* pointer and sets the appropriate
  * typed pointer for the cpu-based array.
  */
  void SetPointers ();
};

/**
 * UGLVertexArray Class.
 * 
 * This class is a UGLArray container that can contain
 * position/color/normal/texcoord/other arrays.
 * 
 * Methods are provided to:
 * - insert/remove/get/copy arrays.
 * - load and unload the array.
 */
class UGL_API UGLVertexArray
{
  struct Array
  {
    UGLArray* array;
    bool enabled;
    Array ()
    : array(NULL)
    , enabled(false)
    {
    }
    Array (UGLArray* array, bool enabled)
    : array(array)
    , enabled(enabled)
    {
    }
  };
  typedef DsList<Array> List;
public:
  typedef List::Iterator Iterator;
  typedef UGLArray* (*ArrayCopyFunc)(const UGLArray* source);
public:
  /**
   * Sets the array copying function.
   * If 'func' is NULL, the function is set to the
   * default value UGLArray::CreateFromArray.
   */
  static void SetArrayCopyFunc (ArrayCopyFunc func);
  /**
   * Constructor
   */
  UGLVertexArray ();
  /**
   * Destructor
   */
  virtual ~UGLVertexArray ();
  /**
   * Inserts an array to the list.
   * 'enabled' signals if the array must be enabled or disabled.
   * Returns true if successful.
   *
   * Note: This function cannot be called during an iteration.
   */
  bool Insert (UGLArray* array, bool enabled=true);
  /**
   * Removes an array from the list.
   * Returns false if array not on the list, true otherwise.
   *
   * Note: This function cannot be called during an iteration.
   */
  bool Remove (UGLArray* array);
  /**
   * Enables/disables an array on the list.
   *
   * Note: This function cannot be called during an iteration.
   */
  void SetEnabled (UGLArray* array, bool enabled);
  /**
   * Removes all vertex arrays from the list.
   *
   * Note: This function cannot be called during an iteration.
   */
  void Clear ();
  /**
   * Returns an iterator of the array list.
   * Default usage:
   * UGLVertexArray* va = ...;
   * for (UGLVertexArray::Iterator i = va->ITBegin(); va->ITValid(i); va->ITNext(i)) {
   *   UGLArray* a  = va->ITCurr(i);
   *   bool enabled = va->ITIsCurrEnabled(i);
   *   ...
   * }
   */
  Iterator ITBegin ()
  {
    return m_list.Begin();
  }
  /**
   * Returns true if there the iterator is valid (if ITCurr()/ITIsCurrEnabled() can be called)
   * or false otherwise.
   */
  bool ITValid (Iterator& i)
  {
    return i.Valid();
  }
  /**
   * Returns the current array on the iteration.
   */
  UGLArray* ITCurr (Iterator& i)
  {
    return i->array;
  }
  /**
   * Returns true if the current array on the iteration is enabled, false otherwise.
   */
  bool ITIsCurrEnabled (Iterator& i)
  {
    return i->enabled;
  }
  /**
   * Proceeds to the next list element.
   */
  void ITNext (Iterator& i)
  {
    ++i;
  }
  /**
   * Gets the first array with type 'which' found, NULL if none found.
   */
  UGLArray* GetArray (int which);
  /**
   *  Informs if all enabled vertex arrays are in main memory.
   */
  bool IsInMainMemory ();
  /**
   * Copies all the arrays in array container 'in'.
   * Returns if the copy was successful.
   */
  virtual bool CopyArrays (const UGLVertexArray& in);
  /**
   * Creates VBOs for all enabled arrays.
   */
  bool CreateVBOs ();
  /**
   * Loads all enabled arrays.
   */
  void Load ();
  /**
  * Unloads loaded arrays.
  */
  void Unload ();
  /**
   * Loads enabled arrays for transform feedback mode.
   */
  void LoadFeedback ();
  /**
  * Unloads loaded arrays from transform feedback mode.
  */
  void UnloadFeedback ();
  /**
   * Obtains the position array size.
   */
  int GetSize ();
  /**
   * Transforms the vertices of all enabled arrays according to the matrix 'm'
   */
  void Transform (const AlgMatrix &m);
private:
  void UpdateEnabledList ();
private:
  DsArray<Array> m_enabled_arrays;
  List m_list;
};

#endif
