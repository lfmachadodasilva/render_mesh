/**
* Metodos de query de distancia de segmentos e pontos
*/

#ifndef __SEGMENT_QUERY_H__
#define __SEGMENT_QUERY_H__

#include "../math_includes.h"

/**
* Dado um ponto P e um Semento AB, determina o ponto D no segmento AB mais proximo de P,alem disto retorna o valor de t onde
* d(t) = a + t(b-a);
*/

/**
* Dado um ponto P e um Semento AB, determina o ponto D no segmento AB mais proximo de P, alem disto retorna o valor de t onde
* d(t) = a + t(b-a);
*/
/**
* Em 2d !
*/
template <class Real> VECTOR2<Real> Closest_Point_on_Segment2D(Real& t,const VECTOR2<Real>& Point,const SEGMENT2D<Real>& Segment);

/**
* Retorna a distancia de um ponto ao um segmento. Em 2D
*/
template <class Real> Real Distance_From_Segment2D(const VECTOR2<Real>& Point,const SEGMENT2D<Real>& Segment);

/**
* Retorna a distancia de um ponto ao um segmento. Em 2D
*/
template <class Real> Real Square_Distance_From_Segment2D(const VECTOR2<Real>& Point,const SEGMENT2D<Real>& Segment);

#endif
