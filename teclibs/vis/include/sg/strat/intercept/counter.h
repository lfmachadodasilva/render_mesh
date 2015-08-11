// Counter strategy
// fabraham@tecgraf.puc-rio.br
// Jul 2003

#ifndef SG_COUNTER
#define SG_COUNTER

#include <sg/strat/interceptor.h>

/**
 * Counter traversal strategy.
 * This strategy will intercept the calls to a strategy counting
 * vertices, triangles, lines and objects.
 */
class SG_API SGCounter : public SGInterceptor
{
  int m_obj_count;
  int m_vertex_count;
  int m_tri_count;
  int m_line_count;
public:
  SGCounter (SGStrategy* strategy);
  virtual ~SGCounter ();
  int GetObjectCount ()
  {
    return m_obj_count;
  }
  int GetVertexCount ()
  {
    return m_vertex_count; 
  }
  int GetTriangleCount () 
  {
    return m_tri_count; 
  }
  int GetLineCount () 
  {
    return m_line_count; 
  }
  virtual void Load (SGShape* s);
  virtual int Load (SGObject* o);
  virtual int Load (SGScene* s);
  virtual int Load (SGColObject* o);
  virtual int Load (SGColScene* s);
};
#endif
