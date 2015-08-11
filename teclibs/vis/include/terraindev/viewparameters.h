//* viewparameters.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Mai 2009

#ifndef TRN_VIEWPARAMETERS_H
#define TRN_VIEWPARAMETERS_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "baseclass.h"
#include <mthread/critsection.h>
#include <alg/vector.h>
#include <alg/matrix.h>
#include <ds/array.h>

class VglViewSurface;

//---------------------------//
// TrnViewParameters Typedef //
//---------------------------//

struct TrnViewParameters
{
public:

  AlgVector position;
  float fovy;
  float aspect;
  float farDist;
  float nearDist;
  float nearXSize;
  float nearYSize;
  float tiltAngleCos;
  float lambda;
  float tolerance;        // view dependent screen space error tolerance
  float invLambdaTol;     // lambda / tolerance
  float floorHeight;
  AlgVector camAxes[3];
  AlgVector nearPyramid[6];
  AlgPlane frustumPlanes[6];
  AlgMatrix viewmatrix;
  AlgMatrix projmatrix;
  AlgMatrix viewinverse;
  AlgMatrix projinverse;
  int viewport[4];
  long frameNumber; // last rendered frame number
  long updateStamp;

public:

  TrnViewParameters ()
  : tolerance(FLT_MAX)
  , frameNumber(RECENTLY_USED_FRAME_COUNT + 1)
  , updateStamp(0)
  {
  }

};

//---------------------------//
// TrnViewListener Interface //
//---------------------------//

class TERRAINAPI TrnViewListener
{
public:

  // View Change Notification Method

  virtual void HandleViewChanged () = 0;

};

//------------------------//
// TrnViewSpecifier Class //
//------------------------//

class TERRAINAPI TrnViewSpecifier : public TrnBaseClass
{
public:

  // Class Name

  static const char* CLASSNAME () { return "TrnViewSpecifier"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  // Constructor and Destructor

  TrnViewSpecifier ();
  virtual ~TrnViewSpecifier ();

  // Listener Methods

  virtual void AddListener (TrnViewListener* listener);
  virtual void RemListener (TrnViewListener* listener);

  // View Parameters Methods

  virtual void FlagViewParametersChanged ();
  virtual void UpdateViewParameters (const int viewport[4]);
  virtual void UpdateViewParameters (const int viewport[4], const float viewmatrix[16], const float projmatrix[16]);
  virtual void UpdateViewParameters ();
  virtual void UpdateViewParameters (VglViewSurface* surface);
  virtual void UpdateViewParameters (const TrnViewParameters& viewParams);
  virtual void UpdateViewParameters (long frameNumber, float errorTolerance);
  virtual void UpdateViewParameters (float floorHeight);

  virtual TrnViewParameters GetViewParameters ();
  virtual TrnViewParameters& GetViewParametersRef ();
  virtual void FreeViewParametersRef ();

  // Static Methods

  static void CalculateSecondaryParameters (TrnViewParameters& viewParams);

protected:

  // Listener Methods

  virtual void NotifyListeners ();

private:

  DsArray<TrnViewListener*> m_listeners;
  TrnViewParameters m_viewParams;
  MtlCritSection m_critsection;

};

#endif // TRN_VIEWPARAMETERS_H
