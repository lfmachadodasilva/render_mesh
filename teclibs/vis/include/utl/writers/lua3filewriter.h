#ifndef UTL_LUA3FILE_WRITER_H
#define UTL_LUA3FILE_WRITER_H

#include "luafilewriter.h"

class UtlLua3FileWriter : public UtlLuaFileWriter
{
public:
  UtlLua3FileWriter()
  {
  }
  virtual ~UtlLua3FileWriter()
  {
  }	
	virtual void WriteBool (const char* name, bool b)
  {
    WriteInt(name,b?1:0);
  }
};

#endif
