// Shader class
// fabraham@tecgraf.puc-rio.br
// Aug 2003 

#ifndef SG_SHADER_H
#define SG_SHADER_H

#include <sg/state.h>
#include <sg/state/texture.h>

/**
 * SGShader class.
 * This class presents the interface to setup, load and unload a shader.
 * Methods must be provided to:
 * - setup the variable names bound to vertex parameters like position, normal, color, texture coordinates, etc.
 * - setup the variable names bound to fragment parameters like textures.
 * - setup constant parameters.
 * - setup state matrix parameters, eg. the modelview matrix.
 * - load and unload the shader.
 */
class SG_API SGShader : public SGState
{
public:
  /**
   * State matrix. (automatically tracked by CG)
   */
  typedef enum 
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
  } Matrix;
  /**
   * State matrix transformation.
   */
  typedef enum 
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
  } Transform;
  /**
   * Target program.
   */
  typedef enum
  {
    /**
     * vertex program.
     */
    VP,
    /**
     * Fragment program.
     */
    FP,
  } Target;
  static const char* CLASSNAME () { return "Shader"; }
  virtual const char* ClassName () { return CLASSNAME(); }
  bool CompileFile (Target target, const char* file, const char* entry="main", const char** args=0)
  {
    return CompileFiles(target, 1, &file, entry, args);
  }
  bool CompileString (Target target, const char* code, const char* entry="main", const char** args=0)
  {
    return CompileStrings(target, 1, &code, entry, args);
  }
  virtual bool CompileFiles (Target target, int file_count, const char** files, const char* entry="main", const char** args=0) = 0;
  virtual bool CompileStrings (Target target, int string_count, const char** codes, const char* entry="main", const char** args=0) = 0;
  /**
   * Links the VP (if existing) with the FP (if existing). On success, true must be returned.
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
   * Informs the name of the variable bound with the vertex texture coordinate set 'unit' on the vertex program. 'unit' must be less than 16.
   */
  virtual bool BindTexCoord (const char* name, int unit) = 0;
  /**
   * Informs the name of the variable bound with the sampler parameter 'texture' on the fragment program.
   */
  virtual bool BindTexture (const char* name, SGTexture* texture) = 0;
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
   * Sets a constant of type float[rows]x[columns]. 'm' is assumed to be of size rows*columns in matrix column order.
   */
  virtual bool SetConstant (Target target, const char* name, int rows, int columns, float* m) = 0;
  /**
   * Sets a state matrix (type float4x4) of type 'matrix' and transformation 'transform'.
   */
  virtual bool TrackMatrix (Target target, const char* name, Matrix matrix, Transform transform) = 0;
};

#endif
