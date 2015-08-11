// Texture Combiner class
// djavanes@tecgraf.puc-rio.br
// Jun 2009

#ifndef SGTEXCOMBINER_H
#define SGTEXCOMBINER_H

#include <sg/state.h>
#include <sg/state/texture.h>

class SG_API SGTexCombiner : public SGState
{
public:
  SGTexCombiner (SGTexture *t0, SGTexture *t1);
  virtual ~SGTexCombiner ();
  virtual void Load ();
  virtual void Unload ();
  virtual bool IsOpaque () const
  {
    return m_texture0->IsOpaque() && m_texture1->IsOpaque();
  }
  void SetCombinerFactor (float cfactor);

private:
  SGTexture *m_texture0;
  SGTexture *m_texture1;
  float m_cfactor;
};
#endif
