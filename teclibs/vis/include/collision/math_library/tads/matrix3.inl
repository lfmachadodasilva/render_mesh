/**
* Modulo de implementacao dos metodos da classe MATRIX3
* @author Fabio Nakamura
*/

#include <assert.h>
/**
* Construtores
*/
template <class Real> inline MATRIX3<Real>::MATRIX3()
{
}

template <class Real> inline MATRIX3<Real>::MATRIX3(Real* Elements)
{
	memcpy(this->Elements,Elements,sizeof(Real)*9);
}




template <class Real> inline MATRIX3<Real>::MATRIX3(const Real a11,const Real a12,const Real a13,
											 const Real a21,const Real a22,const Real a23,
											 const Real a31,const Real a32,const Real a33)											
{
	this->Elements[0] = a11;
	this->Elements[1] = a21;
	this->Elements[2] = a31;
	this->Elements[3] = a12;
	this->Elements[4] = a22;
	this->Elements[5] = a32;
	this->Elements[6] = a13;
	this->Elements[7] = a23;
	this->Elements[8] = a33;	
	
}

template <class Real> inline MATRIX3<Real>::MATRIX3(const MATRIX3& Matrix)
{
	memcpy(this->Elements,Matrix.Elements,sizeof(Real)*9);
}

template < class Real> inline MATRIX3<Real>::MATRIX3(const VECTOR3<Real>& V1,const VECTOR3<Real>& V2,
											  const VECTOR3<Real>& V3)
{
	this->Elements[0] = V1.x;
	this->Elements[1] = V1.y;
	this->Elements[2] = V1.z;
	
	this->Elements[3] = V2.x;
	this->Elements[4] = V2.y;
	this->Elements[5] = V2.z;
	
	this->Elements[6] = V3.x;
	this->Elements[7] = V3.y;
	this->Elements[8] = V3.z;
	

}


template <class Real> inline MATRIX3<Real>::operator const Real*()const
{
	return(this->Elements);
}

template <class Real> inline MATRIX3<Real>::operator Real*()
{
	return(this->Elements);
}

template <class Real> inline unsigned int MATRIX3<Real>::Get_Index(unsigned int row,unsigned int column)
{
	assert((row < 3) && (column < 3));

	return(row + 3*column);
}


template <class Real> inline MATRIX3<Real>& MATRIX3<Real>::operator = (const MATRIX3& Matrix)
{
	memcpy(this->Elements,Matrix.Elements,9*sizeof(Real));
	return(*this);
}

template <class Real> inline MATRIX3<Real> MATRIX3<Real>::operator + (const MATRIX3& Matrix)const
{
	return(MATRIX3(this->Elements[0] + Matrix.Elements[0],this->Elements[3] + Matrix.Elements[3],this->Elements[6] + Matrix.Elements[6],
				   this->Elements[1] + Matrix.Elements[1],this->Elements[4] + Matrix.Elements[4],this->Elements[7] + Matrix.Elements[7],
				   this->Elements[2] + Matrix.Elements[2],this->Elements[5] + Matrix.Elements[5],this->Elements[8] + Matrix.Elements[8]));
}

template <class Real> inline MATRIX3<Real> MATRIX3<Real>::operator - (const MATRIX3& Matrix)const
{
	return(MATRIX3(this->Elements[0] - Matrix.Elements[0],this->Elements[3] - Matrix.Elements[3],this->Elements[6] - Matrix.Elements[6],
				   this->Elements[1] - Matrix.Elements[1],this->Elements[4] - Matrix.Elements[4],this->Elements[7] - Matrix.Elements[7],
				   this->Elements[2] - Matrix.Elements[2],this->Elements[5] - Matrix.Elements[5],this->Elements[8] - Matrix.Elements[8]));
}

template <class Real> inline MATRIX3<Real> MATRIX3<Real>::operator * (const Real Scalar)const
{
	return(MATRIX3(this->Elements[0] * Scalar,this->Elements[3] * Scalar,this->Elements[6] * Scalar,
				   this->Elements[1] * Scalar,this->Elements[4] * Scalar,this->Elements[7] * Scalar,
				   this->Elements[2] * Scalar,this->Elements[5] * Scalar,this->Elements[8] * Scalar));
				  
}

template <class Real> inline MATRIX3<Real> MATRIX3<Real>::operator / (const Real Scalar)const
{
	if(Scalar > EPSILON)
	{
		float Inv_Scalar = 1.0f / Scalar;

		return(MATRIX3(this->Elements[0] * Inv_Scalar,this->Elements[3] * Inv_Scalar,this->Elements[6] * Inv_Scalar,
					   this->Elements[1] * Inv_Scalar,this->Elements[4] * Inv_Scalar,this->Elements[7] * Inv_Scalar,
					   this->Elements[2] * Inv_Scalar,this->Elements[5] * Inv_Scalar,this->Elements[8] * Inv_Scalar));
	}
	else
		return(MATRIX3(this->Elements));
}


/**
* Operadores de atualizacao
*/

template <class Real> inline MATRIX3<Real>& MATRIX3<Real>::operator += (const MATRIX3& Matrix)
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
	
	return(*this);
}

template <class Real> inline MATRIX3<Real>& MATRIX3<Real>::operator -= (const MATRIX3& Matrix)
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
	
	return(*this);
}


template <class Real> inline MATRIX3<Real>& MATRIX3<Real>::operator *= (const Real Scalar)
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
	
	return(*this);
}


template <class Real> inline  MATRIX3<Real>& MATRIX3<Real>::operator /= (const Real Scalar)
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
	}
	return(*this);
}


template <class Real> inline  MATRIX3<Real> MATRIX3<Real>::Multiply(const MATRIX3& Matrix)const
{
	//Real Temp[9];
	//memcpy(Temp,Matrix.Elements,9*sizeof(Real));

	/*return(MATRIX3(this->Elements[0]*Temp[0] + this->Elements[3]*Temp[1] + this->Elements[6]*Temp[2],
				   this->Elements[0]*Temp[3] + this->Elements[3]*Temp[4] + this->Elements[6]*Temp[5],
				   this->Elements[0]*Temp[6] + this->Elements[3]*Temp[7] + this->Elements[6]*Temp[8],
				   this->Elements[1]*Temp[0] + this->Elements[4]*Temp[1] + this->Elements[7]*Temp[2],
				   this->Elements[1]*Temp[3] + this->Elements[4]*Temp[4] + this->Elements[7]*Temp[5],
				   this->Elements[1]*Temp[6] + this->Elements[4]*Temp[7] + this->Elements[7]*Temp[8],
				   this->Elements[2]*Temp[0] + this->Elements[5]*Temp[1] + this->Elements[8]*Temp[2],
				   this->Elements[2]*Temp[3] + this->Elements[5]*Temp[4] + this->Elements[8]*Temp[5],
				   this->Elements[2]*Temp[6] + this->Elements[5]*Temp[7] + this->Elements[8]*Temp[8]));
*/
	return(MATRIX3(this->Elements[0]*Matrix.Elements[0] + this->Elements[3]*Matrix.Elements[1] + this->Elements[6]*Matrix.Elements[2],
				   this->Elements[0]*Matrix.Elements[3] + this->Elements[3]*Matrix.Elements[4] + this->Elements[6]*Matrix.Elements[5],
				   this->Elements[0]*Matrix.Elements[6] + this->Elements[3]*Matrix.Elements[7] + this->Elements[6]*Matrix.Elements[8],
				   this->Elements[1]*Matrix.Elements[0] + this->Elements[4]*Matrix.Elements[1] + this->Elements[7]*Matrix.Elements[2],
				   this->Elements[1]*Matrix.Elements[3] + this->Elements[4]*Matrix.Elements[4] + this->Elements[7]*Matrix.Elements[5],
				   this->Elements[1]*Matrix.Elements[6] + this->Elements[4]*Matrix.Elements[7] + this->Elements[7]*Matrix.Elements[8],
				   this->Elements[2]*Matrix.Elements[0] + this->Elements[5]*Matrix.Elements[1] + this->Elements[8]*Matrix.Elements[2],
				   this->Elements[2]*Matrix.Elements[3] + this->Elements[5]*Matrix.Elements[4] + this->Elements[8]*Matrix.Elements[5],
				   this->Elements[2]*Matrix.Elements[6] + this->Elements[5]*Matrix.Elements[7] + this->Elements[8]*Matrix.Elements[8]));
	
}

template <class Real> inline  MATRIX3<Real> MATRIX3<Real>::Multiply_Transpose(const MATRIX3& Matrix)const
{

	return(MATRIX3(this->Elements[0]*Matrix.Elements[0] + this->Elements[1]*Matrix.Elements[1] + this->Elements[2]*Matrix.Elements[2],
				   this->Elements[0]*Matrix.Elements[3] + this->Elements[1]*Matrix.Elements[4] + this->Elements[2]*Matrix.Elements[5],
				   this->Elements[0]*Matrix.Elements[6] + this->Elements[1]*Matrix.Elements[7] + this->Elements[2]*Matrix.Elements[8],
				   this->Elements[3]*Matrix.Elements[0] + this->Elements[4]*Matrix.Elements[1] + this->Elements[5]*Matrix.Elements[2],
				   this->Elements[3]*Matrix.Elements[3] + this->Elements[4]*Matrix.Elements[4] + this->Elements[5]*Matrix.Elements[5],
				   this->Elements[3]*Matrix.Elements[6] + this->Elements[4]*Matrix.Elements[7] + this->Elements[5]*Matrix.Elements[8],
				   this->Elements[6]*Matrix.Elements[0] + this->Elements[7]*Matrix.Elements[1] + this->Elements[8]*Matrix.Elements[2],
				   this->Elements[6]*Matrix.Elements[3] + this->Elements[7]*Matrix.Elements[4] + this->Elements[8]*Matrix.Elements[5],
				   this->Elements[6]*Matrix.Elements[6] + this->Elements[7]*Matrix.Elements[7] + this->Elements[8]*Matrix.Elements[8]));
}



template <class Real> inline  VECTOR3<Real> MATRIX3<Real>::Multiply_Vector(const VECTOR3<Real>& Vector)const
{
	return(VECTOR3<Real>(Vector.x*this->Elements[0] + Vector.y*this->Elements[3] + Vector.z*this->Elements[6],
		                 Vector.x*this->Elements[1] + Vector.y*this->Elements[4] + Vector.z*this->Elements[7],
						 Vector.x*this->Elements[2] + Vector.y*this->Elements[5] + Vector.z*this->Elements[8]));
	
}

template <class Real> inline  VECTOR3<Real> MATRIX3<Real>::Multiply_Transpose_Vector(const VECTOR3<Real>& Vector)const
{
	return(VECTOR3<Real>(Vector.x*this->Elements[0] + Vector.y*this->Elements[1] + Vector.z*this->Elements[2],
		                 Vector.x*this->Elements[3] + Vector.y*this->Elements[4] + Vector.z*this->Elements[5],
						 Vector.x*this->Elements[6] + Vector.y*this->Elements[7] + Vector.z*this->Elements[8]));
	
}

/**
* Operacoes de transformacao
*/

template <class Real> inline  void MATRIX3<Real>::Set_Identity(void)
{
	memset(this->Elements,0,9*sizeof(Real));
	this->Elements[0] = 
	this->Elements[4] = 
	this->Elements[8] = 1.0f;

	return;
}

template <class Real> inline  void MATRIX3<Real>::Set_Rotate_X(const Real Angle)
{
	float Cos = (Real)cos(DEG_TO_RAD(Angle));
	float Sin = (Real)sin(DEG_TO_RAD(Angle));

	this->Elements[0] = 1.0f;
	this->Elements[1] = 0.0f;
	this->Elements[2] = 0.0f;
	this->Elements[3] = 0.0f;
	this->Elements[4] = Cos;
	this->Elements[5] = Sin;
	this->Elements[6] = 0.0f;
	this->Elements[7] = -Sin;
	this->Elements[8] = Cos;
	return;
}

template <class Real> inline  void MATRIX3<Real>::Set_Rotate_Y(const Real Angle)
{
	float Cos = (Real)cos(DEG_TO_RAD(Angle));
	float Sin = (Real)sin(DEG_TO_RAD(Angle));

	this->Elements[0] = Cos;
	this->Elements[1] = 0.0f;
	this->Elements[2] = -Sin;
	this->Elements[3] = 0.0f;
	this->Elements[4] = 1.0f;
	this->Elements[5] = 0.0f;
	this->Elements[6] = Sin;
	this->Elements[7] = 0.0f;
	this->Elements[8] = Cos;
	return;
}


template <class Real> inline  void MATRIX3<Real>::Set_Rotate_Z(const Real Angle)
{
	float Cos = (Real)cos(DEG_TO_RAD(Angle));
	float Sin = (Real)sin(DEG_TO_RAD(Angle));

	this->Elements[0] = Cos;
	this->Elements[1] = Sin;
	this->Elements[2] = 0.0f;
	this->Elements[3] = -Sin;
	this->Elements[4] = Cos;
	this->Elements[5] = 0.0f;
	this->Elements[6] = 0.0f;
	this->Elements[7] = 0.0f;
	this->Elements[8] = 1.0f;
	
	return;
}

template <class Real> inline  void MATRIX3<Real>::Set_Rotate(const Real X,const Real Y,const Real Z,const Real Angle)
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
    Real Cos = (Real)cos(DEG_TO_RAD(Angle));
	Real Sin = (Real)sin(DEG_TO_RAD(Angle));

	/* Temos que normalizar os eixos de rotacao */
	Normal.Normalize();

	xn = Normal.x;
	yn = Normal.y;
	zn = Normal.z;

	t = (1 - Cos);
	X_2 = xn*xn;
	Y_2 = yn*yn;
	Z_2 = zn*zn;

	this->Elements[0] = Cos + t*X_2;
	this->Elements[3] = t*xn*yn - zn*Sin;
	this->Elements[6] = t*xn*zn + yn*Sin;
	this->Elements[1] = t*xn*yn + zn*Sin;
	this->Elements[4] = Cos + t*Y_2;
	this->Elements[7] = t*yn*zn - xn*Sin;
	this->Elements[2] = t*xn*zn - yn*Sin;
	this->Elements[5] = t*yn*zn + xn*Sin;
	this->Elements[8] = Cos + t*Z_2;

	return;
} 

template <class Real> inline  void MATRIX3<Real>::Set_Rotate(const VECTOR3<Real>& Vector,const Real Angle)
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
    Real Cos = cos(DEG_TO_RAD(Angle));
	Real Sin = sin(DEG_TO_RAD(Angle));

	/* Temos que normalizar os eixos de rotacao */
	Normal.Normalize();

	xn = Normal.x;
	yn = Normal.y;
	zn = Normal.z;

	t = (1 - Cos);
	X_2 = xn*xn;
	Y_2 = yn*yn;
	Z_2 = zn*zn;

	this->Elements[0] = Cos + t*X_2;
	this->Elements[3] = t*xn*yn - zn*Sin;
	this->Elements[6] = t*xn*zn + yn*Sin;
	this->Elements[1] = t*xn*yn + zn*Sin;
	this->Elements[4] = Cos + t*Y_2;
	this->Elements[7] = t*yn*zn - xn*Sin;
	this->Elements[2] = t*xn*zn - yn*Sin;
	this->Elements[5] = t*yn*zn + xn*Sin;
	this->Elements[8] = Cos + t*Z_2;
	return;

} 

template <class Real> inline  MATRIX3<Real> MATRIX3<Real>::Transpose(void)const
{
	return(MATRIX3(this->Elements[0],this->Elements[1],this->Elements[2],this->Elements[3],
				   this->Elements[4],this->Elements[5],this->Elements[6],this->Elements[7],this->Elements[8]));
}
template <class Real> inline  void MATRIX3<Real>::Set_Transpose(void)
{
	Real Temp[9];
	memcpy(Temp,this->Elements,sizeof(Real)*9);

	this->Elements[1] = Temp[3];
	this->Elements[2] = Temp[6];
	this->Elements[3] = Temp[1];
	this->Elements[5] = Temp[7];
	this->Elements[6] = Temp[2];
	this->Elements[7] = Temp[5];
		
	return;
}


template <class Real> inline  Real MATRIX3<Real>::Det_2x2(Real a11,Real a12,Real a21,Real a22)
{
	Real Result;

	Result = a11*a22 - a12*a21;
	return (Result);
}



template <class Real> inline  Real MATRIX3<Real>::Elem_Det_3x3(Real a11,Real a12,Real a13,
												  Real a21,Real a22,Real a23,
												  Real a31,Real a32,Real a33)
{

	Real Result;

	Result =  a11 * this->Det_2x2(a22,a23,a32,a33)
			- a21 * this->Det_2x2(a12,a13,a32,a33)
			+ a31 * this->Det_2x2(a12,a13,a22,a23);

	return Result;
}

template<class Real> inline Real MATRIX3<Real>::Det_3x3(void)
{
	return(this->Elem_Det_3x3(this->Elements[0],this->Elements[1],this->Elements[2],
		   this->Elements[3],this->Elements[4],this->Elements[5],
		   this->Elements[6],this->Elements[7],this->Elements[8]));
}
template<class Real> inline MATRIX3<Real> MATRIX3<Real>::Inverse(void)const
{
 // Invert a 3x3 using cofactors.  This is faster than using a generic
    // Gaussian elimination because of the loop overhead of such a method.

    MATRIX3<Real> Inverse;

	Inverse.Elements[0] = this->Elements[4]*this->Elements[8] - this->Elements[7]*this->Elements[5];
    Inverse.Elements[3] = this->Elements[6]*this->Elements[5] - this->Elements[3]*this->Elements[8];
    Inverse.Elements[6] = this->Elements[3]*this->Elements[7] - this->Elements[6]*this->Elements[4];
    Inverse.Elements[1] = this->Elements[7]*this->Elements[2] - this->Elements[1]*this->Elements[8];
    Inverse.Elements[4] = this->Elements[0]*this->Elements[8] - this->Elements[6]*this->Elements[2];
    Inverse.Elements[7] = this->Elements[6]*this->Elements[1] - this->Elements[0]*this->Elements[7];
    Inverse.Elements[2] = this->Elements[1]*this->Elements[5] - this->Elements[4]*this->Elements[2];
    Inverse.Elements[5] = this->Elements[3]*this->Elements[2] - this->Elements[0]*this->Elements[5];
    Inverse.Elements[8] = this->Elements[0]*this->Elements[4] - this->Elements[3]*this->Elements[1];

    Real Det = (this->Elements[0]*Inverse.Elements[0] + this->Elements[3]*Inverse.Elements[1]+
        this->Elements[6]*Inverse.Elements[3]);

     Inverse /= Det;
	 return Inverse;

}

template <class Real> inline  QUATERNION<Real> MATRIX3<Real>::To_Quaternion(void)const
{
	// O traco da matriz
	Real Trace;
	Real Root;
	Real Real_Temp;
	Real Temp[3][3];

	Temp[0][0] = this->Elements[0];
	Temp[0][1] = this->Elements[1];
	Temp[0][2] = this->Elements[2];
	Temp[1][0] = this->Elements[3];
	Temp[1][1] = this->Elements[4];
	Temp[1][2] = this->Elements[5];
	Temp[2][0] = this->Elements[6];
	Temp[2][1] = this->Elements[7];
	Temp[2][2] = this->Elements[8];
	
	Trace = Temp[0][0] + Temp[1][1] + Temp[2][2];

	if(Trace > 0.0f)
	{
		Root = sqrt(Trace + 1.0f); // == 2*W
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


		Root = sqrt(Temp[i][i] - Temp[j][j] - Temp[k][k] + 1.0f);
		Real* Quat_aux[3] = {&Result.Imaginary.x,&Result.Imaginary.y,&Result.Imaginary.z};
		*Quat_aux[i] = 0.5f*Root;
		Root = 0.5f/Root;
		Result.Real_Value = (Temp[k][j] - Temp[j][k])*Root;
		*Quat_aux[j] = (Temp[j][i] + Temp[i][j])*Root;
		*Quat_aux[k] = (Temp[k][i] + Temp[i][k])*Root;
		return(Result);
	}
}

template <class Real> inline  void MATRIX3<Real>::Build_Covariance_Matrix(const VECTOR3<Real>* Points,unsigned int Num_of_Points)
{
	Real Inv_n = (Real)1.0 / (Real)Num_of_Points;
	VECTOR3<Real> Center((Real)0.0,(Real)0.0,(Real)0.0);

	
	unsigned int i;

	/**
	* Centroid dos pontos.
	*/

	for( i = 0 ; i < Num_of_Points ; i+=1)
	{
		Center.x += Points[i].x;
		Center.y += Points[i].y;
		Center.z += Points[i].z;
	}
	Center.x *= Inv_n;
	Center.y *= Inv_n;
	Center.z *= Inv_n;

	// Matriz de covariancia

	Real e00 = (Real)0.0;
	Real e11 = (Real)0.0;
	Real e22 = (Real)0.0;
	Real e01 = (Real)0.0;
	Real e02 = (Real)0.0;
	Real e12 = (Real)0.0;

	VECTOR3<Real> Diff;
	for( i = 0 ; i < Num_of_Points ; i+=1)
	{
		Diff.x = Points[i].x - Center.x;
		Diff.y = Points[i].y - Center.y;
		Diff.z = Points[i].z - Center.z;

		e00 += Diff.x * Diff.x;
		e11 += Diff.y * Diff.y;
		e22 += Diff.z * Diff.z;
		e01 += Diff.x * Diff.y;
		e02 += Diff.x * Diff.z;
		e12 += Diff.y * Diff.z;
	}

	this->Elements[0] = e00*Inv_n;
	this->Elements[4] = e11*Inv_n;
	this->Elements[8] = e22*Inv_n;
	this->Elements[1] = this->Elements[3] = e01*Inv_n;
	this->Elements[2] = this->Elements[6] = e02*Inv_n;
	this->Elements[5] = this->Elements[7] = e12*Inv_n;
	return;
}


template <class Real> inline  void MATRIX3<Real>::Build_Covariance_Matrix(const Real* Points,unsigned int Num_of_Points)
{
	Real Inv_n = (Real)1.0 / (Real)Num_of_Points;
	VECTOR3<Real> Center((Real)0.0,(Real)0.0,(Real)0.0);

	
	unsigned int i;
	unsigned int Num_of_Points_3 = Num_of_Points*3;

	/**
	* Centroid dos pontos.
	*/

	for( i = 0 ; i < Num_of_Points_3 ; i+=3)
	{
		Center.x += Points[i];
		Center.y += Points[i+1];
		Center.z += Points[i+2];
	}
	Center.x *= Inv_n;
	Center.y *= Inv_n;
	Center.z *= Inv_n;

	// Matriz de covariancia

	Real e00 = (Real)0.0;
	Real e11 = (Real)0.0;
	Real e22 = (Real)0.0;
	Real e01 = (Real)0.0;
	Real e02 = (Real)0.0;
	Real e12 = (Real)0.0;

	VECTOR3<Real> Diff;
	for( i = 0 ; i < Num_of_Points_3 ; i+=1)
	{
		Diff.x = Points[i] - Center.x;
		Diff.y = Points[i+=1] - Center.y;
		Diff.z = Points[i+=1] - Center.z;

		e00 += Diff.x * Diff.x;
		e11 += Diff.y * Diff.y;
		e22 += Diff.z * Diff.z;
		e01 += Diff.x * Diff.y;
		e02 += Diff.x * Diff.z;
		e12 += Diff.y * Diff.z;
	}

	this->Elements[0] = e00*Inv_n;
	this->Elements[4] = e11*Inv_n;
	this->Elements[8] = e22*Inv_n;
	this->Elements[1] = this->Elements[3] = e01*Inv_n;
	this->Elements[2] = this->Elements[6] = e02*Inv_n;
	this->Elements[5] = this->Elements[7] = e12*Inv_n;
	return;
}

template <class Real> inline  void MATRIX3<Real>::Set(const Real* Matrix)
{
	memcpy(this->Elements,Matrix,9*sizeof(Real));
	return;
}

template <class Real> inline  void MATRIX3<Real>::Set(const MATRIX3<Real>& Matrix)
{
	memcpy(this->Elements,Matrix.Elements,9*sizeof(Real));
	return;
}

template <class Real> inline void MATRIX3<Real>::Set_Basis(const VECTOR3<Real> Axis_X,const VECTOR3<Real> Axis_Y,const VECTOR3<Real> Axis_Z)
{
	this->Elements[0] = Axis_X.x;
	this->Elements[1] = Axis_X.y;
	this->Elements[2] = Axis_X.z;

	this->Elements[3] = Axis_Y.x;
	this->Elements[4] = Axis_Y.y;
	this->Elements[5] = Axis_Y.z;

	this->Elements[6] = Axis_Z.x;
	this->Elements[7] = Axis_Z.y;
	this->Elements[8] = Axis_Z.z;
	return;
}


template <class Real> inline  void MATRIX3<Real>::Make_From_Euler(const Real Pitch,const Real Yaw,const Real Roll)
{
	Real c_Pitch = (Real)cos(DEG_TO_RAD(Pitch));
	Real c_Yaw = (Real)cos(DEG_TO_RAD(Yaw));
	Real c_Roll = (Real)cos(DEG_TO_RAD(Roll));

	Real s_Pitch = (Real)sin(DEG_TO_RAD(Pitch));
	Real s_Yaw = (Real)sin(DEG_TO_RAD(Yaw));
	Real s_Roll = (Real)sin(DEG_TO_RAD(Roll));


	this->Elements[0] = c_Roll*c_Yaw - s_Roll*s_Pitch*s_Yaw;
	this->Elements[1] = s_Roll*c_Yaw + c_Roll*s_Pitch*s_Yaw;
	this->Elements[2] = -c_Pitch*s_Yaw;
	
	this->Elements[3] = -s_Roll*c_Pitch;
	this->Elements[4] = c_Roll*c_Pitch;
	this->Elements[5] = s_Pitch;
	
	this->Elements[6] = c_Roll*s_Yaw + s_Roll*s_Pitch*c_Yaw;
	this->Elements[7] = s_Roll*s_Yaw - c_Roll*s_Pitch*c_Yaw;
	this->Elements[8] = c_Pitch*c_Yaw;
	
	return;
}

template <class Real> inline  void MATRIX3<Real>::SymSchum(const MATRIX3<Real>& Matrix,unsigned int p,unsigned int q,
												  Real& Sin,Real& Cos)
{
	if( fabs((Real)(Matrix.Elements[MATRIX3<Real>::Get_Index(p,q)])) > EPSILON)
	{
		Real r = (Matrix.Elements[MATRIX3<Real>::Get_Index(q,q)] - Matrix.Elements[MATRIX3<Real>::Get_Index(p,p)])
					/((Real)2.0 * Matrix.Elements[MATRIX3<Real>::Get_Index(p,q)]);
		Real t;
		if( r > (Real)0.0)
			t = (Real)1.0 / (r + sqrt((Real)1.0 + r*r));
		else
			t = (Real)-1.0 / (-r + sqrt((Real)1.0 + r*r));

		Cos = (Real)1.0 / sqrt( (Real)1.0 + t*t);
		Sin = t*Cos;
	}
	else
	{
		Cos = (Real)1.0;
		Sin = (Real)0.0;
	}
	return;
}


template <class Real> inline  void MATRIX3<Real>::EigenDecomposition(MATRIX3<Real>& Result,VECTOR3<Real>& EigenValues)const
{
	/**
	* Usa-se o metodo de JACOBI para determinar os autovalores e auto vetores.
	*/
	unsigned int i,j,n,p,q;
	Real prevoff,cos,sin;
	MATRIX3<Real> Jacobi;
	MATRIX3<Real> B;
	MATRIX3<Real> T;
	
	Result.Set_Identity();
	B.Set(*this);

	for( n = 0 ; n < MAX_ITERATIONS ; n+=1)
	{
		p = 0;
		q = 1;
		for( i = 0 ; i < 3 ; i+=1)
		{
			for( j = 0 ; j < 3 ; j+=1)
			{
				if( j == i)
					continue;
				if(fabs(B.Elements[MATRIX3<Real>::Get_Index(i,j)]) > fabs(B.Elements[MATRIX3<Real>::Get_Index(p,q)]))
				{
					p = i;
					q = j;
				}
			}
		}
	

		MATRIX3<Real>::SymSchum(B,p,q,sin,cos);
		Jacobi.Set_Identity();
		
		Jacobi.Elements[MATRIX3<Real>::Get_Index(p,p)] = cos;
		Jacobi.Elements[MATRIX3<Real>::Get_Index(p,q)] = sin;
		Jacobi.Elements[MATRIX3<Real>::Get_Index(q,p)] = -sin;
		Jacobi.Elements[MATRIX3<Real>::Get_Index(q,q)] = cos;

		Result = Result.Multiply(Jacobi);

		
		T = Jacobi.Transpose();
		B = T.Multiply(B);
		B = B.Multiply(Jacobi);

		Real off = (Real)0.0;
		prevoff = (Real)0.0;
		for( i = 0 ; i < 3 ; i+=1)
		{
			for( j = 0 ; j < 3 ; j+=1)
			{
				if(i==j)
					continue;
				off += B.Elements[MATRIX3<Real>::Get_Index(i,j)]*B.Elements[MATRIX3<Real>::Get_Index(i,j)];
			}
		}

		if( n > 2 && off >= prevoff)
		{
			Real Temp;
			
			/**
			* Ordena por ordem de maior para o menor autovalor.
			*/

			// 2 coluna maior que 1 
			if(B.Elements[4] > B.Elements[0])
			{
				Temp = Result.Elements[3];
				Result.Elements[3] = Result.Elements[0];
				Result.Elements[0] = Temp;
				Temp = Result.Elements[4];
				Result.Elements[4] = Result.Elements[1];
				Result.Elements[1] = Temp;
				Temp = Result.Elements[5];
				Result.Elements[5] = Result.Elements[2];
				Result.Elements[2] = Temp;
				Temp = B.Elements[4];
				B.Elements[4] = B.Elements[0];
				B.Elements[0] = Temp;

			}	

			// 3 coluna maior que 2 
			if(B.Elements[8] > B.Elements[4])
			{
				Temp = Result.Elements[6];
				Result.Elements[6] = Result.Elements[3];
				Result.Elements[3] = Temp;
				Temp = Result.Elements[7];
				Result.Elements[7] = Result.Elements[4];
				Result.Elements[4] = Temp;
				Temp = Result.Elements[8];
				Result.Elements[8] = Result.Elements[5];
				Result.Elements[5] = Temp;
				Temp = B.Elements[8];
				B.Elements[8] = B.Elements[4];
				B.Elements[4] = Temp;

			}	

			// 2 coluna maior que 1 
			if(B.Elements[4] > B.Elements[0])
			{
				Temp = Result.Elements[3];
				Result.Elements[3] = Result.Elements[0];
				Result.Elements[0] = Temp;
				Temp = Result.Elements[4];
				Result.Elements[4] = Result.Elements[1];
				Result.Elements[1] = Temp;
				Temp = Result.Elements[5];
				Result.Elements[5] = Result.Elements[2];
				Result.Elements[2] = Temp;
				Temp = B.Elements[4];
				B.Elements[4] = B.Elements[0];
				B.Elements[0] = Temp;

			}	
			EigenValues.Set(B.Elements[0],B.Elements[4],B.Elements[8]);			
			return;
		}

		prevoff = off;
	}

	Real Temp;
			
	/**
	* Ordena por ordem de maior para o menor autovalor.
	*/

	// 2 coluna maior que 1 
	if(B.Elements[4] > B.Elements[0])
	{
		Temp = Result.Elements[3];
		Result.Elements[3] = Result.Elements[0];
		Result.Elements[0] = Temp;
		Temp = Result.Elements[4];
		Result.Elements[4] = Result.Elements[1];
		Result.Elements[1] = Temp;
		Temp = Result.Elements[5];
		Result.Elements[5] = Result.Elements[2];
		Result.Elements[2] = Temp;
		Temp = B.Elements[4];
		B.Elements[4] = B.Elements[0];
		B.Elements[0] = Temp;

	}	
	// 3 coluna maior que 2 
	if(B.Elements[8] > B.Elements[4])
	{
		Temp = Result.Elements[6];
		Result.Elements[6] = Result.Elements[3];
		Result.Elements[3] = Temp;
		Temp = Result.Elements[7];
		Result.Elements[7] = Result.Elements[4];
		Result.Elements[4] = Temp;
		Temp = Result.Elements[8];
		Result.Elements[8] = Result.Elements[5];
		Result.Elements[5] = Temp;
		Temp = B.Elements[8];
		B.Elements[8] = B.Elements[4];
		B.Elements[4] = Temp;
	}	

	// 2 coluna maior que 1 
	if(B.Elements[4] > B.Elements[0])
	{
		Temp = Result.Elements[3];
		Result.Elements[3] = Result.Elements[0];
		Result.Elements[0] = Temp;
		Temp = Result.Elements[4];
		Result.Elements[4] = Result.Elements[1];
		Result.Elements[1] = Temp;
		Temp = Result.Elements[5];
		Result.Elements[5] = Result.Elements[2];
		Result.Elements[2] = Temp;
		Temp = B.Elements[4];
		B.Elements[4] = B.Elements[0];
		B.Elements[0] = Temp;
	}	
	EigenValues.Set(B.Elements[0],B.Elements[4],B.Elements[8]);			
	return;
}

template <class Real> inline  void MATRIX3<Real>::EigenDecomposition(Real* vResult,Real* EigenValues)const
{
	/**
	* Usa-se o metodo de JACOBI para determinar os autovalores e auto vetores.
	*/
	unsigned int i,j,n,p,q;
	Real prevoff,cos,sin;
	MATRIX3<Real> Jacobi;
	MATRIX3<Real> B;
	MATRIX3<Real> T;
	MATRIX3<Real>Result;

	
	Result.Set_Identity();
	B.Set(*this);

	for( n = 0 ; n < MAX_ITERATIONS ; n+=1)
	{
		p = 0;
		q = 1;
		for( i = 0 ; i < 3 ; i+=1)
		{
			for( j = 0 ; j < 3 ; j+=1)
			{
				if( j == i)
					continue;
				if(fabs(B.Elements[MATRIX3<Real>::Get_Index(i,j)]) > fabs(B.Elements[MATRIX3<Real>::Get_Index(p,q)]))
				{
					p = i;
					q = j;
				}
			}
		}
	

		MATRIX3<Real>::SymSchum(B,p,q,sin,cos);
		Jacobi.Set_Identity();
		
		Jacobi.Elements[MATRIX3<Real>::Get_Index(p,p)] = cos;
		Jacobi.Elements[MATRIX3<Real>::Get_Index(p,q)] = sin;
		Jacobi.Elements[MATRIX3<Real>::Get_Index(q,p)] = -sin;
		Jacobi.Elements[MATRIX3<Real>::Get_Index(q,q)] = cos;

		Result = Result.Multiply(Jacobi);

		
		T = Jacobi.Transpose();
		B = T.Multiply(B);
		B = B.Multiply(Jacobi);

		Real off = (Real)0.0;
		prevoff = (Real)0.0;
		for( i = 0 ; i < 3 ; i+=1)
		{
			for( j = 0 ; j < 3 ; j+=1)
			{
				if(i==j)
					continue;
				off += B.Elements[MATRIX3<Real>::Get_Index(i,j)]*B.Elements[MATRIX3<Real>::Get_Index(i,j)];
			}
		}

		if( n > 2 && off >= prevoff)
		{
			Real Temp;
			
			/**
			* Ordena por ordem de maior para o menor autovalor.
			*/

			// 2 coluna maior que 1 
			if(B.Elements[4] > B.Elements[0])
			{
				Temp = Result.Elements[3];
				Result.Elements[3] = Result.Elements[0];
				Result.Elements[0] = Temp;
				Temp = Result.Elements[4];
				Result.Elements[4] = Result.Elements[1];
				Result.Elements[1] = Temp;
				Temp = Result.Elements[5];
				Result.Elements[5] = Result.Elements[2];
				Result.Elements[2] = Temp;
				Temp = B.Elements[4];
				B.Elements[4] = B.Elements[0];
				B.Elements[0] = Temp;

			}	

			// 3 coluna maior que 2 
			if(B.Elements[8] > B.Elements[4])
			{
				Temp = Result.Elements[6];
				Result.Elements[6] = Result.Elements[3];
				Result.Elements[3] = Temp;
				Temp = Result.Elements[7];
				Result.Elements[7] = Result.Elements[4];
				Result.Elements[4] = Temp;
				Temp = Result.Elements[8];
				Result.Elements[8] = Result.Elements[5];
				Result.Elements[5] = Temp;
				Temp = B.Elements[8];
				B.Elements[8] = B.Elements[4];
				B.Elements[4] = Temp;

			}	

			// 2 coluna maior que 1 
			if(B.Elements[4] > B.Elements[0])
			{
				Temp = Result.Elements[3];
				Result.Elements[3] = Result.Elements[0];
				Result.Elements[0] = Temp;
				Temp = Result.Elements[4];
				Result.Elements[4] = Result.Elements[1];
				Result.Elements[1] = Temp;
				Temp = Result.Elements[5];
				Result.Elements[5] = Result.Elements[2];
				Result.Elements[2] = Temp;
				Temp = B.Elements[4];
				B.Elements[4] = B.Elements[0];
				B.Elements[0] = Temp;

			}	
			EigenValues[0] = B.Elements[0];
			EigenValues[1] = B.Elements[4];
			EigenValues[2] = B.Elements[8];
			memcpy(vResult,Result.Elements,sizeof(Real)*9);
			return;
		}

		prevoff = off;
	}

	Real Temp;
			
	/**
	* Ordena por ordem de maior para o menor autovalor.
	*/

	// 2 coluna maior que 1 
	if(B.Elements[4] > B.Elements[0])
	{
		Temp = Result.Elements[3];
		Result.Elements[3] = Result.Elements[0];
		Result.Elements[0] = Temp;
		Temp = Result.Elements[4];
		Result.Elements[4] = Result.Elements[1];
		Result.Elements[1] = Temp;
		Temp = Result.Elements[5];
		Result.Elements[5] = Result.Elements[2];
		Result.Elements[2] = Temp;
		Temp = B.Elements[4];
		B.Elements[4] = B.Elements[0];
		B.Elements[0] = Temp;

	}	
	// 3 coluna maior que 2 
	if(B.Elements[8] > B.Elements[4])
	{
		Temp = Result.Elements[6];
		Result.Elements[6] = Result.Elements[3];
		Result.Elements[3] = Temp;
		Temp = Result.Elements[7];
		Result.Elements[7] = Result.Elements[4];
		Result.Elements[4] = Temp;
		Temp = Result.Elements[8];
		Result.Elements[8] = Result.Elements[5];
		Result.Elements[5] = Temp;
		Temp = B.Elements[8];
		B.Elements[8] = B.Elements[4];
		B.Elements[4] = Temp;
	}	

	// 2 coluna maior que 1 
	if(B.Elements[4] > B.Elements[0])
	{
		Temp = Result.Elements[3];
		Result.Elements[3] = Result.Elements[0];
		Result.Elements[0] = Temp;
		Temp = Result.Elements[4];
		Result.Elements[4] = Result.Elements[1];
		Result.Elements[1] = Temp;
		Temp = Result.Elements[5];
		Result.Elements[5] = Result.Elements[2];
		Result.Elements[2] = Temp;
		Temp = B.Elements[4];
		B.Elements[4] = B.Elements[0];
		B.Elements[0] = Temp;
	}	
	EigenValues[0] = B.Elements[0];
	EigenValues[1] = B.Elements[4];
	EigenValues[2] = B.Elements[8];	
	memcpy(vResult,Result.Elements,sizeof(Real)*9);

	return;
}

