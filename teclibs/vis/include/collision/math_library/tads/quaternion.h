/**
* Modulo de definicao de uma classe quaternion.
* @author: Fabio Nakamura
*/

#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "vector3.h"
#include "matrix4.h"
#include "matrix3.h"

template <class Real> class QUATERNION
{
	public:

		/**
		* A parte real do quaternion
		*/
		Real Real_Value;

		/**
		* A parte imginaria do quaternion
		*/
		VECTOR3<Real> Imaginary;

	
		/**
		* Construtores
		*/

		/**
		* Construtor Vazio
		*/
		QUATERNION();

		/**
		*Construtor dado um numero real e um vetor
		*/
		QUATERNION(const Real Real_Value,const VECTOR3<Real>& Imaginary);
	
		/**
		* Dado 4 valores escalaras
		*/
		QUATERNION(const Real Real_Value,const Real Axis_x,const Real Axis_y,const Real Axis_z);

		/**
		* Dado um angulo e um eixo de rotacao
		*/
		QUATERNION(const VECTOR3<Real>& Axis,const Real Angle);

		/**
		* Dado um outro Quaternion
		*/
		QUATERNION(const QUATERNION<Real>& Quaternion);

		/**
		* Operadores Logicos
		*/
		
		/**
		* Operador de igualdade
		*/
		bool operator == (const QUATERNION<Real>& Quaternion)const;

		/**
		* Operador de desigualdade
		*/
		bool operator != (const QUATERNION<Real>& Quaternion)const;
		
		/**
		* Operadores sobre Quaternion
		*/

		/**
		* Soma dois quaternions
		*/
		QUATERNION operator + (const QUATERNION<Real>& Quaternion)const;

		/**
		* Subtrai dois quaternions
		*/
		QUATERNION operator - (const QUATERNION<Real>& Quaternion)const;

		/**
		* Multiplica dois quaternions
		*/
		//TODO
		QUATERNION operator * (const QUATERNION<Real>& Quaternion)const;


		/**
		* Operacoes elementares
		*/

		/**
		* Retorna o conjugado deste quaternion
		*/
		QUATERNION Get_Conjugate(void) const;

		/**
		* Transforma o quaternion em seu conjugado
		*/
		void Apply_Conjugate(void);

		/**
		* Retorna a norma do quaternion
		*/
		Real Norma(void)const;

		/**
		* Retorna o quadrado da norma deste quaternion
		*/
		Real Square_Norma(void)const;

		/**
		* Normaliza este quaternion
		* Se norma for menor que EPSILON, entao nao faz nada.
		*/
		void Normalize(void);

		/**
		* Aplica um dot entre as partes imaginarias
		*/
		Real Imaginary_Dot(const QUATERNION<Real>& Q)const;

		/**
		* Retorna o quaternion normalizado
		*/
		QUATERNION Get_Normalize(void)const;

		/**
		* Transforma o quaternion numa matriz 4x4
		*/
		MATRIX4<Real> To_Matrix_4x4(void);
		MATRIX3<Real> To_Matrix_3x3(void);

		/**
		* Metodos de Set
		*/
		void Set(const Real Real_Value,const VECTOR3<Real>& Imaginary);
		void Set(const Real Real_Value,const Real Axis_X,const Real Axis_Y,const Real Axis_Z);
		void Set(const QUATERNION<Real>& Quaternion);

		/**
		* Dado um angulo e um Eixo determina o quaternion responsavel pela rotacao
		*/
		void Set_Rotation(const Real Angle,const VECTOR3<Real>& Axis);
		void Set_Rotation(const Real Angle,const Real Axis_x,const Real Axis_y,const Real Axis_z);

		/**
		* Rotaciona um vetor dado um quaternion de rotacao.
		* O vetor e rotacionado por 
		*/
		VECTOR3<Real> Apply_Rotation(const VECTOR3<Real>& Vector)const;

		/**
		* Rotaciona um quaternion dado um outro quaternion
		*/
		QUATERNION<Real> Apply_Rotation(const QUATERNION<Real>& Quaternion)const;


		/**
		* Calcula o inverso de um quaternion de rotacao.
		*/
		QUATERNION<Real> Get_Inverse(void)const;

		/**
		* Transforma o quaternion que chamou o metodo em seu inverso
		*/
		void Apply_Inverse(void);

		/**
		* Dado os angulos de Euller, constroi o quaternion que representa a rotacao
		*/
		void Set_From_Euler(const Real Pitch,const Real Yaw,const Real Roll);

};
#include "quaternion.inl"

typedef QUATERNION<float> QUATERNIONf;

#endif
