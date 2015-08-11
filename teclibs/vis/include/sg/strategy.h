// Strategy class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jul 2002
 
#ifndef SG_STRATEGY
#define SG_STRATEGY

#include "defines.h"

class SGItem;

class SGAttribute;
class SGState;
class SGBackground;
class SGShape;

class SGNode;
class SGLight;
class SGSpace;
class SGEntity;
class SGObject;
class SGGroup;
class SGSwitch;
class SGScene;
class SGCollection;
class SGColObject;
class SGColLight;
class SGColScene;
class SGBin;

/**
 * SGStrategy class.
 *
 * This class represents a scene graph traversal strategy.
 * All algorithms that need to traverse the scene graph can use the strategy mechanism.
 * All scene graph nodes (root node or internal nodes) can be traversed using this method:
 * 
 * int Traverse(SGStrategy* s);
 *
 * This will initiate a recursive process that will begin on the initial node, performing a
 * depth-first traversal on the scene tree. 
 * When a node is traversed, its main attributes are loaded and unloaded in a certain
 * order (see individual node documentation on the Traverse() method).
 *
 * Ex1: when an object is traversed, the following methods are called:
 * - Load(object)
 * - Load(object state)
 * - Traverse(shapes)
 * - Unload(object state)
 * - Unload(object)
 *
 * Ex2: when a node group is traversed, the following methods are called:
 * - Load(group)
 * - Load(group state)
 * - for each child, Traverse(child)
 * - Unload(group state)
 * - Unload(group)
 *
 * This will provide a flexible way to use the scene graph, since what is actually done when an
 * appearance/shape/group/entity/etc is loaded/unloaded is implemented on the concrete strategies.
 *
 * With strategies, one can for example:
 * - render the entire scene graph background/geometry.
 * - query the scene graph, like finding/collecting/counting items, etc.
 * - implement rendering techniques (single or multiple pass).
 * - compose strategies in a certain order (eg: Load(state) { otherstrategy->Load(state); Treat(state); }).
 * - build a data structure with relevant information about the scene graph.
 * - implement culling strategies, which will bypass some subgraphs to gain performance.
 *
 * Default methods are provided and can be reimplemented to:
 * - Load/Unload components (states, backgrounds and shapes)
 * - Load/Unload scene graph nodes (nodes, lights, spaces, entities, objects, groups, switches, scenes)
 * - Load/Unload collections (objects, lights, scenes, bins)
 *
 * Only the desired methods must be implemented. If for example the Load(SGObject) is not implemented
 * but the Load(SGEntity) method is (its parent in the class hierarchy), Load(SGObject) will
 * automatically call Load(Entity) due to the default SGStrategy implementation.
 * 
 * The methods for nodes/collections return an integer signaling if the traversal must:
 * - continue: continues the traversal.
 * - skip: stops traversing the current node (does not go deeper in the tree) but continues the traversal.
 * - break: stops the whole traversal. This value is propagated up the recursion.
 * 
 * This is useful for example to culling strategies, which will skip subgraphs/leaves according to some
 * culling criteria.
 */
class SG_API SGStrategy
{
public:
  enum 
  {
    CONTINUE=0,
    BREAK   =1,
    SKIP    =2,
  };
  virtual ~SGStrategy ()
  {
  }
  virtual void Load (SGItem* i)
  {
  }
  virtual void Unload (SGItem* i)
  {
  }
	// components
  virtual void Load (SGAttribute* a)
  {
    Load((SGItem*)a);
  }
  virtual void Unload (SGAttribute* a)
  {
    Unload((SGItem*)a);
  }
  virtual void Load (SGState* s)
  {
    Load((SGAttribute*)s);
  }
  virtual void Unload (SGState* s)
  {
    Unload((SGAttribute*)s);
  }
  virtual void Load (SGBackground* b)
  {
    Load((SGAttribute*)b);
  }
  virtual void Unload (SGBackground* b)
  {
    Unload((SGAttribute*)b);
  }
  virtual void Load (SGShape* s)
  {
    Load((SGAttribute*)s);
  }
	// nodes
  virtual int Load (SGNode* n)
  {
    Load((SGItem*)n);
    return CONTINUE;
  }
  virtual int Unload (SGNode* n)
  {
    Unload((SGItem*)n);
    return CONTINUE;
  }
  virtual int Load (SGLight* l)
  {
    return Load((SGNode*)l);
  }
  virtual int Unload (SGLight* l)
  {
    return Unload((SGNode*)l);
  }
	// nodes: spaces
  virtual int Load (SGSpace* c)
  {
    return Load((SGNode*)c);
  }
  virtual int Unload (SGSpace* c)
  {
    return Unload((SGNode*)c);
  }
  virtual int Load (SGEntity* e)
  {
    return Load((SGSpace*)e);
  }
  virtual int Unload (SGEntity* e)
  {
    return Unload((SGSpace*)e);
  }
  virtual int Load (SGObject* o)
  {
    return Load((SGEntity*)o);
  }
  virtual int Unload (SGObject* o)
  {
    return Unload((SGEntity*)o);
  }
  virtual int Load (SGGroup* g)
  {
    return Load((SGEntity*)g);
  }
  virtual int Unload (SGGroup* g)
  {
    return Unload((SGEntity*)g);
  }
  virtual int Load (SGSwitch* s)
  {
    return Load((SGGroup*)s);
  }
  virtual int Unload (SGSwitch* s)
  {
    return Unload((SGGroup*)s);
  }
  virtual int Load (SGScene* s)
  {
    return Load((SGSpace*)s);
  }
  virtual int Unload (SGScene* s)
  {
    return Unload((SGSpace*)s);
  }
	// nodes: collections
	virtual int Load (SGCollection* c)
	{
		return Load((SGNode*)c);
	}
	virtual int Unload (SGCollection* c)
	{
		return Unload((SGNode*)c);
	}
  virtual int Load (SGColObject* c)
  {
    return Load((SGCollection*)c);
  }
  virtual int Unload (SGColObject* c)
  {
    return Unload((SGCollection*)c);
  }
  virtual int Load (SGColLight* l)
  {
    return Load((SGCollection*)l);
  }
  virtual int Unload (SGColLight* l)
  {
    return Unload((SGCollection*)l);
  }
  virtual int Load (SGColScene* s)
  {
    return Load((SGCollection*)s);
  }
  virtual int Unload (SGColScene* s)
  {
    return Unload((SGCollection*)s);
  }
  virtual int Load (SGBin* b)
  {
    return Load((SGCollection*)b);
  }
  virtual int Unload (SGBin* b)
  {
    return Unload((SGCollection*)b);
  }
};

#endif
