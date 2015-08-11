/**
* Modulo de declaracao dos metodos responsaveis por query de intersecao entre OBBBs contra
* plano, raio, esferas,caixas, caixas alinhadas,triangulos...
*/

#ifndef __OBB_INTERSECTION_H__
#define __OBB_INTERSECTION_H__

#include "../../math_includes.h"
#include "../../queries/query_includes.h"

/**
* Determina se uma OBB esta colidindo contra um plano.
* Retorna true se estiver colidindo , false caso contrario.
*/
template <class Real> bool OBB_Against_Plane(const OBB3D<Real>& OBB,const PLANE3<Real>& Plane);


/**
* Determina se uma OBB esta "dentro" do semi plano negativo do plano. TODO
*/
template <class Real> bool OBB_Inside_Plane(const OBB3D<Real>& OBB,const PLANE3<Real>& Plane);

/**
* Determina se esfera esta a esquerda do plano, a direita do plano ou colidindo com o plano
* -1 se esquerda, 0 se colidindo e 1 se a direita
*/
template <class Real> int OBB_Which_Side_Plane(const OBB3D<Real>& OBB,const PLANE3<Real>& Plane);


/**
* Determina se uma OBB esta colidindo contra um raio
* Se houver colisao entao retorna a menor distancia, caso contrario retorna -1
*/
template<class Real> Real OBB_Against_Ray(const OBB3D<Real>& OBB,const RAY3D<Real>& Ray);

/*
* true no caso de haver colisao em todos os metodos, false caso contrario.
*/

/**
* Determina se uma OBB esta colidindo contra outra OBB
*/
template <class Real> bool OBB_Against_OBB(const OBB3D<Real>& OBB_A,const OBB3D<Real>& OBB_B);

/**
* Determina se uma OBB esta colidindo contra uma esfera.
*/
template <class Real> bool OBB_Against_Sphere(const OBB3D<Real>& OBB,const SPHERE<Real>& Sphere);

/**
* Determina se uma OBB esta colidindo contra uma caixa orientada.
*/
template <class Real> bool OBB_Against_AABB(const OBB3D<Real>& OBB,const AABB3D<Real>& AABB);

/**
* Determina se uma OBB esta colidindo contra um triangulo
*/
template <class Real> bool OBB_Against_Triangle(const OBB3D<Real>& OBB,const TRIANGLE3D<Real>& Triangle);


#include "obb_intersections.inl"

#endif
