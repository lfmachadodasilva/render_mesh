// GLSLShader class
// fabraham@tecgraf.puc-rio.br
// celes@tecgraf.puc-rio.br
// Nov 2004

#ifndef SHADER_GLSLSHADER_H
#define SHADER_GLSLSHADER_H

#include <GL/glew.h>
#include "shader.h"
#include <ds/list.h>
#include <ds/hash.h>

class GLSLUniformData;
class UGLArray;
class UGLInterleavedArray;

class SHADER_API GLSLShader : public Shader
{
public:
  /**
   * Static Initialization Method (for GLEW)
   */
  static bool Init ();
  /**
   * Static Information Method
   */
  static void PrintInfo ();
  /**
   * Static Extension-Support Information Variables
   */
  static bool s_supportsShaders;
  static bool s_supportsGL20;
  static bool s_supportsNonSquareMatrices;
  static bool s_supportsVertexAttribs;
  static bool s_supportsGeometryShaders;
//static bool s_supportsBindFragDataLoc;
  static bool s_supportsProgramParameters;
  static bool s_supportsIntegerUniforms;
  static bool s_supportsIntegerAttributes;
  static bool s_supportsIntegerParameters;
  static bool s_supportsBindableUniforms;
  static bool s_supportsTransformFeedback;

  /**
   * Constructor
   */
  GLSLShader ();
  /**
   * Destructor
   */
  virtual ~GLSLShader ();
  /**
   * Auxiliary Getters
   */
  unsigned int GetProgramHandle ();
  int GetUniformLocation (const char* name);
  int GetVaryingLocation (const char* name);
  int GetAttribLocation (const char* name);
  /**
   * Compilation and Linkage
   */
  virtual bool CompileFiles (Target target, int file_count, const char** files, const char* entry="main", const char** args=0);
  virtual bool CompileStrings (Target target, int string_count, const char** codes, const char* entry="main", const char** args=0);
  virtual bool Link ();
  /**
   * Geometry Shaders and Transform Feedback
   */
  virtual bool SetGeometryShaderParameters (unsigned int inputPrimitive, unsigned int outputPrimitive, int maxOutVertices); // Will re-link a previously linked program!
  virtual unsigned int GetGeometryInputPrimitive () {return m_geometryInput;}
  virtual unsigned int GetGeometryOutputPrimitive () {return m_geometryOutput;}
  virtual int GetGeometryMaxOutVertices () {return m_geometryMaxOutVertices;}
  /**
   * Transform Feedback
   */
  virtual bool SetActiveVarying (const char* varyingName, bool activeStatus = true); // Will re-link a previously linked program!
  virtual void SetTransformFeedbackVaryings (int varyingCount, const char* varyingNames[], AttribMode attribMode);
  virtual void BeginTransformFeedback(unsigned int primitiveType, UGLArray* separateArrays[], unsigned int writtenQueryId = 0, unsigned int generatedQueryId = 0);
  virtual void BeginTransformFeedback(unsigned int primitiveType, UGLInterleavedArray* interleavedArray, int start = 0, int count = 0, unsigned int writtenQueryId = 0, unsigned int generatedQueryId = 0);
  virtual void EndTransformFeedback();
  /**
   * Queries
   */
  virtual void PrintActiveVaryings ();
  /**
   * Enabling and Disabling Lazy Uniform Loading
   */
  virtual bool EnableLazyUniforms ();
  virtual bool DisableLazyUniforms ();
  /**
   * Bind methods (dummy, unavailable to GLSL shaders)
   */
  virtual bool BindPosition (const char* name);
  virtual bool BindNormal (const char* name);
  virtual bool BindColor (const char* name);
  virtual bool BindTexCoord (const char* name, int unit);
  /**
   * Informs the name of the variable bound with the sampler parameter on texture unit 'unit'.
   */
  virtual bool BindTexture (const char* name, unsigned int unit);
  /**
   * Setting up Uniforms
   */
  virtual bool SetConstant (Target target, const char* name, float x);
  virtual bool SetConstant (Target target, const char* name, float x, float y);
  virtual bool SetConstant (Target target, const char* name, float x, float y, float z);
  virtual bool SetConstant (Target target, const char* name, float x, float y, float z, float w);
  virtual bool SetConstant (Target target, const char* name, int x);
  virtual bool SetConstant (Target target, const char* name, int x, int y);
  virtual bool SetConstant (Target target, const char* name, int x, int y, int z);
  virtual bool SetConstant (Target target, const char* name, int x, int y, int z, int w);
  virtual bool SetConstant (Target target, const char* name, int rows, int columns, const float* m);
  virtual bool SetConstantArray (Target target, const char* name, int count, int components, const float *v);
  virtual bool SetConstantArray (Target target, const char* name, int count, int components, const GLint *v);
  virtual bool SetConstantArray (Target target, const char* name, int count, int rows, int columns, const float* m);
  /**
   * Matrix Tracking and Array Pointer Methods (dummy, unavailable to GLSL shaders)
   */
  virtual bool TrackMatrix (Target target, const char* name, Matrix matrix, Transform transform);
  virtual void SetVertexPointer (int size, unsigned int type, int stride, const void* pointer);
  virtual void SetNormalPointer (unsigned int type, int stride, const void* pointer);
  virtual void SetColorPointer (int size, unsigned int type, int stride, const void* pointer);
  virtual void SetTexCoordPointer (int size, unsigned int type, int stride, const void* pointer, int unit);
  virtual void EnableVertexArray ();
  virtual void EnableNormalArray ();
  virtual void EnableColorArray ();
  virtual void EnableTexCoordArray (int unit);
  virtual void DisableVertexArray ();
  virtual void DisableNormalArray ();
  virtual void DisableColorArray ();
  virtual void DisableTexCoordArray (int unit);
  /**
   * Loading and Unloading the GLSL Shader
   */
  virtual void Load ();
  virtual void Unload ();

private:
  DsList<unsigned int> m_shaders;
  DsHash<DsStringKey, bool> m_activeVaryings;
  DsHash<DsStringKey, GLSLUniformData*> m_uniforms;
  UGLArray** m_tfArrays;
  UGLInterleavedArray* m_tfInterleaved;
  unsigned int m_program;
  unsigned int m_geometryInput;
  unsigned int m_geometryOutput;
  unsigned int m_queryWrittenId;
  unsigned int m_queryGeneratedId;
  int m_geometryMaxOutVertices;
  int m_tfVaryingCount;
  bool m_geometryPresent;
  bool m_loaded;
  bool m_lazyUniforms;
};

#endif
