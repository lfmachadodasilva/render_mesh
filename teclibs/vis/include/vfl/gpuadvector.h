#ifndef VFL_GPUADVECTOR_H
#define VFL_GPUADVECTOR_H

//----------//
// Includes //
//----------//

#include "defines.h"

#include <alg/vector.h>
#include <ds/array.h>

#include <GL/glew.h>

//----------------------//
// Forward Declarations //
//----------------------//

class VflFieldLineRenderer;
class VflFieldLineList;
class VflFieldLine;
class VflMultiFieldLine;
class VflGPUVectorField;
class VflGPUVectorIntegrator;

class UGLArray;
class GLSLShader;

//-----------------------------------//
// Class Definition - VflGPUAdvector //
//-----------------------------------//

class VFL_API VflGPUAdvector
{
public:

  // Constructors and Destructor

  VflGPUAdvector ();
  virtual ~VflGPUAdvector ();

  // Parameters

  void SetMaxVertsForward (int maxVertsForward);
  int GetMaxVertsForward ()
  {
    return m_maxVertsForward;
  }

  void SetMaxVertsBackward (int maxVertsBackward);
  int GetMaxVertsBackward ()
  {
    return m_maxVertsBackward;
  }

  void SetVectorField (VflGPUVectorField* vectorField);
  VflGPUVectorField* GetVectorField ()
  {
    return m_vectorField;
  }

  void SetIntegrator (VflGPUVectorIntegrator* integrator);
  VflGPUVectorIntegrator* GetIntegrator ()
  {
    return m_integrator;
  }

  void SetUseStrips (bool state);
  bool GetUseStrips ()
  {
    return m_useStrips;
  }

  // Seeds

  void AddSeed (const AlgVector& position);
  void ClearSeeds ();

  // Advection

  VflFieldLineList* AdvectPacked ();
  VflMultiFieldLine* AdvectInterleaved ();

  int AdvectPacked (VflFieldLineList* fieldLineList);
  int AdvectInterleaved (VflMultiFieldLine* multiFieldLine);

  bool AdvectRenderGpu (VflFieldLineRenderer* renderer);

protected:

  // Advection

  void AdvectPacked (VflFieldLine* fieldLine, int seedNumber);
  bool AdvectInterleaved (VflMultiFieldLine* multiFieldLine, int seedNumber, int maxVerts);

  // Memory Management

  void FreeQueryObjects ();
  bool AssertQueryObjects (int maxObjects);

  bool GenerateShaderProgram ();

private:

  int m_maxVertsForward;
  int m_maxVertsBackward;
  int m_maxVertsShader;

  int m_numQueries;
  int m_queryOffset;

  GLuint* m_queryObjects;
  GLSLShader* m_shaderProgram;

  VflGPUVectorField* m_vectorField;
  VflGPUVectorIntegrator* m_integrator;

  UGLArray* m_seedPositions;

  bool m_useStrips;

};

#endif // VFL_GPUADVECTOR_H
