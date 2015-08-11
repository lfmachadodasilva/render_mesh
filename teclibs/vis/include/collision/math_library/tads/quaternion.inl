/**
* Modulo de implementacao dos metodos da classe Quaternion
*/

/**
* Construtores
*/

/**
* Vazio
*/
template <class Real> inline QUATERNION<Real>::QUATERNION()
{
}

/**
* Dado os valores iniciais
*/
template <class Real> inline QUATERNION<Real>::QUATERNION(const Real Real_Value,const VECTOR3<Real>& Imaginary)
{
	this->Real_Value = Real_Value;
	this->Imaginary.Set(Imaginary);
}

template <class Real> inline QUATERNION<Real>::QUATERNION(const Real Real_Value,const Real Axis_x,const Real Axis_y,const Real Axis_z)
{
	this->Real_Value = Real_Value;
	this->Imaginary.Set(Axis_x,Axis_y,Axis_z);
}

template <class Real> inline QUATERNION<Real>::QUATERNION(const QUATERNION<Real>& Quaternion)
{
	this->Real_Value = Quaternion.Real_Value;
	this->Imaginary.Set(Quaternion.Imaginary);
}

/**
* Dado um eixo de rotacao e um angulo de rotacao
*/
template <class Real> inline QUATERNION<Real>::QUATERNION(const VECTOR3<Real>& Axis,const Real Angle)
{
	Real Sin = sinf(DEG_TO_RAD(Angle*2.0f));
	Real Cos = cosf(DEG_TO_RAD(Angle*2.0f));

	this->Real_Value = Cos;
	this->Imaginary.Set(Axis);
	this->Imaginary.x *= Sin;
	this->Imaginary.y *= Sin;
	this->Imaginary.z *= Sin;
	this->Imaginary.Normalize();
}

/**
* Operadores logicos
*/

template <class Real> inline bool QUATERNION<Real>::operator == (const QUATERNION& Quaternion)const
{
	if( (this->Real_Value != Quaternion.Real_Value) || (this->Imaginary.x != Quaternion.Imaginary.x) ||
		(this->Imaginary.y != Quaternion.Imaginary.y) || (this->Imaginary.z != Quaternion.Imaginary.z))
		return(false);
	else
		return(true);

}

template <class Real> inline bool QUATERNION<Real>::operator != (const QUATERNION& Quaternion)const
{
	return((this->Real_Value != Quaternion.Real_Value) || (this->Imaginary.x != Quaternion.Imaginary.x) ||
		(this->Imaginary.y != Quaternion.Imaginary.y) || (this->Imaginary.z != Quaternion.Imaginary.z));
		
}



/**
* Operadores Aritmeticos
*/
template <class Real> inline QUATERNION<Real> QUATERNION<Real>:: operator + (const QUATERNION& Quaternion)const
{
	return(QUATERNION<Real>(this->Real_Value + Quaternion.Real_Value,VECTOR3<Real>(this->Imaginary.x + Quaternion.Imaginary.x,
																			 this->Imaginary.y + Quaternion.Imaginary.y,
																			 this->Imaginary.z + Quaternion.Imaginary.z) ));
}

template <class Real> inline QUATERNION<Real> QUATERNION<Real>:: operator - (const QUATERNION& Quaternion)const
{
	return(QUATERNION<Real>(this->Real_Value - Quaternion.Real_Value,VECTOR3<Real>(this->Imaginary.x - Quaternion.Imaginary.x,
																			 this->Imaginary.y - Quaternion.Imaginary.y,
																			 this->Imaginary.z - Quaternion.Imaginary.z)));
}

template <class Real> inline QUATERNION<Real> QUATERNION<Real>:: operator * (const QUATERNION& Quaternion)const
{
	return( QUATERNION<Real>( (this->Real_Value * Quaternion.Real_Value) - this->Imaginary.x * Quaternion.Imaginary.x
					   - this->Imaginary.y * Quaternion.Imaginary.y - this->Imaginary.z * Quaternion.Imaginary.z,
					     this->Real_Value*Quaternion.Imaginary.x + this->Imaginary.x*Quaternion.Real_Value + (this->Imaginary.y * Quaternion.Imaginary.z - this->Imaginary.z * Quaternion.Imaginary.y),
						 this->Real_Value*Quaternion.Imaginary.y + this->Imaginary.y*Quaternion.Real_Value + (this->Imaginary.z * Quaternion.Imaginary.x - this->Imaginary.x * Quaternion.Imaginary.z),
						 this->Real_Value*Quaternion.Imaginary.z + this->Imaginary.z*Quaternion.Real_Value + (this->Imaginary.x * Quaternion.Imaginary.y - this->Imaginary.y * Quaternion.Imaginary.x)));
}

template <class Real> inline QUATERNION<Real> QUATERNION<Real>::Get_Conjugate(void)const
{
	return(QUATERNION(this->Real_Value,-this->Imaginary.x,-this->Imaginary.y,-this->Imaginary.z));
}

template <class Real> inline void QUATERNION<Real>::Apply_Conjugate(void)
{
	this->Imaginary.x = -this->Imaginary.x;
	this->Imaginary.y = -this->Imaginary.y;
	this->Imaginary.z = -this->Imaginary.z;
	return;
}

template <class Real> inline Real QUATERNION<Real>::Norma(void)const
{
	return(sqrt( (this->Real_Value*this->Real_Value) + (this->Imaginary.x * this->Imaginary.x) + 
		(this->Imaginary.y * this->Imaginary.y) + (this->Imaginary.z * this->Imaginary.z)));
}

template <class Real> inline Real QUATERNION<Real>::Square_Norma(void)const
{
	return((this->Real_Value*this->Real_Value) + (this->Imaginary.x * this->Imaginary.x) + 
		(this->Imaginary.y * this->Imaginary.y) + (this->Imaginary.z * this->Imaginary.z));
}


template <class Real> inline void QUATERNION<Real>::Normalize(void)
{
	Real Norma = this->Norma();

	if(Norma > EPSILON)
	{
		Real Inv_Norma = 1.0f / Norma;
		this->Real_Value *= Inv_Norma;
		this->Imaginary.x *= Inv_Norma;
		this->Imaginary.y *= Inv_Norma;
		this->Imaginary.z *= Inv_Norma;
		return;
	}
	
	return;
}

template <class Real> inline QUATERNION<Real> QUATERNION<Real>::Get_Normalize(void)const
{
	QUATERNION<Real> Temp(*this);
	Temp.Normalize();
	return(QUATERNION(Temp));
}

template <class Real> inline Real QUATERNION<Real>::Imaginary_Dot(const QUATERNION<Real>& Q)const
{
	return(this->Imaginary.Dot(Q.Imaginary));
}

template <class Real> inline MATRIX4<Real> QUATERNION<Real>::To_Matrix_4x4(void)
{
	
	this->Normalize();
	Real tx = 2.0f*this->Imaginary.x;
	Real ty = 2.0f*this->Imaginary.y;
	Real tz = 2.0f*this->Imaginary.z;
	Real xx = this->Imaginary.x * tx;
	Real yy = this->Imaginary.y * ty;
	Real zz = this->Imaginary.z * tz;
	Real wx = this->Real_Value * tx;
	Real wy = this->Real_Value * ty;
	Real wz = this->Real_Value * tz;
	Real yz = this->Imaginary.y * tz;
	Real xz = this->Imaginary.x * tz;
	Real xy = this->Imaginary.x * ty;

	return(MATRIX4<Real>(1.0f - (yy + zz),xy - wz,xz + wy,0.0f,xy + wz,1.0f - (xx + zz),yz - wx,
						 0.0f,xz - wy,yz + wx,1.0f - (xx + yy),0.0f,0.0f,0.0f,0.0f,1.0f));
}
				

template <class Real> inline MATRIX3<Real> QUATERNION<Real>::To_Matrix_3x3(void)
{
	
	this->Normalize();
	Real tx = 2.0f*this->Imaginary.x;
	Real ty = 2.0f*this->Imaginary.y;
	Real tz = 2.0f*this->Imaginary.z;
	Real xx = this->Imaginary.x * tx;
	Real yy = this->Imaginary.y * ty;
	Real zz = this->Imaginary.z * tz;
	Real wx = this->Real_Value * tx;
	Real wy = this->Real_Value * ty;
	Real wz = this->Real_Value * tz;
	Real yz = this->Imaginary.y * tz;
	Real xz = this->Imaginary.x * tz;
	Real xy = this->Imaginary.x * ty;

	return(MATRIX3<Real>(1.0f - (yy + zz),xy - wz,xz + wy,xy + wz,1.0f - (xx + zz),yz - wx,
						 xz - wy,yz + wx,1.0f - (xx + yy)));
}
				

template <class Real> inline void QUATERNION<Real>::Set(const Real Real_Value,const VECTOR3<Real>& Imaginary)
{
	this->Real_Value = Real_Value;
	this->Imaginary.Set(Imaginary);
	return;
}

template <class Real> inline void QUATERNION<Real>::Set(const Real Real_Value,const Real Axis_X,const Real Axis_Y,const Real Axis_Z)
{
	this->Real_Value = Real_Value;
	this->Imaginary.x = Axis_X;
	this->Imaginary.y = Axis_Y;
	this->Imaginary.z = Axis_Z;
	return;
}

template <class Real> inline void QUATERNION<Real>::Set(const QUATERNION<Real>& Quaternion)
{
	this->Real_Value = Quaternion.Real_Value;
	this->Imaginary.Set(Quaternion.Imaginary);
	return;
}

template <class Real> inline void QUATERNION<Real>::Set_Rotation(const Real Angle,const VECTOR3<Real>& Axis)
{
	Real Sin = sinf(DEG_TO_RAD(Angle*2.0f));
	Real Cos = cosf(DEG_TO_RAD(Angle*2.0f));

	this->Real_Value = Cos;
	this->Imaginary.Set(Axis);
	this->Imaginary.x *= Sin;
	this->Imaginary.y *= Sin;
	this->Imaginary.z *= Sin;
	this->Imaginary.Normalize();
	return;
}

template <class Real> inline void QUATERNION<Real>::Set_Rotation(const Real Angle,const Real Axis_x,const Real Axis_y,const Real Axis_z)
{
	Real Sin = sinf(DEG_TO_RAD(Angle*2.0f));
	Real Cos = cosf(DEG_TO_RAD(Angle*2.0f));

	this->Real_Value = Cos;
	this->Imaginary.Set(Axis_x,Axis_y,Axis_z);
	this->Imaginary.x *= Sin;
	this->Imaginary.y *= Sin;
	this->Imaginary.z *= Sin;
	this->Imaginary.Normalize();
	return;
}

template <class Real> inline QUATERNION<Real> QUATERNION<Real>::Get_Inverse(void)const
{
	Real Norma = this->Norma();

	if(Norma > EPSILON)
	{
		Real Inv_Norma = 1.0f / Norma;
		return(QUATERNION<Real>(this->Real_Value*Inv_Norma,-this->Imaginary.x*Inv_Norma,-this->Imaginary.y*Inv_Norma,-this->Imaginary.z*Inv_Norma));
	}
	else
		return(*this);
}


template <class Real> inline void QUATERNION<Real>::Apply_Inverse(void)
{
	Real Norma = this->Norma();

	if(Norma > EPSILON)
	{
		Real Inv_Norma = 1.0f / Norma;
		this->Real_Value *= Inv_Norma;

		Inv_Norma = -Inv_Norma;
		this->Imaginary.x *= Inv_Norma;
		this->Imaginary.y *= Inv_Norma;
		this->Imaginary.z *= Inv_Norma;
	}
	return;
}

template <class Real> inline VECTOR3<Real> QUATERNION<Real>::Apply_Rotation(const VECTOR3<Real>& Vector)const 
{
	QUATERNION<Real> Temp(0.0f,Vector);
	QUATERNION<Real> Conj = this->Get_conjugate();
    
	/**
	* A rotacao e dada por qvq*
	*/
	QUATERNION<Real> Aux = Temp*Conj;
	Aux = this*Aux;

	return(VECTOR3<Real>(Aux.Imaginary));
}

template <class Real> inline QUATERNION<Real> QUATERNION<Real>::Apply_Rotation(const QUATERNION<Real>& Quaternion)const 
{
	
	QUATERNION<Real> Conj = this->Get_conjugate();
    
	/**
	* A rotacao e dada por qvq*
	*/
	QUATERNION<Real> Aux = Quaternion*Conj;
	Aux = this*Aux;

	return(QUATERNION<Real>(Aux));
}


template <class Real> inline void QUATERNION<Real>::Set_From_Euler(const Real Pitch,const Real Yaw,const Real Roll)
{
	Real cPitch = cosf(DEG_TO_RAD(Pitch*2.0f));
	Real cYaw = cosf(DEG_TO_RAD(Yaw*2.0f));
	Real cRoll = cosf(DEG_TO_RAD(Roll*2.0f));

	Real sPitch = sinf(DEG_TO_RAD(Pitch*2.0f));
	Real sYaw = sinf(DEG_TO_RAD(Yaw*2.0f));
	Real sRoll = sinf(DEG_TO_RAD(Roll*2.0f));

	Real cYawcPitch = cYaw*cPitch;
	Real sYawsPitch = sYaw*sPitch;
	Real cYawsPitch = cYaw*sPitch;
	Real sYawcPitch = sYaw*cPitch;

	return(QUATERNION<Real>((cYawcPitch*cRoll + sYawsPitch*sRoll),(cYawcPitch*sRoll - sYawsPitch*cRoll),
							(cYawsPitch*cRoll + sYawcPitch*sRoll),sYawcPitch*cRoll - cYawsPitch*sRoll));
}
