/**
* Modulo de implementacao dos metodos inline da classe RAY3D
*/

template <class Real> inline RAY3D<Real>::RAY3D(void)
{
}

template <class Real> inline RAY3D<Real>::RAY3D(const VECTOR3<Real>& Origin,const VECTOR3<Real>& Direction)
{
	this->Origin.Set(Origin);
	this->Direction.Set(Direction);
}

template <class Real> inline VECTOR3<Real> RAY3D<Real>::Get_Origin(void)const
{
	return(this->Origin);
}

template <class Real> inline void RAY3D<Real>::Set_New_Origin(const VECTOR3<Real>& Origin)
{
	this->Origin.Set(Origin);
	return;
}

template <class Real> inline VECTOR3<Real> RAY3D<Real>::Get_Direction(void)const
{
	return(this->Direction);
}

template <class Real> inline void RAY3D<Real>::Set_New_Direction(const VECTOR3<Real>& Direction)
{
	this->Direction.Set(Direction);
	return;
}
