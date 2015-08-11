// Hierarchy Listeners
// fabraham@tecgraf.puc-rio.br
// Feb 2005

#ifndef SG_LISTENER_H
#define SG_LISTENER_H

#include "defines.h"

class SGObject;
class SGSpace;
class SGNode;
class SGShape;
class SGPLight;
class SGDLight;
class SGSLight;

/**
 * Hierarchy listener interface.
 * 
 * This interface enables the user to watch for certain hierarchy
 * events.
 * This is particularly useful to:
 * - keep other data structures aligned with the scene graph, such as bounding volume or collision hierarchies.
 * - inform other systems of changes in the scene graph.
 */
class SG_API SGHierarchyListener
{
public:
  virtual ~SGHierarchyListener ()
  {
  }
  /**
   * Called when a 'child' node is inserted onto a 'parent' node.
   * 'parent' is also a 'SGNodeList'.
   * Cast like this: (SGNodeList*)(RealType)parent;
   */
  virtual void Insert (SGSpace *parent, SGNode *child)
  {
  }
  /**
   * Called when a shape 'child' is inserted onto a 'parent' object node.
   */
  virtual void Insert (SGObject *parent, SGShape *child)
  {
  }
  /**
   * Called when a 'child' node is removed from a 'parent' node.
   * 'parent' is also a 'SGNodeList'.
   * Cast like this: (SGNodeList*)(RealType)parent;
   */
  virtual void Remove (SGSpace *parent, SGNode *child)
  {
  }
  /**
   * Called when a shape 'child' is removed from a 'parent' object node.
   */
  virtual void Remove (SGObject *parent, SGShape *child)
  {
  }
  /**
   * Called when the transform of a 'space' changes.
   */
  virtual void TransformChange (SGSpace *space)
  {
  }
  /**
   * Called when a shape changes.
   */
  virtual void ShapeChange (SGShape *shape)
  {
  }
  /**
   * Called before a shape is destroyed.
   */
  virtual void ShapeDestruction (SGShape *shape)
  {
  }
  /**
   * Called before a node is destroyed.
   */
  virtual void NodeDestruction (SGNode *node)
  {
  }
};

class SG_API SGLightChangesListener
{
public:
  virtual ~SGLightChangesListener ()
  {
  }
  virtual void PositionChange (SGPLight *light)
  {
  }
  virtual void DirectionChange (SGDLight *light)
  {
  }
  virtual void DirectionChange (SGSLight *light)
  {
  }
};

/**
 * Inserts an hierarchy listener to the listener list.
 */
SG_API void sg_inserthierarchylistener (SGHierarchyListener *listener);
/**
 * Removes an hierarchy listener from the listener list.
 */
SG_API bool sg_removehierarchylistener (SGHierarchyListener *listener);
/**
 * Inserts a light changes listener to the listener list.
 */
SG_API void sg_insertlightchangeslistener (SGLightChangesListener *listener);
/**
 * Removes a light changes listener from the listener list.
 */
SG_API bool sg_removelightchangeslistener (SGLightChangesListener *listener);
/**
 * Notifies that the shapes vertices have changed.
 */
SG_API void sg_notifyshapechange (SGShape *shape);

#endif
