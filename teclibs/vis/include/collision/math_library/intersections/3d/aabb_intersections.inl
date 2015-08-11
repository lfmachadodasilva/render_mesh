/**
* Modulo de implementacao dos metodos de colisao de AABB contra
* outras primitivas
*/

template <class Real> inline bool AABB_Against_Plane(const AABB3D<Real>& AABB,const PLANE3<Real>& Plane)
{
	VECTOR3<Real> Center = AABB.Get_Center();
	VECTOR3<Real> Ext;
	AABB.Get_Extensions(Ext);

	Real t1 = Ext.x*fabs(Plane.Normal.x);
	Real t2 = Ext.y*fabs(Plane.Normal.y);
	Real t3 = Ext.z*fabs(Plane.Normal.z);

	Real R = t1 + t2 + t3;
	Real S = Plane.Normal.Dot(Center) - Plane.D;
	return(fabs(S) <= R);
}

template <class Real> inline bool AABB_Inside_Plane(const AABB3D<Real>& AABB,const PLANE3<Real>& Plane)
{
	VECTOR3<Real> Ext;
	VECTOR3<Real> Center = AABB.Get_Center();
	AABB.Get_Extensions(Ext);

	Real t1 = Ext.x*fabs(Plane.Normal.x);
	Real t2 = Ext.y*fabs(Plane.Normal.y);
	Real t3 = Ext.z*fabs(Plane.Normal.z);

	Real R = t1 + t2 + t3;

	Real S = Plane.Normal.Dot(Center) - Plane.D;

	return( S < -R);	
}


template <class Real> inline int AABB_Which_Side_Plane(const AABB3D<Real>& AABB,const PLANE3<Real>& Plane)
{
	VECTOR3<Real> Ext;
	VECTOR3<Real> Center = AABB.Get_Center();
	AABB.Get_Extensions(Ext);

	Real t1 = Ext.x*fabs(Plane.Normal.x);
	Real t2 = Ext.y*fabs(Plane.Normal.y);
	Real t3 = Ext.z*fabs(Plane.Normal.z);

	Real R = t1 + t2 + t3;

	Real S = Plane.Normal.Dot(Center) - Plane.D;
	if( S <= -R)
		return(-1);
	else if(S > R)
		return(1);
	else
		return(0);
}


template <class Real> inline bool AABB_Against_AABB(const AABB3D<Real>& AABB_A,const AABB3D<Real>& AABB_B)
{
	/**
	* Eixo 1,0,0
	*/
	if(AABB_A.Min_Point.x > AABB_B.Max_Point.x || AABB_B.Min_Point.x > AABB_A.Max_Point.x)
		return(false);

	/**
	* Eixo 0,1,0
	*/
	if(AABB_A.Min_Point.y > AABB_B.Max_Point.y || AABB_B.Min_Point.y > AABB_A.Max_Point.y)
		return(false);

	/**
	* Eixo 0,0,1
	*/
	if(AABB_A.Min_Point.z > AABB_B.Max_Point.z || AABB_B.Min_Point.z > AABB_A.Max_Point.z)
		return(false);

	return(true);
}

template <class Real> inline bool AABB_Against_Sphere(const AABB3D<Real>& AABB,const SPHERE<Real>& Sphere)
{
	Real Sqr_Dist =  Square_Distance_Point_AABB3D<Real>(Sphere.Center,AABB);
	return(Sqr_Dist < (Sphere.Radius*Sphere.Radius));
}



