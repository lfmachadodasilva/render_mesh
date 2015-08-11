#ifndef UTL_SERVER_H_OLD
#define UTL_SERVER_H_OLD

#include <uso/server.h>
#include <utl/defines.h>

class UTL_API UtlServer : public USOServer
{
public:
  UtlServer(int port) : USOServer(port)
  {
  }
};

#endif
