#ifndef SKYENVIRONMENT_FACTORY_H
#define SKYENVIRONMENT_FACTORY_H

#include "sky.h"
#include <alg/vector.h>

class SKY_API SkyEnvironmentFactory {
  SkyBackground * background;
  SkyAstro * sol;
  SkyAstro * sol2;
  SkyAstro * lua;
  SkyAstro * lua2;
  SkyClouds * nuvens1;
  SkyClouds * nuvens2;
  SkyClouds * nuvens3;
  SkyStars * estrelas;

  float radius_sphere;
public:
  enum type{
    DAWN= 1,   //AMANHECER//
    MORNING,   //DE MANHA//
    AFTERNOON, //DE TARDE//
    SUNSET,    //POR DO SOL//
    NIGHT,     //DE NOITE//
    CLOUDY,    //DIA NUBLADO//
    ALIEN,     //CEU ALIEN//
    PANORAMIC,  //VISTA PANORAMICA//
    GREENNIGHT //DE NOITE COM HORIZONTE VERDE//
  };
  // Construtor
  SkyEnvironmentFactory();
  // Destrutor
  ~SkyEnvironmentFactory();

  // Metodo de criacao de um Environment
  SkyEnvironment * CreateEnvironment (int Environment_type, float radius_sphere = 0);
};

#endif
