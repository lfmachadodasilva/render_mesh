/**
* Modulo de declaracao de uma caixa alinhada 2d.
* @author: Fabio Nakamura
*/

#ifndef __AABB2D_H__
#define __AABB2D_H__

#include "vector2.h"

template <class Real> class AABB2D
{
	public:

		/**
		* O ponto minimo da caixa
		*/
		VECTOR2<Real> Min_Point;

		/**
		* O ponto maximo da caixa
		*/
		VECTOR2<Real> Max_Point;

	
		/**
		* Construtor
		*/
		/**
		* Vazio
		*/
		AABB2D(void);

		/**
		* Copia
		*/
		AABB2D(const AABB2D<Real>& Box);

		/**
		* Dado dois vetores Min e Max
		*/
		AABB2D(const VECTOR2<Real>& Min_Point,const VECTOR2<Real>& Max_Point);

		/**
		* dado os valores reais dos pontos
		*/
		AABB2D(const Real Min_x,const Real Max_x,const Real Min_y,const Real Max_y);

		/**
		* Dado dois vetores Min e Max de tamanho 2
		*/
		AABB2D(const Real* Min_Point,const Real* Max_Point);

		/**
		* Metodos Get e Set
		*/
		
		/**
		* Retorna o centro da caixa
		* O centro sera dado por ( (Min_Point + Max_Point)/2
		*/
		VECTOR2<Real> Get_Center(void)const;

		/**
		* Retorna a extensao da caixa em X e Y
		* A extensao e dada por ((Max_Point - Min_Point)/2
		*/
		void Get_Extensions(Real& Extension_x,Real& Extension_y)const;
		void Get_Extensions(VECTOR2<Real>& Extensions)const;

		/**
		* Novo ponto minimo
		*/
		void Set_New_Min_Point(const VECTOR2<Real>& New_Min_Point);
		void Set_New_Min_Point(const Real* New_Min_Point);
		void Set_New_Min_Point(const Real New_Min_Point_x,const Real New_Min_Point_y);

		void Set_New_Max_Point(const VECTOR2<Real>& New_Max_Point);
		void Set_New_Max_Point(const Real* New_Max_Point);
		void Set_New_Max_Point(const Real New_Max_Point_x,const Real New_Max_Point_y);

		/**
		* Calcula os vertices dessa caixa alinhada.
		*/
		void Compute_Vextex(VECTOR2<Real> Vertex[4])const;

		/**
		* Deve ser um vetor de 4*2*sizeof(Real)
		* A ordem e dada da seguinte maneira:
		*   3- - - -  2 
		*   |         |
		*   |         |
		*   0 - - - - 1 
		*/
		void Compute_Vextex(Real* Vertex)const;

};
#include "aabb2d.inl"

typedef AABB2D<float> AABB2f;

#endif




