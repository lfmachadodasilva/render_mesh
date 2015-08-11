//* handlerpick.h
// vbarata@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Fev 2009

#ifndef TRN_HANDLER_PICK_H
#define TRN_HANDLER_PICK_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "baseclass.h"
#include "handler.h"

#include <alg/vector.h>
#include <vgl/hnd/selection.h>

class TrnTerrain;

//----------------------//
// TrnHandlerPick Class //
//----------------------//

// This class implements a pick handler for terrains

class TERRAINAPI TrnHandlerPick : public VglSelectionHandler, public TrnHandler
{
public:

  // Class Name
  static const char* CLASSNAME () { return "TrnHandlerPick"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  // Constructor and Destructor
  TrnHandlerPick (VglViewSurface* surface, TrnViewSpecifier* viewSpecifier, int sel_buf_size = 512, double tolw = 1.0, double tolh = 1.0);
  virtual ~TrnHandlerPick ();

  // Handlers
  virtual int MouseEntry (bool st);
  virtual int MouseMotion (int bt, float x, float y);
  virtual int MouseButton (int bt, int st, float x, float y);

  // Flags
  void SetPickCoordsOutdated ();
  void SetPickObjectOutdated ();
  virtual void AssertPickCoordsUpdated ();
  virtual void AssertPickObjectUpdated ();
  virtual void AssertPickResultsUpdated ();

  // Pick
  virtual bool HasPick ();
  virtual void Pick (float xwindow, float ywindow);
  virtual void PickRenderless (float xwindow, float ywindow);

  // Results
  AlgVector GetPickWrlCoords ();
  TrnObjectType GetPickTrnObject ();

protected:

  // Flags
  virtual void UpdateFlagsPick ();
  virtual void UpdateFlagsPickRenderless();

  // Pick
  virtual void DoPickInit ();
  virtual void DoPick (float xwindow, float ywindow);
  virtual void DoPickRenderless (float xwindow, float ywindow);
  virtual void DoPickCamera ();

  virtual void ProcessFunction (VglSelectionHit* hits, int n);
  virtual void ProcessHit (VglSelectionHit* hit);

  void GetLastPosition (float& xwindow, float& ywindow);
  bool AssertValidOrCenter (float& xwindow, float& ywindow);

protected:

  TrnObjectType m_pick_trnobject;
  AlgVector m_pick_wrlcoords;

  float m_pick_xwindow;   // Window X coordinate of the current or last pick update
  float m_pick_ywindow;   // Window Y coordinate of the current or last pick update
  bool m_pick_overWindow; // Whether the current/last pick update started on a position inside the window

  bool m_outdated_coords; // Whether the pick coordinates are outdated
  bool m_outdated_object; // Whether the pick object is outdated
};

#endif // TRN_HANDLER_PICK_H
