/**
* Modulo de declaracao de uma classe PLANE3.Esta classe tem como objetivo
* representar e implementar as funcoes basicas de operacoes sobre um plano.
* @author: Fabio Nakamura
*/

#ifndef __PLANE3_H__
#define __PLANE3_H__

#include "vector3.h"

template <class Real> class PLANE3
{
	public:

		/**
		* Um plano e definido por um vetor normal e uma distancia D.
		*/

		/**
		* A normal do plano
		*/
        VECTOR3<Real> Normal;

		/**
		* A constante D
		*/
		Real D;

		/**
		* Construtor
		*/
		/**
		* Construtor Vazio
		*/
		PLANE3(void);

		/**
		* Construtor dado um vetor e uma constante
		*/
		PLANE3(const VECTOR3<Real>& Normal,Real Distance);

		/**
		* Construtor dado 4 valores Reais A,B,C,D
		*/
		PLANE3(Real A,Real B,Real C,Real D);

		/**
		* Construtor dado um plano PLANE3
		*/
		PLANE3(const PLANE3& Plane);

		/**
		* Construtor dado uma normal e um ponto no plano.
		*/
		PLANE3(const VECTOR3<Real>& Normal,const VECTOR3<Real>& Point_in_Plane);

		/**
		* construtor dado 3 pontos no plano
		* o plano sera dado por N = (P1 - P0)x(P2 - P0) e D = N.P0
		*/
		PLANE3(const VECTOR3<Real>& P0,const VECTOR3<Real>& P1,const VECTOR3<Real>& P2);

		/**
		* Operadores sobre o plano
		*/

		/**
		* operator =
		*/
		PLANE3& operator = (const PLANE3& Plane);

		/**
		* A funcao retorna 1 se ponto estiver no semi plano na direcao da normal,
		* -1 se estiver no semi plano inverso a normal e 0 se estiver no plano
		*/
		int Which_Side(const VECTOR3<Real>& Point)const;

		/**
		* Retorna a distancia do ponto ao plano
		*/
		Real Distance_To(const VECTOR3<Real>& Point)const;


		/**
		* Constroi o plano dado 3 pontos (consideramos os 3 pontos como sendo um triangulo
		* orientado CCW
		*/
		void Build_Plane(const VECTOR3<Real>& V0,const VECTOR3<Real>& V1,const VECTOR3<Real>& V2);

};
#include "plane3.inl"
#endif
