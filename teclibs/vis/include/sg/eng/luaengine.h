// luaengine class
// fabraham@tecgraf.puc-rio.br
// Jul 2003

#ifndef SG_LUA_ENGINE_H
#define SG_LUA_ENGINE_H

extern "C" {
#include <lua.h>
}
#include <sg/engine.h>

class SGLuaEngine : public SGEngine
{
	lua_State* m_L;
  char* m_startfunc;
  char* m_applyfunc;
	bool SetFunc (const char* name, const char* chunk);
	void CallFunc (const char* name, float par);
public:
  static const char* CLASSNAME () { return "LuaEngine"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  SGLuaEngine (lua_State* L);
  virtual ~SGLuaEngine ();

  bool SetStartFunc (const char* chunk);
  bool SetApplyFunc (const char* chunk);

  virtual void Start (float time);
  virtual void Apply (float time);
  virtual void Write (UtlWriter* writer);
};

#endif
