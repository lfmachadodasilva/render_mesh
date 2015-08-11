/**
* Modulo de declaracao dos metodos responsaveis por query de intersecao entre esferas contra
* plano, raio, esferas,caixas, caixas alinhadas,triangulos...
*/

#ifndef __SPHERE_INTERSECTION_H__
#define __SPHERE_INTERSECTION_H__

#include "../../math_includes.h"
#include "../../queries/query_includes.h"

/**
* Determina se uma esfera esta colidindo contra um plano.
* Retorna true se estiver colidindo , false caso contrario.
*/
template <class Real> bool Sphere_Against_Plane(const SPHERE<Real>& Sphere,const PLANE3<Real>& Plane);


/**
* Determina se uma esfera esta "dentro" do semi plano negativo do plano
*/
template <class Real> bool Sphere_Inside_Plane(const SPHERE<Real>& Sphere,const PLANE3<Real>& Plane);

/**
* Determina se esfera esta a esquerda do plano, a direita do plano ou colidindo com o plano
* -1 se esquerda, 0 se colidindo e 1 se a direita
*/
template <class Real> int Sphere_Which_Side_Plane(const SPHERE<Real>& Sphere,const PLANE3<Real>& Plane);


/**
* Determina se uma esfera esta colidindo contra um raio
* Se houver colisao entao retorna a menor distancia, caso contrario retorna -1
*/
template <class Real> Real Sphere_Against_Ray(const SPHERE<Real>& Sphere,const RAY3D<Real>& Ray);

/*
* true no caso de haver colisao em todos os metodos, false caso contrario.
*/

/**
* Determina se uma esfera esta colidindo contra outra esfera
*/
template <class Real> bool Sphere_Against_Sphere(const SPHERE<Real>& Sphere_A,const SPHERE<Real>& Sphere_B);

/**
* Determina se uma esfera esta colidindo contra uma caixa alinhada.
*/
template <class Real> bool Sphere_Against_AABB(const SPHERE<Real>& Sphere,const AABB3D<Real>& AABB);

/**
* Determina se uma esfera esta colidindo contra uma caixa orientada.
*/
template <class Real> bool Sphere_Against_OBB(const SPHERE<Real>& Sphere,const OBB3D<Real>& OBB);

/**
* Determina se uma esfera esta colidindo contra um triangulo
*/
template <class Real> bool Sphere_Against_Triangle(const SPHERE<Real>& Sphere,const TRIANGLE3D<Real>& Triangle);


#include "sphere_intersections.inl"

#endif
