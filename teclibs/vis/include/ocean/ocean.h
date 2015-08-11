#ifndef OCEAN_H
#define OCEAN_H

#include "defines.h"
#include "triple.h"

class CWaterOGLRenderer;
class CWaterSim;

class OCEAN_API COcean
{
public:
  COcean(CTriple planeOrigin, CTriple planeNormal, float windDirAngleDegrees);
  ~COcean();

  void render();
  void update( float elapsedSeconds );

  float WindDirAngle(float windDirAngleDegrees);
  float WindDirAngle();
  void  SetTrack( int track );
  
  CWaterOGLRenderer* waterRenderer;
  CWaterSim*		 waterSim;

  float GetWindDirAngleDegrees() { return m_windDirAngleDegrees; }
  CTriple GetPlaneOrigin() { return m_oceanPlaneOrigin; }
  CTriple GetPlaneNormal() { return m_oceanPlaneNormal; }

private:
  void setLod();
  int getLod(float x, float z, float modelMatrix2, float modelMatrix10, float modelMatrix14, float znear, float unitsPerPixelY);

  float m_windDirAngleDegrees;
  CTriple m_oceanPlaneOrigin; // Plane Origin
  CTriple m_oceanPlaneNormal; // Plane Normal
  int* m_lod;
  int imin, imax, jmin, jmax;
  int m_track;
};

#endif

