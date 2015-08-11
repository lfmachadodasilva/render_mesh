// Scene class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Apr 2001
#ifndef SG_SCENE_H
#define SG_SCENE_H

#include <uso/clock.h>
#include <ds/list.h>
#include "wrlspace.h"

class SGBackground;
class SGEngine;
class SGStrategy;
class SGState;

/**
 * SGScene Class.
 * 
 * A scene contains the scene graph and the simulation that animates it.
 * 
 * It is composed by:
 * - an associated state
 * - a background
 * - a simulation time clock.
 * - an engine list
 * - child nodes (inherited from SGWorldSpace)
 *
 * It provides methods to:
 * - add/remove/obtain engines from the engine list.
 * - set/get the associated state.
 * - set/get the background.
 * - start/stop/pause/query/update the simulation clock.
 * - update the engine list with the current simulation time, allowing them to do animation.
 * - write its description.
 */
class SG_API SGScene : public SGWorldSpace
{
public:
  typedef DsPList<SGEngine> EngList;
private:
  EngList m_engines;
	USOClock m_clock;
  SGBackground* m_bg;
  SGState* m_state;
public:
  static const char* CLASSNAME () { return "Scene"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
	/**
	 * Constructor.
	 * */
  SGScene ();
	/**
	 * Destructor.
	 */
  virtual ~SGScene ();
	/**
	 * Inserts an engine to the engine list. 'start' signals if the engine should be Started().
	 */
  void AddEngine (SGEngine* engine, bool start = false);
	/**
	 * Removes an engine from the engine list.
	 */
  bool RemEngine (SGEngine* engine);
	/**
	 * Obtains the engine list.
	 */
  EngList::Iterator GetEngines () const
	{
		return m_engines.Begin();
	}
	/**
	 * Sets the state.
	 */
  void SetState (SGState* s);
	/**
	 * Sets the background.
	 */
  void SetBackground (SGBackground* bg);
	/**
	 * Gets the state.
	 */
  SGState* GetState () const { return m_state; }
	/**
	 * Gets the background.
	 */
  SGBackground* GetBackground () const { return m_bg; }
  /**
	 * Starts the simulation clock. Time t0 is obtained from the machine's clock.
	 */
  void StartClock ();
  /**
	 * Starts the simulation clock. 'reference' is the t0.
	 */
  void StartClock (double reference);
  /**
	 * Stops the simulation clock.
	 */
  void StopClock ();
  /**
	 * Pauses/unpauses the simulation clock.
	 */
  void PauseClock ();
	/**
	 * Obtains the current simulation time.
	 */
  float GetTime () const;
	/**
	 * Updates the engine list with the current simulation time.
	 */
  void Update ();
	/**
	 * Updates the engine list with time 'time'.
	 */
  void Update (double time);
  /**
   * Traverses the scene with a traversal strategy.
   * This scene will do the following:
	 * - skip if the scene is disabled.
	 * - load itself.
	 * - load its background.
	 * - load its state.
	 * - traverse it's children.
	 * - unload its state.
	 * - unload its background.
	 * - unload itself.
   */
  virtual int Traverse(SGStrategy* s);
	/**
	 * Writes the scene description
	 */
  virtual void Write (UtlWriter * writer);
};

#endif

