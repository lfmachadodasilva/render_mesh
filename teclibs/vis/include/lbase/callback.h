#ifndef CALLBACK_H
#define CALLBACK_H

#include <stdio.h>
#include "defines.h"

class LBASEAPI Callback
{
public:

  typedef void (*Function)(void* data);
  Callback ();
  ~Callback ();
  void SetFunction (Function func, void* data=NULL);
  void Call ();
private:
  Function m_func;
  void* m_data;
};

#endif