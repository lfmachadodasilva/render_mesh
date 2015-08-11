/************************************************************************
  PtcObstacle Class Header
  Represents an obstacle such as a cube or sphere.
  rcosta@tecgraf.puc-rio.br
  Jan 2009
*************************************************************************/

#ifndef _PARTICLES_OBSTACLE_H_
#define _PARTICLES_OBSTACLE_H_

#include <float.h>
#include <alg/vector.h>
#include <alg/matrix.h>
#include "defines.h"

/************************************************************************
  Class Declaration
*************************************************************************/

class PARTICLES_API PtcObstacle
{
public:
  struct Material
  {
    float diffuse[4];
    float specular[4];
    float ambient[4];
    float emissive[4];
    float shininess;
  };

  enum CullMode
  {
      CULL_NONE,
      CULL_BACK,
      CULL_FRONT,
  };

public:
  PtcObstacle ();
  virtual ~PtcObstacle ();

  virtual void Draw () = 0;

  const Material& GetFrontMaterial () const;
  const Material& GetBackMaterial () const;

  bool HasTransparency () const;

  void SetBackDiffuse (float r, float g, float b, float a);
  void SetBackSpecular (float r, float g, float b, float a);
  void SetBackAmbient (float r, float g, float b, float a);
  void SetBackEmissive (float r, float g, float b, float a);
  void SetBackShininess (float shi);
  void SetFrontDiffuse (float r, float g, float b, float a);
  void SetFrontSpecular (float r, float g, float b, float a);
  void SetFrontAmbient (float r, float g, float b, float a);
  void SetFrontEmissive (float r, float g, float b, float a);
  void SetFrontShininess (float shi);

  void SetFrontMaterial (const Material& mat);
  void SetBackMaterial (const Material& mat);

  int GetMaterialId () const;
  void SetMaterialId (int id);
  void SetMaterialColors (const float* colors);

  void SetCullMode (CullMode cullmode);

  const float* GetTransform () const;
  void SetTransform (const AlgMatrix& matrix);

protected:
  AlgMatrix m_transform;

  Material m_frontmat;
  Material m_backmat;
  int m_materialid;

  CullMode m_cullmode;
};

/************************************************************************
  Inline Methods
*************************************************************************/

inline const PtcObstacle::Material& PtcObstacle::GetFrontMaterial () const
{
  return m_frontmat;
}

inline const PtcObstacle::Material& PtcObstacle::GetBackMaterial () const
{
  return m_backmat;
}

inline int PtcObstacle::GetMaterialId () const
{
  return m_materialid;
}

inline const float* PtcObstacle::GetTransform () const
{
  return m_transform.GetMatrix();
}

inline bool PtcObstacle::HasTransparency () const
{
	return m_frontmat.diffuse[3] < (1.0f - FLT_MIN) || m_backmat.diffuse[3] < (1.0f - FLT_MIN);
}

inline void PtcObstacle::SetFrontMaterial (const PtcObstacle::Material& mat)
{
  m_frontmat = mat;
}

inline void PtcObstacle::SetBackMaterial (const PtcObstacle::Material &mat)
{
  m_backmat = mat;
}

inline void PtcObstacle::SetMaterialId (int id)
{
  m_materialid = id;
}

inline void PtcObstacle::SetCullMode (CullMode cullmode)
{
  m_cullmode = cullmode;
}

inline void PtcObstacle::SetTransform (const AlgMatrix& matrix)
{
  m_transform = matrix;
}

#endif
