#ifndef SKYENVIRONMENTS_TRANSITION_H
#define SKYENVIRONMENTS_TRANSITION_H

#include "sky.h"
#include <alg/vector.h>

class SKY_API SkyEnvironmentsTransition
{
  SkyEnvironment * source_Environment;
  SkyEnvironment * target_Environment;

  float vtime;
  float transition_time;
  float time;
  float percentage_alpha;
public:

  // Construtor
  SkyEnvironmentsTransition();

  // Destrutor
  ~SkyEnvironmentsTransition();

  // Atualiza a variacao do tempo
  void UpdateVtime (float vtime);

  // Configura o Environments original e o Environment alvo para a transicao
  void SetTransition (SkyEnvironment * source, SkyEnvironment * target, float transition_time = 1000);

  // Metodo de renderizacao
  void Render();

};
#endif
