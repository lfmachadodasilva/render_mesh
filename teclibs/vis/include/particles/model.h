/************************************************************************
PtcModel Class Header
Represents a group of particles and obstacles.
rcosta@tecgraf.puc-rio.br
Dec 2008
*************************************************************************/

#ifndef _PARTICLES_MODEL_H_
#define _PARTICLES_MODEL_H_

#include <ds/array.h>
#include <ugl/vertexarray.h>
#include <particles/defines.h>
#include <particles/concretepointset.h>

/************************************************************************
Forward Declarations
*************************************************************************/

class UGLTexture;
class PtcCPURenderer;
class PtcObstacle;

/************************************************************************
Class Declaration
*************************************************************************/

class PARTICLES_API PtcModel
{
public:
  enum Dimension
  {
    DIM_2D = 2,
    DIM_3D = 3
  };

  PtcModel (Dimension dim);
  ~PtcModel ();

  void AddObstacle (PtcObstacle* obstacle);
  void ResetObstacles ();

  const float* GetColors () const;
  Dimension GetDimension () const;
  UGLTexture* GetMaterialTexture () const;
  const float* GetMaterialTexCoords () const;
  int GetObstacleCount () const;
  PtcObstacle* const * GetObstacles () const;
  unsigned int GetParticleCount () const;
  const float* GetParticlePositions () const;
  float GetParticleScale () const;

  const float* GetRadiusArray () const;

  /**
   * Sets an optional texture to be used as the particle shape texture.
   */
  UGLTexture* GetTexture () const;

  /**
   * Returns whether the material with the given id is currently enabled in
   * this model.
   */
  bool IsMaterialEnabled (int matid) const;

  /**
   * Sets default colors of particles, intended to be used when no material 
   * texture is set. The length of the colors array must be equal to the number
   * of particles in the model.
   * 
   * Particle colors are loaded as color attributes of OpenGL vertices.
   */
  void SetColors (const float* colors);

  /**
   * Sets whether each material is enabled or not. The length of the 
   * enabled array must be equal to the number of materials in the model.
   */
  void SetEnabledMaterials(int count, bool* enabled);

  /**
   * Sets the material ids associated to each particle.
   * The length of the materials array must be equal to the number of particles
   * in the model.
   */
  void SetMaterials (const int* materials);

  /**
   * Sets the colors of materials associated to particles and obstacles in 
   * the model. The length of the color array must be equal to the number of materials
   * in the model. Information about currently enabled materials is used in order
   * to determine if a given particle is visible. If the material associated
   * to the particle is not enabled, the alpha component of the particle's color 
   * will be set to zero.
   * 
   * This method overwrites the color array set by SetColors(). If the model
   * has materials, the colors will be replaced by material colors. Otherwise,
   * the color array will just be cleared.
   *
   * Material colors are loaded as color attributes of OpenGL vertices.
   */
  void SetMaterialColors (const float* colors);

  /**
   * Sets the texture used to map particle materials into colors.
   */ 
  void SetMaterialTexture (UGLTexture* texture);

  /**
   * Sets the array of material texture coordinates. The texture coordinates 
   * will overwrite any previously scalar field set by SetScalarField().
   * The length of the texcoords array must be equal to the number of particles
   * in the model.
   */
  void SetMaterialTexCoords (const float* texcoords, int dim);
  void SetParticleCount (unsigned int n);
  void SetParticlePositions (const float* positions);
  void SetParticleScale (float factor);
  void SetRadiusArray (const float* radii);

  /**
   * Sets the current particle scalar field. The scalar field is loaded as
   * textures coordinates of particles and thus will overwrite the 
   * the values previously set by SetMaterialTexCoords().
   *
   * Scalar field is loaded as texture coordinates of OpenGL vertices.
   */
  void SetScalarField (const float* values, float vmin, float vmax);
  void SetTexture (UGLTexture* texture);
  void SetVectorField (const float* values, float vmin, float vmax);

  PtcPointSet* GetPointSet () const;
  PtcVectorSet* GetVectorSet () const;

private:
  PtcConcretePointSet* m_pointset;
  DsArray<PtcObstacle*> m_obstacles;
  DsArray<bool> m_matenabled;
};

/************************************************************************
Inline Methods
*************************************************************************/

inline void PtcModel::AddObstacle (PtcObstacle* obstacle)
{
  m_obstacles.Append(obstacle);
}

inline void PtcModel::ResetObstacles ()
{
  m_obstacles.Resize(0);
}

inline const float* PtcModel::GetColors () const
{
  return m_pointset->GetColors();
}


inline int PtcModel::GetObstacleCount () const
{
  return m_obstacles.Size();
}

inline PtcObstacle* const * PtcModel::GetObstacles () const
{
  return m_obstacles.GetArrayConst();
}

inline PtcModel::Dimension PtcModel::GetDimension () const
{
  int dim = m_pointset->GetDimension();
  assert(dim == 2 || dim == 3);
  if (dim == 3)
    return PtcModel::DIM_3D;
  else
    return PtcModel::DIM_2D;
}

inline unsigned int PtcModel::GetParticleCount () const
{
  return m_pointset->GetPointCount();
}

inline const float* PtcModel::GetParticlePositions () const
{
  return m_pointset->GetPositions();
}

inline UGLTexture* PtcModel::GetMaterialTexture () const
{
  return m_pointset->GetMaterialTexture();
}

inline const float* PtcModel::GetMaterialTexCoords () const
{
  return m_pointset->GetMaterialTexCoords();
}

inline float PtcModel::GetParticleScale () const
{
  return m_pointset->GetScale();
}

inline UGLTexture* PtcModel::GetTexture () const
{
  return m_pointset->GetTexture();
}

inline const float* PtcModel::GetRadiusArray () const
{
  return m_pointset->GetRadiusArray();
}

inline void PtcModel::SetEnabledMaterials (int count, bool* enabled)
{
  m_matenabled.Resize(count);
  memcpy(m_matenabled.GetArray(), enabled, count * sizeof(bool));
  m_pointset->SetEnabledMaterials(count, enabled);
}

inline bool PtcModel::IsMaterialEnabled (int matid) const
{
  if (m_matenabled.Size() == 0)
    return true;
  return m_matenabled.Get(matid-1);
}

inline void PtcModel::SetColors (const float* colors)
{
  m_pointset->SetColors(colors);
}

inline void PtcModel::SetMaterialTexCoords (const float* texcoords, int dim)
{
  m_pointset->SetMaterialTexCoords(texcoords, dim);
}

inline void PtcModel::SetMaterialTexture (UGLTexture* texture)
{
  return m_pointset->SetMaterialTexture(texture);
}

inline void PtcModel::SetParticlePositions (const float* positions)
{
  return m_pointset->SetPositions(positions);
}

inline void PtcModel::SetParticleScale (float factor)
{
  return m_pointset->SetScale(factor);
}

inline void PtcModel::SetTexture (UGLTexture* texture)
{
  return m_pointset->SetTexture(texture);
}



#endif
