/**
* Modulo de declaracao de uma classe VECTOR2D.
* Esta classe tem como objetivo implementar as funcoes basicas
* de uma biblioteca de vetor 2D
* @Author: Fabio Nakamura
*/

#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__

#include <math.h>
#include "constants.h"

template <class Real> class VECTOR2
{
	public:

		/**
		* Atributos da classe
		*/

		/**
		* Coordenada X
		*/
		Real x;

		/**
		* Coordenada Y
		*/
		Real y;

		/**
		* Construtores
		*/

		/**
		* Constroi um vetor dado X e Y
		*/
		VECTOR2(const Real X,const Real Y);

		/**
		* Construtor Vazio
		*/
		VECTOR2(void);

		/**
		* construtor dado um outro VECTOR2
		*/
		VECTOR2(const VECTOR2& Vector);

		/**
		* Dado um vetor de elementos
		*/
		VECTOR2(const Real* Vector);

		/**
		* Operadores de Acesso
		*/
		operator const Real*()const;
		operator Real*();
		VECTOR2& operator = (const VECTOR2& Vector);

		/**
		* Operadores aritmeticos
		*/

		/**
		* Soma dois vetores
		*/
		VECTOR2 operator + (const VECTOR2& Vector)const;

		/**
		* Subtrai dois vetores
		*/
		VECTOR2 operator - (const VECTOR2& Vector)const;

		/**
		* Multiplica o vetor por um escalar
		*/
		VECTOR2 operator * (const Real Scalar)const;

		/**
		* Divide um vetor por um escalar
		*/
		VECTOR2 operator / (const Real Scalar)const;

		/**
		* Retorna o vetor inverso a que chamou
		*/
		VECTOR2 operator -(void)const;

		/**
		* Operadores de atualizacao
		*/
		VECTOR2& operator += (const VECTOR2& Vector);
		VECTOR2& operator -= (const VECTOR2& Vector);
		VECTOR2& operator *= (const Real Scalar);
		VECTOR2& operator /= (const Real Scalar);

		/**
		* Operadores Logicos
		*/

		/**
		* Compara dois vetores e determina se eles sao iguais
		*/
		bool operator == (const VECTOR2& Vector)const;

		/**
		* Compara dois vetores e determina se eles sao diferentes
		*/
		bool operator != (const VECTOR2& Vector)const;

		/**
		* Operadores vetoriais em 2 dimensoes
		*/

		/**
		* Retorna a norma do vetor
		*/
		Real Norma(void)const;

		/**
		* Retorna o quadrado da norma do vetor
		*/
		Real Square_Norma(void)const;

		/**
		* Retorna o produto escalar entre os dois vetores
		*/
		Real Dot(const VECTOR2& Vector)const;

		/**
		* Normaliza o vetor
		*/
		Real Normalize(void);

		/**
		* Retorna o vetor normalizado
		*/
		VECTOR2 Get_Normalize(void)const;
        
		/**
		* retorna um vetor perpendicular a this
		*/
		VECTOR2 Get_Perpendicular(void)const;

		/**
		* retorna um vetor perpendicular unitario a this
		*/
		VECTOR2 Get_Unit_Perpendicular(void)const;

		/**
		* Retorna o produto vetorial entre dois vetore.
		* Se o produto for positivo entao this - Origin esta no sentido horario de vector
		* caso contrario se for negativo this - Origin, esta no sentido anti horario de vector
		* e se for zero entao eles sao colineares.
		*/
		Real Cross(const VECTOR2& Origin,const VECTOR2& Vector)const;

		/**
		* Retorna o escalar que determina se u esta a direita ou a esquerda de v
		*/
		Real Cross_2D(const VECTOR2& v1)const;

		/**
		* Operadores de atribuicao
		*/

		/**
		* Atribui as novas coordenadas do vetor
		*/
		void Set(Real X,Real Y);

		/**
		* Atribui as novas coordenadas do vetor dado um vetor
		*/
		void Set(const VECTOR2& Vector);

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
		* U e input e deve estar normalizado
		*/
		static void Create_Orthonormal_Basis(const VECTOR2<Real>& U,VECTOR2<Real>& V);



};
#include "vector2.inl"

typedef VECTOR2<float> VECTOR2f;

#endif
