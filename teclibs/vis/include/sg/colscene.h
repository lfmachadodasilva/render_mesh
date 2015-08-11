// Collected scene class
// fabraham@tecgraf.puc-rio.br
// Apr 2003

#ifndef SG_COL_SCENE_H
#define SG_COL_SCENE_H

#include <alg/matrix.h>
#include <ds/list.h>
#include "collection.h"

class SGColLight;
class SGStrategy;
class SGBin;
class SGScene;
class SGNode;

/**
 * SGColScene class.
 * 
 * This class represents the result of a collect made on a scene.
 * 
 * It is composed by the list of collected lights and bins holding the remaining collected items.
 * 
 * It contains methods to:
 * - insert lights to the list of collected lights.
 * - insert bins.
 * - get the source scene.
 * - traverse this collection with a traversal strategy.
 * - release this collection
 */
class SG_API SGColScene : public SGCollection
{
public:
  typedef DsPList<SGColLight> LightList;
  typedef DsPList<SGBin> BinList;
  typedef LightList::Iterator LightListIterator;
  typedef BinList::Iterator BinListIterator;
  static const char* CLASSNAME () { return "ColScene"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructor. Receives the collection root.
   */
  SGColScene (SGNode* n);
  /**
   * Destructor
   */ 
  virtual ~SGColScene ();
  /**
   * Inserts a collected light to the list
   */
  void InsertLight (SGColLight* l);
  /**
   * Inserts a bin to the list
   */ 
  void InsertBin (SGBin* b);
  /**
   * Obtains the collected scene (deprecated)
   */
  SGScene* GetScene () const
  {
    return (SGScene*)m_root;
  }
  /**
   * Obtains the collection root
   */
  SGNode* GetRoot () const
  {
    return m_root;
  }
  /**
   * Obtains an iterator for the collected lights
   */
  LightListIterator GetColLights()
  {
    return m_light_list.Begin();
  }
  /**
   * Obtains an iterator for the collected bins
   */
  BinListIterator GetBins()
  {
    return m_bin_list.Begin();
  }
  /**
   * Traverses this collection with a traversal strategy.
   * This will do the following:
   * - skip if this collect is disabled.
   * - load itself.
   * - load each light in the order of insertion.
   * - load the collected scene background.
   * - load the collected scene state.
   * - traverse each bin.
   * - unload the collected scene state.
   * - unload the collected scene background.
   * - unload itself
   */
  virtual int Traverse (SGStrategy * s);
  /**
   * Releases all collections related to this collection.
   */
  virtual void Release ();
private:
  LightList m_light_list;
  BinList m_bin_list;
  SGNode* m_root;
};

#endif
