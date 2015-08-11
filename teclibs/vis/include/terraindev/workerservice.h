#ifndef TRN_WORKERSERVICE_H
#define TRN_WORKERSERVICE_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "baseclass.h"
#include "typedefs.h"

#include <mthread/critsection.h>
#include <mthread/workerservice.h>

class TrnRenderer;

//------------------//
// Class Definition //
//------------------//

class TERRAINAPI TrnWorkerService : public TrnBaseClass, public MtlWorkerService
{
public:

  // Class Name

  static const char* CLASSNAME () {return "TrnWorkerService";}
  virtual const char* ClassName () const {return CLASSNAME();}

  // Constructor and Destructor

  TrnWorkerService ();
  virtual ~TrnWorkerService ();

  // Configuration

  void SetRenderer (TrnRenderer* renderer);

  // Service Control

  virtual void RequestRun ();

protected:

  // Configuration

  virtual void ApplyConfig (); // Override and call back to implement asynchronous configuration

  // Internal Getters

  TrnRenderer* GetCurRenderer ();

  // Thread Control

  void LockConfig ();
  void UnlockConfig ();

  // Requests

  void RequestCfgRedraw (); // Use outside DoService()
  void RequestCurRedraw (); // Use inside DoService()

private:

  // Service Main (Loop) Function

  virtual void ServiceLoop ();
  virtual void DoService () = 0; // Implement the service here

private:

  TrnRenderer* m_cfgRenderer; // Renderer (protected by config section)

  TrnRenderer* m_curRenderer; // Renderer (single thread)

  MtlCritSection  m_cs_config;

};

#endif // TRN_WORKERSERVICE_H
