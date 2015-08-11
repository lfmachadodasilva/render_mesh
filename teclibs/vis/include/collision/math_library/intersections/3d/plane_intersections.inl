
template <class Real> bool Plane_Against_Plane(const PLANE3<Real>& Plane_A,const PLANE3<Real>& Plane_B)
{
	VECTOR3<Real> D = Plane_A.Normal.Cross(Plane_B.Normal); // Direction
	Real Denom = D.Square_Norma();

	if( Denom < EPSILON)
		return(false);

	/**
	Linha de intersecao
	P = Cross(Plane_A.D*Plane_B.Normal - Plane_B.D*Plane_A.Normal,D);
	*/
	return(true);
}


template <class Real> Real Plane_Against_Ray(const PLANE3<Real>& Plane,const RAY3D<Real>& Ray)
{
	Real A = Plane.Normal.Dot(Ray.Direction);

	if( A == (Real)0.0) // raio paralelo ao plano
		return((Real)-1.0);

	Real B = -(Plane.Normal.Dot(Ray.Origin) + Plane.D);
	Real t = B/A;

	if(t < (Real)0.0)
		return((Real)-1.0);
	else
		return(t);
}


