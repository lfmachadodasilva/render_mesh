/**
* Modulo de declaracao dos metodos que fazem query de distancia entre pontos e AABB
*/

#ifndef __AABB_QUERY_H__
#define __AABB_QUERY_H__

#include "../math_includes.h"


/**
* Dado um ponto P, e uma AABB Box, determina o ponto dentro ou na borda de Box que e mais proximo
* de P
*/
template <class Real> VECTOR3<Real> Closest_Point_AABB3D(const VECTOR3<Real>& Point,const AABB3D<Real>& Box);

/**
* Dado um ponto P, e uma AABB Box, determina o ponto dentro ou na borda de Box que e mais proximo
* de P
*/
template <class Real> VECTOR2<Real> Closest_Point_AABB2D(const VECTOR2<Real>& Point,const AABB2D<Real>& Box);


/**
* Dado um ponto P e uma AABB , retorna a menor distancia do ponto P a AABB
*/
template <class Real> Real Distance_Point_AABB3D(const VECTOR3<Real>& Point,const AABB3D<Real>& Box);

/**
* Dado um ponto P e uma AABB , retorna a menor distancia do ponto P a AABB
*/
template <class Real> Real Distance_Point_AABB2D(const VECTOR2<Real>& Point,const AABB2D<Real>& Box);

/**
* Dado um ponto P e uma AABB , retorna a menor distancia ao quadrado do ponto P a AABB
*/
template <class Real> Real Square_Distance_Point_AABB3D(const VECTOR3<Real>& Point,const AABB3D<Real>& Box);

/**
* Dado um ponto P e uma AABB , retorna a menor distancia ao quadrado do ponto P a AABB
*/
template <class Real> Real Square_Distance_Point_AABB2D(const VECTOR2<Real>& Point,const AABB2D<Real>& Box);

#endif
