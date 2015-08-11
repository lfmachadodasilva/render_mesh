/**
* Modulo de declaracao do modulo BOUNDING_AABB. Esta classe tem como objetivo
* implementar uma caixa alinhada envolvente.
*/

#ifndef __BOUNDING_AABB_H__
#define __BOUNDING_AABB_H__

#include "boundingvolumes.h"
#include "bounding_sphere.h"
#include "bounding_obb.h"
#include "../tads/aabb3d.h"

template<class Real>
class BOUNDING_AABB :public BOUNDING_VOLUME<Real>
{
	protected:
		
		/**
		* A AABB envolvente.
		*/
		AABB3D<Real> AABB;

	public:
		/**
		* Construtor
		*/
		/**
		* Constroi dado um vetor de vertices, o numero de vertices, e um offset
		*/
		BOUNDING_AABB(const Real* Vertices,unsigned int Num_of_Vertices):BOUNDING_VOLUME<Real>()
		{
			this->Create_Bounding_Volume(Vertices,Num_of_Vertices);
			this->BV_TYPE = BOUNDING_VOLUME<Real>::BV_AABB;
		}
		
		BOUNDING_AABB(void):BOUNDING_VOLUME<Real>()
		{
			this->Reset_Bounding_Volume();
			this->BV_TYPE = BOUNDING_VOLUME<Real>::BV_AABB;
		}

		/**
		* Destrutor
		*/
		~BOUNDING_AABB(void)
		{
		}

		/**
		* Dado um vetor de vertices , a quantidade de vertices 
		* cria-se o volume envolvente.
		*/
		void Create_Bounding_Volume(const Real* Vertices,unsigned int Num_of_Vertices);

		
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
			this->AABB.Max_Point.Set((Real)0.0,(Real)0.0,(Real)0.0);
			this->AABB.Min_Point.Set((Real)0.0,(Real)0.0,(Real)0.0);
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
			BOUNDING_AABB<Real>* Aux = (BOUNDING_AABB*)Source_BV;
			this->AABB.Set_New_Max_Point(Aux->AABB.Max_Point);
			this->AABB.Set_New_Min_Point(Aux->AABB.Min_Point);	
			this->Bounding_Volume_Volume = Aux->Bounding_Volume_Volume;
			this->Is_Created = true;
			return;
		}

		/**
		* Retorna a AABB deste volume envolvente
		*/
		const AABB3D<Real>& Get_AABB3D(void)const
		{
			return(this->AABB);
		}

		/**
		* Atribui nova AABB
		*/
		void Set_New_AABB(const VECTOR3<Real>& New_Min_Point,const VECTOR3<Real>& New_Max_Point)
		{
			this->AABB.Set_New_Max_Point(New_Max_Point);
			this->AABB.Set_New_Min_Point(New_Min_Point);
            Real Volume;
            Real dx,dy,dz;

            dx = fabs(New_Max_Point.x - New_Min_Point.x);
            dy = fabs(New_Max_Point.y - New_Min_Point.y);
            dz = fabs(New_Max_Point.z - New_Min_Point.z);
            Volume = dx*dy*dz;

            this->Bounding_Volume_Volume = Volume;
			return;
		}

};

typedef BOUNDING_AABB<float> BOUNDING_AABBf;


#endif
