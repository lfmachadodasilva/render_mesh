/**
* Modulo de declaracao de uma classe SEGMENT2D.Esta classe tem como objetivo
* representar um segmento 2D.Um segmento e dado por um ponto O (origem), mais
* uma direcao e a extensao ( O + eD) e ( O - ed);
* @author: Fabio Nakamura
*/

#ifndef __SEGMENT2D_H__
#define __SEGMENT2D_H__

#include "vector2.h"

template<class Real> class SEGMENT2D
{
	public:

		/**
		* A origem do segmento
		*/
		VECTOR2<Real> m_A;

		/**
		* A direcao do segmento
		*/
		VECTOR2<Real> m_B;

		
		/**
		* Construtor
		*/
		SEGMENT2D(void);


		/**
		* Constroi segmento dado dois pontos A e B; Direction = B-A e origem = A
		*/
		SEGMENT2D(const VECTOR2<Real>& A,const VECTOR2<Real>& B);

		/**
		* Faz o set do segmento dado dois pontos A e B . A e menor que B
		*/
		void Set_New_Segment(const VECTOR2<Real>& A,const VECTOR2<Real>& B);

};
#include "segment2d.inl"

#endif


