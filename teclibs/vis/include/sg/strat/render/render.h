// Render Strategy
// fabraham@tecgraf.puc-rio.br
// Mar 2003

#ifndef SG_RENDER
#define SG_RENDER

#include <sg/strat/immediate.h>

class SGLoadLights;
/**
 * Render traversal strategy.
 * This strategy will traverse the scene graph and will perform all operations
 * immediately. Transformations, states and lighting setup will be passed 
 * directly to the OpenGL pipeline.
 */
class SG_API SGRender : public SGImmediate
{
  SGLoadLights* m_loadlights;
protected:
  SGLoadLights* GetLoadLights () const
	{
		return m_loadlights;
	}
public:
  SGRender ();
  virtual ~SGRender ();
  /**
   * Starts the rendering of the hierarchy below node 'node'.
   * It is simply a call to node->Traverse(this=render)
   */
  void Render (SGNode *node)
  {
    node->Traverse(this);
  }
	virtual void SetCamera (SGCamera* camera);
  virtual void Load (SGState* s);
  virtual void Load (SGBackground* b);
  virtual void Unload (SGState* s);
  virtual void Unload (SGBackground* b);
  virtual void Load (SGShape* s);
  virtual int Load (SGScene* s);
  virtual int Unload (SGScene* s);
  virtual int Load (SGColLight* l);
  virtual int Unload (SGColLight* l);
  virtual int Load (SGColScene* s);
  virtual int Unload (SGColScene* s);
};

#endif
