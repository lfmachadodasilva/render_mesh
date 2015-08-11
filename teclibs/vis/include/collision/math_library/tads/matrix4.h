/**
* Classe responsavel por definir as operacoes necesserias sobre uma matriz 4x4
* @autor Fabio Nakamura
*/

#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include <math.h>
#include <memory.h>
#include "vector3.h"
#include "constants.h"
#include "matrix3.h"

template <class Real> class QUATERNION;
template <class Real> class MATRIX4
{
	private:

		

		/**
		* Usado no calculo da matriz adjunta e da matriz inversa
		*/
		 static Real Det_3x3(const Real a11,const Real a12,const Real a13,
							 const Real a21,const Real a22,const Real a23,
							 const Real a31,const Real a32,const Real a33);

		 static Real Det_2x2(const Real a11,const Real a12,const Real a21,const Real a22);

	public:

		/**
		* Os elementos da Matrix 4 x 4.
		*/
		/**
		* Os elementos serao dados no padrao da OpenGl.
		* onde o padrao e dado por Column Major Order.
		*/
		Real Elements[16];

		/**
		* Construtores
		*/

		/**
		* Construtor Vazio
		*/
		MATRIX4();

		/**
		* Construtor dado um vetor de elementos.
		*/
		/**
		* Constante
		*/
		MATRIX4(const Real* Elements);

		/**
		* Nao constante
		*/
		MATRIX4(Real* Elements);

		/**
		* Dado uma Matrix MATRIX4
		*/
		MATRIX4(const MATRIX4& Matrix);

		/**
		* Dado 3 vetores VECTOR, onde cada vetor sera uma coluna da matriz
		*/
		MATRIX4(const VECTOR3<Real>& V1,const VECTOR3<Real>& V2,
				const VECTOR3<Real>& V3,const VECTOR3<Real>& V4);

		/**
		* Dado os 16 Elementos
		*/
		MATRIX4(const Real a11,const Real a12,const Real a13,const Real a14,
				const Real a21,const Real a22,const Real a23,const Real a24,
				const Real a31,const Real a32,const Real a33,const Real a34,
				const Real a41,const Real a42,const Real a43,const Real a44);

		/**
		* Operadores de Acesso
		*/
		operator const Real*()const;
		operator Real*();
		MATRIX4& operator = (const MATRIX4& Matrix);

		

		/**
		* Operadores Algebricos
		*/

		/**
		* Operador de soma
		*/
        MATRIX4 operator + (const MATRIX4& Matrix)const;

		/**
		* Operador de subtracao
		*/
		MATRIX4 operator - (const MATRIX4& Matrix)const;

		/**
		* Operador de Multiplicacao entre um Escalar e uma Matrix
		*/
		MATRIX4 operator * (const Real Scalar)const;

		/**
		* Operador de Divisao entre um Escalar e uma Matrix
		* Se Scalar < Epsilon, entao retorna a propria matriz.
		*/
		MATRIX4 operator / (const Real Scalar)const;

		/**
		* Operador de Atualizacao matematico
		*/

		/**
		* Operador Mais igual
		*/
		MATRIX4& operator += (const MATRIX4& Matrix);

		/**
		* Operador menos igual
		*/
		MATRIX4& operator -= (const MATRIX4& Matrix);

		/**
		* Operadores escalares
		*/
		MATRIX4& operator *= (const Real Scalar);
		MATRIX4& operator /= (const Real Scalar);

		/**
		* Multiplica duas matrizes; A ordem e dada por : this*Matrix
		*/
		MATRIX4 Multiply(const MATRIX4& Matrix)const;

		/**
		* Multiplica duas matrizes 4x4 onde as matrizes sao do tipo | RS T |
		*															| 0  1 |
		*/
		MATRIX4 Multiply_RST(const MATRIX4& Matrix)const;

		/**
		* Multiplica duas matrizes; A ordem e dada por : this^T*Matrix
		*/
		MATRIX4 Multiply_Transpose(const MATRIX4& Matrix)const;

		/**
		* Dado uma matriz 3x3 multiplica a parte R da matriz 4x4
		*/
		MATRIX3<Real> Multiply_3x3(const MATRIX3<Real>& Matrix)const;

		/**
		* Operadores de Algebra Linear
		*/

		/**
		* Transforma esta matriz numa matriz identidade.
		*/
		void Set_Identity(void);

		/**
		* Transforma esta matriz numa matriz de translacao
		*/
		/**
		* Dado 3 valores Reais
		*/
		void Set_Translate(const Real X,const Real Y,const Real Z);

		/**
		* Dado um vetor tipo VECTOR3
		*/
		void Set_Translate(const VECTOR3<Real>& Vector);

		/**
		* Dado um vetor tipo Real*
		*/
		void Set_Translate(const Real* Vector);

		/**
		* Transforma esta matriz numa matriz de rotacao 
		*/

		/**
		* Matriz de rotacao em torno de X
		*/
		void Set_Rotate_X(const Real Angle);

		/**
		* Matriz de rotacao em torno de Y
		*/
		void Set_Rotate_Y(const Real Angle);

		/**
		* Matriz de rotacao em torno de Y
		*/
		void Set_Rotate_Z(const Real Angle);

		/**
		* Rotacao em torno de um eixo qualquer.
		*/
		void Set_Rotate(const Real X,const Real Y,const Real Z,const Real Angle);
		void Set_Rotate(const VECTOR3<Real>& Axis,const Real Angle);

		/**
		* Retorna a matriz transposta
		*/
		MATRIX4 Transpose(void)const;

		/**
		* Transforma a matriz em sua transposta.
		*/
		void Set_Transpose(void);


		/**
		* Retorna a inversa da matriz.
		*/
		MATRIX4 Inverse(void)const;

		/**
		* Retorna a matriz Adjunta 
		*/
		MATRIX4 Adjoint(void)const;


		/**
		* Retorna o determinante da matriz
		*/
		Real Det_4x4(void)const;

		/**
		* Retorna o quaternion associado a uma matriz de rotacao
		*/
		QUATERNION<Real> To_Quaternion(void)const;

		/**
		* Aplica a matriz a um vetor VECTOR3
		* A multiplicacao e dada por v'= M*v
		* v e um vetor tipo ( x,y,z,1)
		*/
		VECTOR3<Real> Multiply_Vector(const VECTOR3<Real>& Vector)const;

		/**
		* Aplica a matriz a um vetor VECTOR3
		* A multiplicacao e dada por v'= M^t*v
		* v e um vetor tipo ( x,y,z,1)
		*/
		VECTOR3<Real> Multiply_Transpose_Vector(const VECTOR3<Real>& Vector)const;


		/**
		* transforma um vetor por uma matriz tipo 4x4 onde a ultima linha
		* e igual a 0.0 0.0 0.0 1.0
		*/
		VECTOR3<Real> Affine_Transform(const VECTOR3<Real>& Vector)const;

		/**
		* Calcula as projecoes Oblica, Perpectiva e Reflectiva.
		*/

		void Make_Oblique_Projection(const VECTOR3<Real>& Normal,const VECTOR3<Real>& Point,const VECTOR3<Real>& Direction);
		void Make_Perspective_Projection(const VECTOR3<Real>& Normal,const VECTOR3<Real>& Point,const VECTOR3<Real>& Eye);
		void Make_Reflective_Projection(const VECTOR3<Real>& Normal,const VECTOR3<Real>& Point);


		/**
		* Set 
		*/
		void Set(const Real* Matrix);
		void Set(const MATRIX4<Real>& Matrix);
		void Set_Basis(const VECTOR3<Real> Axis_X,const VECTOR3<Real> Axis_Y,const VECTOR3<Real> Axis_Z);


		/**
		* Cria uma matriz de orientacao dado os tres angulos Pitch,
		* Yaw, Roll
		*/
		void Make_From_Euler(const Real Pitch,const Real Yaw,const Real Roll);

};
#include "matrix4.inl"

typedef MATRIX4<float> MATRIX4f;

#endif



