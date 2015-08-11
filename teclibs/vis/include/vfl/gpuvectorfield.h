#ifndef VFL_GPUVECTORFIELD_H
#define VFL_GPUVECTORFIELD_H

//----------//
// Includes //
//----------//

#include "defines.h"

#include <alg/vector.h>

#include <GL/glew.h>

//----------------------//
// Forward Declarations //
//----------------------//

class GLSLShader;

//--------------------------------------//
// Class Definition - VflGPUVectorField //
//--------------------------------------//

class VFL_API VflGPUVectorField
{
public:

  // Constructors and Destructor

  VflGPUVectorField ()
  : m_shaderProgram(NULL)
  {
  }

  virtual ~VflGPUVectorField ()
  {
  }

  // Parameters

  void SetShaderProgram (GLSLShader* shaderProgram);
  GLSLShader* GetShaderProgram () const
  {
    return m_shaderProgram;
  }

  // Shader Methods

  bool CompileShader ();
  bool SetShaderUniforms ();

protected:

  // Shader Information

  virtual bool DoSetShaderUniforms ();
  virtual const char* GetShaderFile () = 0;
  virtual const char* GetShaderString () = 0;

protected:

  GLSLShader* m_shaderProgram;

};

//--------------------------------------------//
// Class Definition - VflGPUVectorFieldDipole //
//--------------------------------------------//

class VFL_API VflGPUVectorFieldDipole : public VflGPUVectorField
{
public:

  // Constructors and Destructor

  VflGPUVectorFieldDipole (float scale = 1.0f)
  : VflGPUVectorField()
  , m_scale(scale)
  , m_source()
  , m_sink()
  {
  }

  VflGPUVectorFieldDipole (float scale, const AlgVector& source, const AlgVector& sink)
  : VflGPUVectorField()
  , m_scale(scale)
  , m_source(source)
  , m_sink(sink)
  {
  }

  virtual ~VflGPUVectorFieldDipole ()
  {
  }

  // Parameters

  void SetScale (float scale);
  float GetScale () const
  {
    return m_scale;
  }

  void SetSource (const AlgVector& source);
  AlgVector GetSource () const
  {
    return m_source;
  }

  void SetSink (const AlgVector& sink);
  AlgVector GetSink () const
  {
    return m_sink;
  }

protected:

  // Shader Information

  virtual bool DoSetShaderUniforms ();
  virtual const char* GetShaderFile ();
  virtual const char* GetShaderString ();

protected:

  float m_scale;
  AlgVector m_source;
  AlgVector m_sink;
};

#endif // VFL_GPUVECTORFIELD_H
