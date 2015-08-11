/**
* Modulo de declaracao dos metodos responsaveis por query de intersecao entre AABBBs contra
* plano, raio, esferas,caixas, caixas alinhadas,triangulos...
*/

#ifndef __AABB_INTERSECTION_H__
#define __AABB_INTERSECTION_H__

#include "../../math_includes.h"
#include "../../queries/query_includes.h"


/**
* Determina se uma AABB esta colidindo contra um plano.
* Retorna true se estiver colidindo , false caso contrario.
*/
template <class Real> bool AABB_Against_Plane(const AABB3D<Real>& AABB,const PLANE3<Real>& Plane);


/**
* Determina se uma AABB esta "dentro" do semi plano negativo do plano. 
*/
template <class Real> bool AABB_Inside_Plane(const AABB3D<Real>& AABB,const PLANE3<Real>& Plane);

/**
* Determina se esfera esta a esquerda do plano, a direita do plano ou colidindo com o plano
* -1 se esquerda, 0 se colidindo e 1 se a direita
*/
template <class Real> int AABB_Which_Side_Plane(const AABB3D<Real>& AABB,const PLANE3<Real>& Plane);



/**
* Determina se uma AABB esta colidindo contra um raio
* Se houver colisao entao retorna a menor distancia, caso contrario retorna -1
*/
template<class Real> Real AABB_Against_Ray(const AABB3D<Real>& AABB,const RAY3D<Real>& Ray);

/*
* true no caso de haver colisao em todos os metodos, false caso contrario.
*/

/**
* Determina se uma AABB esta colidindo contra outra AABB
*/
template <class Real> bool AABB_Against_AABB(const AABB3D<Real>& AABB_A,const AABB3D<Real>& AABB_B);

/**
* Determina se uma AABB esta colidindo contra uma esfera.
*/
template <class Real> bool AABB_Against_Sphere(const AABB3D<Real>& AABB,const SPHERE<Real>& Sphere);

/**
* Determina se uma AABB esta colidindo contra uma caixa orientada.
*/
template <class Real> bool AABB_Against_OBB(const AABB3D<Real>& AABB,const OBB3D<Real>& OBB);

/**
* Determina se uma AABB esta colidindo contra um triangulo
*/
template <class Real> bool AABB_Against_Triangle(const AABB3D<Real>& AABB,const TRIANGLE3D<Real>& Triangle);

#include "aabb_intersections.inl"

#endif
