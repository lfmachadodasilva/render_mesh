/**
* Modulo de implementacao dos metodos inline da classe VECTOR2
*/

/**
* Construtores
*/
template <class Real> inline VECTOR2<Real>::VECTOR2(const Real X,const Real Y)
{
	this->x = X;
	this->y = Y;
}

template <class Real> inline VECTOR2<Real>::VECTOR2(void)
{	
}

template <class Real> inline VECTOR2<Real>::VECTOR2(const Real* Vector)
{
	this->x = Vector[0];
	this->y = Vector[1];
}

template <class Real> inline VECTOR2<Real>::VECTOR2(const VECTOR2<Real>& Vector)
{
	this->x = Vector.x;
	this->y = Vector.y;
}


template <class Real> inline VECTOR2<Real>::operator const Real*(void)const
{
	return((Real*)this);
}

template <class Real> inline VECTOR2<Real>::operator Real*(void)
{
	return((Real*)this);
}

template <class Real> inline VECTOR2<Real>& VECTOR2<Real>::operator = (const VECTOR2<Real>& Vector)
{
	this->x = Vector.x;
	this->y = Vector.y;
	return(*this);
}

/**
* Operadores Aritmeticos
*/

template <class Real> inline VECTOR2<Real> VECTOR2<Real>::operator + (const VECTOR2<Real>& Vector)const
{
	return(VECTOR2<Real>(this->x + Vector.x,this->y + Vector.y));
}

template <class Real> inline VECTOR2<Real> VECTOR2<Real>::operator - (const VECTOR2<Real>& Vector)const
{
	return(VECTOR2<Real>(this->x - Vector.x,this->y - Vector.y));
}

template <class Real> inline VECTOR2<Real> VECTOR2<Real>::operator * (const Real Scalar)const
{
	return(VECTOR2<Real>(this->x*Scalar,this->y*Scalar));
}

template <class Real> inline VECTOR2<Real> VECTOR2<Real>::operator / (const Real Scalar)const
{
	if(Scalar > EPSILON)
	{
		Real Inv_Scalar = 1.0f/ Scalar;
		return(VECTOR2<Real>(this->x * Inv_Scalar,this->y * Inv_Scalar));
	}
	else
		return(VECTOR2<Real>(_INFINITE,_INFINITE));
}

template <class Real> inline VECTOR2<Real> VECTOR2<Real>::operator - (void) const
{
	return(VECTOR2<Real>(-this->x,-this->y));
}

/**
* Operadores de atualizacao
*/
template <class Real> inline VECTOR2<Real>& VECTOR2<Real>::operator += (const VECTOR2<Real>& Vector)
{
	this->x += Vector.x;
	this->y += Vector.y;
	return(*this);
}

template <class Real> inline VECTOR2<Real>& VECTOR2<Real>::operator -= (const VECTOR2<Real>& Vector)
{
	this->x -= Vector.x;
	this->y -= Vector.y;
	return(*this);
}

template <class Real> inline VECTOR2<Real>& VECTOR2<Real>::operator *= (const Real Scalar)
{
	this->x *= Scalar;
	this->y *= Scalar;
	return(*this);
}

template <class Real> inline VECTOR2<Real>& VECTOR2<Real>::operator /= (const Real Scalar)
{
	if(Scalar > EPSILON)
	{
		Real Inv_Scalar = 1.0f / Scalar;
		this->x *= Inv_Scalar;
		this->y *= Inv_Scalar;
	}
	else
	{
		this->x = _INFINITE;
		this->y = _INFINITE;
	}
    return(*this);
}

/**
* Operacoes Logicas
*/

template <class Real> inline bool VECTOR2<Real>::operator == (const VECTOR2<Real>& Vector)const
{
	return(!( fabs((Real)(this->x - Vector.x)) > EPSILON || fabs((Real)(this->y - Vector.y)) > EPSILON ));	
}

template <class Real> inline bool VECTOR2<Real>::operator != (const VECTOR2<Real>& Vector)const
{
	return(( fabs((Real)(this->x - Vector.x)) > EPSILON || fabs((Real)(this->y - Vector.y)) > EPSILON ));	
}


/**
* Operadores vetoriais
*/
template <class Real> inline Real VECTOR2<Real>::Norma(void)const
{
	return((Real)sqrtf((float)((this->x*this->x) + (this->y*this->y))));
}

template <class Real> inline Real VECTOR2<Real>::Square_Norma(void)const
{
	return((this->x*this->x) + (this->y*this->y));
}

template <class Real> inline Real VECTOR2<Real>::Dot(const VECTOR2<Real>& Vector)const
{
	return(this->x * Vector.x + this->y + Vector.y);
}

template <class Real> inline Real VECTOR2<Real>::Normalize(void)
{
	Real Length = this->Norma();

	if(Length > EPSILON)
	{
		Real Inv_Lenght = 1.0f / Length;
		this->x *= Inv_Lenght;
		this->y *= Inv_Lenght;
		return(Length);
	}
	return(Length);
}

template <class Real> inline VECTOR2<Real> VECTOR2<Real>::Get_Normalize(void)const
{
	VECTOR2<Real> Temp(this->x,this->y);
	Temp.Normalize();
	return(Temp);
}

template <class Real> inline VECTOR2<Real> VECTOR2<Real>::Get_Perpendicular(void)const
{
	return(VECTOR2<Real>(-this->y,this->x));
}

template <class Real> inline VECTOR2<Real> VECTOR2<Real>::Get_Unit_Perpendicular(void)const
{
	VECTOR2<Real> Temp(-this->y,this->x);
	Temp.Normalize();
	return(Temp);
}

template <class Real> inline Real VECTOR2<Real>::Cross(const VECTOR2<Real>& Origin,const VECTOR2<Real>& Vector)const
{
	return(((this->x - Origin.x)*(Vector.y - Origin.y) - (this->y - Origin.y)*(Vector.x - Origin.x)));
}

template <class Real> inline Real VECTOR2<Real>::Cross_2D(const VECTOR2<Real>& v1)const
{
	return(this->y*v1.x - this->x*v1.y);
}

/**
* Operadores de Atribuicao
*/

template <class Real> inline void VECTOR2<Real>::Set(const Real X,const Real Y)
{
	this->x = X;
	this->y = Y;
	return;
}

template <class Real> inline void VECTOR2<Real>::Set(const VECTOR2& Vector)
{
	this->x = Vector.x;
	this->y = Vector.y;
	return;
}

template <class Real> inline void VECTOR2<Real>::Set(const Real* Vector)
{
	this->x = Vector[0];
	this->y = Vector[1];
	return;
}

template <class Real> inline void VECTOR2<Real>::Set(Real* Vector)
{
	this->x = Vector[0];
	this->y = Vector[1];
	return;
}

template <class Real>
inline void VECTOR2<Real>::Create_Orthonormal_Basis(const VECTOR2<Real>& U,VECTOR2<Real>& V)
{
	V = U.Get_Perpendicular();
	return;
}
