/**
* Modulo de implementacao dos metodos da classe MATRIX4
* @author Fabio Nakamura
*/

/**
* Construtores
*/
template <class Real> inline MATRIX4<Real>::MATRIX4()
{
}

template <class Real> inline MATRIX4<Real>::MATRIX4(Real* Elements)
{
	memcpy(this->Elements,Elements,sizeof(Real)*16);
}




template <class Real> inline MATRIX4<Real>::MATRIX4(const Real a11,const Real a12,const Real a13,const Real a14,
											 const Real a21,const Real a22,const Real a23,const Real a24,
											 const Real a31,const Real a32,const Real a33,const Real a34,
											 const Real a41,const Real a42,const Real a43,const Real a44)
{
	this->Elements[0] = a11;
	this->Elements[1] = a21;
	this->Elements[2] = a31;
	this->Elements[3] = a41;
	this->Elements[4] = a12;
	this->Elements[5] = a22;
	this->Elements[6] = a32;
	this->Elements[7] = a42;
	this->Elements[8] = a13;
	this->Elements[9] = a23;
	this->Elements[10] = a33;
	this->Elements[11] = a43;
	this->Elements[12] = a14;
	this->Elements[13] = a24;
	this->Elements[14] = a34;
	this->Elements[15] = a44;
}

template <class Real> inline MATRIX4<Real>::MATRIX4(const MATRIX4& Matrix)
{
	memcpy(this->Elements,Matrix.Elements,sizeof(Real)*16);
}

template < class Real> inline MATRIX4<Real>::MATRIX4(const VECTOR3<Real>& V1,const VECTOR3<Real>& V2,
											  const VECTOR3<Real>& V3,const VECTOR3<Real>& V4)
{
	this->Elements[0] = V1.x;
	this->Elements[1] = V1.y;
	this->Elements[2] = V1.z;
	this->Elements[3] = 0.0f;

	this->Elements[4] = V2.x;
	this->Elements[5] = V2.y;
	this->Elements[6] = V2.z;
	this->Elements[7] = 0.0f;

	this->Elements[8] = V3.x;
	this->Elements[9] = V3.y;
	this->Elements[10] = V3.z;
	this->Elements[11] = 0.0f;

	this->Elements[12] = V4.x;
	this->Elements[13] = V4.y;
	this->Elements[14] = V4.z;
	this->Elements[15] = 1.0f;

}


template <class Real> inline MATRIX4<Real>::operator const Real*()const
{
	return(this->Elements);
}

template <class Real> inline MATRIX4<Real>::operator Real*()
{
	return(this->Elements);
}

template <class Real> inline MATRIX4<Real>& MATRIX4<Real>::operator = (const MATRIX4& Matrix)
{
	memcpy(this->Elements,Matrix.Elements,16*sizeof(Real));
	return(*this);
}

template <class Real> inline MATRIX4<Real> MATRIX4<Real>::operator + (const MATRIX4& Matrix)const
{
	return
    MATRIX4(
      this->Elements[0] + Matrix.Elements[0],
      this->Elements[4] + Matrix.Elements[4],
      this->Elements[8] + Matrix.Elements[8],
      this->Elements[12] + Matrix.Elements[12],
      this->Elements[1] + Matrix.Elements[1],
      this->Elements[5] + Matrix.Elements[5],
      this->Elements[9] + Matrix.Elements[9],
      this->Elements[13] + Matrix.Elements[13],
      this->Elements[2] + Matrix.Elements[2],
      this->Elements[6] + Matrix.Elements[6],
      this->Elements[10] + Matrix.Elements[10],
      this->Elements[14] + Matrix.Elements[14],
      this->Elements[3] + Matrix.Elements[3],
      this->Elements[7] + Matrix.Elements[7],
      this->Elements[11] + Matrix.Elements[11],
      this->Elements[15] + Matrix.Elements[15]
    );
}

template <class Real> inline MATRIX4<Real> MATRIX4<Real>::operator - (const MATRIX4& Matrix)const
{
	return(MATRIX4(this->Elements[0] - Matrix.Elements[0],this->Elements[4] - Matrix.Elements[4],this->Elements[8] - Matrix.Elements[8],this->Elements[12] - Matrix.Elements[12],
				   this->Elements[1] - Matrix.Elements[1],this->Elements[5] - Matrix.Elements[5],this->Elements[9] - Matrix.Elements[9],this->Elements[13] - Matrix.Elements[13],
				   this->Elements[2] - Matrix.Elements[2],this->Elements[6] - Matrix.Elements[6],this->Elements[10] - Matrix.Elements[10],this->Elements[14] - Matrix.Elements[14],
				   this->Elements[3] - Matrix.Elements[3],this->Elements[7] - Matrix.Elements[7],this->Elements[11] - Matrix.Elements[11],this->Elements[15] - Matrix.Elements[15]));
}

template <class Real> inline MATRIX4<Real> MATRIX4<Real>::operator * (const Real Scalar)const
{
	return(MATRIX4(this->Elements[0] * Scalar,this->Elements[4] * Scalar,this->Elements[8] * Scalar,this->Elements[12]  * Scalar,
				   this->Elements[1] * Scalar,this->Elements[5] * Scalar,this->Elements[9] * Scalar,this->Elements[13]  * Scalar,
				   this->Elements[2] * Scalar,this->Elements[6] * Scalar,this->Elements[10] * Scalar,this->Elements[14] * Scalar,
				   this->Elements[3] * Scalar,this->Elements[7] * Scalar,this->Elements[11] * Scalar,this->Elements[15] * Scalar));
}

template <class Real> inline MATRIX4<Real> MATRIX4<Real>::operator / (const Real Scalar)const
{
	if(Scalar > EPSILON)
	{
		float Inv_Scalar = 1.0f / Scalar;

		return(MATRIX4(this->Elements[0] * Inv_Scalar,this->Elements[4] * Inv_Scalar,this->Elements[8] * Inv_Scalar,this->Elements[12]  * Inv_Scalar,
					this->Elements[1] * Inv_Scalar,this->Elements[5] * Inv_Scalar,this->Elements[9] * Inv_Scalar,this->Elements[13]  * Inv_Scalar,
					this->Elements[2] * Inv_Scalar,this->Elements[6] * Inv_Scalar,this->Elements[10] * Inv_Scalar,this->Elements[14] * Inv_Scalar,
					this->Elements[3] * Inv_Scalar,this->Elements[7] * Inv_Scalar,this->Elements[11] * Inv_Scalar,this->Elements[15] * Inv_Scalar));
	}
	else
		return(MATRIX4(this->Elements));
}


/**
* Operadores de atualizacao
*/

template <class Real> inline MATRIX4<Real>& MATRIX4<Real>::operator += (const MATRIX4& Matrix)
{
	this->Elements[0] += Matrix.Elements[0];
	this->Elements[1] += Matrix.Elements[1];
	this->Elements[2] += Matrix.Elements[2];
	this->Elements[3] += Matrix.Elements[3];

	this->Elements[4] += Matrix.Elements[4];
	this->Elements[5] += Matrix.Elements[5];
	this->Elements[6] += Matrix.Elements[6];
	this->Elements[7] += Matrix.Elements[7];

	this->Elements[8] += Matrix.Elements[8];
	this->Elements[9] += Matrix.Elements[9];
	this->Elements[10] += Matrix.Elements[10];
	this->Elements[11] += Matrix.Elements[11];

	this->Elements[12] += Matrix.Elements[12];
	this->Elements[13] += Matrix.Elements[13];
	this->Elements[14] += Matrix.Elements[14];
	this->Elements[15] += Matrix.Elements[15];

	return(*this);
}

template <class Real> inline MATRIX4<Real>& MATRIX4<Real>::operator -= (const MATRIX4& Matrix)
{
	this->Elements[0] -= Matrix.Elements[0];
	this->Elements[1] -= Matrix.Elements[1];
	this->Elements[2] -= Matrix.Elements[2];
	this->Elements[3] -= Matrix.Elements[3];

	this->Elements[4] -= Matrix.Elements[4];
	this->Elements[5] -= Matrix.Elements[5];
	this->Elements[6] -= Matrix.Elements[6];
	this->Elements[7] -= Matrix.Elements[7];

	this->Elements[8] -= Matrix.Elements[8];
	this->Elements[9] -= Matrix.Elements[9];
	this->Elements[10] -= Matrix.Elements[10];
	this->Elements[11] -= Matrix.Elements[11];

	this->Elements[12] -= Matrix.Elements[12];
	this->Elements[13] -= Matrix.Elements[13];
	this->Elements[14] -= Matrix.Elements[14];
	this->Elements[15] -= Matrix.Elements[15];
	return(*this);
}


template <class Real> inline MATRIX4<Real>& MATRIX4<Real>::operator *= (const Real Scalar)
{
	this->Elements[0] *= Scalar;
	this->Elements[1] *= Scalar;
	this->Elements[2] *= Scalar;
	this->Elements[3] *= Scalar;

	this->Elements[4] *= Scalar;
	this->Elements[5] *= Scalar;
	this->Elements[6] *= Scalar;
	this->Elements[7] *= Scalar;

	this->Elements[8] *= Scalar;
	this->Elements[9] *= Scalar;
	this->Elements[10] *= Scalar;
	this->Elements[11] *= Scalar;

	this->Elements[12] *= Scalar;
	this->Elements[13] *= Scalar;
	this->Elements[14] *= Scalar;
	this->Elements[15] *= Scalar;
	return(*this);
}


template <class Real> inline MATRIX4<Real>& MATRIX4<Real>::operator /= (const Real Scalar)
{
	if(Scalar > EPSILON)
	{
		float Inv_Scalar = 1.0f / Scalar;

		this->Elements[0] *= Inv_Scalar;
		this->Elements[1] *= Inv_Scalar;
		this->Elements[2] *= Inv_Scalar;
		this->Elements[3] *= Inv_Scalar;

		this->Elements[4] *= Inv_Scalar;
		this->Elements[5] *= Inv_Scalar;
		this->Elements[6] *= Inv_Scalar;
		this->Elements[7] *= Inv_Scalar;

		this->Elements[8] *= Inv_Scalar;
		this->Elements[9] *= Inv_Scalar;
		this->Elements[10] *= Inv_Scalar;
		this->Elements[11] *= Inv_Scalar;

		this->Elements[12] *= Inv_Scalar;
		this->Elements[13] *= Inv_Scalar;
		this->Elements[14] *= Inv_Scalar;
		this->Elements[15] *= Inv_Scalar;
	}
	return(*this);
}


template <class Real> inline MATRIX4<Real> MATRIX4<Real>::Multiply(const MATRIX4& Matrix)const
{
	Real a00 = this->Elements[0]*Matrix.Elements[0] + this->Elements[4]*Matrix.Elements[1] + this->Elements[8]*Matrix.Elements[2] + this->Elements[12]*Matrix.Elements[3];
	Real a01 = this->Elements[0]*Matrix.Elements[4] + this->Elements[4]*Matrix.Elements[5] + this->Elements[8]*Matrix.Elements[6] + this->Elements[12]*Matrix.Elements[7];
	Real a02 = this->Elements[0]*Matrix.Elements[8] + this->Elements[4]*Matrix.Elements[9] + this->Elements[8]*Matrix.Elements[10] + this->Elements[12]*Matrix.Elements[11];
	Real a03 = this->Elements[0]*Matrix.Elements[12] + this->Elements[4]*Matrix.Elements[13] + this->Elements[8]*Matrix.Elements[14] + this->Elements[12]*Matrix.Elements[15];
	Real a10 = this->Elements[1]*Matrix.Elements[0] + this->Elements[5]*Matrix.Elements[1] + this->Elements[9]*Matrix.Elements[2] + this->Elements[13]*Matrix.Elements[3];
	Real a11 = this->Elements[1]*Matrix.Elements[4] + this->Elements[5]*Matrix.Elements[5] + this->Elements[9]*Matrix.Elements[6] + this->Elements[13]*Matrix.Elements[7];
	Real a12 = this->Elements[1]*Matrix.Elements[8] + this->Elements[5]*Matrix.Elements[9] + this->Elements[9]*Matrix.Elements[10] + this->Elements[13]*Matrix.Elements[11];
	Real a13 = this->Elements[1]*Matrix.Elements[12] + this->Elements[5]*Matrix.Elements[13] + this->Elements[9]*Matrix.Elements[14] + this->Elements[13]*Matrix.Elements[15];
	Real a20 = this->Elements[2]*Matrix.Elements[0] + this->Elements[6]*Matrix.Elements[1] + this->Elements[10]*Matrix.Elements[2] + this->Elements[14]*Matrix.Elements[3];
	Real a21 = this->Elements[2]*Matrix.Elements[4] + this->Elements[6]*Matrix.Elements[5] + this->Elements[10]*Matrix.Elements[6] + this->Elements[14]*Matrix.Elements[7];
	Real a22 = this->Elements[2]*Matrix.Elements[8] + this->Elements[6]*Matrix.Elements[9] + this->Elements[10]*Matrix.Elements[10] + this->Elements[14]*Matrix.Elements[11];
	Real a23 = this->Elements[2]*Matrix.Elements[12] + this->Elements[6]*Matrix.Elements[13] + this->Elements[10]*Matrix.Elements[14] + this->Elements[14]*Matrix.Elements[15];
	Real a30 = this->Elements[3]*Matrix.Elements[0] + this->Elements[7]*Matrix.Elements[1] + this->Elements[11]*Matrix.Elements[2] + this->Elements[15]*Matrix.Elements[3];
	Real a31 = this->Elements[3]*Matrix.Elements[4] + this->Elements[7]*Matrix.Elements[5] + this->Elements[11]*Matrix.Elements[6] + this->Elements[15]*Matrix.Elements[7];
	Real a32 = this->Elements[3]*Matrix.Elements[8] + this->Elements[7]*Matrix.Elements[9] + this->Elements[11]*Matrix.Elements[10] + this->Elements[15]*Matrix.Elements[11];
	Real a33 =  this->Elements[3]*Matrix.Elements[12] + this->Elements[7]*Matrix.Elements[13] + this->Elements[11]*Matrix.Elements[14] + this->Elements[15]*Matrix.Elements[15];

	return (MATRIX4(a00,a01,a02,a03,a10,a11,a12,a13,
				    a20,a21,a22,a23,a30,a31,a32,a33));
}			   
				  

template <class Real> inline MATRIX4<Real> MATRIX4<Real>::Multiply_RST(const MATRIX4& Matrix)const
{
	Real a = this->Elements[0]*Matrix.Elements[0] + this->Elements[4]*Matrix.Elements[1] + this->Elements[8]*Matrix.Elements[2];
	Real b = this->Elements[0]*Matrix.Elements[4] + this->Elements[4]*Matrix.Elements[5] + this->Elements[8]*Matrix.Elements[6];
	Real c = this->Elements[0]*Matrix.Elements[8] + this->Elements[4]*Matrix.Elements[9] + this->Elements[8]*Matrix.Elements[10];
	Real d = this->Elements[0]*Matrix.Elements[12]+ this->Elements[4]*Matrix.Elements[13]+ this->Elements[8]*Matrix.Elements[14] + this->Elements[12]*Matrix.Elements[15];
	Real e = this->Elements[1]*Matrix.Elements[0] + this->Elements[5]*Matrix.Elements[1] + this->Elements[9]*Matrix.Elements[2];
	Real f = this->Elements[1]*Matrix.Elements[4] + this->Elements[5]*Matrix.Elements[5] + this->Elements[9]*Matrix.Elements[6];
	Real g = this->Elements[1]*Matrix.Elements[8] + this->Elements[5]*Matrix.Elements[9] + this->Elements[9]*Matrix.Elements[10];
	Real h = this->Elements[1]*Matrix.Elements[12]+ this->Elements[5]*Matrix.Elements[13]+ this->Elements[9]*Matrix.Elements[14] + this->Elements[13]*Matrix.Elements[15];
	Real i = this->Elements[2]*Matrix.Elements[0] + this->Elements[6]*Matrix.Elements[1] + this->Elements[10]*Matrix.Elements[2];
	Real j = this->Elements[2]*Matrix.Elements[4] + this->Elements[6]*Matrix.Elements[5] + this->Elements[10]*Matrix.Elements[6];
	Real k = this->Elements[2]*Matrix.Elements[8] + this->Elements[6]*Matrix.Elements[9] + this->Elements[10]*Matrix.Elements[10];
	Real l = this->Elements[2]*Matrix.Elements[12]+ this->Elements[6]*Matrix.Elements[13]+ this->Elements[10]*Matrix.Elements[14] + this->Elements[14]*Matrix.Elements[15];

	return(MATRIX4(a,b,c,d,e,f,g,h,i,j,k,l,(Real)0.0,(Real)0.0,(Real)0.0,(Real)1.0));
	
				  /* return(MATRIX4(this->Elements[0]*Matrix.Elements[0] + this->Elements[4]*Matrix.Elements[1] + this->Elements[8]*Matrix.Elements[2],
				   this->Elements[0]*Matrix.Elements[4] + this->Elements[4]*Matrix.Elements[5] + this->Elements[8]*Matrix.Elements[6],
				   this->Elements[0]*Matrix.Elements[8] + this->Elements[4]*Matrix.Elements[9] + this->Elements[8]*Matrix.Elements[10],
				   this->Elements[0]*Matrix.Elements[12]+ this->Elements[4]*Matrix.Elements[13]+ this->Elements[8]*Matrix.Elements[14] + this->Elements[12]*Matrix.Elements[15],
				   this->Elements[1]*Matrix.Elements[0] + this->Elements[5]*Matrix.Elements[1] + this->Elements[9]*Matrix.Elements[2],
				   this->Elements[1]*Matrix.Elements[4] + this->Elements[5]*Matrix.Elements[5] + this->Elements[9]*Matrix.Elements[6], 
				   this->Elements[1]*Matrix.Elements[8] + this->Elements[5]*Matrix.Elements[9] + this->Elements[9]*Matrix.Elements[10]
				   this->Elements[1]*Matrix.Elements[12]+ this->Elements[5]*Matrix.Elements[13]+ this->Elements[9]*Matrix.Elements[14] + this->Elements[13]*Matrix.Elements[15],
				   this->Elements[2]*Matrix.Elements[0] + this->Elements[6]*Matrix.Elements[1] + this->Elements[10]*Matrix.Elements[2],
				   this->Elements[2]*Matrix.Elements[4] + this->Elements[6]*Matrix.Elements[5] + this->Elements[10]*Matrix.Elements[6],
				   this->Elements[2]*Matrix.Elements[8] + this->Elements[6]*Matrix.Elements[9] + this->Elements[10]*Matrix.Elements[10],
				   this->Elements[2]*Matrix.Elements[12]+ this->Elements[6]*Matrix.Elements[13]+ this->Elements[10]*Matrix.Elements[14] + this->Elements[14]*Matrix.Elements[15],
				   0.0f,0.0f,0.0f,1.0f ));*/
}

template<class Real>
inline MATRIX3<Real> MATRIX4<Real>::Multiply_3x3(const MATRIX3<Real>& Matrix)const
{
	Real a = this->Elements[0]*Matrix.Elements[0] + this->Elements[4]*Matrix.Elements[1] + this->Elements[8]*Matrix.Elements[2];
	Real b = this->Elements[0]*Matrix.Elements[3] + this->Elements[4]*Matrix.Elements[4] + this->Elements[8]*Matrix.Elements[5];
	Real c = this->Elements[0]*Matrix.Elements[6] + this->Elements[4]*Matrix.Elements[7] + this->Elements[8]*Matrix.Elements[8];
	Real d = this->Elements[1]*Matrix.Elements[0] + this->Elements[5]*Matrix.Elements[1] + this->Elements[9]*Matrix.Elements[2];
	Real e = this->Elements[1]*Matrix.Elements[3] + this->Elements[5]*Matrix.Elements[4] + this->Elements[9]*Matrix.Elements[5];
	Real f = this->Elements[1]*Matrix.Elements[6] + this->Elements[5]*Matrix.Elements[7] + this->Elements[9]*Matrix.Elements[8];
	Real g = this->Elements[2]*Matrix.Elements[0] + this->Elements[6]*Matrix.Elements[1] + this->Elements[10]*Matrix.Elements[2];
	Real h = this->Elements[2]*Matrix.Elements[3] + this->Elements[6]*Matrix.Elements[4] + this->Elements[10]*Matrix.Elements[5];
	Real i = this->Elements[2]*Matrix.Elements[6] + this->Elements[6]*Matrix.Elements[7] + this->Elements[10]*Matrix.Elements[8];
	return(MATRIX3<Real>(a,b,c,d,e,f,g,h,i));
}

template <class Real> inline MATRIX4<Real> MATRIX4<Real>::Multiply_Transpose(const MATRIX4& Matrix)const
{
	Real a00 = this->Elements[0]*Matrix.Elements[0] + this->Elements[1]*Matrix.Elements[1] + this->Elements[2]*Matrix.Elements[2] + this->Elements[3]*Matrix.Elements[3];
	Real a01 = this->Elements[0]*Matrix.Elements[4] + this->Elements[1]*Matrix.Elements[5] + this->Elements[2]*Matrix.Elements[6] + this->Elements[3]*Matrix.Elements[7];
	Real a02 = this->Elements[0]*Matrix.Elements[8] + this->Elements[1]*Matrix.Elements[9] + this->Elements[2]*Matrix.Elements[10] + this->Elements[3]*Matrix.Elements[11];
	Real a03 = this->Elements[0]*Matrix.Elements[12] + this->Elements[1]*Matrix.Elements[13] + this->Elements[2]*Matrix.Elements[14] + this->Elements[3]*Matrix.Elements[15];
	Real a10 = this->Elements[4]*Matrix.Elements[0] + this->Elements[5]*Matrix.Elements[1] + this->Elements[6]*Matrix.Elements[2] + this->Elements[7]*Matrix.Elements[3];
	Real a11 = this->Elements[4]*Matrix.Elements[4] + this->Elements[5]*Matrix.Elements[5] + this->Elements[6]*Matrix.Elements[6] + this->Elements[7]*Matrix.Elements[7];
	Real a12 = this->Elements[4]*Matrix.Elements[8] + this->Elements[5]*Matrix.Elements[9] + this->Elements[6]*Matrix.Elements[10] + this->Elements[7]*Matrix.Elements[11];
	Real a13 = this->Elements[4]*Matrix.Elements[12] + this->Elements[5]*Matrix.Elements[13] + this->Elements[6]*Matrix.Elements[14] + this->Elements[7]*Matrix.Elements[15];
	Real a20 = this->Elements[8]*Matrix.Elements[0] + this->Elements[9]*Matrix.Elements[1] + this->Elements[10]*Matrix.Elements[2] + this->Elements[11]*Matrix.Elements[3];
	Real a21 = this->Elements[8]*Matrix.Elements[4] + this->Elements[9]*Matrix.Elements[5] + this->Elements[10]*Matrix.Elements[6] + this->Elements[11]*Matrix.Elements[7];
	Real a22 = this->Elements[8]*Matrix.Elements[8] + this->Elements[9]*Matrix.Elements[9] + this->Elements[10]*Matrix.Elements[10] + this->Elements[11]*Matrix.Elements[11];
	Real a23 = this->Elements[8]*Matrix.Elements[12] + this->Elements[9]*Matrix.Elements[13] + this->Elements[10]*Matrix.Elements[14] + this->Elements[11]*Matrix.Elements[15];
	Real a30 = this->Elements[12]*Matrix.Elements[0] + this->Elements[13]*Matrix.Elements[1] + this->Elements[14]*Matrix.Elements[2] + this->Elements[15]*Matrix.Elements[3];
	Real a31 = this->Elements[12]*Matrix.Elements[4] + this->Elements[13]*Matrix.Elements[5] + this->Elements[14]*Matrix.Elements[6] + this->Elements[15]*Matrix.Elements[7];
	Real a32 = this->Elements[12]*Matrix.Elements[8] + this->Elements[13]*Matrix.Elements[9] + this->Elements[14]*Matrix.Elements[10] + this->Elements[15]*Matrix.Elements[11];
	Real a33 =  this->Elements[12]*Matrix.Elements[12] + this->Elements[13]*Matrix.Elements[13] + this->Elements[14]*Matrix.Elements[14] + this->Elements[15]*Matrix.Elements[15];

	return (MATRIX4(a00,a01,a02,a03,a10,a11,a12,a13,
				    a20,a21,a22,a23,a30,a31,a32,a33));
}

template <class Real> inline VECTOR3<Real> MATRIX4<Real>::Multiply_Vector(const VECTOR3<Real>& Vector)const
{
	Real X = Vector.x*this->Elements[0] + Vector.y*this->Elements[4] + Vector.z*this->Elements[8] + this->Elements[12];
	Real Y = Vector.x*this->Elements[1] + Vector.y*this->Elements[5] + Vector.z*this->Elements[9] + this->Elements[13];
	Real Z = Vector.x*this->Elements[2] + Vector.y*this->Elements[6] + Vector.z*this->Elements[10] + this->Elements[14];
	
	return(VECTOR3<Real>(X,Y,Z));
}

template <class Real> inline VECTOR3<Real> MATRIX4<Real>::Multiply_Transpose_Vector(const VECTOR3<Real>& Vector)const
{
	Real X = Vector.x*this->Elements[0] + Vector.y*this->Elements[1] + Vector.z*this->Elements[2] + this->Elements[3];
	Real Y = Vector.x*this->Elements[4] + Vector.y*this->Elements[5] + Vector.z*this->Elements[6] + this->Elements[7];
	Real Z = Vector.x*this->Elements[8] + Vector.y*this->Elements[9] + Vector.z*this->Elements[10] + this->Elements[11];
	
	return(VECTOR3<Real>(X,Y,Z));

}

template <class Real> inline VECTOR3<Real> MATRIX4<Real>::Affine_Transform(const VECTOR3<Real>& Vector)const
{
	
	Real X = Vector.x*this->Elements[0] + Vector.y*this->Elements[4] + Vector.z*this->Elements[8] + this->Elements[12];
	Real Y = Vector.x*this->Elements[1] + Vector.y*this->Elements[5] + Vector.z*this->Elements[9] + this->Elements[13];
	Real Z = Vector.x*this->Elements[2] + Vector.y*this->Elements[6] + Vector.z*this->Elements[10] + this->Elements[14];
	
	return(VECTOR3<Real>(X,Y,Z));
}

/**
* Operacoes de transformacao
*/

template <class Real> inline void MATRIX4<Real>::Set_Identity(void)
{
	this->Elements[1] = 0.0f;
	this->Elements[2] = 0.0f;
	this->Elements[3] = 0.0f;
	this->Elements[4] = 0.0f;
	this->Elements[6] = 0.0f;
	this->Elements[7] = 0.0f;
	this->Elements[8] = 0.0f;
	this->Elements[9] = 0.0f;
	this->Elements[11] = 0.0f;
	this->Elements[12] = 0.0f;
	this->Elements[13] = 0.0f;
	this->Elements[14] = 0.0f;
	this->Elements[0] = 
	this->Elements[5] = 
	this->Elements[10] = 
	this->Elements[15] = 1.0f;

	return;
}

template <class Real> inline void MATRIX4<Real>::Set_Translate(const Real X,const Real Y,const Real Z)
{
	this->Elements[0] = 1.0f;
	this->Elements[1] = 0.0f;
	this->Elements[2] = 0.0f;
	this->Elements[3] = 0.0f;
	this->Elements[4] = 0.0f;
	this->Elements[5] = 1.0f;
	this->Elements[6] = 0.0f;
	this->Elements[7] = 0.0f;
	this->Elements[8] = 0.0f;
	this->Elements[9] = 0.0f;
	this->Elements[10] = 1.0f;
	this->Elements[11] = 0.0f;
	this->Elements[12] = X;
	this->Elements[13] = Y;
	this->Elements[14] = Z;
	this->Elements[15] = 1.0f;

	return;
}

template <class Real> inline void MATRIX4<Real>::Set_Translate(const Real* Vector)
{
	this->Elements[0] = 1.0f;
	this->Elements[1] = 0.0f;
	this->Elements[2] = 0.0f;
	this->Elements[3] = 0.0f;
	this->Elements[4] = 0.0f;
	this->Elements[5] = 1.0f;
	this->Elements[6] = 0.0f;
	this->Elements[7] = 0.0f;
	this->Elements[8] = 0.0f;
	this->Elements[9] = 0.0f;
	this->Elements[10] = 1.0f;
	this->Elements[11] = 0.0f;
	this->Elements[12] = Vector[0];
	this->Elements[13] = Vector[1];
	this->Elements[14] = Vector[2];
	this->Elements[15] = 1.0f;

	return;
}

template <class Real> inline void MATRIX4<Real>::Set_Translate(const VECTOR3<Real>& Vector)
{
	this->Elements[0] = 1.0f;
	this->Elements[1] = 0.0f;
	this->Elements[2] = 0.0f;
	this->Elements[3] = 0.0f;
	this->Elements[4] = 0.0f;
	this->Elements[5] = 1.0f;
	this->Elements[6] = 0.0f;
	this->Elements[7] = 0.0f;
	this->Elements[8] = 0.0f;
	this->Elements[9] = 0.0f;
	this->Elements[10] = 1.0f;
	this->Elements[11] = 0.0f;
	this->Elements[12] = Vector.x;
	this->Elements[13] = Vector.y;
	this->Elements[14] = Vector.z;
	this->Elements[15] = 1.0f;

	return;
}


template <class Real> inline void MATRIX4<Real>::Set_Rotate_X(const Real Angle)
{
	float Cos = cosf(DEG_TO_RAD(Angle));
	float Sin = sinf(DEG_TO_RAD(Angle));

	this->Elements[0] = 1.0f;
	this->Elements[1] = 0.0f;
	this->Elements[2] = 0.0f;
	this->Elements[3] = 0.0f;
	this->Elements[4] = 0.0f;
	this->Elements[5] = Cos;
	this->Elements[6] = Sin;
	this->Elements[7] = 0.0f;
	this->Elements[8] = 0.0f;
	this->Elements[9] = -Sin;
	this->Elements[10] = Cos;
	this->Elements[11] = 0.0f;
	this->Elements[12] = 0.0f;
	this->Elements[13] = 0.0f;
	this->Elements[14] = 0.0f;
	this->Elements[15] = 1.0f;
	return;
}

template <class Real> inline void MATRIX4<Real>::Set_Rotate_Y(const Real Angle)
{
	float Cos = cosf(DEG_TO_RAD(Angle));
	float Sin = sinf(DEG_TO_RAD(Angle));

	this->Elements[0] = Cos;
	this->Elements[1] = 0.0f;
	this->Elements[2] = -Sin;
	this->Elements[3] = 0.0f;
	this->Elements[4] = 0.0f;
	this->Elements[5] = 1.0f;
	this->Elements[6] = 0.0f;
	this->Elements[7] = 0.0f;
	this->Elements[8] = Sin;
	this->Elements[9] = 0.0f;
	this->Elements[10] = Cos;
	this->Elements[11] = 0.0f;
	this->Elements[12] = 0.0f;
	this->Elements[13] = 0.0f;
	this->Elements[14] = 0.0f;
	this->Elements[15] = 1.0f;
	return;
}


template <class Real> inline void MATRIX4<Real>::Set_Rotate_Z(const Real Angle)
{
	float Cos = cosf(DEG_TO_RAD(Angle));
	float Sin = sinf(DEG_TO_RAD(Angle));

	this->Elements[0] = Cos;
	this->Elements[1] = Sin;
	this->Elements[2] = 0.0f;
	this->Elements[3] = 0.0f;
	this->Elements[4] = -Sin;
	this->Elements[5] = Cos;
	this->Elements[6] = 0.0f;
	this->Elements[7] = 0.0f;
	this->Elements[8] = 0.0f;
	this->Elements[9] = 0.0f;
	this->Elements[10] = 1.0f;
	this->Elements[11] = 0.0f;
	this->Elements[12] = 0.0f;
	this->Elements[13] = 0.0f;
	this->Elements[14] = 0.0f;
	this->Elements[15] = 1.0f;
	return;
}

template <class Real> inline void MATRIX4<Real>::Set_Rotate(const Real X,const Real Y,const Real Z,const Real Angle)
{
	VECTOR3<Real> Normal(X,Y,Z);
	Real t;
	Real X_2;
	Real Y_2;
	Real Z_2;
	Real xn;
	Real yn;
	Real zn;

	/* Graus para ficar igual ao padrao OpenGL */
    Real Cos = cosf(DEG_TO_RAD(Angle));
	Real Sin = sinf(DEG_TO_RAD(Angle));

	/* Temos que normalizar os eixos de rotacao */
	Normal.Normalize();

	xn = Normal.x;
	yn = Normal.y;
	zn = Normal.z;

	t = (1 - Cos);
	X_2 = xn*xn;
	Y_2 = yn*yn;
	Z_2 = zn*zn;

	return(MATRIX4(Cos + t*X_2,t*xn*yn - zn*Sin,t*xn*zn + yn*Sin,0.0f,t*xn*yn + zn*Sin,Cos + t*Y_2,t*yn*zn - xn*Sin,0.0f,
				   t*xn*zn - yn*Sin,t*yn*zn + xn*Sin,Cos + t*Z_2,0.0f,0.0f,0.0f,0.0f,1.0f));
} 

template <class Real> inline void MATRIX4<Real>::Set_Rotate(const VECTOR3<Real>& Vector,const Real Angle)
{
	VECTOR3<Real> Normal(Vector);
	Real t;
	Real X_2;
	Real Y_2;
	Real Z_2;
	Real xn;
	Real yn;
	Real zn;

	/* Graus para ficar igual ao padrao OpenGL */
    Real Cos = cosf(DEG_TO_RAD(Angle));
	Real Sin = sinf(DEG_TO_RAD(Angle));

	/* Temos que normalizar os eixos de rotacao */
	Normal.Normalize();

	xn = Normal.x;
	yn = Normal.y;
	zn = Normal.z;

	t = (1 - Cos);
	X_2 = xn*xn;
	Y_2 = yn*yn;
	Z_2 = zn*zn;

	return(MATRIX4(Cos + t*X_2,t*xn*yn - zn*Sin,t*xn*zn + yn*Sin,0.0f,t*xn*yn + zn*Sin,Cos + t*Y_2,t*yn*zn - xn*Sin,0.0f,
				   t*xn*zn - yn*Sin,t*yn*zn + xn*Sin,Cos + t*Z_2,0.0f,0.0f,0.0f,0.0f,1.0f));
} 

template <class Real> inline MATRIX4<Real> MATRIX4<Real>::Transpose(void)const
{
	return(MATRIX4(this->Elements[0],this->Elements[1],this->Elements[2],this->Elements[3],this->Elements[4],this->Elements[5],this->Elements[6],this->Elements[7],
		this->Elements[8],this->Elements[9],this->Elements[10],this->Elements[11],this->Elements[12],this->Elements[13],this->Elements[14],this->Elements[15]));
}

template <class Real> inline void MATRIX4<Real>::Set_Transpose(void)
{
	Real Temp[16];
	memcpy(Temp,this->Elements,sizeof(Real)*16);

	this->Elements[1] = Temp[4];
	this->Elements[2] = Temp[8];
	this->Elements[3] = Temp[12];

	this->Elements[4] = Temp[1];
	this->Elements[6] = Temp[9];
	this->Elements[7] = Temp[13];

	this->Elements[8] = Temp[2];
	this->Elements[9] = Temp[6];
	this->Elements[11] = Temp[14];

	this->Elements[12] = Temp[3];
	this->Elements[13] = Temp[7];
	this->Elements[14] = Temp[11];
	
	return;
}


template <class Real> inline Real MATRIX4<Real>::Det_2x2(const Real a11,const Real a12,const Real a21,const Real a22)
{
	Real Result;

	Result = a11*a22 - a12*a21;
	return (Result);
}



template <class Real> inline Real MATRIX4<Real>::Det_3x3(const Real a11,const Real a12,const Real a13,
												  const Real a21,const Real a22,const Real a23,
												  const Real a31,const Real a32,const Real a33)
{
	Real t1 = a11 * Det_2x2(a22,a23,a32,a33);
	Real t2 = a21 * Det_2x2(a12,a13,a32,a33);
	Real t3 = a31 * Det_2x2(a12,a13,a22,a23);
	return(t1 - t2 + t3);
}

template <class Real> inline Real MATRIX4<Real>::Det_4x4(void)const
{
	Real a1,a2,a3,a4,b1,b2,b3,b4,c1,c2,c3,c4,d1,d2,d3,d4; // facilitar nas contas !!

	a1 = this->Elements[0];   
	a2 = this->Elements[1];
	a3 = this->Elements[2];
	a4 = this->Elements[3];

	b1 = this->Elements[4];
	b2 = this->Elements[5];
	b3 = this->Elements[6];
	b4 = this->Elements[7];

	c1 = this->Elements[8];
	c2 = this->Elements[9];
	c3 = this->Elements[10];
	c4 = this->Elements[11];

	d1 = this->Elements[12];
	d2 = this->Elements[13];
	d3 = this->Elements[14];
	d4 = this->Elements[15];

	Real t1 = a1 * Det_3x3(b2,b3,b4,c2,c3,c4,d2,d3,d4);
	Real t2 = b1 * Det_3x3(a2,a3,a4,c2,c3,c4,d2,d3,d4);
	Real t3 = c1 * Det_3x3(a2,a3,a4,b2,b3,b4,d2,d3,d4);
	Real t4 = d1 * Det_3x3(a2,a3,a4,b2,b3,b4,c2,c3,c4);
	
	return(t1-t2+t3-t4);
}


template <class Real> inline MATRIX4<Real> MATRIX4<Real>::Adjoint(void)const
{

	Real a1,a2,a3,a4,b1,b2,b3,b4,c1,c2,c3,c4,d1,d2,d3,d4; // facilitar nas contas !!
	Real Result[16];

	a1 = this->Elements[0];   
	a2 = this->Elements[1];
	a3 = this->Elements[2];
	a4 = this->Elements[3];

	b1 = this->Elements[4];
	b2 = this->Elements[5];
	b3 = this->Elements[6];
	b4 = this->Elements[7];

	c1 = this->Elements[8];
	c2 = this->Elements[9];
	c3 = this->Elements[10];
	c4 = this->Elements[11];

	d1 = this->Elements[12];
	d2 = this->Elements[13];
	d3 = this->Elements[14];
	d4 = this->Elements[15];

	Result[0] = Det_3x3(b2,b3,b4,c2,c3,c4,d2,d3,d4);
	Result[1] = -Det_3x3(a2,a3,a4,c2,c3,c4,d2,d3,d4);
	Result[2] = Det_3x3(a2,a3,a4,b2,b3,b4,d2,d3,d4);
	Result[3] = -Det_3x3(a2,a3,a4,b2,b3,b4,c2,c3,c4);

	Result[4] = -Det_3x3(b1,b3,b4,c1,c3,c4,d1,d3,d4);
	Result[5] = Det_3x3(a1,a3,a4,c1,c3,c4,d1,d3,d4);
	Result[6] = -Det_3x3(a1,a3,a4,b1,b3,b4,d1,d3,d4);
	Result[7] = Det_3x3(a1,a3,a4,b1,b3,b4,c1,c3,c4);

	Result[8] = Det_3x3(b1,b2,b4,c1,c2,c4,d1,d2,d4);
	Result[9] = -Det_3x3(a1,a2,a4,c1,c2,c4,d1,d2,d4);
	Result[10] = Det_3x3(a1,a2,a4,b1,b2,b4,d1,d2,d4);
	Result[11] = -Det_3x3(a1,a2,a4,b1,b2,b4,c1,c2,c4);

	Result[12] = -Det_3x3(b1,b2,b3,c1,c2,c3,d1,d2,d3);
	Result[13] = Det_3x3(a1,a2,a3,c1,c2,c3,d1,d2,d3);
	Result[14] = -Det_3x3(a1,a2,a3,b1,b2,b3,d1,d2,d3);
	Result[15] = Det_3x3(a1,a2,a3,b1,b2,b3,c1,c2,c3);

	return(MATRIX4(Result));
    
}


template <class Real> inline MATRIX4<Real> MATRIX4<Real>::Inverse(void)const
{
	
	Real Det;
	MATRIX4 Result;
	Result.Set_Identity();

	Det = this->Det_4x4();
	
	if(fabs(Det) < EPSILON)
		return Result;

	Result = this->Adjoint();

	Real Inv_Det = 1.0f / Det;
	return (MATRIX4(Result.Elements[0]*Inv_Det,Result.Elements[4]*Inv_Det,Result.Elements[8]*Inv_Det,Result.Elements[12]*Inv_Det,
					Result.Elements[1]*Inv_Det,Result.Elements[5]*Inv_Det,Result.Elements[9]*Inv_Det,Result.Elements[13]*Inv_Det,
					Result.Elements[2]*Inv_Det,Result.Elements[6]*Inv_Det,Result.Elements[10]*Inv_Det,Result.Elements[14]*Inv_Det,
					Result.Elements[3]*Inv_Det,Result.Elements[7]*Inv_Det,Result.Elements[11]*Inv_Det,Result.Elements[15]*Inv_Det));
}


template <class Real> inline QUATERNION<Real> MATRIX4<Real>::To_Quaternion(void)const
{
	// O traco da matriz
	Real Trace;
	Real Root;
	Real Real_Temp;
	Real Temp[3][3];

	Temp[0][0] = this->Elements[0];
	Temp[0][1] = this->Elements[1];
	Temp[0][2] = this->Elements[2];
	Temp[1][0] = this->Elements[4];
	Temp[1][1] = this->Elements[5];
	Temp[1][2] = this->Elements[6];
	Temp[2][0] = this->Elements[8];
	Temp[2][1] = this->Elements[9];
	Temp[2][2] = this->Elements[10];
	
	Trace = Temp[0][0] + Temp[1][1] + Temp[2][2];

	if(Trace > 0.0f)
	{
		Root = sqrtf(Trace + 1.0f); // == 2*W
		Real_Temp = 0.5f*Root;
		Root = 0.5f/Root ; // == w/4
		return(QUATERNION<Real>(Real_Temp,(Temp[2][1] - Temp[1][2])*Root,(Temp[0][2] - Temp[2][0])*Root,(Temp[1][0] - Temp[0][1])*Root));

	}
	else
	{
		QUATERNION<Real> Result;
		// |w| <= 1/2
        static int s_iNext[3] = { 1, 2, 0 };
        int i = 0;
        if ( Temp[1][1] > Temp[0][0] )
            i = 1;
        if ( Temp[2][2] > Temp[i][i] )
            i = 2;
        int j = s_iNext[i];
        int k = s_iNext[j];


		Root = sqrtf(Temp[i][i] - Temp[j][j] - Temp[k][k] + 1.0f);
		float* Quat_aux[3] = {&Result.Imaginary.x,&Result.Imaginary.y,&Result.Imaginary.z};
		*Quat_aux[i] = 0.5f*Root;
		Root = 0.5f/Root;
		Result.Real_Value = (Temp[k][j] - Temp[j][k])*Root;
		*Quat_aux[j] = (Temp[j][i] + Temp[i][j])*Root;
		*Quat_aux[k] = (Temp[k][i] + Temp[i][k])*Root;
		return(Result);
	}
}


template <class Real> inline void MATRIX4<Real>::Set(const Real* Matrix)
{
	memcpy(this->Elements,Matrix,16*sizeof(Real));
	return;
}

template <class Real> inline void MATRIX4<Real>::Set(const MATRIX4<Real>& Matrix)
{
	memcpy(this->Elements,Matrix.Elements,16*sizeof(Real));
	return;
}

template <class Real> inline void MATRIX4<Real>::Set_Basis(const VECTOR3<Real> Axis_X,const VECTOR3<Real> Axis_Y,const VECTOR3<Real> Axis_Z)
{
	this->Elements[0] = Axis_X.x;
	this->Elements[1] = Axis_X.y;
	this->Elements[2] = Axis_X.z;
	this->Elements[3] = (Real)0.0;

	this->Elements[4] = Axis_Y.x;
	this->Elements[5] = Axis_Y.y;
	this->Elements[6] = Axis_Y.z;
	this->Elements[7] = (Real)0.0;

	this->Elements[8] = Axis_Z.x;
	this->Elements[9] = Axis_Z.y;
	this->Elements[10] = Axis_Z.z;
	this->Elements[11] = (Real)0.0;

	this->Elements[12] = (Real)0.0;
	this->Elements[13] = (Real)0.0;
	this->Elements[14] = (Real)0.0;
	this->Elements[15] = (Real)1.0;

	return;
}

template <class Real> inline void MATRIX4<Real>::Make_From_Euler(const Real Pitch,const Real Yaw,const Real Roll)
{
	Real c_Pitch = cosf(DEG_TO_RAD(Pitch));
	Real c_Yaw = cosf(DEG_TO_RAD(Yaw));
	Real c_Roll = cosf(DEG_TO_RAD(Roll));

	Real s_Pitch = sinf(DEG_TO_RAD(Pitch));
	Real s_Yaw = sinf(DEG_TO_RAD(Yaw));
	Real s_Roll = sinf(DEG_TO_RAD(Roll));


	this->Elements[0] = c_Roll*c_Yaw - s_Roll*s_Pitch*s_Yaw;
	this->Elements[1] = s_Roll*c_Yaw + c_Roll*s_Pitch*s_Yaw;
	this->Elements[2] = -c_Pitch*s_Yaw;
	this->Elements[3] = (Real)0.0;

	this->Elements[4] = -s_Roll*c_Pitch;
	this->Elements[5] = c_Roll*c_Pitch;
	this->Elements[6] = s_Pitch;
	this->Elements[7] = (Real)0.0;

	this->Elements[8] = c_Roll*s_Yaw + s_Roll*s_Pitch*c_Yaw;
	this->Elements[9] = s_Roll*s_Yaw - c_Roll*s_Pitch*c_Yaw;
	this->Elements[10] = c_Pitch*c_Yaw;
	this->Elements[11] = (Real)0.0;

	this->Elements[12] = (Real)0.0;
	this->Elements[13] = (Real)0.0;
	this->Elements[14] = (Real)0.0;
	this->Elements[15] = (Real)1.0;
	
	return;
}

template <class Real> inline
void MATRIX4<Real>::Make_Oblique_Projection(const VECTOR3<Real>& Normal,const VECTOR3<Real>& Point,const VECTOR3<Real>& Direction)
{
	// The projection plane is Dot(N,X-P) = 0 where N is a 3-by-1 unit-length
    // normal vector and P is a 3-by-1 point on the plane.  The projection
    // is oblique to the plane, in the direction of the 3-by-1 vector D.
    // Necessarily Dot(N,D) is not zero for this projection to make sense.
    // Given a 3-by-1 point U, compute the intersection of the line U+t*D
    // with the plane to obtain t = -Dot(N,U-P)/Dot(N,D).  Then
    //
    //   projection(U) = P + [I - D*N^T/Dot(N,D)]*(U-P)
    //
    // A 4-by-4 homogeneous transformation representing the projection is
    //
    //       +-                               -+
    //   M = | D*N^T - Dot(N,D)*I   -Dot(N,P)D |
    //       |          0^T          -Dot(N,D) |
    //       +-                               -+
    //
    // where M applies to [U^T 1]^T by M*[U^T 1]^T.  The matrix is chosen so
    // that M[3][3] > 0 whenever Dot(N,D) < 0 (projection is onto the
    // "positive side" of the plane).

	Real Dot_NP = Normal.Dot(Point);
	Real Dot_ND = Normal.Dot(Direction);

	this->Elements[0] = Direction.x * Normal.x - Dot_ND;
	this->Elements[4] = Direction.x * Normal.y;
	this->Elements[8] = Direction.x * Normal.z;
	this->Elements[12] = -Dot_NP*Direction.x;

	this->Elements[1] = Direction.y * Normal.x;
	this->Elements[5] = Direction.y * Normal.y - Dot_ND;
	this->Elements[9] = Direction.y * Normal.z;
	this->Elements[13] = -Dot_NP*Direction.y;

	this->Elements[2]  = Direction.z * Normal.x;
	this->Elements[6]  = Direction.z * Normal.y;
	this->Elements[10] = Direction.z * Normal.z - Dot_ND;
	this->Elements[14] = -Dot_NP*Direction.z;

	this->Elements[3] = (Real)0.0;
	this->Elements[7] = (Real)0.0;
	this->Elements[11] = (Real)0.0;
	this->Elements[15] = -Dot_ND;

	return;
}

template <class Real> inline
void MATRIX4<Real>::Make_Perspective_Projection(const VECTOR3<Real>& Normal,const VECTOR3<Real>& Point,const VECTOR3<Real>& Eye)
{
	//     +-                                                 -+
    // M = | Dot(N,E-P)*I - E*N^T    -(Dot(N,E-P)*I - E*N^T)*E |
    //     |        -N^t                      Dot(N,E)         |
    //     +-                                                 -+
    //
    // where E is the eye point, P is a point on the plane, and N is a
    // unit-length plane normal.

	Real Dot_NEP = Normal.Dot(Eye-Point);
	Real Dot_NE = Normal.Dot(Eye);

	this->Elements[0] = Dot_NEP - Eye.x*Normal.x;
	this->Elements[4] = - Eye.x * Normal.y;
	this->Elements[8] = - Eye.x * Normal.z;
	this->Elements[12] = -(this->Elements[0]*Eye.x + this->Elements[4]*Eye.y + this->Elements[8]*Eye.z);

	this->Elements[1] = -Eye.y * Normal.x;
	this->Elements[5] = Dot_NEP - Eye.y * Normal.y;
	this->Elements[9] = - Eye.y * Normal.z;
	this->Elements[13] = -(this->Elements[1]*Eye.x + this->Elements[5]*Eye.y + this->Elements[9]*Eye.z);

	this->Elements[2] = -Eye.z * Normal.x;
	this->Elements[6] = -Eye.z * Normal.y;
	this->Elements[10] = Dot_NEP - Eye.z * Normal.z;
	this->Elements[14] = -(this->Elements[2]*Eye.x + this->Elements[6]*Eye.y + this->Elements[12]*Eye.z);

	this->Elements[3] = -Normal.x;
	this->Elements[7] = -Normal.y;
	this->Elements[11] = -Normal.z;
	this->Elements[15] = Dot_NE;

	return;
}

template <class Real> inline
void MATRIX4<Real>::Make_Reflective_Projection(const VECTOR3<Real>& Normal,const VECTOR3<Real>& Point)
{
	//     +-                         -+
    // M = | I-2*N*N^T    2*Dot(N,P)*N |
    //     |     0^T            1      |
    //     +-                         -+
    //
    // where P is a point on the plane and N is a unit-length plane normal.

	Real Dot_NP = ((Real)2.0)*(Normal.Dot(Point));
	
	this->Elements[0] = ((Real)1.0) - ((Real)2.0) * Normal.x*Normal.x;
	this->Elements[4] = - ((Real)2.0)* Normal.x * Normal.y;
	this->Elements[8] = - ((Real)2.0)* Normal.x * Normal.z;
	this->Elements[12] = Dot_NP * Normal.x;

	this->Elements[1] =  - ((Real)2.0)* Normal.y * Normal.x;
	this->Elements[5] = ((Real)1.0) - ((Real)2.0) * Normal.y*Normal.y;
	this->Elements[9] = - ((Real)2.0)* Normal.y * Normal.z;
	this->Elements[13] = Dot_NP * Normal.y;

	this->Elements[2] =  - ((Real)2.0)* Normal.z * Normal.x;
	this->Elements[6] =  - ((Real)2.0)* Normal.z * Normal.y;
	this->Elements[10] = ((Real)1.0)- ((Real)2.0) * Normal.z*Normal.z;
	this->Elements[14] = Dot_NP * Normal.z;

	this->Elements[3] = (Real)0.0;
	this->Elements[7] = (Real)0.0;
	this->Elements[11] = (Real)0.0;
	this->Elements[15] = (Real)1.0;

	return;
}
