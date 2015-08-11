#ifndef __ITR_ENVIRONMENT__
#define __ITR_ENVIRONMENT__

#include "interactapi.h"
/*
%C Variaveis globais que servem para ajustar comportamento padrao do interact.
*/
class INTERACT_API itrEnvironment
{
public:
   static long int FeedBackColor;     // Cor dos feedbacks (XOR)
   static void Initialize();
};

void INTERACT_API ItrOpen();

#endif
