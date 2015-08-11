#ifndef VFL_RENDERER_H
#define VFL_RENDERER_H

//----------//
// Includes //
//----------//

#include "defines.h"
#include "fieldline.h"

#include <ds/list.h>
#include <alg/vector.h>
#include <alg/matrix.h>

//----------------------//
// Forward Declarations //
//----------------------//

class VflMultiFieldLine;
class VflScalarFunctionSinePower;
class VflScalarIntegratorSimpson;

class UGLTexture;
class GLSLShader;

//-----------------------------------------//
// Class Definition - VflFieldLineRenderer //
//-----------------------------------------//

class VFL_API VflFieldLineRenderer
{
public:

  enum ColorModel
  {
    COLOR_SINGLE           = 0,  // The entire line is rendered in a single color
    COLOR_ARRAY            = 1,  // Use the colors in the line's color array
    COLOR_VERTICES         = 2,  // Use vertex  coordinates as colors
    COLOR_TANGENTS         = 3,  // Use tangent coordinates as colors
    COLOR_DIFFUSE_NORMALS  = 4,  // Use diffuse  normal coordinates as colors
    COLOR_SPECULAR_NORMALS = 5,  // Use specular normal coordinates as colors
    COLOR_TEX_MAGNITUDES   = 6,  // Use magnitudes as texcoords    for a color scale texture
    COLOR_TEX_COORDS       = 7   // Use the line's texcoords array for a color scale texture
  };

  enum LightModel
  {
    LIGHT_NONE                   = 0, // Do not use lighting
    LIGHT_TANGENTS               = 1, // Use the given tangents as normals (pre-calculated in CPU)
    LIGHT_DIFFUSE_NORMALS        = 2, // Use the given diffuse normals (pre-calculated in CPU)
    LIGHT_SPECULAR_NORMALS       = 3, // Use the given specular normals (pre-calculated in CPU)
    LIGHT_DUAL_NORMALS           = 4, // Use the given diffuse and specular normals (pre-calculated in CPU)
    LIGHT_MAXREFLECTION          = 5, // Calculate max reflection lighting using textures alone
    LIGHT_SHADER_MAXREFLECTION   = 6, // Calculate max reflection lighting in GPU shader
    LIGHT_CYLINDERAVERAGE        = 7, // Calculate cylinder average lighting using textures alone
    LIGHT_SHADER_CYLINDERAVERAGE = 8  // Calculate cylinder average lighting in GPU shader
  };

  // Constructors and Destructor

  VflFieldLineRenderer ();
  virtual ~VflFieldLineRenderer ();

  // Getters and Setters

  UGLTexture*  GetColorScale        () {return m_colorScale;}
  float        GetShininess         () {return m_shininess;}
  float        GetSpecularIntensity () {return m_specular;}
  float        GetDiffuseIntensity  () {return m_diffuse;}
  float        GetAmbientIntensity  () {return m_ambient;}
  float        GetLineWidth         () {return m_width;}
  float        GetPointSize         () {return m_psize;}
  ColorModel   GetColorModel        () {return m_colorModel;}
  LightModel   GetLightModel        () {return m_lightModel;}
  unsigned int GetLightCount        () {return m_lightCount;}
  bool         GetRenderLines       () {return m_renderLines;}
  bool         GetRenderPoints      () {return m_renderPoints;}

  bool SetColorScale        (const char*  strFilename);
  void SetColorScale        (UGLTexture*  colorScale, bool takeOwnership = false);
  void SetShininess         (float        shininess);
  void SetSpecularIntensity (float        intensity);
  void SetDiffuseIntensity  (float        intensity);
  void SetAmbientIntensity  (float        intensity);
  void SetLineWidth         (float        width);
  void SetPointSize         (float        psize);
  bool SetColorModel        (ColorModel   colorModel);
  bool SetLightModel        (LightModel   lightModel);
  void SetLightCount        (unsigned int lightCount);
  void SetTextureSize       (unsigned int texSize);
  void SetRenderLines       (bool         state);
  void SetRenderPoints      (bool         state);

  void SetLightViewVectors (const AlgVector& lightVector, const AlgVector& viewVector);
  void SetColorScaleMap    (float minValue, float maxValue);

  void ResetShaders ();

  // Pre-Rendering

  void ComputeBaseColorsWhite (VflFieldLineList* fieldLineList);
  void ComputeBaseColorsWhite (VflFieldLine* fieldLine);

  void ComputeBaseColorsRandom (VflFieldLineList* fieldLineList);
  void ComputeBaseColorsRandom (VflFieldLine* fieldLine);

  void ComputeTangents2Point (VflFieldLineList* fieldLineList);
  void ComputeTangents2Point (VflFieldLine* fieldLine);

  void ComputeTangents3Point (VflFieldLineList* fieldLineList);
  void ComputeTangents3Point (VflFieldLine* fieldLine);

  void ComputeDiffuseNormals (VflFieldLineList* fieldLineList, const AlgVector& lightPos, bool localLight); // Max reflection
  void ComputeDiffuseNormals (VflFieldLine* fieldLine, const AlgVector& lightPos, bool localLight); // Max reflection

  void ComputeSpecularNormals (VflFieldLineList* fieldLineList, const AlgVector& eyePos, const AlgVector& lightPos, bool localEye, bool localLight); // Max reflection
  void ComputeSpecularNormals (VflFieldLine* fieldLine, const AlgVector& eyePos, const AlgVector& lightPos, bool localEye, bool localLight); // Max reflection

  void ComputeVertexIDTexcoords (VflFieldLineList* fieldLineList);
  void ComputeVertexIDTexcoords (VflFieldLine* fieldLine);

  // Rendering

  void BeginLinesRender ();
  void EndLinesRender   ();

  void Render (VflMultiFieldLine* multiFieldLines);
  void Render (VflFieldLineList* fieldLineList);
  void Render (VflFieldLine* fieldLine, bool unbindVBOs = true);

protected:

  bool AssertAuxBuffer (int size);

  void FreeTexDiffMaxReflection ();
  void FreeTexSpecMaxReflection ();
  void FreeTexDiffCylinderAverage ();
  void FreeTexSpecCylinderAverage ();
  void FreeTexDiffCylinderAverageShader ();
  void FreeTexSpecCylinderAverageShader ();
  void FreeSineIntegral ();

  bool GenerateTexDiffMaxReflection ();
  bool GenerateTexSpecMaxReflection ();
  bool GenerateTexDiffCylinderAverage ();
  bool GenerateTexSpecCylinderAverage ();
  bool GenerateTexDiffCylinderAverageShader ();
  bool GenerateTexSpecCylinderAverageShader ();
  bool GenerateSineIntegral ();

  bool GenerateMaxReflectionShader ();
  bool GenerateCylinderAverageShader ();
  bool GenerateSineFunction ();
  bool GenerateIntegrator ();

  double GetSineIntegral (double x);

  void LoadColorArray (VflFieldLine* fieldLine);
  void UnloadColorArray (VflFieldLine* fieldLine);

  void LoadLightingArray (VflFieldLine* fieldLine);
  void UnloadLightingArray (VflFieldLine* fieldLine);

private:

  VflScalarIntegratorSimpson* m_integrator;
  VflScalarFunctionSinePower* m_sineFunction;

  double* m_sineIntegral;
  float* m_auxBuffer;
  int m_auxBufferSize;

  UGLTexture* m_colorScale;
  UGLTexture* m_texDiffMaxReflection;
  UGLTexture* m_texSpecMaxReflection;
  UGLTexture* m_texDiffCylinderAverage;
  UGLTexture* m_texSpecCylinderAverage;
  UGLTexture* m_texDiffCylinderAverageShader;
  UGLTexture* m_texSpecCylinderAverageShader;

  GLSLShader* m_shaderMaxReflection;
  GLSLShader* m_shaderCylinderAverage;

  AlgVector m_lightVector;
  AlgVector m_viewVector;
  AlgMatrix m_texMatrixMaxReflection;
  AlgMatrix m_texMatrixCylindAverage;
  AlgMatrix m_texMatrixColorScale;

  float m_shininess;
  float m_specular;
  float m_diffuse;
  float m_ambient;
  float m_width;
  float m_psize;

  ColorModel m_colorModel;
  LightModel m_lightModel;
  unsigned int m_lightCount;
  unsigned int m_texSize;

  unsigned int m_unitDiff;
  unsigned int m_unitSpec;
  unsigned int m_unitColor;

  bool m_useColorScale;
  bool m_ownColorScale;
  bool m_renderLines;
  bool m_renderPoints;

};

#endif // VFL_RENDERER_H
