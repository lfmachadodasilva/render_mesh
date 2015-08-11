// Immediate Strategy
// fabraham@tecgraf.puc-rio.br
// Mar 2003

#ifndef SG_IMMEDIATE
#define SG_IMMEDIATE

#include <alg/glstack.h>
#include <sg/scene.h>
#include <sg/colscene.h>
#include "transfstrategy.h"

/**
 * This class defines the SGImmediate strategy type.
 * It contains a OpenGL matrix stack.
 */
class SG_API SGImmediate : public SGTransfStrategy
{
  AlgGLStack* m_stack;
protected:
  /**
   * Constructor.
   */
  SGImmediate () : m_stack(new AlgGLStack())
  {
  }
public:
  /**
   * Destructor.
   */
  virtual ~SGImmediate ()
  {
    if (m_stack)
      delete m_stack;
  }
  void SetStack (AlgGLStack* stack)
  {
    m_stack = stack;
  }
  virtual AlgStack* GetStack () 
  {
    return m_stack;
  }
  virtual AlgMatrix GetBase ()
  {
    return GetProjection();
  }
  virtual int Load (SGScene* s)
  {
    // set the view matrix (current top) as the stack identity,
    // so that stack->Identity() takes us to the world space.
    m_stack->SetIdentity(m_stack->GetTop());
    // load scene transformations
    return SGTransfStrategy::Load(s); 
  }
  virtual int Load (SGColScene* s)
  {
    // save matrix
    SGTransfStrategy::Load(s);
    // set the view matrix (current top) as the stack identity,
    // so that stack->Identity() takes us to the world space.
    m_stack->SetIdentity(m_stack->GetTop());
    m_stack->Identity();
    return CONTINUE;
  }
};

#endif
