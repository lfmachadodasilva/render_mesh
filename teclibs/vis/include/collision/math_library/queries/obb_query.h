/**
* Modulo de declaracao dos metodos que fazem query de distancia entre pontos e OBB
*/

#ifndef __OBB_QUERY_H__
#define __OBB_QUERY_H__

#include "../math_includes.h"

/**
* Dado um ponto P, e uma OBB Box, determina o ponto dentro ou na borda de Box que e mais proximo
* de P
*/
template <class Real> VECTOR3<Real> Closest_Point_OBB3D(const VECTOR3<Real>& Point,const OBB3D<Real>& Box);


/**
* Dado um ponto P e uma OBB , retorna a menor distancia do ponto P a OBB
*/
template <class Real> Real Distance_Point_OBB3D(const VECTOR3<Real>& Point,const OBB3D<Real>& Box);

/**
* Dado um ponto P e uma OBB , retorna a menor distancia ao quadrado do ponto P a OBB
*/
template <class Real> Real Distance_Point_OBB3D(const VECTOR3<Real>& Point,const OBB3D<Real>& Box);

/**
* Dado um ponto P e uma OBB , retorna a menor distancia ao quadrado do ponto P a OBB
*/
template <class Real> Real Square_Distance_Point_OBB3D(const VECTOR3<Real>& Point,const OBB3D<Real>& Box);

#endif
