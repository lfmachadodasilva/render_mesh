/**
* Funcoes de query de distancia entre ponto e plano.
*/

#ifndef __PLANE_QUERY_H__
#define __PLANE_QUERY_H__

#include "../math_includes.h"

template <class Real> VECTOR3<Real> Closest_Point_From_Plane(const VECTOR3<Real>& Point,const PLANE3<Real>& Plane);
template <class Real> Real Distance_From_Plane(const VECTOR3<Real>& Point,const PLANE3<Real>& Plane);


/*
* Dado um ponto 3d e um plano , determina o ponto mais proximo deste plano do ponto P
*/
template <class Real> VECTOR3<Real> Closest_Point_From_Plane(const VECTOR3<Real>& Point,const PLANE3<Real>& Plane)
{
	Real T = Plane.Normal.Dot(Point) - Plane.D;
	return(VECTOR3<Real>(Point.x - T*Plane.Normal.x,
						 Point.y - T*Plane.Normal.y,
						 Point.z - T*Plane.Normal.z));
}

/**
* Retorna a distancia do ponto P a um plano 
*/
template <class Real> Real Distance_From_Plane(const VECTOR3<Real>& Point,const PLANE3<Real>& Plane)
{
	return(Plane.Distance_To(Point));
}

#endif
