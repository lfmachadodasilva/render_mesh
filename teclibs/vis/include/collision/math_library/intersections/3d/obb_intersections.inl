/**
* Modulo de implementacao dos metodos de colisao de OBB contra
* outras primitivas
*/

template <class Real> inline bool OBB_Against_Plane(const OBB3D<Real>& OBB,const PLANE3<Real>& Plane)
{

	Real t1 = OBB.i_Length*fabs(OBB.Axis_i.Dot(Plane.Normal));
	Real t2 = OBB.j_Length*fabs(OBB.Axis_j.Dot(Plane.Normal));
	Real t3 = OBB.k_Length*fabs(OBB.Axis_k.Dot(Plane.Normal));	
	Real R = t1 + t2 + t3;			 
	Real S = Plane.Normal.Dot(OBB.Center) - Plane.D;

	return( fabs(S) <= R);	
}

template <class Real> inline bool OBB_Inside_Plane(const OBB3D<Real>& OBB,const PLANE3<Real>& Plane)
{
	Real t1 = OBB.i_Length*fabs(OBB.Axis_i.Dot(Plane.Normal));
	Real t2 = OBB.j_Length*fabs(OBB.Axis_j.Dot(Plane.Normal));
	Real t3 = OBB.k_Length*fabs(OBB.Axis_k.Dot(Plane.Normal));	
	Real R = t1 + t2 + t3;	
	Real S = Plane.Normal.Dot(OBB.Center) - Plane.D;

	return( S <= -R);	
}


template <class Real> int OBB_Which_Side_Plane(const OBB3D<Real>& OBB,const PLANE3<Real>& Plane)
{
	Real t1 = OBB.i_Length*fabs(OBB.Axis_i.Dot(Plane.Normal));
	Real t2 = OBB.j_Length*fabs(OBB.Axis_j.Dot(Plane.Normal));
	Real t3 = OBB.k_Length*fabs(OBB.Axis_k.Dot(Plane.Normal));	
	Real R = t1 + t2 + t3;	

	Real S = Plane.Normal.Dot(OBB.Center) - Plane.D;
	if( S <= -R)
		return(-1);
	else if( S > R)
		return(1);
	else
		return(0);
	
}

template <class Real> inline bool OBB_Against_Sphere(const OBB3D<Real>& OBB,const SPHERE<Real>& Sphere)
{
	VECTOR3<Real> P = Closest_Point_OBB3D(Sphere.Center,OBB);

	VECTOR3<Real> Dist(P.x - Sphere.Center.x,
					   P.y - Sphere.Center.y,
					   P.z - Sphere.Center.z);

	return(Dist.Square_Norma() <= Sphere.Radius*Sphere.Radius);
}



