/**
* Modulo de declaracao dos metodos responsaveis por query de intersecao entre planos contra
* plano, raio,...
*/

#ifndef __PLANE_INTERSECTION_H__
#define __PLANE_INTERSECTION_H__

#include "../../math_includes.h"

/**
* Detecta se dois planos estao colidindo
*/

template <class Real> bool Plane_Against_Plane(const PLANE3<Real>& Plane_A,const PLANE3<Real>& Plane_B);

/**
* Detecta se a colisao entre um raio e um plano
*/

template <class Real> Real Plane_Against_Ray(const PLANE3<Real>& Plane_A,const RAY3D<Real>& Ray);

#include "plane_intersections.inl"
#endif
