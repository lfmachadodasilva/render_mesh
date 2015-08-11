/**
* Modulo de implementacao dos metodos inline da classe SPHERE
*/


/**
* Construtor
*/

/**
* Vazio
*/
template <class Real> inline SPHERE<Real>::SPHERE(void)
{
}

template <class Real> inline SPHERE<Real>::SPHERE(const VECTOR3<Real>& Center,const Real Radius)
{
	this->Center.Set(Center);
	this->Radius = Radius;
}

template <class Real> inline SPHERE<Real>::SPHERE(const SPHERE<Real>& Sphere)
{
	this->Center.Set(Sphere.Center);
	this->Radius = Sphere.Radius;
}

template <class Real> inline SPHERE<Real>::SPHERE(const Real* Center,const Real Radius)
{
	this->Center.Set(Center);
	this->Radius = Radius;
}


template <class Real> inline SPHERE<Real>::SPHERE(const Real Center_x,const Real Center_y,const Real Center_z,const Real Radius)
{
	this->Center.Set(Center_x,Center_y,Center_z);
	this->Radius = Radius;
}

/**
* Metodos get / set 
*/

template <class Real> inline void SPHERE<Real>::Set_New_Radius(const Real New_Radius)
{
	this->Radius = New_Radius;
	return;
}

template <class Real> inline void SPHERE<Real>::Set_New_Center(const VECTOR3<Real>& New_Center)
{
	this->Center.Set(New_Center);
	return;
}

template <class Real> inline void SPHERE<Real>::Set_New_Center(const Real* New_Center)
{
	this->Center.Set(New_Center);
	return;
}

template <class Real> inline void SPHERE<Real>::Set_New_Center(const Real New_Center_x,const Real New_Center_y,const Real New_Center_z)
{
	this->Center.Set(New_Center_x,New_Center_y,New_Center_z);
	return;
}

