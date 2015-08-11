/************************************************************************
  PtcConcretePointSet Class
  Represents a group of particles and obstacles.
  rcosta@tecgraf.puc-rio.br
  rodesp@tecgraf.puc-rio.br
  Dec 2008 - Apr 2011
*************************************************************************/

#ifndef _PARTICLES_CONCRETE_POINT_SET_H_
#define _PARTICLES_CONCRETE_POINT_SET_H_

#include <particles/defines.h>
#include <particles/pointset.h>
#include <particles/vectorset.h>

/************************************************************************
Class Declaration
*************************************************************************/

/**
 * A concrete implementation of the PtcPointSet interface.
 */
class PARTICLES_API PtcConcretePointSet : public PtcPointSet, public PtcVectorSet
{
public:
  PtcConcretePointSet (int dimension);

  ~PtcConcretePointSet ();

  void AddChangeListener (PtcPointSetChangeListener* listener);

  void RemoveChangeListener (PtcPointSetChangeListener* listener);

  void AddChangeListener (PtcVectorSetChangeListener* listener);

  void RemoveChangeListener (PtcVectorSetChangeListener* listener);

  /**
   * Internal use.
   *
   * Loads OpenGL vertex arrays
   */
  virtual void Load (AttribFlags attribflags);

  /**
   * Internal use.
   *
   * Loads OpenGL vertex arrays
   */
  virtual void Unload ();

  const float* GetColors () const;

  virtual int GetDimension ();

  virtual UGLTexture* GetMaterialTexture ();

  const float* GetMaterialTexCoords () const;

  virtual unsigned int GetPointCount ();

  const float* GetPositions ();

  float GetScale ();

  const float* GetRadiusArray ();

  UGLTexture* GetTexture ();

  /**
   * Returns whether the material with the given id is currently enabled in
   * this model.
   */
  bool IsMaterialEnabled (int matid) const;

  /**
   * Sets default point colors, intended to be used when no material 
   * texture is set. The length of the colors array must be equal to the number
   * of points.
   * 
   * Point colors are loaded as color attributes of OpenGL vertices.
   */
  void SetColors (const float* colors);

  /**
   * Sets whether each material is enabled or not. The length of the 
   * enabled array must be equal to the number of materials in the model.
   */
  void SetEnabledMaterials(int count, bool* enabled);

  /**
   * Sets the material ids associated to each point.
   * The length of the materials array must be equal to the number of points
   * in the model.
   */
  void SetMaterials (const int* materials);

  /**
   * Sets the colors of materials associated to points in the model. 
   * The length of the color array must be equal to the number of materials
   * in the model. Information about currently enabled materials is used in order
   * to determine if a given point is visible. If the material associated
   * to the point is not enabled, the alpha component of the points's color 
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
   * Sets the texture used to map point materials onto colors.
   */ 
  void SetMaterialTexture (UGLTexture* texture);

  /**
   * Sets the array of material texture coordinates. The texture coordinates 
   * will overwrite any previously scalar field set by SetScalarField().
   * The length of the texcoords array must be equal to the number of points
   * in the set.
   */
  void SetMaterialTexCoords (const float* texcoords, int dim);

  /**
   * Sets the number of points in the set. Must be set before point attributes
   * (e.g. positions, radii, etc.) are set.
   */
  void SetPointCount (unsigned int n);

  /**
   * Sets the array of point positions. The length of the array must be equal to 
   * the number of points in the set.
   */
  void SetPositions (const float* positions);

  /**
   * Sets the point size scale factor.
   */
  void SetScale (float factor);

  /**
   * Sets an optional texture to be used as the point shape texture.
   * If none was set, the default texture will be used instead.
   */
  void SetTexture (UGLTexture* texture);

  /**
   * Sets the array o point radii. The length of the array must be equal to the
   * number of points in the set.
   */
  void SetRadiusArray (const float* radii);

  /**
   * Internal use.
   *
   * Sets the index of the OpenGL vertex program generic attribute at which the 
   * point radii will be loaded.
   */
  void SetRadiusVPAttribIndex (unsigned int index);

  /**
   * Sets the current point scalar field. The scalar field is loaded as
   * textures coordinates of points and thus will overwrite the 
   * the values previously set by SetMaterialTexCoords().
   *
   * Scalar field is loaded as texture coordinates of OpenGL vertices.
   */
  void SetScalarField (const float* values, float vmin, float vmax);

  /**
   * Sets the current point vector field.
   */
  void SetVectorField (const float* values, float vmin, float vmax);

  virtual const float* GetVectorField ();

  virtual void GetVectorFieldMagnitudeLimits (float* mag_min, float* mag_max);

private:
  void NotifyPositionsChanged ();
  void NotifyRadiiChanged ();
  void NotifyVectorFieldChanged ();

private:
  int m_dimension;
  unsigned int m_partcount;

  int m_loadedattribs;
  UGLArray* m_posarray;
  UGLArray* m_radii;
  UGLArray* m_vectorarray;
  UGLArray* m_colorsarray;
  UGLArray* m_texcoordsarray;
  UGLTexture* m_texture;
  UGLTexture* m_mattexture;

  float m_vector_vmin;
  float m_vector_vmax;

  DsArray<int> m_materials;
  DsArray<bool> m_matenabled;

  float m_partscale;

  DsArray<PtcPointSetChangeListener*> m_listeners;
  DsArray<PtcVectorSetChangeListener*> m_vector_listeners;
};

/************************************************************************
Inline Methods
*************************************************************************/
inline const float* PtcConcretePointSet::GetColors () const
{
  if (!m_colorsarray) {
    return NULL;
  }
  return m_colorsarray->GetArray();
}

inline int PtcConcretePointSet::GetDimension () 
{
  return m_dimension;
}

inline unsigned int PtcConcretePointSet::GetPointCount () 
{
  return m_partcount;
}

inline const float* PtcConcretePointSet::GetPositions () 
{
  return m_posarray->GetArray();
}

inline UGLTexture* PtcConcretePointSet::GetMaterialTexture () 
{
  return m_mattexture;
}

inline const float* PtcConcretePointSet::GetMaterialTexCoords () const
{
  if (!m_texcoordsarray) {
    return NULL;
  }
  return m_texcoordsarray->GetArray();
}

inline float PtcConcretePointSet::GetScale () 
{
  return m_partscale;
}

inline UGLTexture* PtcConcretePointSet::GetTexture () 
{
  return m_texture;
}

inline const float* PtcConcretePointSet::GetRadiusArray () 
{
  return m_radii->GetArray();
}

inline void PtcConcretePointSet::SetEnabledMaterials (int count, bool* enabled)
{
  m_matenabled.Resize(count);
  memcpy(m_matenabled.GetArray(), enabled, count * sizeof(bool));
}

inline bool PtcConcretePointSet::IsMaterialEnabled (int matid) const
{
  if (m_matenabled.Size() == 0) {
    return true;
  }
  return m_matenabled.Get(matid-1);
}

#endif