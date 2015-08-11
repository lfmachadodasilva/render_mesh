/**
* Classe responsavel por definir as operacoes necesserias sobre uma matriz 3x3
* @autor Fabio Nakamura
*/

#ifndef __MATRIX3_H__
#define __MATRIX3_H__

#include <math.h>
#include <memory.h>
#include "vector3.h"
#include "constants.h"

template <class Real>class QUATERNION;
template <class Real> class MATRIX3
{
	private:

		
		 /**
		 * Usado no calculo da matriz adjunta e da matriz inversa
		 */
		 Real Elem_Det_3x3(Real a11,Real a12,Real a13,
						   Real a21,Real a22,Real a23,
						   Real a31,Real a32,Real a33);

		 Real Det_2x2(Real a11,Real a12,Real a21,Real a22);

		 /**
		 * Usado no metodo de JACOBI para decomposicao de autovalores e 
		 * autovetores.
		 */
		 static void SymSchum(const MATRIX3<Real>& Matrix,unsigned int p,unsigned q,Real& Sin,Real& Cos);

	public:

		/**
		* Os elementos da Matrix 3 x 3.
		*/
		/**
		* Os elementos serao dados no padrao da OpenGl.
		* onde o padrao e dado por Column Major Order.
		*/
		Real Elements[9];

		/**
		* Construtores
		*/

		/**
		* Construtor Vazio
		*/
		MATRIX3();

		/**
		* Construtor dado um vetor de elementos.
		*/
		/**
		* Constante
		*/
		MATRIX3(const Real* Elements);

		/**
		* Nao constante
		*/
		MATRIX3(Real* Elements);

		/**
		* Dado uma Matrix MATRIX4
		*/
		MATRIX3(const MATRIX3& Matrix);

		/**
		* Dado 3 vetores VECTOR, onde cada vetor sera uma coluna da matriz
		*/
		MATRIX3(const VECTOR3<Real>& V1,const VECTOR3<Real>& V2,
				const VECTOR3<Real>& V3);

		/**
		* Dado os 16 Elementos
		*/
		MATRIX3(const Real a11,const Real a12,const Real a13,
				const Real a21,const Real a22,const Real a23,
				const Real a31,const Real a32,const Real a33);
		
		/**
		* Operadores de Acesso
		*/
		operator const Real*()const;
		operator Real*();
		MATRIX3& operator = (const MATRIX3& Matrix);

		/**
		* Operadores Algebricos
		*/

		/**
		* Operador de soma
		*/
        MATRIX3 operator + (const MATRIX3& Matrix)const;

		/**
		* Operador de subtracao
		*/
		MATRIX3 operator - (const MATRIX3& Matrix)const;

		/**
		* Operador de Multiplicacao entre um Escalar e uma Matrix
		*/
		MATRIX3 operator * (const Real Scalar)const;

		/**
		* Operador de Divisao entre um Escalar e uma Matrix
		* Se Scalar < Epsilon, entao retorna a propria matriz.
		*/
		MATRIX3 operator / (const Real Scalar)const;

		/**
		* Operador de Atualizacao matematico
		*/

		/**
		* Operador Mais igual
		*/
		MATRIX3& operator += (const MATRIX3& Matrix);

		/**
		* Operador menos igual
		*/
		MATRIX3& operator -= (const MATRIX3& Matrix);

		/**
		* Operadores escalares
		*/
		MATRIX3& operator *= (const Real Scalar);
		MATRIX3& operator /= (const Real Scalar);

		/**
		* Multiplica duas matrizes; A ordem e dada por : this*Matrix
		*/
		MATRIX3 Multiply(const MATRIX3& Matrix)const;

		/**
		* Multiplica a matriz transposta que chamou o metodo pela matriz dada
		* como argumento. A ordem e dada por : this*Matrix
		*/
		MATRIX3 Multiply_Transpose(const MATRIX3& Matrix)const;

		/**
		* Operadores de Algebra Linear
		*/

		/**
		* Transforma esta matriz numa matriz identidade.
		*/
		void Set_Identity(void);
		
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
		MATRIX3 Transpose(void)const;

		/**
		* Transforma a matriz em sua transposta.
		*/
		void Set_Transpose(void);


		/**
		* Retorna a inversa da matriz.
		*/
		MATRIX3 Inverse(void)const;

		/**
		* Retorna a matriz Adjunta 
		*/
		MATRIX3 Adjoint(void)const;


		/**
		* Retorna o determinante da matriz
		*/
		Real Det_3x3(void);

		/**
		* Retorna o quaternion associado a uma matriz de rotacao
		*/
		QUATERNION<Real> To_Quaternion(void)const;

		/**
		* Aplica a matriz a um vetor VECTOR3
		* A multiplicacao e dada por v'= M*v
		* v e um vetor tipo ( x,y,z)
		*/
		VECTOR3<Real> Multiply_Vector(const VECTOR3<Real>& Vector)const;

		/**
		* Multiplica a transposta desta matriz pelo vetor
		* v' = M^t v
		*/
		VECTOR3<Real> Multiply_Transpose_Vector(const VECTOR3<Real>& Vector)const;

		/**
		* Set 
		*/
		void Set(const Real* Matrix);
		void Set(const MATRIX3<Real>& Matrix);
		void Set_Basis(const VECTOR3<Real> Axis_X,const VECTOR3<Real> Axis_Y,const VECTOR3<Real> Axis_Z);

		/**
		* Cria uma matriz de orientacao dado os tres angulos Pitch,
		* Yaw, Roll
		*/
		void Make_From_Euler(const Real Pitch,const Real Yaw,const Real Roll);

		/**
		* Operadores de matrizes
		*/
		/**
		* Dada uma matriz 3x3 e simetrica entao retorna uma matriz onde
		* as colunas de M serao os auto-vetores os auto valores serao retornados
		* no vetor.
		* os auto valores.
		*/
		void EigenDecomposition(MATRIX3<Real>& Result,VECTOR3<Real>& EigenValues)const;

		/**
		* Dada uma matriz 3x3 e simetrica entao retorna uma matriz onde
		* as colunas de M serao os auto-vetores os auto valores serao retornados
		* no vetor.
		* os auto valores.
		*/
		void EigenDecomposition(Real* Result,Real* EigenValues)const;

		/**
		* Dado um vetor de pontos 3d no espaco e a quantidade de pontos.
		* constroi a matriz de covariancia desses pontos.
		*/
		void Build_Covariance_Matrix(const VECTOR3<Real>* Points,unsigned int Num_of_Points);

		/**
		* Dado um vetor de pontos 3d no espaco e a quantidade de pontos.
		* constroi a matriz de covariancia desses pontos.
		*/
		void Build_Covariance_Matrix(const Real* Points,unsigned int Num_of_Points);


		/**
		* Operador indexador
		*/
		/**
		* Dado dois valores p e q retorna o indice que representa elemento no
		* vetor da matriz.
		*/
		static unsigned int Get_Index(unsigned int row,unsigned int column);

};
#include "matrix3.inl"

typedef MATRIX3<float> MATRIX3f;

#endif



