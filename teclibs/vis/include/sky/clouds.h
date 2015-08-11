#ifndef SKYCLOUDS_H
#define SKYCLOUDS_H

#include "sky.h"
#include <alg/vector.h>

class SKY_API SkyClouds {
  AlgVector m_camera_pos;
  float height, radius;
  float texture_repeat;
  float alpha, source_alpha;
  float coord_pos_x, coord_pos_z;
  float velocity;
  float sin_direction, cos_direction;
  UtlTexture * Cloud_tex;
  float ajuste;
  bool estado; 
public:

  // Construtor
  SkyClouds();

  // Destrutor
  ~SkyClouds();

  // Configura a textura de renderizacao daa Cloud(Source e Alpha)
  bool SetTexture (const char * image_name = 0, const char * alpha_image_name = 0);

  // Configura a transparencia da textura utilizada
  void SetAlpha (float percentage_alpha = 1);

  // Configura as nuvens
  void SetCloud (float radius = 0, float height = 0, float texture_repeat = 0, float velocity = 0, float direction = 0, float alpha = 0);

  // Atualiza a posicao de observacao
  void UpdateCameraPos (AlgVector & camera_pos);

  // Configura a variacao do tempo
  void UpdateVtime (float vtime);

  // Metodo de renderizacao
  void Render();
};
#endif
