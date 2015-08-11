#include "aabb_intersections.h"
#include "obb_intersections.h"
#include "sphere_intersections.h"

/**
* Modulo de implementacao dos metodos de query de intersecao de triangulo,
* contra outras primitivas..
*/

template <class Real> inline bool Triangle_Inside_Plane(const TRIANGLE3D<Real>& Triangle,const PLANE3<Real>& Plane)
{
	Real dot1,dot2,dot3;
	dot1 = Plane.Normal.Dot(Triangle.V1) - Plane.D;
	dot2 = Plane.Normal.Dot(Triangle.V2) - Plane.D;
	dot3 = Plane.Normal.Dot(Triangle.V3) - Plane.D;

	if( (dot1 < ((Real)0.0)) && (dot2 < ((Real)0.0)) && (dot3 < ((Real)0.0)))
		return(true);
	
	return(false);
}

/**
* Determina se uma esfera esta colidindo contra uma caixa alinhada.
*/
template <class Real> inline bool Triangle_Against_AABB(const TRIANGLE3D<Real>& Triangle,const AABB3D<Real>& AABB)
{
	return(AABB_Against_Triangle<Real>(AABB,Triangle));
}

/**
* Determina se uma esfera esta colidindo contra uma caixa orientada.
*/
template <class Real> inline bool Triangle_Against_OBB(const TRIANGLE3D<Real>& Triangle,const OBB3D<Real>& OBB)
{
	return(OBB_Against_Triangle<Real>(OBB,Triangle));
}

/**
* Determina se uma esfera esta colidindo contra um triangulo
*/
template <class Real> inline bool Triangle_Against_Sphere(const TRIANGLE3D<Real>& Triangle,const SPHERE<Real>& Sphere)
{
	return(Sphere_Against_Triangle<Real>(Sphere,Triangle));
}

