/**
* Modulo de declaracao dos metodos responsaveis por query de intersecao entre esferas contra
* plano, raio, esferas,caixas, caixas alinhadas,triangulos...
*/

#ifndef __TRI3D_INTERSECTION_H__
#define __TRI3D_INTERSECTION_H__

#include "../../math_includes.h"
#include "../../queries/query_includes.h"
#include "../2d/segment_intersections.h"

/**
* Determina se uma esfera esta colidindo contra um plano.
* Retorna true se estiver colidindo , false caso contrario.
*/
template <class Real> bool Triangle_Against_Plane(const TRIANGLE3D<Real>& Triangle,const PLANE3<Real>& Plane);


/**
* Determina se uma esfera esta "dentro" do semi plano negativo do plano
*/
template <class Real> bool Triangle_Inside_Plane(const TRIANGLE3D<Real>& Triangle,const PLANE3<Real>& Plane);


/**
* Determina se uma esfera esta colidindo contra um raio
* Se houver colisao entao retorna a menor distancia, caso contrario retorna -1
*/
template<class Real> Real Triangle_Against_Ray(const TRIANGLE3D<Real>& Triangle,const RAY3D<Real>& Ray);

/*
* true no caso de haver colisao em todos os metodos, false caso contrario.
*/

/**
* Determina se uma esfera esta colidindo contra outra esfera
*/
template <class Real> bool Triangle_Against_Triangle(const TRIANGLE3D<Real>& Triangle_A,const TRIANGLE3D<Real>& Triangle_B);

/**
* Determina se uma esfera esta colidindo contra uma caixa alinhada.
*/
template <class Real> bool Triangle_Against_AABB(const TRIANGLE3D<Real>& Triangle,const AABB3D<Real>& AABB);

/**
* Determina se uma esfera esta colidindo contra uma caixa orientada.
*/
template <class Real> bool Triangle_Against_OBB(const TRIANGLE3D<Real>& Triangle,const OBB3D<Real>& OBB);

/**
* Determina se uma esfera esta colidindo contra um triangulo
*/
template <class Real> bool Triangle_Against_Sphere(const TRIANGLE3D<Real>& Triangle,const SPHERE<Real>& Sphere);

#include "triangle_intersections.inl"

#endif
