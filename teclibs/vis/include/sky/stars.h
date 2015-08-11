#ifndef SKYSTARS_H
#define SKYSTARS_H

#include "sky.h"
#include <alg/vector.h>

class SKY_API SkyStars {
  AlgVector m_center_sphere;
  int stars;
  float altura_min, angle_min;
  float pixel_size;
  float radius_stars;
  float radius_sphere;
  float * vector_stars;
  float vtime, i_vtime;
  float percentage_alpha;
  UtlTexture * Star_tex;

public:

  // Construtor
  SkyStars();

  // Destrutor
  ~SkyStars();

  // Reposicionamento das estrelas - Aleatorio
  void SetNewPosition();

  // Configura o raio da esfera imaginaria onde as estrelas estao posicionadas
  void SetSphere (float radius = 0);

  // Configura a transparencia da textura utilizada
  void SetAlpha (float percentage_alpha = 1);

  // Configura as propriedades das estrelas
  void SetStars (int num_stars = 0, float angle_min = 0, float pixel_size = 0);

  // Configura a textura de renderizacao das estrelas(Source e Alpha da textura)
  bool SetTexture (const char * image_name = 0, const char * alpha_image_name = 0);

  // Atualiza a posicao de observacao
  void UpdateCameraPos (AlgVector & center_sphere);

  // Configura a variacao do tempo
  void UpdateVtime (float vtime);

  // Metodo de renderizacao
  void Render();

};
#endif
