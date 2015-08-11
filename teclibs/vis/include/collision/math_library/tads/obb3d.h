/**
* Modulo de declaracao da classe OBB3D. Esta classe e responsavel por definir uma caixa orientada no espaco 3D
* @author: Fabio Nakamura
*/

#ifndef __OBB3D_H__
#define __OBB3D_H__

#include "vector3.h"

template <class Real> class OBB3D
{
	public:

		/**
		* A OBB e definida por um centro e uma base i , j e k com seus respectivos tamanhos.
		*/

		/**
		* O centro da OBB
		*/
		VECTOR3<Real> Center;

		/**
		* A extensao no eixo i
		*/
        Real i_Length;

		/**
		* A extensao no eixo j
		*/
		Real j_Length;

		/**
		* A extensao no eixo k
		*/
		Real k_Length;

		/**
		* A base de rotacao da OBB
		*/
		VECTOR3<Real> Axis_i;
		VECTOR3<Real> Axis_j;
		VECTOR3<Real> Axis_k;

		/**
		* Construtores
		*/

		/**
		* Vazio
		*/
		OBB3D(void);

		/**
		* Construtor de copia
		*/
		OBB3D(const OBB3D<Real>& Obb);

		/**
		* Construtor dado o centro , as extensoes e a base
		*/
		OBB3D(const VECTOR3<Real>& Center,const VECTOR3<Real>& Axis_i,const VECTOR3<Real>& Axis_j,const VECTOR3<Real>& Axis_k,
			  const Real i_Length,const Real j_Length,const Real K_Length);
		OBB3D(const VECTOR3<Real>& Center,const VECTOR3<Real>* Axis,const Real i_Length,const Real j_Length,const Real K_Length);
		OBB3D(const VECTOR3<Real>& Center,const Real* Axis_i,const Real* Axis_j,const Real* Axis_K,
			  const Real i_Length,const Real j_Length,const Real K_Length);
		
		/**
		* Calcula os vertices dessa caixa
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
		*/
		
		void Compute_Vextex(VECTOR3<Real> Vertex[8])const;

		/**
		* Deve ser um vetor de 8*3*sizeof(Real)
		*/
		void Compute_Vextex(Real* Vertex)const;

		/**
		* Metodos Set / Get
		*/
				
		/**
		* Atribui novo centro
		*/
		void Set_New_Center(const VECTOR3<Real>& New_Center);
		void Set_New_Center(const Real Center_x,const Real Center_y,const Real Center_z);

		/**
		* Onde New_Center[0] = Center.x e New_Center[1] = Center.y, New_Center[2] = Center.z
		*/
		void Set_New_Center(const Real* New_Center);

		/**
		* Atribui novas extensoes
		*/
		void Set_New_Extensions(const Real i_Length,const Real j_Length,const Real k_Length);

		
		/**
		* Atribui nova base
		*/
		void Set_New_Basis(const VECTOR3<Real>& New_Axis_i,const VECTOR3<Real>& New_Axis_j,const VECTOR3<Real>& New_Axis_k);

		/**
		* Onde New_Axis_i[0] = this->Axis_i.x e  New_Axis_i[1] = this->Axis_i.y New_Axis_i[2] = this->Axis_i.z 
		*      New_Axis_j[0] = this->Axis_j.x e  New_Axis_j[1] = this->Axis_j.y New_Axis_j[2] = this->Axis_j.z
		*	   New_Axis_k[0] = this->Axis_k.x e  New_Axis_k[1] = this->Axis_k.y New_Axis_k[2] = this->Axis_k.z
		*/
		void Set_New_Basis(const Real* New_Axis_i,const Real* New_Axis_j,const Real* New_Axis_k);


		void Set_New_Basis(const Real New_Axis_i_x,const Real New_Axis_i_y,const Real New_Axis_i_z,
						   const Real New_Axis_j_x,const Real New_Axis_j_y,const Real New_Axis_j_z,
						   const Real New_Axis_k_x,const Real New_Axis_k_y,const Real New_Axis_k_z);



};
#include "obb3d.inl"

typedef OBB3D<float> OBB3f;

#endif





