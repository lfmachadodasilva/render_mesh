/**
* Modulo de declaracao do modulo BOUNDING_SPHERE. Esta classe tem como objetivo
* implementar uma esfera envolvente.
*/

#ifndef __BOUNDING_SPHERE_H__
#define __BOUNDING_SPHERE_H__

#include "boundingvolumes.h"
#include "bounding_aabb.h"
#include "bounding_obb.h"
#include "../tads/sphere.h"

#include <GL/glew.h>

template<class Real>
class BOUNDING_SPHERE :public BOUNDING_VOLUME<Real>
{
	
	protected:

		/**
		* A Esfera envolvente.
		*/
		SPHERE<Real> Sphere;

		/**
		* Para podermos desenhar a esfera envolvente devemos guardar
		* uma quadrica em Opengl para desenhar.Note isto e somente para
		* visualizacao e testes.
		* Pode ser destruido no futuro.
		* Quadrica para esfera 
		*/
		GLUquadricObj* Quad_Sphere;

	public:

		/**
		* Construtor
		*/
		/**
		* Constroi dado um vetor de vertices, o numero de vertices, e um offset
		*/
		BOUNDING_SPHERE(const Real* Vertices,unsigned int Num_of_Vertices):BOUNDING_VOLUME<Real>()
		{
			this->Create_Bounding_Volume(Vertices,Num_of_Vertices);
			this->BV_TYPE = BOUNDING_VOLUME<Real>::BV_SPHERE;
			this->Quad_Sphere = gluNewQuadric();
		}
		
		BOUNDING_SPHERE(void):BOUNDING_VOLUME<Real>()
		{
			this->Reset_Bounding_Volume();
			this->BV_TYPE = BOUNDING_VOLUME<Real>::BV_SPHERE;
			this->Quad_Sphere = gluNewQuadric();
		}

		/**
		* Destrutor
		*/
		~BOUNDING_SPHERE(void)
		{
			this->Destroy_Bounding_Volume();
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
			if(this->Quad_Sphere)
			{
				gluDeleteQuadric(this->Quad_Sphere);
				this->Quad_Sphere = NULL;
			}
			return;
		}


		/**
		* Faz a reinicializacao com valores default do volume envolvente
		*/
		void Reset_Bounding_Volume(void)
		{
			this->Sphere.Radius = (Real)0.0;
			this->Sphere.Set_New_Center((Real)0.0,(Real)0.0,(Real)0.0);
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
			BOUNDING_SPHERE<Real>* Aux = (BOUNDING_SPHERE*)Source_BV;

			this->Sphere.Center.Set(Aux->Sphere.Center);
			this->Sphere.Radius = Aux->Sphere.Radius;
			this->Bounding_Volume_Volume = Aux->Bounding_Volume_Volume;
			this->Is_Created = true;
			return;
		}

		/**
		* Retorna a AABB deste volume envolvente
		*/
		const SPHERE<Real>& Get_Sphere(void)const
		{
			return(this->Sphere);
		}

		/**
		* Atribui nova esfera
		*/
		void Set_New_Sphere(const VECTOR3<Real>& New_Center,Real New_Radius)
		{
			this->Sphere.Set_New_Center(New_Center);
			this->Sphere.Set_New_Radius(New_Radius);
            this->Bounding_Volume_Volume = (4*PI*this->Sphere.Radius*this->Sphere.Radius*this->Sphere.Radius)/(Real)3.0;
			return;
		}

};

typedef BOUNDING_SPHERE<float> BOUNDING_SPHEREf;

#endif
