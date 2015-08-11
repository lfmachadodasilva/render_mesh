/**
* Modulo de declaracao dos metodos que fazem query de distancia entre pontos e triangulos
*/

#ifndef __TRIANGLE_QUERY_H__
#define __TRIANGLE_QUERY_H__

#include "../math_includes.h"

/**
* Determina o ponto mais proximo do triangulo3D ao ponto dado P
*/

template <class Real> VECTOR3<Real> Closest_Point_In_Triangle3D(const VECTOR3<Real>& Point,const TRIANGLE3D<Real>& Triangle);

/**
* Determina se um ponto 3D esta dentro de um triagulo 3D. 
*/
template <class Real> bool Point_Inside_Triangle3D(const VECTOR3<Real>& Point,const TRIANGLE3D<Real>& Triangle);

/**
* Determina se um ponto 2D esta dentro de um triagulo 2D. 
*/
template <class Real> bool Point_Inside_Triangle2D(const VECTOR2<Real>& Point,const TRIANGLE2D<Real>& Triangle);

/**
* Determina o ponto mais proximo do triangulo2D ao ponto dado P
*/
template <class Real> VECTOR2<Real> Closest_Point_In_Triangle2D(const VECTOR2<Real>& Point,const TRIANGLE2D<Real>& Triangle);

#endif

