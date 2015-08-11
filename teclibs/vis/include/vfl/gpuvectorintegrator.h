#ifndef VFL_GPUVECTORINTEGRATOR_H
#define VFL_GPUVECTORINTEGRATOR_H

//----------//
// Includes //
//----------//

#include "defines.h"

#include <GL/glew.h>

//----------------------//
// Forward Declarations //
//----------------------//

class VflGPUVectorField;

class GLSLShader;

//-------------------------------------------//
// Class Definition - VflGPUVectorIntegrator //
//-------------------------------------------//

class VFL_API VflGPUVectorIntegrator
{
public:

  // Constructors and Destructor

  VflGPUVectorIntegrator ()
  : m_timeStep(0.1f)
  , m_numSteps(1)
  , m_shaderProgram(NULL)
  {
  }

  virtual ~VflGPUVectorIntegrator ()
  {
  }

  // Parameters

  void SetTimeStep (float timeStep);
  float GetTimeStep () const
  {
    return m_timeStep;
  }

  void SetNumSteps (int numSteps);
  int GetNumSteps () const
  {
    return m_numSteps;
  }

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

  float m_timeStep;
  int m_numSteps;

  GLSLShader* m_shaderProgram;

};

//------------------------------------------------//
// Class Definition - VflGPUVectorIntegratorEuler //
//------------------------------------------------//

class VFL_API VflGPUVectorIntegratorEuler : public VflGPUVectorIntegrator
{
public:

  // Constructors and Destructor

  VflGPUVectorIntegratorEuler ()
  : VflGPUVectorIntegrator()
  {
  }

  virtual ~VflGPUVectorIntegratorEuler ()
  {
  }

protected:

  // Shader Information

  virtual bool DoSetShaderUniforms ();
  virtual const char* GetShaderFile ();
  virtual const char* GetShaderString ();
};

//----------------------------------------//
// Class Definition - VflGPUIntegratorRK4 //
//----------------------------------------//

class VFL_API VflGPUVectorIntegratorRK4 : public VflGPUVectorIntegrator
{
public:

  // Constructors and Destructor

  VflGPUVectorIntegratorRK4 ()
  : VflGPUVectorIntegrator()
  {
  }

  virtual ~VflGPUVectorIntegratorRK4 ()
  {
  }

protected:

  // Shader Information

  virtual bool DoSetShaderUniforms ();
  virtual const char* GetShaderFile ();
  virtual const char* GetShaderString ();
};

#endif // VFL_GPUVECTORINTEGRATOR_H
