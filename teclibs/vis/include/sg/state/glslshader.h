// GLSLShader class
// fabraham@tecgraf.puc-rio.br
// Nov 2004

#ifndef SG_GLSLSHADER_H
#define SG_GLSLSHADER_H

#include <sg/state/shader.h>

class GLSLShader;

class SG_API SGGLSLShader : public SGShader
{
  GLSLShader* m_loader;
  bool m_isopaque;
public:
  static const char* CLASSNAME () { return "GLSLShader"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static bool Init ();

  SGGLSLShader ();
  virtual ~SGGLSLShader ();
  void SetIsOpaque(bool flag)
  {
    m_isopaque = flag;
  }
  virtual bool CompileFiles (Target target, int file_count, const char** files, const char* entry="main", const char** args=0);
  virtual bool CompileStrings (Target target, int string_count, const char** codes, const char* entry="main", const char** args=0);
  virtual bool Link ();
  virtual bool BindPosition (const char* name);
  virtual bool BindNormal   (const char* name);
  virtual bool BindColor    (const char* name);
  virtual bool BindTexCoord (const char* name, int unit);
  virtual bool BindTexture (const char* name, SGTexture* texture);
  virtual bool BindTexture (const char* name, unsigned int unit);
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
