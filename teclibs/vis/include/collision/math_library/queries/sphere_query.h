/**
* Modulo de declaracao dos metodos que fazem query de distancia entre pontos e esferas
*/

#ifndef __SPHERE_QUERY_H__
#define __SPHERE_QUERY_H__

#include "../math_includes.h"

template <class Real> VECTOR3<Real> Closest_Point_In_SPHERE(const VECTOR3<Real>& Point,const SPHERE<Real>& Sphere);
template <class Real> bool Point_In_Sphere(const VECTOR3<Real>& Point,const SPHERE<Real>& Sphere);
/**
* Determina o ponto mais proximo da esfera ao ponto dado P
*/
template <class Real> VECTOR3<Real> Closest_Point_In_SPHERE(const VECTOR3<Real>& Point,const SPHERE<Real>& Sphere)
{
	VECTOR3<Real> Direction(Point.x - Sphere.Center.x,
							Point.y - Sphere.Center.y,
							Point.z - Sphere.Center.z);

	Direction.Normalize();

	return(VECTOR3<Real>(Sphere.Radius*Direction.x,
						 Sphere.Radius*Direction.y,
						 Sphere.Radius*Direction.z));
}


/**
* Determina se o ponto esta na esfera 
*/
template <class Real> bool Point_In_Sphere(const VECTOR3<Real>& Point,const SPHERE<Real>& Sphere)
{
	
	VECTOR3<Real> Dist(Point.x - Sphere.Center.x,
					   Point.y - Sphere.Center.y,
					   Point.z - Sphere.Center.z);

	Real Dist_Sqr = Dist.Square_Norma();
	if(Dist_Sqr > Sphere.Radius*Sphere.Radius)
		return(false);
	else
		return(true);
}
#endif
