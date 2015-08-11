// ------------------------------------------------------------------------------------------------- 
// Anflex Project -- Tecgraf/PUC-Rio  CENPES/Petrobras 
// www.tecgraf.puc-rio.br 
// 
// Created by lfmachado in April/2011.
// 
// $URL: $ 
// $Revision: $ 
// $Date: $ 
// 
// $LastChangedBy: $ 
// -------------------------------------------------------------------------------------------------
#ifndef ANFLEX_INTERFACE_BOX_H
#define ANFLEX_INTERFACE_BOX_H

#include "alg\vector.h"

struct sBox   
{
  AlgVector min, max;

  sBox(void) { reset(); }
  sBox(const sBox &b) { *this = b; }
  sBox(float xmin, float xmax, float ymin, 
       float ymax, float zmin, float zmax);

  void operator=(const sBox& b) { min = b.min; max = b.max; }
  //void operator+=(const AlgVector &pt) { *this = *this + pt; }

  friend sBox operator+(const sBox&, AlgVector&);

  void add(const sBox &box);
  void reset(void);

  double volume(void) const { return (max.x - min.x) * (max.y - min.y) * (max.z - min.z); }
};

/* Verifica se ha' intersecao entre duas caixas. */
bool BoxIntersection(const sBox&, const sBox&);

/* Calcula a caixa alinhada com os eixos que envolve um conjunto de
* quadrilateros com uma folga de tol. */
//void BoxBoundQuads(sBox*, dCoord (**quads)[4], int, double);

/* Transforma a caixa alinhada com os eixos orig pela transformacao M e pela
* translacao T e retorna em res uma caixa alinha com os eixos envolvendo o
* resultado. */
void BoxTransform(sBox* res, sBox* orig, float M[9], float T[3]);

#endif