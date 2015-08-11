// Flattener strategy
// fabraham@tecgraf.puc-rio.br
// Mar 2005

#ifndef SG_FLATTEN
#define SG_FLATTEN

#include <sg/strategy.h>
#include <alg/matrixstack.h>

/**
 * Flattener traversal strategy.
 *
 * This strategy will traverse a node hierarchy,
 * removing any transforms from internal nodes and
 * inprinting them onto the shapes vertices.
 *
 * This strategy must not be used with hierarchies that
 * have SGWorldSpace/SGClipSpace/SGEyeSpace nodes below
 * them.
 * It must not be used also with hierarchies that have
 * shaped shares below them, because transformations will be inprinted
 * onto the shapes vertices.
 */
class SG_API SGFlattener : public SGStrategy
{
  AlgMatrixStack m_matstack;
  bool m_error;
public:
  SGFlattener ();
  virtual ~SGFlattener ();
  /**
   * Flattens the hierarchy starting at node 'n'.
   * Returns false if a SGWorldSpace/SGEyeSpace/SGClipSpace node
   * was detected below 'n', true otherwise.
   */
  bool Flatten (SGNode* n);
  virtual int Load (SGSpace *s);
  virtual int Unload (SGSpace *s);
  virtual void Load (SGShape *s);
};

#endif
