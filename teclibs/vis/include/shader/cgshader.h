// CGShader class
// fabraham@tecgraf.puc-rio.br
// Aug 2003 

#ifndef CGSHADER_H
#define CGSHADER_H

#include "shader.h"
#include "shadercg.h"
#include <stdio.h>

#define SHADER_CG_TEX_UNITS 16 // TODO: detect tex unit number

class CGShaderData;
/**
 * This class presents a simplified interface to setup, load and unload a CG shader.
 * Methods are provided to:
 * - initialize CG
 * - load vertex/fragment programs from a file.
 * - load vertex/fragment programs from a code string.
 * - setup the variable names bound to vertex parameters like position, normal, color, texture coordinates, etc.
 * - setup the variable names bound to fragment parameters like textures.
 * - setup constant parameters.
 * - setup state matrix parameters, eg. the modelview matrix.
 * - load and unload the shader.
 * The class usage is:
 * - If the ARB profile is being used for both vertex and fragment shaders:
 *   - at init:
 *    - if (!CGShader::Init()) dontusecgshaders.
 *    - load vertex/fragment programs from a file or string, checking for errors.
 *    - setup the constant parameters.
 *    - setup the texture (sampler) parameters.
 *    - use glstate.* inside the shaders, accessing the opengl state, do not use the cg matrix tracking mechanism.
 *   - at render time, before rendering geometry:
 *    - shader->Load();
 *   - at render time, after rendering geometry:
 *    - shader->Unload();
 * - Else if using other profiles:  
 *   - at init:
 *     - if (!CGShader::Init()) dontusecgshaders;
 *     - load vertex/fragment programs from a file or string, checking for errors.
 *     - setup the vertex program variables if (at least position is required).
 *     - setup the constant parameters.
 *     - setup the texture (sampler) parameters.
 *     - setup the state matrix parameters.
 *   - at render time, before rendering geometry:
 *     - shader->Load();
 *   - at render time, while rendering geometry:
 *     - shader->Set*Pointer(size,type,stride,pointer), just like gl*Pointer(size,type,stride,pointer).
 *     - shader->Enable*Array() to enable the array.
 *     - shader->Disable*Array() to disable the array.
 *   - at render time, after rendering geometry:
 *     - shader->Unload();
 */
class SHADERCGAPI CGShader : public Shader
{
private:
  CGShaderData* m_data;
  bool SetConstant (Target target, const char* name, int n, float x, float y=0.0f, float z=0.0f, float w=0.0f);
public:
  static bool Init (const char* vertex_profile=0, const char* fragment_profile=0);
  /**
   * Returns if the given vertex and fragment profiles are supported.
   */
  static bool SupportsProfile (const char* reqvpprofile=NULL, const char* reqfpprofile=NULL);
  /**
   * Constructor
   */
  CGShader ();
  /**
   * Destructor
   */
  virtual ~CGShader ();
  virtual bool CompileFiles (Target target, int file_count, const char** files, const char* entry="main", const char** args=0);
  virtual bool CompileStrings (Target target, int string_count, const char** codes, const char* entry="main", const char** args=0);
  /**
   * Links the VP (if existing) with the FP (if existing). On success, true is returned.
   */
  virtual bool Link ();
  /**
   * Informs the name of the variable bound with the vertex position on the vertex program.
   */
  virtual bool BindPosition (const char* name);
  /**
   * Informs the name of the variable bound with the vertex normal on the vertex program.
   */
  virtual bool BindNormal (const char* name);
  /**
   * Informs the name of the variable bound with the vertex color on the vertex program.
   */
  virtual bool BindColor (const char* name);
  /**
   * Informs the name of the variable bound with the vertex texture coordinate set 'unit' on the vertex program.
   */
  virtual bool BindTexCoord (const char* name, int unit);
  /**
   * Informs the name of the variable bound with the sampler parameter of texture name 'id' on the fragment program.
   */
  virtual bool BindTexture (const char* name, unsigned int id);
  /**
   * Sets a constant of type float1.
   */
  virtual bool SetConstant (Target target, const char* name, float x);
  /**
   * Sets a constant of type float2.
   */
  virtual bool SetConstant (Target target, const char* name, float x, float y);
  /**
   * Sets a constant of type float3.
   */
  virtual bool SetConstant (Target target, const char* name, float x, float y, float z);
  /**
   * Sets a constant of type float4.
   */
  virtual bool SetConstant (Target target, const char* name, float x, float y, float z, float w);
  /**
   * Sets a constant of type float[rows]x[columns]. 'm' is assumed to be of size rows*columns in matrix column order.
   */
  virtual bool SetConstant (Target target, const char* name, int rows, int columns, const float* m);
  /**
   * Sets a state matrix (type float4x4) of type 'matrix' and transformation 'transform'.
   */
  virtual bool TrackMatrix (Target target, const char* name, Matrix matrix, Transform transform);
  /**
   * Sets the current vertex pointer (just like glVertexPointer)
   */
  virtual void SetVertexPointer (int size, unsigned int type, int stride, const void* pointer);
  /**
   * Sets the current normal pointer (just like glNormalPointer)
   */
  virtual void SetNormalPointer (unsigned int type, int stride, const void* pointer);
  /**
   * Sets the current color pointer (just like glColorPointer)
   */
  virtual void SetColorPointer (int size, unsigned int type, int stride, const void* pointer);
  /**
   * Sets the current texture coordinate pointer (just like glTexCoordPointer) for texture unit 'unit'.
   */
  virtual void SetTexCoordPointer (int size, unsigned int type, int stride, const void* pointer, int unit);
  /**
   * Enables the current vertex array.
   */
  virtual void EnableVertexArray ();
  /**
   * Enables the current normal array.
   */
  virtual void EnableNormalArray ();
  /**
   * Enables the current color array.
   */
  virtual void EnableColorArray ();
  /**
   * Enables the current texture coordinate array for texture unit 'unit'.
   */
  virtual void EnableTexCoordArray (int unit);
  /**
   * Disables the current vertex array.
   */
  virtual void DisableVertexArray ();
  /**
   * Disables the current normal array.
   */
  virtual void DisableNormalArray ();
  /**
   * Disables the current color array.
   */
  virtual void DisableColorArray ();
  /**
   * Disables the current texture coordinate array for texture unit 'unit'.
   */
  virtual void DisableTexCoordArray (int unit);
  /**
   * Loads the vertex/fragment programs.
   */
  virtual void Load ();
  /**
   * Unloads the vertex/fragment programs.
   */
  virtual void Unload ();
};

#endif
