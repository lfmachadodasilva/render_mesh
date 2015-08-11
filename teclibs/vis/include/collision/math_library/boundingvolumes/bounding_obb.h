/**
* Modulo de declaracao da classe BOUNDING_OBB, para representar uma volume envolvente
* como sendo uma OBB.
* @author: Fabio Nakamura
*/

#ifndef __BOUNDING_OBB_H__
#define __BOUNDING_OBB_H__

#include "boundingvolumes.h"
#include "bounding_sphere.h"
#include "bounding_aabb.h"
#include "../tads/obb3d.h"

template<class Real>
class BOUNDING_OBB :public BOUNDING_VOLUME<Real>
{
	
	protected:

		/**
		* A AABB envolvente.
		*/
		OBB3D<Real> OBB;

		Real Minimum_Area_Rectangle(const VECTOR2<Real>* Points,unsigned int Num_of_Points,
									VECTOR2<Real>* Center,VECTOR2<Real>* Axis_i,VECTOR2<Real>* Axis_j,
									Real* Ext_i,Real* Ext_j);

	
	public:
		/**
		* Construtor
		*/
		/**
		* Constroi dado um vetor de vertices, o numero de vertices, e um offset
		*/
		BOUNDING_OBB(const Real* Vertices,unsigned int Num_of_Vertices):BOUNDING_VOLUME<Real>()
		{
			this->Create_Bounding_Volume(Vertices,Num_of_Vertices);
			this->BV_TYPE = BOUNDING_VOLUME<Real>::BV_OBB;
			
		}
		
		BOUNDING_OBB(void):BOUNDING_VOLUME<Real>()
		{
			this->Reset_Bounding_Volume();
			this->BV_TYPE = BOUNDING_VOLUME<Real>::BV_OBB;
		}


		/**
		* Destrutor
		*/
		~BOUNDING_OBB(void)
		{
		}

		/**
		* Dado um vetor de vertices , a quantidade de vertices 
		* cria-se o volume envolvente.
		*/
		void Create_Bounding_Volume(const Real* Vertices,unsigned int Num_of_Vertices) ;

		
		/**
		* Destroi volume envolvente
		*/
         void Destroy_Bounding_Volume(void)
		 {
			 return;
		 }


		/**
		* Faz a reinicializacao com valores default do volume envolvente
		*/
		void Reset_Bounding_Volume(void)
		{
			this->OBB.Set_New_Basis(VECTOR3<Real>((Real)1.0,(Real)0.0,(Real)0.0),
							VECTOR3<Real>((Real)0.0,(Real)1.0,(Real)0.0),
							VECTOR3<Real>((Real)0.0,(Real)0.0,(Real)1.0));
			this->OBB.Set_New_Center((Real)0.0,(Real)0.0,(Real)0.0);
			this->OBB.Set_New_Extensions((Real)0.0,(Real)0.0,(Real)0.0);
			this->Is_Created = false;
			this->Bounding_Volume_Volume = (Real)0.0;
			return;
		}

		/**
		* Faz a juncao (Merge) de dois volumes envolventes.Os volumes envolventes devem estar 
		* no mesmo espaco , para a correta juncao.
		* O resultado final sera do tipo : BVa += BVb
		* TRANSFORMATION<Real> e uma classe de Transformacao do volume envolvente a ser inserido.
		*/
		void Merge_Bounding_Volumes(const BOUNDING_VOLUME<Real>* BoundVolume,const TRANSFORMATION<Real>* Matrix) ;

		/**
		* Faz a juncao (Merge) de dois volumes envolventes.Os volumes envolventes devem estar 
		* no mesmo espaco , para a correta juncao.
		* O resultado final sera do tipo : BVa += BVb
		* Real e um vetor que representa uma matrix 4x4 onde segue-se a ordem Column_Major_Order..
		*/
		void Merge_Bounding_Volumes(const BOUNDING_VOLUME<Real>* BoundVolume,const MATRIX4<Real>* Matrix) ;

		
		/**
		* Testes de colisao
		*/

		/**
		* Testa a colisao entre o volume envolvente e um raio.Serve para implementacao de 
		* picking3D tambem.Retorna a menor distancia entre o raio e o BV se houver colisao.
		*/
		Real Test_Ray_Collision(const TRANSFORMATION<Real>* My_Space,const VECTOR3<Real>& Ray_Origin,const VECTOR3<Real>& Ray_Direction)const ;
		Real Test_Ray_Collision(const MATRIX4<Real>* My_Space,const VECTOR3<Real>& Ray_Origin,const VECTOR3<Real>& Ray_Direction)const ;


		/**
		* Testa a colisao entre o volume envolvente e um plano.
		*/
		bool Test_Plane_Collision(const TRANSFORMATION<Real>* My_Space,const PLANE3<Real>& Plane,const TRANSFORMATION<Real>* Plane_Space)const ;
		bool Test_Plane_Collision(const MATRIX4<Real>* My_Space,const PLANE3<Real>& Plane,const MATRIX4<Real>* Plane_Space)const ;

		/**
		* Testa a colisao entre o volume envolvente e um triangulo
		*/
		bool Test_Triangle_Collision(const TRANSFORMATION<Real>* My_Space,const TRIANGLE3D<Real>& Triangle,const TRANSFORMATION<Real>* Triangle_Space)const;
		bool Test_Triangle_Collision(const MATRIX4<Real>* My_Space,const TRIANGLE3D<Real>& Triangle,const MATRIX4<Real>* Triangle_Space)const;
		
		/**
		* Testa a colisao deste volume contra os outros volumes envolventes existentes na biblioteca.
		* BV e o volume envolvente definido pela assinatura da funcao. Nao ha garantias de funcionamento
		* se o usuario chamar o metodo com o volume envolvente diferente do esperado.
		*/
		bool Test_Sphere_Collision(const TRANSFORMATION<Real>* My_Space,const BOUNDING_VOLUME<Real>* BV,const TRANSFORMATION<Real>* BV_Space)const ;
		bool Test_Sphere_Collision(const MATRIX4<Real>* My_Space,const BOUNDING_VOLUME<Real>* BV,const MATRIX4<Real>* BV_Space)const ;

		/**
		* Testa a colisao deste volume contra os outros volumes envolventes existentes na biblioteca.
		* BV e o volume envolvente definido pela assinatura da funcao. Nao ha garantias de funcionamento
		* se o usuario chamar o metodo com o volume envolvente diferente do esperado.
		*/
		bool Test_AABB_Collision(const TRANSFORMATION<Real>* My_Space,const BOUNDING_VOLUME<Real>* BV,const TRANSFORMATION<Real>* BV_Space)const ;
		bool Test_AABB_Collision(const MATRIX4<Real>* My_Space,const BOUNDING_VOLUME<Real>* BV,const MATRIX4<Real>* BV_Space)const ;

		/**
		* Testa a colisao deste volume contra os outros volumes envolventes existentes na biblioteca.
		* BV e o volume envolvente definido pela assinatura da funcao. Nao ha garantias de funcionamento
		* se o usuario chamar o metodo com o volume envolvente diferente do esperado.
		*/
		bool Test_OBB_Collision(const TRANSFORMATION<Real>* My_Space,const BOUNDING_VOLUME<Real>* BV,const TRANSFORMATION<Real>* BV_Space)const ;
		bool Test_OBB_Collision(const MATRIX4<Real>* My_Space,const BOUNDING_VOLUME<Real>* BV,const MATRIX4<Real>* BV_Space)const ;

		/**
		* Para teste de Culling
		* Dado um plano determina em qual lado o volume envolvente esta.
		* Se resultado == 1 entao esta no semi plano positivo, se 0 entao corta plano e se 
		* -1 entao esta no semi plano negativo.
		*/
		int Which_Side(const TRANSFORMATION<Real>* My_Space,const PLANE3<Real>& Plane,const TRANSFORMATION<Real>* Plane_Space)const  ;
		int Which_Side(const MATRIX4<Real>* My_Space,const PLANE3<Real>& Plane,const MATRIX4<Real>* Plane_Space)const ;
		
		/**
		* Funcao de DEBUG !!
		*/
		void Render_BV(void)const ;


		/**
		* Metodo responsavel por transformar um volume envolvente
		* BV_Result sera um ponteiro para o volume a ser usado.Como esta classe
		* e abstrada, entao nao sabemos ainda se e uma esfera, caixa alinhada ou caixa orientada.
		*/
		void Transform_BV(const TRANSFORMATION<Real>* My_Space,BOUNDING_VOLUME<Real>* Result_BV)const;
		void Transform_BV(const MATRIX4<Real>* My_Space,BOUNDING_VOLUME<Real>* Result_BV)const ;

		/**
		* Metodo responsavel por fazer uma copia do volume envolvente.
		*/
		void Copy_BV(const BOUNDING_VOLUME<Real>* Source_BV)
		{
			BOUNDING_OBB<Real>* Aux = (BOUNDING_OBB*)Source_BV;
			this->OBB.Set_New_Basis(Aux->OBB.Axis_i,Aux->OBB.Axis_j,Aux->OBB.Axis_k);
			this->OBB.Set_New_Center(Aux->OBB.Center);
			this->OBB.Set_New_Extensions(Aux->OBB.i_Length,Aux->OBB.j_Length,Aux->OBB.k_Length);
			this->Bounding_Volume_Volume = Aux->Bounding_Volume_Volume;
			this->Is_Created = true;
			
			return;
		}

		/**
		* Retorna a OBB deste volume envolvente
		*/
		const OBB3D<Real>& Get_OBB3D(void)const
		{
			return(this->OBB);
		}

		/**
		* Atribui uma nova OBB
		*/
		void Set_New_OBB(const VECTOR3<Real>& New_Center,const VECTOR3<Real>& New_Extents,
						 const VECTOR3<Real>& New_Axis_i,const VECTOR3<Real>& New_Axis_j,const VECTOR3<Real>& New_Axis_k)
		{
			this->OBB.Set_New_Center(New_Center);
			this->OBB.Set_New_Extensions(New_Extents.x,New_Extents.y,New_Extents.z);
			this->OBB.Set_New_Basis(New_Axis_i,New_Axis_j,New_Axis_k);
            Real Volume;
	        Real dx,dy,dz;

	        dx = (Real)2.0*this->OBB.i_Length;
	        dy = (Real)2.0*this->OBB.j_Length;
	        dz = (Real)2.0*this->OBB.k_Length;
        	
	        Volume = dx*dy*dz;
	        this->Bounding_Volume_Volume = Volume;
			return;
		}

};


typedef BOUNDING_OBB<float> BOUNDING_OBBf;

#endif

