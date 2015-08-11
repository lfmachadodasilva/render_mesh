#ifndef UTL_MESSAGE_H_OLD
#define UTL_MESSAGE_H_OLD

#include <ufont/glutmessage.h>
#include <utl/defines.h>

class UTLH_API UtlMessage : public UFontGLUTMessage
{
public:
  UtlMessage (float x=-0.9, float y=0.9, float z = 0.9) : UFontGLUTMessage(x,y,z)
  {
  }
};

#endif
