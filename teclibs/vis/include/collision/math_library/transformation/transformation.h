/**
* Modulo de declaracao de uma classe TRANSFORMATION.Esta classe tem como objetivo
* guardar as 3 matrizes de transformacao ( Rotacao, Escala e Translacao do no).
* alem de aplicar de forma correta as transformacoes.
* @author: Fabio Nakamura
*/

#ifndef ___TRANSFORMATION_H__
#define ___TRANSFORMATION_H__

#include "../tads/vector3.h"
#include "../tads/matrix3.h"
#include "../tads/matrix4.h"
#include "../tads/plane3.h"

template<class Real>
class TRANSFORMATION
{
	public:

		/**
		* A matriz de rotacao do no.
		*/
		MATRIX3<Real> Rotation;

		/**
		* Vetor de translacao
		*/
		VECTOR3<Real> Translation;

		/*
		* A escala uniforme
		*/
		Real Scale;

		/**
		* Se for identidade
		*/
		bool Is_Identity;
    
	public:	

		/**
		* Construtor
		*/

		/**
		* Vazio
		*/
		TRANSFORMATION(void);		

		/**
		* Copia
		*/
		TRANSFORMATION(const TRANSFORMATION<Real>& Transformation);

		/**
		* Atribuicao
		*/
		TRANSFORMATION(const MATRIX3<Real>& Rotation,const Real Scale,const VECTOR3<Real>& Translation);

		/**
		* Querries
		*/
		bool Is_Identity_Matrix(void)const;
		void Make_Identity(void);
		
		/**
		* Metodos de atribuicao
		*/

		/**
		* Rotacoes
		*/
		void Set_Rotate(const MATRIX3<Real>& Rotation);
		void Set_Rotate(const VECTOR3<Real>& Axis_X,const VECTOR3<Real>& Axis_Y,const VECTOR3<Real>& Axis_Z);
		void Set_Rotate(const VECTOR3<Real>& Axis,Real Angle);
		const MATRIX3<Real>& Get_Rotate(void)const;

		/**
		* Translacoes
		*/
		void Set_Translate(const VECTOR3<Real>& Translation);
		void Set_Translate(const Real tx,const Real ty,const Real tz);
		const VECTOR3<Real>& Get_Translate(void)const;

		/**
		* Escalas
		*/
		void Set_Uniform_Scale(const Real Scale);
		const Real Get_Uniform_Scale(void)const;

		/**
		* Dado uma Transformacao, copia para this
		*/
		void Set_Transformation(const TRANSFORMATION<Real>& Trans);

		/**
		* Retorna uma matriz que corresponde a concatenacao dos blocos
		* | RS T |
		  | 0  1 |
		*/
		MATRIX4<Real> Get_4x4_Matrix(void)const;

		/**
		* Aplica a transformacao desta classe no ponto e retorna o 
		* resultado.
		*/
		VECTOR3<Real> Apply_Transform(const VECTOR3<Real>& Point)const;
		
		/**
		* Aplica a transformacao desta classe no vetor de pontos e retorna o 
		* resultado no vetor de saida.E responsabilidade do usuario entrar com 
		* vetores de tamanho certo.
		*/
		void Apply_Transform(unsigned int Quantity,VECTOR3<Real>* Input_Point,
								VECTOR3<Real>* Output_Point)const;

		/**
		* Aplica a transformacao desta classe no vetor e retorna o 
		* resultado.
		*/
		VECTOR3<Real> Apply_Transform_Vector(const VECTOR3<Real>& Vector)const;

		/**
		* Aplica a transformacao desta classe no vetor de vetor e retorna o 
		* resultado no vetor de saida.E responsabilidade do usuario entrar com 
		* vetores de tamanho certo.
		*/
		void Apply_Transform_Vector(unsigned int Quantity,VECTOR3<Real>* Input_Vector,
								VECTOR3<Real>* Output_Vector)const;

		/**
		* Aplica a matriz inversa ao ponto e retorna o vetor resultante.
		*/
		VECTOR3<Real> Apply_Inverse(const VECTOR3<Real>& Point)const;

		/**
		* Aplica a transformacao desta classe no vetor de pontos e retorna o 
		* resultado inverso no vetor de saida.E responsabilidade do usuario entrar com 
		* vetores de tamanho certo.
		*/
		void Apply_Inverse(unsigned int Quantity,VECTOR3<Real>* Input_Point,
								VECTOR3<Real>* Output_Point)const;

		/**
		* Aplica a matriz inversa ao vetor e retorna o vetor resultante.
		*/
		VECTOR3<Real> Apply_Inverse_Vector(const VECTOR3<Real>& Vector)const;

		/**
		* Aplica a transformacao desta classe no vetor de vetores e retorna o 
		* resultado inverso no vetor de saida.E responsabilidade do usuario entrar com 
		* vetores de tamanho certo.
		*/
		void Apply_Inverse_Vector(unsigned int Quantity,VECTOR3<Real>* Input_Vector,
								VECTOR3<Real>* Output_Vector)const;


		/**
		* A transformacao de um plano e diferente da transformacao de um vetor
		* ou ponto, por isso este metodo a parte.
		*/
		PLANE3<Real> Apply_Plane_Transform(const PLANE3<Real>& Plane)const;

		/**
		* Retorna em Inv_Transformation, as transformacoes inversas da 
		* instancia de transformation que chamou o metodo.
		*/
		void Get_Inverse(TRANSFORMATION<Real>& Inv_Transformation)const;


		/**
		* Concatena duas transformacoes e retorna a nova transformacao
		* C = AxB
		*/
		TRANSFORMATION<Real> Concatene(const TRANSFORMATION<Real>& Trans)const;

		/**
		* Concatena duas transformacoes
		* A = AxB
		*/
		void Concatene(const TRANSFORMATION<Real>& Trans);

		/**
		* Esta transformacao e a concatenacao de outras duas.
		* this = AxB
		*/
		void Concatene(const TRANSFORMATION<Real>& Trans_A,const TRANSFORMATION<Real>& Trans_B);

};

#include "transformation.inl"

typedef TRANSFORMATION<float> TRANSFORMATIONf;

#endif
