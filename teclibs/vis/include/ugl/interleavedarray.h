// Interleaved Vertex Array class
// vbarata@tecgraf.puc-rio.br
// Ago 2007

#ifndef UGL_INTERLEAVEDARRAY_H
#define UGL_INTERLEAVEDARRAY_H

#include "defines.h"
#include "uglmem.h"
#include <ds/array.h>

class UGLDataArrayType;
class UGLDataArray;
class UGLSubArray;

/**
* UGLInterleavedArray Class.
*
* This class implements OpenGL vertex arrays with the following features:
* - Interleaved vertex, color, normal, texcoord, generic attribute data
* - Multiple sub-arrays with the same components and types
* - One single GL buffer object to avoid multiple binds/unbinds
* - Efficient rendering of multiple arrays with a single GL pointer setup call
* - Methods to manipulate the array in main or video memory
*
* Methods are provided to:
* - create, resize and destroy the array
* - query the size of the array
* - load and unload the array
* - set, add and get individual vertices values
* - set, add and get ranges of vertices values at once
* - set GL buffer object properties
*
* InterleavedArray internal memory organization:
* 
*                            InterleavedArray (max vertices)
* +--------------------+--------------------+--------------------+-------------+
* |              |\\\\\|              |\\\\\|              |\\\\\|/////////////|
* +--------------------+--------------------+--------------------+-------------+
*       SubArray[0]          SubArray[1]          SubArray[2]
* |--------------------------------------------------------------|
*                          used vertices
*
* SubArray internal memory organization:
*
*                               SubArray (max vertices)
* +----------------------------------------------------------------+-----------+
* |vvvnnnttvvvnnnttvvvnnnttvvvnnnttvvvnnnttvvv***tt******tt******tt|\\\\\\\\\\\|
* +----------------------------------------------------------------+-----------+
*  |------|                                   |-|  |----|  |----|  |-----------|
*   stride                                        unfilled            unused
*
* - Each data array has its own vertex count so they can be filled independently
* - When rendering, if data arrays have different sizes, the smallest is used
* 
* In the above example:
* - 3 data arrays: xyz-vertices, xyz-normals, st-texcoords
* - Filled so far in the example: 6 vertices, 5 normals, 8 texcoords
* - Stride is the size of a fully defined vertex: 3+3+2 = 8 floats = 32 bytes
*/

class UGL_API UGLInterleavedArray
{
public:
  typedef UGLInterleavedArray* (*ArrayCreateFunc) (
    int accessHint,
    int timeHint);

  enum
  {
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
  * ToDo: Possibly used in 'CopyArrays' function for possible SGInterleavedArray.
  */
  static void SetArrayCreateFunc (ArrayCreateFunc func);
  /**
  * Gets the function responsible for creating arrays.
  */
  static ArrayCreateFunc GetArrayCreateFunc ();
  /**
  * Creates an array identical to 'src'.
  */
  static UGLInterleavedArray* CreateFromArray (UGLInterleavedArray* src);

  // Constructor and destructor

  UGLInterleavedArray (int accessHint = -1, int timeHint = -1);
  ~UGLInterleavedArray ();

  // Setup methods for the memory manager and the GL buffer object

  void SetGrowRate (float rate);
  void SetBOUsageHints (int accessHint, int timeHint);
  void SetAutoCreateBO (bool state);
  void SetAutoFreeAfterBO (bool state);
  void SetAutoUpdateBO (bool state);
  float GetGrowRate ();
  int GetBOAccessHint ();
  int GetBOTimeHint ();
  GLuint GetBOId ();
  bool IsInCpu ();
  bool IsInGpu ();
  void FlagCpuChanged ();
  void FlagGpuChanged ();
  bool ReserveCpu (int numVertices, bool exactSize=true);
  bool ReserveGpu (int numVertices, bool exactSize=true, bool unbind=true);
  bool ResizeTightCpu (bool subArrays = true, bool memoryBlock = true);
  bool ResizeTightGpu (bool subArrays = true, bool memoryBlock = true, bool forceKeepCpuCopy = false, bool unbind=true);
  bool CopyToCpu (bool tightCopy=false, bool unbind=true);
  bool CopyToGpu (bool tightCopy=false, bool unbind=true);
  bool CreateVBO (bool tightCopy=false, bool unbind=true);
  void* MapArray (int accessType);
  bool UnmapArray (bool unbind = true);
  void FreeCpu ();
  void FreeGpu ();

  // Early setup methods for DataArrays
  // - Add() can be called only for an empty array

  int AddDataArray (int which, int components, int dataType);
  void SetDataArray (int id, int vpAttribIndex, bool vpAttribNormalize);
  void SetDataArray (int id, bool active);
  int GetDataArrayCount ()
  {
    return m_dataArrayTypes.Size();
  }

  int GetDataArrayId (int which);
  int GetDataArrayWhich (int id);
  int GetDataArrayComponents (int id);
  int GetDataArrayType (int id);
  int GetDataArrayStart (int id);
  unsigned int GetDataArrayAttribIndex (int id);
  bool GetDataArrayAttribNormalize (int id);
  bool GetDataArrayActive (int id);

  int GetStride ();
  int GetTotalDataArrayComponents ();

  // Managing sub-arrays
  // Add() methods work on both cpu and gpu, but allocate memory as requested
  // the other area remains un-allocated until a reserve/copy method

  int GetSubArrayCount ()
  {
    return m_subArrays.Size();
  }

  int AddSubArrayCpu (int maxVertexCount=0, int vertexCount=0, bool keepSizeMinimal=true);
  int AddSubArrayGpu (int maxVertexCount=0, int vertexCount=0, bool keepSizeMinimal=true, bool unbind=true);
  bool ResizeSubArrayCpu (int id, int numVertices, bool exactSize=false, bool keepSizeMinimal=true);
  bool ResizeSubArrayGpu (int id, int numVertices, bool exactSize=false, bool keepSizeMinimal=true);
  bool ReserveSubArrayCpu (int id, int numVertices, bool exactSize=false, bool keepSizeMinimal=true);
  bool ReserveSubArrayGpu (int id, int numVertices, bool exactSize=false, bool keepSizeMinimal=true);
  bool CopySubArrayToCpu (int id, int start=0, int count=0, bool keepSizeMinimal=true);
  bool CopySubArrayToGpu (int id, int start=0, int count=0, bool keepSizeMinimal=true);
  void FreeSubArrayCpu (int id);
  void FreeSubArrayGpu (int id);
  void RemoveSubArray (int id);
  int GetSubArrayStartCpu (int id);
  int GetSubArrayStartGpu (int id);
  int GetSubArrayStart (int id)
  {
    if (IsInGpu()) return GetSubArrayStartGpu(id);
    else return GetSubArrayStartCpu(id);
  }

  void GetSubArrayStartListCpu (GLint* startList);
  void GetSubArrayStartListGpu (GLint* startList);
  void GetSubArrayStartList (GLint* startList)
  {
    if (IsInGpu()) GetSubArrayStartListGpu(startList);
    else GetSubArrayStartListCpu(startList);
  }

  // Managing data arrays and vertex counters

  int GetUsedVertexCountCpu ();
  int GetUsedVertexCountGpu ();
  int GetUsedVertexCount () // Vertices marked as used by sub-arrays
  {
    if (IsInGpu())
      return GetUsedVertexCountGpu();
    else
      return GetUsedVertexCountCpu();
  }

  int GetMaxVertexCountCpu ();
  int GetMaxVertexCountGpu ();
  int GetMaxVertexCount () // Total allocated vertices
  {
    if (IsInGpu())
      return GetMaxVertexCountGpu();
    else
      return GetMaxVertexCountCpu();
  }

  int GetVertexCountCpu ();
  int GetVertexCountGpu ();
  int GetVertexCount () // Drawable vertices in sub-arrays
  {
    if (IsInGpu())
      return GetVertexCountGpu();
    else
      return GetVertexCountCpu();
  }

  int GetVertexCountCpu (int subArrayId, int dataArrayId);
  int GetVertexCountGpu (int subArrayId, int dataArrayId);
  int GetVertexCount (int subArrayId, int dataArrayId) // Drawable vertices
  {
    if (IsInGpu())
      return GetVertexCountGpu(subArrayId, dataArrayId);
    else
      return GetVertexCountCpu(subArrayId, dataArrayId);
  }

  int GetVertexCountCpu (int subArrayId);
  int GetVertexCountGpu (int subArrayId);
  int GetVertexCount (int subArrayId) // Drawable vertices
  {
    if (IsInGpu()) return GetVertexCountGpu(subArrayId);
    else return GetVertexCountCpu(subArrayId);
  }

  void GetVertexCountListCpu (GLsizei* countList);
  void GetVertexCountListGpu (GLsizei* countList);
  void GetVertexCountList (GLsizei* countList) // Drawable vertices
  {
    if (IsInGpu()) GetVertexCountListGpu(countList);
    else GetVertexCountListCpu(countList);
  }

  // Setting, Adding and Getting Data
  // All methods accept and return void* pointers.
  // The client should convert to/from the appropriate type.

  void SetValueCpu (int subArrayId, int dataArrayId, int index, void *value)
  {
    SetRangeCpu(subArrayId, dataArrayId, index, 1, value);
  }

  void AddValueCpu (int subArrayId, int dataArrayId, void *value)
  {
    AddRangeCpu(subArrayId, dataArrayId, 1, value);
  }

  void GetValueCpu (int subArrayId, int dataArrayId, int index, void *value)
  {
    GetRangeCpu(subArrayId, dataArrayId, index, 1, value);
  }

  void SetSubArrayValueCpu (int subArrayId, int index, void *values)
  {
    SetSubArrayRangeCpu(subArrayId, index, 1, values);
  }

  void AddSubArrayValueCpu (int subArrayId, void *values)
  {
    AddSubArrayRangeCpu(subArrayId, 1, values);
  }

  void GetSubArrayValueCpu (int subArrayId, int index, void *values)
  {
    GetSubArrayRangeCpu(subArrayId, index, 1, values);
  }

  void SetRangeCpu (int subArrayId, int dataArrayId, int start, int count, void *values);
  void AddRangeCpu (int subArrayId, int dataArrayId, int count, void *values);
  void GetRangeCpu (int subArrayId, int dataArrayId, int start, int count, void *values);
  void SetSubArrayRangeCpu (int subArrayId, int start, int count, void *values);
  void AddSubArrayRangeCpu (int subArrayId, int count, void *values);
  void GetSubArrayRangeCpu (int subArrayId, int start, int count, void *values);
  void SetValueGpu (int subArrayId, int dataArrayId, int index, void *value)
  {
    SetRangeGpu(subArrayId, dataArrayId, index, 1, value);
  }

  void AddValueGpu (int subArrayId, int dataArrayId, void *value)
  {
    AddRangeGpu(subArrayId, dataArrayId, 1, value);
  }

  void GetValueGpu (int subArrayId, int dataArrayId, int index, void *value)
  {
    GetRangeGpu(subArrayId, dataArrayId, index, 1, value);
  }

  void SetSubArrayValueGpu (int subArrayId, int index, void *values)
  {
    SetSubArrayRangeGpu(subArrayId, index, 1, values);
  }

  void AddSubArrayValueGpu (int subArrayId, void *values)
  {
    AddSubArrayRangeGpu(subArrayId, 1, values);
  }

  void GetSubArrayValueGpu (int subArrayId, int index, void *values)
  {
    GetSubArrayRangeGpu(subArrayId, index, 1, values);
  }

  void SetRangeGpu (int subArrayId, int dataArrayId, int start, int count, void *values);
  void AddRangeGpu (int subArrayId, int dataArrayId, int count, void *values);
  void GetRangeGpu (int subArrayId, int dataArrayId, int start, int count, void *values);
  void SetSubArrayRangeGpu (int subArrayId, int start, int count, void *values);
  void AddSubArrayRangeGpu (int subArrayId, int count, void *values);
  void GetSubArrayRangeGpu (int subArrayId, int start, int count, void *values);
  void SetSubArrayCpu (int subArrayId, void* values)
  {
    int minVertices = 0, maxVertices = 0;
    CalculateMinMaxSubVerticesCpu(subArrayId, &minVertices, &maxVertices);
    SetSubArrayRangeCpu(subArrayId, 0, maxVertices, values);
  }

  void SetSubArrayGpu (int subArrayId, void* values)
  {
    int minVertices = 0, maxVertices = 0;
    CalculateMinMaxSubVerticesGpu(subArrayId, &minVertices, &maxVertices);
    SetSubArrayRangeGpu(subArrayId, 0, maxVertices, values);
  }

  void GetSubArrayCpu (int subArrayId, void* values)
  {
    int minVertices = 0, maxVertices = 0;
    CalculateMinMaxSubVerticesCpu(subArrayId, &minVertices, &maxVertices);
    GetSubArrayRangeCpu(subArrayId, 0, maxVertices, values);
  }

  void GetSubArrayGpu (int subArrayId, void* values)
  {
    int minVertices = 0, maxVertices = 0;
    CalculateMinMaxSubVerticesGpu(subArrayId, &minVertices, &maxVertices);
    GetSubArrayRangeGpu(subArrayId, 0, maxVertices, values);
  }

  void SetDataArrayCpu (int subArrayId, int dataArrayId, void* values);
  void SetDataArrayGpu (int subArrayId, int dataArrayId, void* values);
  void GetDataArrayCpu (int subArrayId, int dataArrayId, void* values);
  void GetDataArrayGpu (int subArrayId, int dataArrayId, void* values);

  // Usage methods

  void Load ();
  void Unload ();
  bool LoadFeedback (int offset=0, int size=0);
  void UnloadFeedback ();

private:

  // Private auxiliary methods

  void CalculateDataStartOffsets ();
  void CalculateStride ();
  void CalculateMinMaxSubVerticesCpu (int subArrayId, int *minVertices, int *maxVertices);
  void CalculateMinMaxSubVerticesGpu (int subArrayId, int *minVertices, int *maxVertices);
  bool VerifyComponents (int which, int components);

  // Private members

  DsArray<UGLSubArray*> m_subArrays;
  DsArray<UGLDataArrayType*> m_dataArrayTypes;
  Mem m_mem;
  int m_stride;
  int m_maxVertexCount;      // Total allocated size
  int m_boMaxVertexCount;
  int m_usedVertexCount;     // Total size marked as used by some sub-array
  int m_boUsedVertexCount;
};

#endif
