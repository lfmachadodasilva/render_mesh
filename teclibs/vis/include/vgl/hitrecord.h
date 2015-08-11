//* hitrecord.h
// fabraham@tecgraf.puc-rio.br
// sam@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef VGL_HIT_RECORD_H
#define VGL_HIT_RECORD_H


#include "defines.h"
#include <stdio.h>

/**
 * This class represents a selection hit record.\n
 * It provides functions to access the record's data:
 * - minimum z of the hit\n
 * - maximum z of the hit\n
 * - the name stack state when the selection hit occurred (depth and values).
 */
class VGL_API VglSelectionHit 
{
public:
  /**
   * Constructs a new VglSelectionHit object.
   * \param name_stack_depth The name stack depth when the hit occurred.
   */
  VglSelectionHit();
  /**
   * Destroys a VglSelectionHit object.
   */
  virtual ~VglSelectionHit();
  /**
   * Sets the minimum z of the hit.
   * \param zmin Minimum z of the hit.
   */
  void SetZMin (unsigned int zmin) { m_zmin = zmin; }
  /**
   * Sets the maximum z of the hit.
   * \param zmin Maximum z of the hit.
   */
  void SetZMax (unsigned int zmax) { m_zmax = zmax; }
  /**
   * Gets the minimum z of the hit.
   * \return Minimum z of the hit.
   */
  unsigned int GetZMin () const { return m_zmin; }
  /**
   * Gets the maximum z of the hit.
   * \return Maximum z of the hit.
   */
  unsigned int GetZMax () const { return m_zmax; }
  /**
   * Gets the minimum z of the hit (the float value).
   * Ranges from 0 (near plane) to 1 (far plane).
   */
  float GetZMinFloat () const { return ((float)m_zmin/0x7fffffff)/2; }
  /**
   * Gets the maximum z of the hit (the float value).
   * Ranges from 0 (near plane) to 1 (far plane).
   */
  float GetZMaxFloat () const { return ((float)m_zmax/0x7fffffff)/2; }
  /**
   * Sets the name stack of the hit.
   * \param name_stack Name stack of the hit.
   */
  void SetNameStack (GLuint * name_stack, int stack_depth);
  /**
   * Gets the name stack depth of the hit.
   * \return Name stack depth of the hit.
   */
  int GetNameStackDepth () const { return m_name_stack_depth; }
  /**
   * Gets the name stack of the hit.
   * \return Name stack of the hit.
   */
  GLuint* GetNameStack () const { return m_name_stack; };
  /**
   * Prints the contents of the selection hit
   * format: [zmin, zmax] (name stack)
   */
  void print(void);

  void operator=(const VglSelectionHit &hit)
  {
    SetZMin(hit.GetZMin());
    SetZMax(hit.GetZMax());
    SetNameStack(hit.GetNameStack(),hit.GetNameStackDepth());
  }

protected:
  unsigned int m_zmin, m_zmax;
  int m_name_stack_depth;
  GLuint* m_name_stack;
};

#endif

