/**
* Modulo de implementacao dos metodos de colisao de esfera contra
* outras primitivas
*/

template <class Real> inline bool Sphere_Against_Plane(const SPHERE<Real>& Sphere,const PLANE3<Real>& Plane)
{
	Real Dist = Sphere.Center.Dot(Plane.Normal) - Plane.D;
	return(fabs(Dist) <= Sphere.Radius);
}

template <class Real> inline bool Sphere_Inside_Plane(const SPHERE<Real>& Sphere,const PLANE3<Real>& Plane)
{
	Real Dist = Sphere.Center.Dot(Plane.Normal) - Plane.D;
	return( Dist <= -Sphere.Radius);
}


template <class Real> inline int Sphere_Which_Side_Plane(const SPHERE<Real>& Sphere,const PLANE3<Real>& Plane)
{
	Real Dist = Sphere.Center.Dot(Plane.Normal) - Plane.D;
	if(Dist <= -Sphere.Radius)
		return(-1);
	else if(Dist > Sphere.Radius)
		return(1);
	else
		return(0);
}

template <class Real> inline bool Sphere_Against_Sphere(const SPHERE<Real>& Sphere_A,const SPHERE<Real>& Sphere_B)
{
	// Diferenca dos raios
	VECTOR3<Real> Center_Diff(Sphere_A.Center.x - Sphere_B.Center.x,
							  Sphere_A.Center.y - Sphere_B.Center.y,
							  Sphere_A.Center.z - Sphere_B.Center.z);

	
	// soma dos raios ao quadrado
	Real Sqr_Radius = (Sphere_A.Radius+Sphere_B.Radius) * (Sphere_A.Radius+Sphere_B.Radius);

	return((Center_Diff.Square_Norma() < Sqr_Radius));
}

template <class Real> inline bool Sphere_Against_AABB(const SPHERE<Real>& Sphere,const AABB3D<Real>& AABB)
{
	Real Sqr_Dist =  Square_Distance_Point_AABB3D<Real>(Sphere.Center,AABB);
	return(Sqr_Dist < (Sphere.Radius*Sphere.Radius));
}

template <class Real> inline bool Sphere_Against_OBB(const SPHERE<Real>& Sphere,const OBB3D<Real>& OBB)
{

	VECTOR3<Real> P = Closest_Point_OBB3D(Sphere.Center,OBB);

	VECTOR3<Real> Dist(P.x - Sphere.Center.x,
					   P.y - Sphere.Center.y,
					   P.z - Sphere.Center.z);

	return(Dist.Square_Norma() <= Sphere.Radius*Sphere.Radius);
}

template <class Real> inline bool Sphere_Against_Triangle(const SPHERE<Real>& Sphere,const TRIANGLE3D<Real>& Triangle)
{
	VECTOR3<Real> P = Closest_Point_In_Triangle3D(Sphere.Center,Triangle);

	VECTOR3<Real> Dist(P.x - Sphere.Center.x,
					   P.y - Sphere.Center.y,
					   P.z - Sphere.Center.z);

	return(Dist.Square_Norma() <= Sphere.Radius*Sphere.Radius);
}


template <class Real> inline Real Sphere_Against_Ray(const SPHERE<Real>& Sphere,const RAY3D<Real>& Ray)
{
	VECTOR3<Real> L (Sphere.Center.x - Ray.Origin.x,
					 Sphere.Center.y - Ray.Origin.y,
					 Sphere.Center.z - Ray.Origin.z);

	Real s = L.Dot(Ray.Direction);
	Real L_Sqr = L.Square_Norma();
	Real Radius_Sqr = Sphere.Radius*Sphere.Radius;

	if( s < (Real)0.0 && L_Sqr > Radius_Sqr)
		return((Real)-1.0);

	Real m_Sqr = L_Sqr - s*s;
	if( m_Sqr > Radius_Sqr)
		return((Real)-1.0);
	
	Real q = sqrt( (Radius_Sqr - m_Sqr));
	Real t;
	if( L_Sqr > Radius_Sqr)
		t = s - q;
	else
		t = s + q;

	return(t);
}

