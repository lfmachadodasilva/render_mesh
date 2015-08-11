/**
* Modulo de implementacao dos metodos inline da classe TRIANGLE3D
*/


/**
* Construtores
*/
template <class Real> inline TRIANGLE3D<Real>::TRIANGLE3D(void)
{
}


template <class Real> inline TRIANGLE3D<Real>::TRIANGLE3D(const VECTOR3<Real>& v1,const VECTOR3<Real>& v2,const VECTOR3<Real>& v3):
V1(v1),V2(v2),V3(v3)
{	
}

template <class Real> inline TRIANGLE3D<Real>::TRIANGLE3D(const VECTOR3<Real>* Vertex ):
V1(Vertex[0]),V2(Vertex[1]),V3(Vertex[2])
{
}

template <class Real> inline TRIANGLE3D<Real>::TRIANGLE3D(const Real* Vertex ):
V1(&Vertex[0]),V2(&Vertex[3]),V3(&Vertex[6])
{	
}


template <class Real> inline VECTOR3<Real> TRIANGLE3D<Real>::Get_Unit_Normal(void)const
{
	VECTOR3<Real>Ed0(this->V2.x - V1.x,
					 this->V2.y - V1.y,
					 this->V2.z - V1.z);

	VECTOR3<Real>Ed1(this->V3.x - V1.x,
					 this->V3.y - V1.y,
					 this->V3.z - V1.z);

	return(VECTOR3<Real>(Ed0.Unit_Cross(Ed1)));
}

template <class Real> inline VECTOR3<Real> TRIANGLE3D<Real>::Get_Normal(void)const
{
	VECTOR3<Real>Ed0(this->V2.x - V1.x,
					 this->V2.y - V1.y,
					 this->V2.z - V1.z);

	VECTOR3<Real>Ed1(this->V3.x - V1.x,
					 this->V3.y - V1.y,
					 this->V3.z - V1.z);
	return(VECTOR3<Real>(Ed0.Cross(Ed1)));
}

template <class Real> inline void TRIANGLE3D<Real>::Set_Triangle(const VECTOR3<Real>& v1,const VECTOR3<Real>& v2,const VECTOR3<Real>& v3)
{
	this->V1.Set(v1);
	this->V2.Set(v2);
	this->V3.Set(v3);
	return;
}

template <class Real> inline void TRIANGLE3D<Real>::Set_Triangle(const TRIANGLE3D<Real>& Triangle)
{
	this->V1.Set(Triangle.V1);
	this->V2.Set(Triangle.V2);
	this->V3.Set(Triangle.V3);
	return;
}

template <class Real> inline bool TRIANGLE3D<Real>::Is_Colinear(void)
{
	VECTOR3<float> A,B;

	A.Set(this->V2.x - this->V1.x,
		  this->V2.y - this->V1.y,
		  this->V2.z - this->V1.z);

	B.Set(this->V3.x - this->V1.x,
		  this->V3.y - this->V1.y,
		  this->V3.z - this->V1.z);

	VECTOR3<float> Cross = A.Cross(B);

	if(fabs(Cross.x) < EPSILON &&
	   fabs(Cross.y) < EPSILON &&
	   fabs(Cross.z) < EPSILON)
	   return(true);
	else
		return(false);
}

template <class Real> inline Real TRIANGLE3D<Real>::Area(void)
{
	VECTOR3<float> A,B;

	A.Set(this->V2.x - this->V1.x,
		  this->V2.y - this->V1.y,
		  this->V2.z - this->V1.z);

	B.Set(this->V3.x - this->V1.x,
		  this->V3.y - this->V1.y,
		  this->V3.z - this->V1.z);

	VECTOR3<float> Cross = A.Cross(B);

	Real Area = Cross.Norma();
	return(Area*(Real)0.5);
}

	

