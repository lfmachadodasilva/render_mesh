#ifndef UTL_VERTEXARRAY_H_OLD
#define UTL_VERTEXARRAY_H_OLD

#include <ugl/vertexarray.h>
#include <utl/defines.h>

class UTL_API UtlArray : public UGLArray
{
  UtlArray (int nv, int which=V_POSITION, int nelem=3, int type=GL_FLOAT) :
    UGLArray(nv,which,nelem,type)
  {
  };
};

class UTLH_API UtlVertexArray : public UGLVertexArray
{
};

#endif
