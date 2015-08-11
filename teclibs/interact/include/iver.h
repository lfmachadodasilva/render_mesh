/*
%M iver.h - Modulo de apresentacao de versao de interact
%a Newton Cunha Sanches
%d 29/05/96
*/

#include <stdlib.h>
#include <stdio.h>
#include "interactapi.h"

/*
%C - class dummy feita para imprimir a data e versao da biblioteca na inicializa
     cao do programa
*/
class INTERACT_API itrVer
{
   static int message_said;
public:
   itrVer();
   static char* GetVer();
};

static itrVer itrVersionNumber;

