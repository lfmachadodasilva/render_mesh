/**
* Classe responsavel por definir as operacoes necesserias sobre um vetor 3D
* @autor Fabio Nakamura
*/

#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__

#include <math.h>
#include "constants.h"

template <class Real> class VECTOR3
{
	public:

		/*
		* As coordenadas do vetor
		*/
		
		/**
		* coordenada X
		*/
		Real x;

		/**
		* coordenada Y
		*/
		Real y;

		/**
		* coordenada Z
		*/
		Real z;

		/**
		* Construtores da classe
		*/

		/**
		* Cosntrutor Vazio
		*/
        VECTOR3();

		/**
		* Construtor recebendo as coordenadas X,Y,Z
		*/
		VECTOR3(const Real X,const Real Y,const Real Z);

		/**
		* Construtor recebendo um outro VECTOR3
		*/
		VECTOR3(const VECTOR3& Vector);

		/**
		* Dado um vetor de Real.
		*/
		/**
		* Constante
		*/
		VECTOR3(const Real* Vector);
		
		/**
		* Nao constante
		*/
		VECTOR3(Real* Vector);

		/**
		* Operadores da classe
		*/

		/**
		* Operadores de Comparacao
		*/

		/**
		* Igualdade entre dois vetores
		*/
		bool operator ==(const VECTOR3& Vector)const;

		/**
		* Sao diferentes ?
		*/
		bool operator !=(const VECTOR3& Vector)const;

		/**
		* Operadores de Acesso
		*/
		operator const Real*()const;
		operator Real*();
		VECTOR3& operator = (const VECTOR3& Vector);

		/**
		* Operadores matematicos
		*/

		/**
		* Retorna a soma de dois vetores
		*/
		VECTOR3 operator + (const VECTOR3& Vector)const;

		/**
		* Retorna a diferenca entre dois vetores
		*/
		VECTOR3 operator - (const VECTOR3& Vector)const;

		/**
		* Retorna o vetor multiplicado pelo escalar scalar
		*/
		VECTOR3 operator * (const Real Scalar)const;

		/**
		* Retorna o vetor dividido pelo escalar scalar
		*/
		VECTOR3 operator / (const Real Scalar)const;

		/**
		* Retorna o inverso do vetor
		*/
		VECTOR3 operator -(void)const;

		/**
		* Operadores de Atualizacao
		*/

		/**
		* Operador de atualizacao de soma.
		*/
		VECTOR3& operator += (const VECTOR3& Vector);

		/**
		* Operador de atualizacao de saubtraacao.
		*/
		VECTOR3& operator -= (const VECTOR3& Vector);

		/**
		* Operador de atualizacao de multiplicacao escalar.
		*/
		VECTOR3& operator *= (const Real Scalar);

		/**
		* Operador de atualizacao de divisao escalar.
		*/
		VECTOR3& operator /= (const Real Vector);


		/**
		* Operacoes de Algebra Linear
		*/

		/**
		* Retorna a Norma do vetor
		*/
		Real Norma(void)const;


		/**
		* Retorna a Norma ao quadrado do vetor
		*/
		Real Square_Norma(void)const;

		/**
		* Normaliza o vetor
        */
		Real Normalize(void);

		/**
		* Retorna o vetor normalizado
		*/
		VECTOR3 Get_Normalize(void)const;

		/**
		* Calcula o produto escalar entre dois vetores
		*/
		Real Dot(const VECTOR3& Vector)const;

		/**
		* Retorna o produto vetorial entre dois vetores
		*/
		VECTOR3 Cross(const VECTOR3& Vector)const;

		/**
		* Retorna o produto vetorial normalizado entre dois vetores
		*/
		VECTOR3 Unit_Cross(const VECTOR3& Vector)const;

		/**
		* Operadores de atribuicao
		*/

		/**
		* Atribui as novas coordenadas do vetor
		*/
		void Set(Real X,Real Y,Real Z);

		/**
		* Atribui as novas coordenadas do vetor dado um vetor
		*/
		void Set(const VECTOR3& Vector);

		/**
		* Dado um vetor de Reais...
		*/
		/** 
		* constante
		*/
		void Set(const Real* Vector);

		/**
		* Nao constante
		*/
		void Set(Real* Vector);

		/**
		* Cria uma base orthonormal
		*/
		/**
		* N e input e deve estar normalizado
		*/
		static void Create_Orthonormal_Basis(const VECTOR3<Real>& N,VECTOR3<Real>& U,VECTOR3<Real>& V);
        
};
#include "vector3.inl"

typedef  VECTOR3<float> VECTOR3f;

#endif
