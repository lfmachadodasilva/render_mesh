// Light class
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_LIGHT_H
#define SG_LIGHT_H

#include "node.h"

/**
 * SGLight Class.
 *
 * This is the light node.
 * It contains:
 * - an intensity (a scale on all components)
 * - an ambient component
 * - a diffuse component
 * - a specular component
 *
 * It provides methods to:
 * - set/get the component values.
 * - load the light on OpenGL. Light id's (GLLIGHT*) will be automatically configured.
 * - traverse the light with a traversal strategy.
 * - write its description.
 */
class SG_API SGLight : public SGNode
{
  int m_id;
  float m_intensity;
  float m_amb[4], m_final_amb[4];
  float m_dif[4], m_final_dif[4];
  float m_spe[4], m_final_spe[4];
  bool m_ambe, m_dife, m_spee;

  void UpdateValues();
protected:
	/**
	 * Constructor
	 */
  SGLight ();
	/**
	 * Obtains the current light's OpenGL id (GL_LIGHT0 -> GL_LIGHT7)
	 */
  int GetId () { return m_id; }
public:
  static const char* CLASSNAME () { return "Light"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
	/**
	 * Destructor
	 */
  virtual ~SGLight ();
  /**
   * Reserves an OpenGL Light ID
   */
  void ReserveId ();
  /**
   * Releases the OpenGL Light ID
   */
  void ReleaseId ();
	/**
	 * Sets the light's intensity, which is simple a scale done on all the components.
	 */
  void SetIntensity (float value);
  /**
   * Gets the light's intensity.
   */
  float GetIntensity ()
  {
    return m_intensity;
  }
	/**
	 * Sets the light's ambient component.
	 */
  void SetAmbient (float red, float green, float blue, float alpha=1.0f);
	/**
	 * Sets the light's diffuse component.
	 */
  void SetDiffuse (float red, float green, float blue, float alpha=1.0f);
	/**
	 * Sets the light's specular component.
	 */
  void SetSpecular (float red, float green, float blue, float alpha=1.0f);
	/**
	 * Gets the light's ambient component.
	 */
  void GetAmbient (float * red, float * green, float * blue, float * alpha) const;
	/**
	 * Gets the light's diffuse component.
	 */
  void GetDiffuse (float * red, float * green, float * blue, float * alpha) const;
	/**
	 * Gets the light's specular component.
	 */
  void GetSpecular (float * red, float * green, float * blue, float * alpha) const;
	/**
	 * Enables/disables the ambient component. (eg. for multipass rendering)
	 */
  void SetAmbientEnabled(bool f);
	/**
	 * Enables/disables the diffuse component. (eg. for multipass rendering)
	 */
  void SetDiffuseEnabled(bool f);
	/**
	 * Enables/disables the specular component. (eg. for multipass rendering)
	 */
  void SetSpecularEnabled(bool f);
  bool GetAmbientEnabled()
  {
    return m_ambe;
  }
  bool GetDiffuseEnabled()
  {
    return m_dife;
  }
  bool GetSpecularEnabled()
  {
    return m_spee;
  }
  virtual void Load ();
  /**
   * Traverses the light with a traversal strategy.
   * This light will do the following:
	 * - skip if the light is disabled.
	 * - load itself.
	 * - unload itself.
   */
	virtual int Traverse(SGStrategy *s);
	/**
	 * Writes the light description
	 */
  virtual void Write (UtlWriter * writer);
};

#endif

