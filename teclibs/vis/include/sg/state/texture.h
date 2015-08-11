// Texture class
// fabraham@tecgraf.puc-rio.br
// Oct 2004

#ifndef SG_TEXTURE_H
#define SG_TEXTURE_H

#include <sg/state.h>
#include <ugl/texture.h>

class SG_API SGTexture : public SGState, public UGLTexture
{
public:
  static const char* CLASSNAME () { return "Texture"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  SGTexture ();
  virtual ~SGTexture();
  static float GetMaxAnisotropy ()
  {
    return UGLTexture::GetMaxAnisotropy();
  }
  virtual void Load ()
  {
    UGLTexture::Load();
  }
  virtual void Unload ()
  {
    UGLTexture::Unload();
  }
  virtual bool IsOpaque () const
  {
    return UGLTexture::IsOpaque();
  }
  virtual void Write (UtlWriter* writer);
};

#endif
