#ifndef __ITSSTACK_H__
#define __ITSSTACK_H__

#include "interactapi.h"
#include "itask.h"

class INTERACT_API itrTaskStack
{
   itrTask** stack;  
   int top;
   int stacksize;
public:
   itrTaskStack();
   ~itrTaskStack();
   void     Push(itrTask*);
   itrTask* Pop();
   itrTask* GetTop();
   itrTask* Get(int index);
   int      GetSize();

   void     PopAll();
};

#endif
