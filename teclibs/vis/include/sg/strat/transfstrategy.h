// Transform Strategy class
// fabraham@tecgraf.puc-rio.br
// Sep 2003

#ifndef SG_TRANSF_STRATEGY
#define SG_TRANSF_STRATEGY

#include <alg/stack.h>
#include <sg/strategy.h>
#include <sg/camera.h>
#include <sg/space.h>
#include <sg/colobject.h>
#include <sg/collight.h>
#include <assert.h>

/**
 * SGTransfStrategy abstract class.
 * 
 * Besides expecting the strategy methods to be implemented, it must contain a
 * matrix stack, for strategies that need to keep track of the current transformation.
 * 
 * Methods are provided to load/unload the nodes' transformation on the stack.
 *
 * Camera anchor management is done by this class too, so a camera must be set when this strategy is used in a traversal.
 * 
 * Derived strategies must implement the GetStack method.
 * Derived strategies can of course override a strategy method or use the default implementation, e.g:
 *
 * int Load (SGSpace* s)
 * {
 *   SGTransfStrategy::Load(s); // load the transformation
 *   ... // do load stuff after the transformation was loaded
 * }
 *
 * int Unload (SGSpace* s)
 * {
 *   ... // do unload stuff
 *   SGTransfStrategy::Unload(s); // unload the transformation
 * }
 * 
 * The order is important to perform correct matrix/attribute stacks push/pops.
 */
class SG_API SGTransfStrategy : public SGStrategy
{
  SGCamera* m_camera;
protected:
  /**
   * Constructor.
   */
  SGTransfStrategy () : m_camera(NULL)
  {
  }
public:
  /**
   * Destructor.
   */ 
  virtual ~SGTransfStrategy ()
  {
    if (m_camera != NULL)
      m_camera->DecRef();
  }
  /**
   * Obtains the current rendering camera.
   */
  SGCamera* GetCamera () const
  {
    return m_camera;
  }
  /**
   * Obtains the current rendering camera's view matrix.
   * Returns the modelview matrix from OpenGL if no camera set.
   */
  AlgMatrix GetView ();
  /**
   * Obtains the current rendering camera's projection matrix.
   * Returns the projection matrix from OpenGL if no camera set.
   */
  AlgMatrix GetProjection ();
  /**
   * Sets the current rendering camera.
   */
  virtual void SetCamera (SGCamera* camera);
  /**
   * Obtains the strategy's matrix stack.
   */
  virtual AlgStack* GetStack () = 0;
  /**
   * Obtains the strategy's base of transformation.
   * It is the part of the PVM matrix that along with the
   * current stack top's matrix (usually VM or M) will enable
   * other strategies to use or manipulate the frustum to provide effects.
   */
  virtual AlgMatrix GetBase () = 0;
  virtual int Load (SGSpace* c)
  {
    // push transformation if any 
    c->AccumTransf(GetStack());
    return CONTINUE;
  }
  virtual int Unload (SGSpace* c)
  {
    // pop transformation if any
    c->UnloadTransf(GetStack());
    return CONTINUE;
  }
  virtual int Load (SGBin *b)
  {
    GetStack()->Push();
    return CONTINUE;
  }
  virtual int Unload (SGBin *b)
  {
    GetStack()->Pop();
    return CONTINUE;
  }
  virtual int Load (SGColObject* o)
  {
    // push transformation matrix
    GetStack()->Push();
    GetStack()->Accum(o->GetMatrix());
    return CONTINUE;
  }
  virtual int Unload (SGColObject* o)
  {
    // pop matrix
    GetStack()->Pop();
    return CONTINUE;
  }
  virtual int Load (SGColLight* l)
  {
    // push transformation matrix
    GetStack()->Push();
    GetStack()->Accum(l->GetMatrix());
    return CONTINUE;
  }
  virtual int Unload (SGColLight* l)
  {
    // pop matrix
    GetStack()->Pop();
    return CONTINUE;
  }
  virtual int Load (SGColScene* s)
  {
    // save matrix
    GetStack()->Push();
    return CONTINUE;
  }
  virtual int Unload (SGColScene* s)
  {
    // restore matrix
    GetStack()->Pop();
    return CONTINUE;
  }
};

#endif

