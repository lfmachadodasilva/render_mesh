#ifndef SKYENVIRONMENT_H
#define SKYENVIRONMENT_H

#include "sky.h"
#include <alg/vector.h>

class SKY_API SkyEnvironment {
  AlgVector camera_pos;
  int i_background_vector;
  int i_astro_vector;
  int i_cloud_vector;
  int i_stars_vector;
  float vtime;

  SkyBackground * Background_vector[10];
  SkyAstro * Astro_vector[10];
  SkyClouds * Cloud_vector[10];
  SkyStars * Stars_vector[10];

public:
  static void SetTexturesPath (const char* path);
  static void ResetTexturesPath();  

  // Construtor
  SkyEnvironment();

  // Destrutor
  ~SkyEnvironment();

  // Insere um objeto Background no vetor de backgrounds
  void AddBackground (SkyBackground * background);

  // Insere um objeto Astro no vetor de astros
  void AddAstro (SkyAstro * astro);
  
  // Insere um objeto stars no vetor de estrelas
  void AddStars (SkyStars * stars);
  
  // Insere um objeto Cloud no vetor de nuvens
  void AddCloud (SkyClouds * cloud);

  // Atualiza a variacao do tempo
  void UpdateVtime (float vtime);

  // Atualiza o Alpha do Environment
  void UpdateAlpha (float percentage_alpha);

  // Metodo que encontra a posicao da camera
  void FindCameraPos();
  
  // Metodo de renderizacao
  void Render();

  // Metodo de renderizacao dos backgrounds
  void BackgroundsRender();

  // Metodo de renderizacao das nuvens
  void CloudsRender();

  // Metodo de renderizacao das nuvens
  void StarsRender();

  // Metodo de renderizacao dos efeitos
  void EffectsRender();

  // Número de fontes de luz
  int GetNumLightSources ();

  // Obtem a direçao da fonte de luz 'index'
  AlgVector GetLightSourceDirection (int index);
};

#endif
