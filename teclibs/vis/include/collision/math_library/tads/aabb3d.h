/**
* Modulo de declaracao de uma caixa alinhada 3d.
* @author: Fabio Nakamura
*/

#ifndef __AABB3D_H__
#define __AABB3D_H__

#include "vector3.h"

template <class Real> class AABB3D
{
	public:

		/**
		* O ponto minimo da caixa
		*/
		VECTOR3<Real> Min_Point;

		/**
		* O ponto maximo da caixa
		*/
		VECTOR3<Real> Max_Point;

	
		/**
		* Construtor
		*/
		/**
		* Vazio
		*/
		AABB3D(void);

		/**
		* Copia
		*/
		AABB3D(const AABB3D<Real>& Box);

		/**
		* Dado dois vetores Min e Max
		*/
		AABB3D(const VECTOR3<Real>& Min_Point,const VECTOR3<Real>& Max_Point);

		/**
		* dado os valores reais dos pontos
		*/
		AABB3D(const Real Min_x,const Real Max_x,const Real Min_y,const Real Max_y,const Real Min_z,const Real Max_z);

		/**
		* Dado dois vetores Min e Max de tamanho 2
		*/
		AABB3D(const Real* Min_Point,const Real* Max_Point);

		/**
		* Metodos Get e Set
		*/
		
		/**
		* Retorna o centro da caixa
		* O centro sera dado por ( (Min_Point + Max_Point)/2
		*/
		VECTOR3<Real> Get_Center(void)const;

		/**
		* Retorna a extensao da caixa em X e Y
		* A extensao e dada por ((Max_Point - Min_Point)/2
		*/
		void Get_Extensions(Real& Extension_x,Real& Extension_y,Real& Extension_z)const;
		void Get_Extensions(VECTOR3<Real>& Extensions)const;

		/**
		* Novo ponto minimo
		*/
		void Set_New_Min_Point(const VECTOR3<Real>& New_Min_Point);
		void Set_New_Min_Point(const Real* New_Min_Point);
		void Set_New_Min_Point(const Real New_Min_Point_x,const Real New_Min_Point_y,const Real New_Min_Point_z);

		void Set_New_Max_Point(const VECTOR3<Real>& New_Max_Point);
		void Set_New_Max_Point(const Real* New_Max_Point);
		void Set_New_Max_Point(const Real New_Max_Point_x,const Real New_Max_Point_y,const Real New_Max_Point_z);

		/**
		* Calcula os vertices dessa caixa alinhada.
		*/
		/**
		* Ordem dos vertices
		*
		*
		*    7 - - - - 6
		*   -         -|
		*  3 - - - - 2 
		*  |         | |
		*  |4 - - - -|5
		*  |         | 
		*  0 - - - - 1
		*
		*/
		void Compute_Vextex(VECTOR3<Real> Vertex[8])const;

		/**
		* Deve ser um vetor de 8*3*sizeof(Real)
		*/
		void Compute_Vextex(Real* Vertex)const;

};
#include "aabb3d.inl"

typedef AABB3D<float> AABB3f;
#endif




