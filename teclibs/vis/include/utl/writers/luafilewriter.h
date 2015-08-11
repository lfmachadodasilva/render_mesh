#ifndef UTL_LUAFILE_WRITER_H
#define UTL_LUAFILE_WRITER_H

#include <utl/writer.h>
#include <stdio.h>

class UTL_API UtlLuaFileWriter : public UtlWriter
{
  FILE* m_file;
  int   m_curr_indent;
  int   m_indent;
  bool  m_fileopened;
  bool  m_error;
public:
  UtlLuaFileWriter();
  virtual ~UtlLuaFileWriter();

  void SetFile(FILE* file);
  void SetOutputToStdOut ();
  void SetIndent(int indent);
  bool Open (const char* filename);
  bool Close ();
  bool GetError ();

	void WriteLine (const char* format, ...);
	
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
