#ifndef UTL_LUAWRITER_H
#define UTL_LUAWRITER_H

#include <utl/writer.h>
#include <utl/lua/utllua.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#include <lauxlib.h>
#ifdef __cplusplus
}
#endif

class UTLLUAAPI UtlLuaWriter : public UtlWriter {
	lua_State* m_L;
public:
	UtlLuaWriter (lua_State* L);
	virtual ~UtlLuaWriter ();

  virtual void WriteFloat (const char* name, float f);
	virtual void WriteBool (const char* name, bool b);
	virtual void WriteInt (const char* name, int i);
  virtual void WriteString (const char* name, const char* s);
  virtual void WriteMultilineString (const char* name, const char* s);
  virtual void WriteCode (const char* name, const char* s);
	virtual void WriteNewBlock (const char* name);
	virtual void WriteSeparator (const char* str);
	virtual void WriteCloseBlock ();
	virtual void WriteFloatArray(const char* name, int n, ...);
};

#endif
