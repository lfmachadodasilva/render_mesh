/**
* Modulo de declaracao de uma classe RAY3D.Esta classe tem como objetivo
* representar um raio 3D.Uma linha e dado por um ponto O (origem), mais
* uma direcao*t;T aqui representa qualquer valor real > 0
* @author: Fabio Nakamura
*/

#ifndef __RAY3D_H__
#define __RAY3D_H__

#include "vector3.h"

template<class Real> class RAY3D
{
	public:

		/**
		* A origem da linha
		*/
		VECTOR3<Real> Origin;

		/**
		* A direcao da linha normalizado
		*/
		VECTOR3<Real> Direction;
		

	

		/**
		* Construtor
		*/
		RAY3D(void);


		/**
		* Constroi segmento dado uma origem, direcao e extensao
		*/
		RAY3D(const VECTOR3<Real>& Origin,const VECTOR3<Real>& Direction);


		/**
		* Metodos Set / Get
		*/

		/**
		* Retorna origem
		*/
		VECTOR3<Real> Get_Origin(void)const;

		/**
		* Retorna direcao
		*/
		VECTOR3<Real> Get_Direction(void)const;

	
		/**
		* Atribui nova origem
		*/
		void Set_New_Origin(const VECTOR3<Real>& Origin);

		/**
		* Atribui nova direcao
		*/
		void Set_New_Direction(const VECTOR3<Real>& Direction);
		
};
#include "ray3d.inl"

#endif


