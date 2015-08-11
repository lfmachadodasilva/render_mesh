/************************************************************************
PtcPointSet Class Header
Represents a set of points.
rcosta@tecgraf.puc-rio.br
rodesp@tecgraf.puc-rio.br
Feb 2011
*************************************************************************/

#ifndef _PARTICLES_VECTOR_SET_H_
#define _PARTICLES_VECTOR_SET_H_

#include <ds/array.h>
#include <ugl/vertexarray.h>
#include <particles/defines.h>

/************************************************************************
Forward Declarations
*************************************************************************/

class UGLTexture;

class PARTICLESH_API PtcVectorSetChangeListener
{
public:
  virtual ~PtcVectorSetChangeListener () 
  {
  }

  virtual void PositionsChanged ()
  {
  }
  virtual void VectorFieldChanged ()
  {
  }
};

class PARTICLESH_API PtcVectorSet
{
public:
  virtual ~PtcVectorSet () {}

  virtual void AddChangeListener (PtcVectorSetChangeListener* listener) = 0;

  virtual void RemoveChangeListener (PtcVectorSetChangeListener* listener) = 0;

  virtual unsigned int GetPointCount () = 0;

  virtual int GetDimension ()  = 0;

  virtual const float* GetPositions () = 0;

  virtual const float* GetVectorField () = 0;

  virtual void GetVectorFieldMagnitudeLimits (float* mag_min, float* mag_max) = 0;

  virtual UGLTexture* GetMaterialTexture () = 0;
};

#endif