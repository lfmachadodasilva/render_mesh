/**
* Modulo de implementacao dos metodos da classe PLANE3
* @author Fabio Nakamura
*/


/**
* Construtores
* Vazio
*/
template <class Real> inline PLANE3<Real>::PLANE3(void)
{
}

/**
* Dado um vetor de uma constante
*/
template <class Real> inline PLANE3<Real>::PLANE3(const VECTOR3<Real>& Normal,Real Constant)
{
	this->Normal.Set(Normal);
	this->D = Constant;
}

template <class Real> inline PLANE3<Real>::PLANE3(Real A,Real B,Real C,Real D)
{
	this->Normal.Set(A,B,C);
	this->D = D;
}

template <class Real> inline PLANE3<Real>::PLANE3(const PLANE3& Plane)
{
	this->Normal.Set(Plane.Normal);
	this->D = Plane.D;
}

template <class Real> inline PLANE3<Real>::PLANE3(const VECTOR3<Real>& Normal,const VECTOR3<Real>& Point_in_Plane)
{
	// D = N.C onde C e um ponto no plano.
	this->Normal.Set(Normal);
	this->D = this->Normal.Dot(Point_in_Plane);
}

template <class Real> inline PLANE3<Real>::PLANE3(const VECTOR3<Real>& P0,const VECTOR3<Real>& P1,const VECTOR3<Real>& P2)
{
	VECTOR3<Real> P10(P1.x - P0.x,P1.y - P0.y,P1.z - P0.z);
	VECTOR3<Real> P20(P2.x - P0.x,P2.y - P0.y,P2.z - P0.z);

	this->Normal = P10.Unit_Cross(P20);
	this->D = this->Normal.Dot(P0);
}

/**
* Operador =
*/
template <class Real> inline PLANE3<Real>& PLANE3<Real>::operator = (const PLANE3<Real>& Plane)
{
	this->Normal.Set(Plane.Normal);
	this->D = Plane.D;
	return(*this);
}

template <class Real> inline int PLANE3<Real>::Which_Side(const VECTOR3<Real>& Point)const
{
	Real Distance = this->Normal.Dot(Point) - this->D;

	if(Distance < (Real)0.0)
		return(-1);
	else if(Distance > (Real)0.0)
		return(1);
	else
		return(0);
}

template <class Real> inline Real PLANE3<Real>::Distance_To(const VECTOR3<Real>& Point)const
{
	return(this->Normal.Dot(Point) - this->D);
}

template <class Real> inline
void PLANE3<Real>::Build_Plane(const VECTOR3<Real>& V0,const VECTOR3<Real>& V1,const VECTOR3<Real>& V2)
{
	VECTOR3<Real> P10(V1.x - V0.x,V1.y - V0.y,V1.z - V0.z);
	VECTOR3<Real> P20(V2.x - V0.x,V2.y - V0.y,V2.z - V0.z);

	this->Normal = P10.Unit_Cross(P20);
	this->D = this->Normal.Dot(V0);
	return;
}

		







