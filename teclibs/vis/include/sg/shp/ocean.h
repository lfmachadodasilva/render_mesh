// ocean.h
// fabraham@tecgraf.puc-rio.br
// Jun 2003

#ifndef SG_OCEAN_H
#define SG_OCEAN_H

#include <sg/shape.h>
#include <alg/vector.h>

class COcean;

class SGOcean : public SGShape
{
  COcean * m_ocean;
public:
  static const char* CLASSNAME () { return "Ocean"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
	
  SGOcean (AlgVector planeOrigin, AlgVector planeNormal, float windDirAngleDegrees=0.0f);
  virtual ~SGOcean ();

  void UpdateVtime (double time);

  void EnableChoppy();
  void DisableChoppy();
  bool IsChoppyEnable() const;

  void EnableNormalFFT();
  void DisableNormalFFT();
  bool IsNormalFFTEnable() const;

  void  SetTrack(int track);
  void  SetChoppyCoef(float choppyCoef);
  float GetChoppyCoef() const;

  void  SetWindDir(float angle);
  float GetWindDir() const;

  void SetWindDependence(int windDependence);
  int  GetWindDependence() const;

  void  SetAmplitude(float amplitudeFactor);
  float GetAmplitude() const;

  void  SetSimulationVelocity(float velocity);
  float GetSimulationVelocity() const;

  void  SetWaterSize(float waterSize);
  float GetWaterSize() const;

  void SetWaterGrid(int gridPower);
  int  GetWaterGrid() const;

  float GetMaxAmplitude() const;
  float GetMaxBoundBoxSizeX() const;
  float GetMaxBoundBoxSizeZ() const;

  virtual bool HasCulling ()
  {
    return true;
  }
  virtual int GetTriangleCount ();
  virtual int GetLineCount ();
  virtual int GetVertexCount ()
  {
    return 0;
  }
  virtual void GetVertex (int index, float *x, float *y, float *z)
  {
  }
  virtual void Draw ();
  virtual void Write (UtlWriter* writer);
};

#endif
