// Lua Hierarchy listener class
// fabraham@tecgraf.puc-rio.br
// Apr 2005
#ifndef LUALISTENER_H
#define LUALISTENER_H

extern "C" {
#include <lua.h>
}
#include <sg/listener.h>

/**
 * Lua hierarchy listener class.
 * 
 * This class enables the construction of hierarchy listeners in lua.
 */
class SGLuaHierarchyListener : public SGHierarchyListener
{
  lua_State* m_L;
public:
  static const char* CLASSNAME () { return "LuaHierarchyListener"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructor. Receives the lua_State in which the object will reside.
   */
  SGLuaHierarchyListener (lua_State* L);
  /**
   * Destructor.
   */
  virtual ~SGLuaHierarchyListener ();
  virtual void Insert (SGSpace *parent, SGNode *child);
  virtual void Insert (SGObject *parent, SGShape *child);
  virtual void Remove (SGSpace *parent, SGNode *child);
  virtual void Remove (SGObject *parent, SGShape *child);
  virtual void TransformChange (SGSpace *space);
  virtual void ShapeChange (SGShape *shape);
  virtual void ShapeDestruction (SGShape *shape);
  virtual void NodeDestruction (SGNode *node);
};

#endif
