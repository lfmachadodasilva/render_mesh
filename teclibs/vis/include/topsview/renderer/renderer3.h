/**
* Modulo de definicao da classe TpvRenderer3 para ser usada como interface para renderizacao da TopsView
*/

#ifndef TPV_RENDERER3_H
#define TPV_RENDERER3_H

#include "../property/property.h"
#include "../geometry/geometry3.h"
#include "../colorscale/colorscale.h"
#include <topsview/defines.h>

/** 
    If defined, reads shader from file, else compiles shader with
  the library.
*/
//#define TPV_COMPILE_SHADER_FILE

/**
  class TpvRenderer3

    Abstract class for geometry rendering.
*/
class TPV_API TpvRenderer3
{
public:
  static float GetOpenGLVersion();
  static int GetAttribStackDepth();

  virtual ~TpvRenderer3() {}

  virtual void SetClippingPlane(float a, float b, float c, float d) {}
  virtual void SetClippingPlaneEnabled(bool flag) {}

  virtual void SetPolygonOffset(float factor, float units) {}
  virtual void SetPolygonOffsetEnabled(bool flag) {}

  /**
      Sets the base id.
    Default base id is 1, what means that ids are 1-indexed.
  */
  virtual void SetBaseId(int id) {}
  virtual int GetBaseId() { return 1; }

  virtual void SetNumOfSteps(int n) = 0;
  virtual void SetCurrentStep(int step_id) = 0;

  virtual bool Update() { return true; }
  virtual void Render() = 0;
};
#endif

