/**
* Modulo de implementacao dos metodos da classe VECTOR3
* @author Fabio Nakamura
*/

/**
* Construtores
*/

template <class Real> inline VECTOR3<Real>::VECTOR3()
{	
}

template <class Real> inline VECTOR3<Real>::VECTOR3(const Real* Vector)
{	
	this->x = Vector[0];
	this->y = Vector[1];
	this->z = Vector[2];
}

template <class Real> inline VECTOR3<Real>::VECTOR3(Real* Vector)
{
	this->x = Vector[0];
	this->y = Vector[1];
	this->z = Vector[2];
}

template <class Real> inline VECTOR3<Real>::VECTOR3(const Real X,const Real Y,const Real Z)
{
	this->x = X;
	this->y = Y;
	this->z = Z;
}

template <class Real> inline VECTOR3<Real>::VECTOR3(const VECTOR3& Vector)
{
	this->x = Vector.x;
	this->y = Vector.y;
	this->z = Vector.z;
}


template <class Real> inline VECTOR3<Real>::operator const Real*(void)const
{
	return((Real*)this);
}

template <class Real> inline VECTOR3<Real>::operator Real*(void)
{
	return((Real*)this);
}

template <class Real> inline VECTOR3<Real>& VECTOR3<Real>::operator = (const VECTOR3<Real>& Vector)
{
	this->x = Vector.x;
	this->y = Vector.y;
	this->z = Vector.z;
	return(*this);
}


/**
* Operadores de comparacao
*/

template <class Real> inline bool VECTOR3<Real>::operator == (const VECTOR3& Vector)const
{
	return(!( fabs(this->x - Vector.x) > EPSILON || 
		      fabs(this->y - Vector.y) > EPSILON ||
			  fabs(this->z - Vector.z) > EPSILON ) );	
}

template <class Real> inline bool VECTOR3<Real>::operator != (const VECTOR3& Vector)const
{
	return( ( fabs(this->x - Vector.x) > EPSILON || 
		      fabs(this->y - Vector.y) > EPSILON ||
			  fabs(this->z - Vector.z) > EPSILON ) );	
}


/**
* Operadores Aritmeticos
*/

template <class Real> inline VECTOR3<Real> VECTOR3<Real>::operator + (const VECTOR3& Vector)const
{
	return(VECTOR3(this->x + Vector.x,this->y + Vector.y,this->z + Vector.z));
}

template <class Real> inline VECTOR3<Real> VECTOR3<Real>::operator - (const VECTOR3& Vector)const
{
	return(VECTOR3(this->x - Vector.x,this->y - Vector.y,this->z - Vector.z));
}

template <class Real> inline VECTOR3<Real> VECTOR3<Real>::operator * (const Real Scalar)const
{
	return(VECTOR3(this->x * Scalar,this->y * Scalar,this->z * Scalar));
}

template <class Real> inline VECTOR3<Real> VECTOR3<Real>::operator / (const Real Scalar)const
{
	if(Scalar > EPSILON)
	{
		float Inv_Scalar = 1.0f / Scalar;
		return(VECTOR3(this->x * Inv_Scalar,this->y * Inv_Scalar,this->z * Inv_Scalar));
	}
	else
		return(VECTOR3(_INFINITE,_INFINITE,_INFINITE));
}

/**
* Operadores de Atualizacao matematico
*/

template <class Real> inline VECTOR3<Real>& VECTOR3<Real>::operator += (const VECTOR3& Vector)
{
	this->x += Vector.x;
	this->y += Vector.y;
	this->z += Vector.z;
	return(*this);
}

template <class Real> inline VECTOR3<Real>& VECTOR3<Real>::operator -= (const VECTOR3& Vector)
{
	this->x -= Vector.x;
	this->y -= Vector.y;
	this->z -= Vector.z;
	return(*this);
}

template <class Real> inline VECTOR3<Real>& VECTOR3<Real>::operator *= (const Real Scalar)
{
	this->x *= Scalar;
	this->y *= Scalar;
	this->z *= Scalar;
	return(*this);
}

template <class Real> inline VECTOR3<Real>& VECTOR3<Real>::operator /= (const Real Scalar)
{
	if(Scalar > EPSILON)
	{
		float Inv_Scalar = 1.0f/Scalar;
		this->x *= Inv_Scalar;
		this->y *= Inv_Scalar;
		this->z *= Inv_Scalar;
	}
	else
	{
		this->x = _INFINITE;
		this->y = _INFINITE;
		this->z = _INFINITE;
	}
	return(*this);
}

template <class Real> inline VECTOR3<Real> VECTOR3<Real>::operator -(void)const
{
	return(VECTOR3(-this->x,-this->y,-this->z));
}


/**
* Operacoes de Algebra Linear
*/

template <class Real> inline Real VECTOR3<Real>::Norma(void)const
{
	return( sqrt((this->x*this->x + this->y*this->y + this->z*this->z)));
}

template <class Real> inline Real VECTOR3<Real>::Square_Norma(void)const
{
	return((this->x*this->x + this->y*this->y + this->z*this->z));
}

template <class Real> inline Real VECTOR3<Real>::Normalize(void)
{
	Real Norma = this->Norma();

	if(Norma > EPSILON)
	{
		Real Inv_Norma = 1.0f / Norma;
		this->x *= Inv_Norma;
		this->y *= Inv_Norma;
		this->z *= Inv_Norma;
		return(Norma);
	}
	return(Norma);
}

template <class Real> inline VECTOR3<Real> VECTOR3<Real>::Get_Normalize(void)const
{
	VECTOR3<Real> Temp(*this);
	Temp.Normalize();
	return(VECTOR3<Real>(Temp));
}


template <class Real> inline Real VECTOR3<Real>::Dot(const VECTOR3& Vector)const
{
	return((this->x*Vector.x + this->y*Vector.y + this->z*Vector.z));
}

template <class Real> inline VECTOR3<Real> VECTOR3<Real>::Cross(const VECTOR3& Vector)const
{
	return( VECTOR3(this->y*Vector.z - this->z*Vector.y,this->z*Vector.x - this->x*Vector.z,
		this->x*Vector.y - this->y*Vector.x));
}

template <class Real> inline VECTOR3<Real> VECTOR3<Real>::Unit_Cross(const VECTOR3& Vector)const
{
	 VECTOR3 Cross(this->y*Vector.z - this->z*Vector.y,this->z*Vector.x - this->x*Vector.z,
		this->x*Vector.y - this->y*Vector.x);
	 
	 Cross.Normalize();
	 return(Cross);
}

/**
* Operadores de Atribuicao
*/

template <class Real> inline void VECTOR3<Real>::Set(const Real X,const Real Y,const Real Z)
{
	this->x = X;
	this->y = Y;
	this->z = Z;
	return;
}

template <class Real> inline void VECTOR3<Real>::Set(const VECTOR3& Vector)
{
	this->x = Vector.x;
	this->y = Vector.y;
	this->z = Vector.z;
	return;
}

template <class Real> inline void VECTOR3<Real>::Set(const Real* Vector)
{
	this->x = Vector[0];
	this->y = Vector[1];
	this->z = Vector[2];
	return;
}

template <class Real> inline void VECTOR3<Real>::Set(Real* Vector)
{
	this->x = Vector[0];
	this->y = Vector[1];
	this->z = Vector[2];
	return;
}

template<class Real>
inline void VECTOR3<Real>::Create_Orthonormal_Basis(const VECTOR3<Real>& N,VECTOR3<Real>& U,VECTOR3<Real>& V)
{
	Real Inv_Lenght;
	if( fabs(N.x) >= fabs(N.y))
	{
		Inv_Lenght = (Real)1.0 / (N.x*N.x + N.z*N.z);
		U.x = -N.z*Inv_Lenght;
		U.y = (Real)0.0;
		U.z = N.x*Inv_Lenght;
	}
	else
	{
		Inv_Lenght = (Real)1.0 / (N.y*N.y + N.z*N.z);
		U.x = (Real)0.0;
		U.y = N.z*Inv_Lenght;
		U.z = -N.y*Inv_Lenght;
	}
	V = N.Cross(U);
	return;
}
