// Shader class
// fabraham@tecgraf.puc-rio.br
// Aug 2003 

#ifndef SHADER_H
#define SHADER_H

#include "defines.h"

/**
 * Shader class.
 * This class presents the interface to setup, load and unload a shader.
 * Methods are provided to:
 * - setup the variable names bound to vertex parameters like position, normal, color, texture coordinates, etc.
 * - setup the variable names bound to fragment parameters like textures.
 * - setup constant parameters.
 * - setup state matrix parameters, eg. the modelview matrix.
 * - set/enable/disable vertex/normal/color/texcoord arrays.
 * - load and unload the shader.
 */
class SHADER_API Shader
{
public:
  /**
   * State matrix.
   */
  enum Matrix
  {
    /**
     * Modelview matrix.
     */
    MODELVIEW,
    /**
     * Projection matrix.
     */
    PROJECTION,
    /**
     * Texture matrix.
     */
    TEXTURE,
    /**
     * Concatenated modelview-projection matrix (model to clipping space).
     */
    MODELVIEW_PROJECTION,
  };
  /**
   * State matrix transformation.
   */
  enum Transform
  {
    /**
     * Apply no transformation.
     */
    IDENTITY,
    /**
     * Transpose the matrix.
     */
    TRANSPOSE,
    /**
     * Invert the matrix.
     */
    INVERSE,
    /**
     * Invert and transpose the matrix.
     */
    INVERSE_TRANSPOSE,
  };
  /**
   * Target program.
   */
  enum Target
  {
    /**
     * vertex program.
     */
    VP,
    /**
     * Fragment program.
     */
    FP,
    /**
     * Gemetry program.
     */
    GP,
  };
  enum AttribMode
  {
    /**
    * Separate Attributes (several buffer objects).
    */
    SEPARATE_ATTRIBS = 0,
    /**
    * Interleaved Attributes (single buffer object).
    */
    INTERLEAVED_ATTRIBS = 1,
  };
public:
  /**
   * Constructor
   */
  Shader () {}
  /**
   * Destructor
   */
  virtual ~Shader () {}
  /**
   * Loads and compiles the 'target' program on file 'file'. On success, true must be returned. "entry" is the main function, args are the arguments passed to it.
   */
  bool CompileFile (Target target, const char* file, const char* entry="main", const char** args=0)
  {
    return CompileFiles(target, 1, &file, entry, args);
  }
  /**
   * Loads and compiles the 'target' program on string 'code'. On success, true must be returned. "entry" is the main function, args are the arguments passed to it.
   */
  bool CompileString (Target target, const char* code, const char* entry="main", const char** args=0)
  {
    return CompileStrings(target, 1, &code, entry, args);
  }
  /**
   * Loads and compiles the 'target' program on the files 'files[0..file_count-1]'. On success, true must be returned. "entry" is the main function, args are the arguments passed to it.
   */
  virtual bool CompileFiles (Target target, int file_count, const char** files, const char* entry="main", const char** args=0) = 0;
  /**
   * Loads and compiles the 'target' program on the strings 'codes[0..string_count-1]'. On success, true must be returned. "entry" is the main function, args are the arguments passed to it.
   */
  virtual bool CompileStrings (Target target, int string_count, const char** codes, const char* entry="main", const char** args=0) = 0;
  /**
   * Links the VP (if existing) with the GP (if existing) and the FP (if existing).
   * On success, true must be returned.
   */
  virtual bool Link () = 0;
  /**
   * Informs the name of the variable bound with the vertex position on the vertex program.
   */
  virtual bool BindPosition (const char* name) = 0;
  /**
   * Informs the name of the variable bound with the vertex normal on the vertex program.
   */
  virtual bool BindNormal (const char* name) = 0;
  /**
   * Informs the name of the variable bound with the vertex color on the vertex program.
   */
  virtual bool BindColor (const char* name) = 0;
  /**
   * Informs the name of the variable bound with the vertex texture coordinate set 'unit' on the vertex program.
   */
  virtual bool BindTexCoord (const char* name, int unit) = 0;
  /**
   * Informs the name of the variable bound with the sampler parameter of texture name 'id' on the fragment program.
   */
  virtual bool BindTexture (const char* name, unsigned int id) = 0;
  /**
   * Sets a constant of type float1.
   */
  virtual bool SetConstant (Target target, const char* name, float x) = 0;
  /**
   * Sets a constant of type float2.
   */
  virtual bool SetConstant (Target target, const char* name, float x, float y) = 0;
  /**
   * Sets a constant of type float3.
   */
  virtual bool SetConstant (Target target, const char* name, float x, float y, float z) = 0;
  /**
   * Sets a constant of type float4.
   */
  virtual bool SetConstant (Target target, const char* name, float x, float y, float z, float w) = 0;
  /**
   * Sets a constant of type float[rows]x[columns]. 'm' must be assumed to be of size rows*columns in matrix column order.
   */
  virtual bool SetConstant (Target target, const char* name, int rows, int columns, const float* m) = 0;
  /**
   * Sets a state matrix (type float4x4) of type 'matrix' and transformation 'transform'.
   */
  virtual bool TrackMatrix (Target target, const char* name, Matrix matrix, Transform transform) = 0;
  /**
   * Sets the current vertex pointer (just like glVertexPointer)
   */
  virtual void SetVertexPointer (int size, unsigned int type, int stride, const void* pointer) = 0;
  /**
   * Sets the current normal pointer (just like glNormalPointer)
   */
  virtual void SetNormalPointer (unsigned int type, int stride, const void* pointer) = 0;
  /**
   * Sets the current color pointer (just like glColorPointer)
   */
  virtual void SetColorPointer (int size, unsigned int type, int stride, const void* pointer) = 0;
  /**
   * Sets the current texture coordinate pointer (just like glTexCoordPointer) for texture unit 'unit'.
   */
  virtual void SetTexCoordPointer (int size, unsigned int type, int stride, const void* pointer, int unit) = 0;
  /**
   * Enables the current vertex array.
   */
  virtual void EnableVertexArray () = 0;
  /**
   * Enables the current normal array.
   */
  virtual void EnableNormalArray () = 0;
  /**
   * Enables the current color array.
   */
  virtual void EnableColorArray () = 0;
  /**
   * Enables the current texture coordinate array for texture unit 'unit'.
   */
  virtual void EnableTexCoordArray (int unit) = 0;
  /**
   * Disables the current vertex array.
   */
  virtual void DisableVertexArray () = 0;
  /**
   * Disables the current normal array.
   */
  virtual void DisableNormalArray () = 0;
  /**
   * Disables the current color array.
   */
  virtual void DisableColorArray () = 0;
  /**
   * Disables the current texture coordinate array for texture unit 'unit'.
   */
  virtual void DisableTexCoordArray (int unit) = 0;
  /**
   * Loads the shader.
   */
  virtual void Load () = 0;
  /**
   * Unloads the shader.
   */
  virtual void Unload () = 0;
};

#endif
