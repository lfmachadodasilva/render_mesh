#ifndef UTL_TT_MESSAGE_H_OLD
#define UTL_TT_MESSAGE_H_OLD

#include <ufont/ttmessage.h>
#include <utl/defines.h>

class UTL_API UtlTTMessage : public UFontTTMessage
{
public:
  UtlTTMessage (float x=-0.9, float y=0.9, float z = 0.9) : UFontTTMessage(x,y,z)
  {
  }
};

#endif
