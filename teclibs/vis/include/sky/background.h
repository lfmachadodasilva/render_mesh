#ifndef SKYBACKGROUND_H
#define SKYBACKGROUND_H

#include "sky.h"
#include <alg/vector.h>

class SKY_API SkyBackground {
  int detail;
  float * vector_ctex_s;
  float * vector_ctex_t;
  float radius_sphere;
  float xfar;
  float fovy, fovy2;
  float fovytex_h, fovytex_v;
  float aspect;
  float back_angle_h, back_angle_v;
  float ctexmax;
  float coord_pos_screen_h, coord_pos_screen_v;
  float alpha, source_alpha;
  AlgVector    m_center_sphere;
  AlgVector  * m_vector_background;
  UtlTexture * Back_tex;

public:

  // Construtor
  SkyBackground();

  // Destrutor
  ~SkyBackground();

  // Seta a textura de renderizacao do Background
  bool SetTexture (const char * image_name = 0, const char * alpha_image_name = 0);

  // Configura a transparencia da textura utilizada
  void SetAlpha (float percentage_alpha = 1);

  // Configura o raio da esfera imaginaria onde os vertices do background estao posicionados
  void SetSphere (float radius = 0);

  // Configura a disposicao do Background
  void SetBack (int detail = 0, float angle_h = 0, float angle_v = 0, float angle_origin_h = 0, float angle_origin_v = 0);

  // Atualiza a posicao de observacao
  void UpdateCameraPos (AlgVector & camera_pos);
  
  // Metodo de renderizacao
  void Render();
};
#endif
