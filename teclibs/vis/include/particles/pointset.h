/************************************************************************
PtcPointSet Class Header
Represents a set of points.
rcosta@tecgraf.puc-rio.br
rodesp@tecgraf.puc-rio.br
Feb 2011
*************************************************************************/

#ifndef _PARTICLES_POINT_SET_H_
#define _PARTICLES_POINT_SET_H_

#include <ds/array.h>
#include <ugl/vertexarray.h>
#include <particles/defines.h>


/************************************************************************
Forward Declarations
*************************************************************************/

class UGLTexture;

/**
 * Defines a listener for changes in a point set.
 */
class PARTICLESH_API PtcPointSetChangeListener
{
public:
  virtual ~PtcPointSetChangeListener () 
  {
  }

  virtual void PositionsChanged ()
  {
  }
  virtual void RadiusChanged () 
  {
  }
};

/**
 * Point set interface. 
 * This is the point set interface expected by point renderers.
 */
class PARTICLESH_API PtcPointSet
{
public:
  enum AttribFlags
  {
    ATTRIB_NONE = 0,
    ATTRIB_POSITIONS = 1,
    ATTRIB_COLORS = 2,
    ATTRIB_TEXCOORDS = 4,
    ATTRIB_RADIUS = 8,
  };

  virtual ~PtcPointSet () {}

  virtual void AddChangeListener (PtcPointSetChangeListener* listener) = 0;

  virtual void RemoveChangeListener (PtcPointSetChangeListener* listener) = 0;

  virtual unsigned int GetPointCount () = 0;

  virtual int GetDimension ()  = 0;

  virtual const float* GetPositions () = 0;

  /**
   * Optional
   * If the return is NULL, a default radius will be assumed.
   */
  virtual const float* GetRadiusArray () = 0;

  virtual float GetScale ()  = 0;

  virtual UGLTexture* GetTexture () = 0;

  virtual UGLTexture* GetMaterialTexture () = 0;

  /**
   * This method takes a mask of attribute flags and loads the corresponding
   * particle attributes by mapping them into OpenGL vertex array attributes:
   *
   *   ATTRIB_POSITIONS -> UGLArray::V_POSITION, (x,y) or (x,y,z)
   *   ATTRIB_COLORS -> UGLArray::V_COLOR, (r,g,b,a)
   *   ATTRIB_TEXCOORDS -> UGLArray::V_TEXCOORD0 + m_mattexture->GetLoadedUnit(), texture 
   *       dimension is set by SetMaterialTexCoords() or corresponds to the current 
   *       particle field.
   *   ATTRIB_RADIUS -> UGLArray::V_VPATTRIB, dimension = 1
   */
  virtual void Load (AttribFlags attribflags) = 0;

  virtual void Unload () = 0;

  virtual void SetRadiusVPAttribIndex (unsigned int index) = 0;
};

#endif