#ifndef SKYASTRO_H
#define SKYASTRO_H

#include "sky.h"
#include <alg/vector.h>

class SKY_API SkyAstro {
  bool effect1, effect2, effect3, VISIBLE, TRANSITION;
  float znear;
  float effect1_alpha_max, effect2_alpha_max, effect3_alpha_max, percentage_alpha;
  float m_radius_sphere, m_radius_astro, m_radius_effects;
  float cos_angle_v_astro, sin_angle_v_astro, cos_angle_h_astro, sin_angle_h_astro;
  float angle, angle2, angle_v_astro, angle_h_astro, angle_effects, temp_angle_effects, angle_size;
  float vtime, transition_time, current_transition_time;

  AlgVector m_pos,
            m_pos1, 
            m_pos2, 
            m_pos3, 
            m_pos4, 
            m_normal, 
            m_right, 
            m_up,
            m_center_sphere;

  UtlTexture * Astro_tex;
  UtlTexture * effect1_tex;
  UtlTexture * effect2_tex;
  UtlTexture * effect3_tex;
  
  bool light_source;
public:
  enum effects{
    LENS_FLARES = 1,
    SUN_SHINE,
    LIGHT_BLUR,
  };

  // Construtor
  SkyAstro();

  // Destrutor
  ~SkyAstro();

  // Configura as propriedades do astro
  void SetAstro (float angle_v = 0, float angle_h = 0, float angle_size = 0);

  // Configura a textura de renderizacao do astro (Source e Alpha)
  bool SetTexture (const char * image_name = 0, const char * alpha_image_name = 0);

  // Configura a textura de renderizacao dos effects do astro (Source e Alpha)
  bool SetEffectsTexture (effects effect, const char * image_name, const char * alpha_image_name = 0);

  // Ativa determinado efeito do astro
  void SetEffect (effects effect, float alpha_max = 0);

  // Configura o raio da esfera imaginaria onde o astro esta posicionado
  void SetSphere (float radius = 0);
  
  // Configura se o astro emite ou nao luz
  void SetLightSource (bool lightsource);

  // Diz se o astro emite luz
  bool IsLightSource ();
  
  // Pega a direcao do astro
  AlgVector GetDirection ();

  // Atualiza a posicao de observacao
  void UpdateCameraPos (AlgVector & camera_pos);

  // Configura a variacao do tempo
  void UpdateVtime (float vtime);

  // Metodo de renderizacao do astro
  void Render();

  // Metodo de renderizacao dos effects
  void EffectsRender();

};
#endif
