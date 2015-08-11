// luastate class
// fabraham@tecgraf.puc-rio.br
// Jul 2003

#ifndef SG_LUA_STATE_H
#define SG_LUA_STATE_H

extern "C" {
#include <lua.h>
}
#include <sg/state.h>

class SGLuaState : public SGState
{
	lua_State* m_L;
  int m_loadfunc;
  int m_unloadfunc;
  int m_isopaquefunc;
public:
  static const char* CLASSNAME () { return "LuaState"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  SGLuaState (lua_State* L);
  virtual ~SGLuaState ();

  void SetLoadFunc (int lo);
  void SetUnloadFunc (int lo);
  void SetIsOpaqueFunc (int lo);

  virtual bool IsOpaque () const;
  virtual void Load ();
  virtual void Unload ();
  virtual void Write (UtlWriter* writer);
};

#endif

