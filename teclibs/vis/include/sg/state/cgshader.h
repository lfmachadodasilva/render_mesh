// CGShader class
// fabraham@tecgraf.puc-rio.br
// Aug 2003 

#ifndef SG_CGSHADER_H
#define SG_CGSHADER_H

#include <sg/state/shader.h>

class CGShader;

class SGCGShader : public SGShader
{
  CGShader* m_loader;
  bool m_isopaque;
public:
  static const char* CLASSNAME () { return "CGShader"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static bool Init (const char* vertex_profile=0, const char* fragment_profile=0);

  SGCGShader ();
  virtual ~SGCGShader ();

  virtual bool CompileFiles (Target target, int file_count, const char** files, const char* entry="main", const char** args=0);
  virtual bool CompileStrings (Target target, int string_count, const char** codes, const char* entry="main", const char** args=0);
  virtual bool Link ();

  void SetIsOpaque(bool flag) { m_isopaque = flag; }

  virtual bool BindPosition (const char* name);
  virtual bool BindNormal   (const char* name);
  virtual bool BindColor    (const char* name);
  virtual bool BindTexCoord (const char* name, int unit);
  virtual bool BindTexture (const char* name, SGTexture* texture);

  virtual bool SetConstant (Target target, const char* name, float x);
  virtual bool SetConstant (Target target, const char* name, float x, float y);
  virtual bool SetConstant (Target target, const char* name, float x, float y, float z);
  virtual bool SetConstant (Target target, const char* name, float x, float y, float z, float w);
  virtual bool SetConstant (Target target, const char* name, int rows, int columns, float* m);
  virtual bool TrackMatrix (Target target, const char* name, Matrix matrix, Transform transform=IDENTITY);

  virtual void Load ();
  virtual void Unload ();
  virtual bool IsOpaque () const;
  virtual void Write (UtlWriter* writer);
};

#endif
