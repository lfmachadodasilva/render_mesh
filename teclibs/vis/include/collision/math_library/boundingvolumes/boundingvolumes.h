/**
* Modulo de declaracao da classe Abstrada BOUNDING_VOLUMES.Esta classe tem como objetivo
* atribuir uma interface base para a implementacao de volumes envolvetes.
* @author: Fabio Nakamura
*/

#ifndef __BOUNDING_VOLUMES_H__
#define __BOUNDING_VOLUMES_H__

/**
* A principio esta classe de volumes envolventes esta sendo desenvolvida para dar 
* suporte a 3 tipos de volumes envolventes: SPHERE, AABB e OBB. Por isso os metodos 
* abstrados so se referem a estes BV.No caso de se desejar adicionar mais volumes entao
* o usuario sera responsavel por adicionar todos os metodos que fazem a colisao entre
* as primitivas ja existentes.
* As funcoes de colisao terao todas 2 tipos. Uma usando a classe TRANSFORMATION<Real> e outra
* usando matrizes genericas.
*/
/**
* Em todos os casos se MATRIX4 == 0 entao identidade e assumida como matriz
*/
/**
* Em todos os metodos que a transformacao for igual a MATRIX4, entao assumise- que nao
* havera escala no modelo.
*/

#include "../tads/matrix4.h"
#include "../tads/vector3.h"

#include "../queries/query_includes.h"
#include "../transformation/transformation.h"
#include "../intersections/3d/intersections.h"

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

template <class Real> class BOUNDING_VOLUME
{
	protected:

		/**
		* Esta classe e abstrada, logo devemos ter seu construtor protegido
		*/
		BOUNDING_VOLUME(void):Is_Created(false)
		{
		}

		/**
		* Determina se volume envolvente esta criado
		*/
		bool Is_Created;

		/**
		* O tipo de volume envolvente criado.
		*/
		int BV_TYPE;

		/**
		* O volume do volume envolvente
		*/
		Real Bounding_Volume_Volume;

	public:

		/**
		* Os tipos de Volume Envolvente.
		*/

		typedef enum bv_types
		{
			BV_SPHERE,
			BV_AABB,
			BV_OBB

		}BOUNDING_VOLUMES_TYPE;
		
		/**
		* Destrutor da classe
		*/
		virtual ~BOUNDING_VOLUME(void)
		{
		}

		/**
		* Esses sao os metodos que todas as classes que derivem de BOUNDING_VOLUME_3D
		* devem implementar
		*/

		/**
		* Para podermos deixar este modulo um pouco mais independente da engine
		* vamos trabalhar com primitivas basicas.
		*/

		/**
		* Dado um vetor de vertices , a quantidade de vertices 
		* cria-se o volume envolvente.
		*/
		virtual void Create_Bounding_Volume(const Real* Vertices,unsigned int Num_of_Vertices) = 0;

		
		/**
		* Destroi volume envolvente
		*/
        virtual void Destroy_Bounding_Volume(void) = 0;


		/**
		* Faz a reinicializacao com valores default do volume envolvente
		*/
		virtual void Reset_Bounding_Volume(void) = 0;

		/**
		* Faz a juncao (Merge) de dois volumes envolventes.Os volumes envolventes devem estar 
		* no mesmo espaco , para a correta juncao.
		* O resultado final sera do tipo : BVa += BVb
		* TRANSFORMATION<Real> e uma classe de Transformacao do volume envolvente a ser inserido.
		*/
		virtual void Merge_Bounding_Volumes(const BOUNDING_VOLUME* BoundVolume,const TRANSFORMATION<Real>* Matrix) = 0;

		/**
		* Faz a juncao (Merge) de dois volumes envolventes.Os volumes envolventes devem estar 
		* no mesmo espaco , para a correta juncao.
		* O resultado final sera do tipo : BVa += BVb
		* Real e um vetor que representa uma matrix 4x4 onde segue-se a ordem Column_Major_Order..
		*/
		virtual void Merge_Bounding_Volumes(const BOUNDING_VOLUME* BoundVolume,const MATRIX4<Real>* Matrix) = 0;

		/**
		* Retorna o tipo de volume envolvente que esta classe e
		*/
		int Get_BV_TYPE(void)const
		{
			return(this->BV_TYPE);
		}

		/**
		* Determina se BV esta criado
		*/
		bool Is_BV_Created(void)const
		{
			return(this->Is_Created);
		}

		/**
		* Testes de colisao
		*/

		/**
		* Testa a colisao entre o volume envolvente e um raio.Serve para implementacao de 
		* picking3D tambem.Retorna a menor distancia entre o raio e o BV se houver colisao.
		*/
		virtual Real Test_Ray_Collision(const TRANSFORMATION<Real>* My_Space,const VECTOR3<Real>& Ray_Origin,const VECTOR3<Real>& Ray_Direction)const = 0;
		virtual Real Test_Ray_Collision(const MATRIX4<Real>* My_Space,const VECTOR3<Real>& Ray_Origin,const VECTOR3<Real>& Ray_Direction)const = 0;


		/**
		* Testa a colisao entre o volume envolvente e um plano.
		*/
		virtual bool Test_Plane_Collision(const TRANSFORMATION<Real>* My_Space,const PLANE3<Real>& Plane,const TRANSFORMATION<Real>* Plane_Space)const = 0;
		virtual bool Test_Plane_Collision(const MATRIX4<Real>* My_Space,const PLANE3<Real>& Plane,const MATRIX4<Real>* Plane_Space)const = 0;
		
		/**
		* Testa a colisao entre o volume envolvente e um triangulo
		*/
		virtual bool Test_Triangle_Collision(const TRANSFORMATION<Real>* My_Space,const TRIANGLE3D<Real>& Triangle,const TRANSFORMATION<Real>* Triangle_Space)const = 0;
		virtual bool Test_Triangle_Collision(const MATRIX4<Real>* My_Space,const TRIANGLE3D<Real>& Triangle,const MATRIX4<Real>* Triangle_Space)const = 0;
		

		/**
		* Testa a colisao deste volume contra os outros volumes envolventes existentes na biblioteca.
		* BV e o volume envolvente definido pela assinatura da funcao. Nao ha garantias de funcionamento
		* se o usuario chamar o metodo com o volume envolvente diferente do esperado.
		*/
		virtual bool Test_Sphere_Collision(const TRANSFORMATION<Real>* My_Space,const BOUNDING_VOLUME* BV,const TRANSFORMATION<Real>* BV_Space)const = 0;
		virtual bool Test_Sphere_Collision(const MATRIX4<Real>* My_Space,const BOUNDING_VOLUME* BV,const MATRIX4<Real>* BV_Space)const = 0;

		/**
		* Testa a colisao deste volume contra os outros volumes envolventes existentes na biblioteca.
		* BV e o volume envolvente definido pela assinatura da funcao. Nao ha garantias de funcionamento
		* se o usuario chamar o metodo com o volume envolvente diferente do esperado.
		*/
		virtual bool Test_AABB_Collision(const TRANSFORMATION<Real>* My_Space,const BOUNDING_VOLUME* BV,const TRANSFORMATION<Real>* BV_Space)const = 0;
		virtual bool Test_AABB_Collision(const MATRIX4<Real>* My_Space,const BOUNDING_VOLUME* BV,const MATRIX4<Real>* BV_Space)const = 0;

		/**
		* Testa a colisao deste volume contra os outros volumes envolventes existentes na biblioteca.
		* BV e o volume envolvente definido pela assinatura da funcao. Nao ha garantias de funcionamento
		* se o usuario chamar o metodo com o volume envolvente diferente do esperado.
		*/
		virtual bool Test_OBB_Collision(const TRANSFORMATION<Real>* My_Space,const BOUNDING_VOLUME* BV,const TRANSFORMATION<Real>* BV_Space)const = 0;
		virtual bool Test_OBB_Collision(const MATRIX4<Real>* My_Space,const BOUNDING_VOLUME* BV,const MATRIX4<Real>* BV_Space)const = 0;


		/**
		* Testa a colisao entre dois BOUNDING_VOLUMES
		*/
		bool Test_Collision(const MATRIX4<Real>* My_Space,const BOUNDING_VOLUME* BV,const MATRIX4<Real>* BV_Space)const
		{
			if(BV->BV_TYPE == BV_AABB)
			{
				return(this->Test_AABB_Collision(My_Space,BV,BV_Space));
			}
			else if(BV->BV_TYPE == BV_SPHERE)
			{
				return(this->Test_Sphere_Collision(My_Space,BV,BV_Space));				
			}
			else
			{
				return(this->Test_OBB_Collision(My_Space,BV,BV_Space));
			}				
		}
		
		bool Test_Collision(const TRANSFORMATION<Real>* My_Space,const BOUNDING_VOLUME* BV,const TRANSFORMATION<Real>* BV_Space)const
		{
			if(BV->BV_TYPE == BV_AABB)
			{
				return(this->Test_AABB_Collision(My_Space,BV,BV_Space));
			}
			else if(BV->BV_TYPE == BV_SPHERE)
			{
				return(this->Test_Sphere_Collision(My_Space,BV,BV_Space));				
			}
			else
			{
				return(this->Test_OBB_Collision(My_Space,BV,BV_Space));
			}
		}



		/**
		* Para teste de Culling
		* Dado um plano determina em qual lado o volume envolvente esta.
		* Se resultado == 1 entao esta no semi plano positivo, se 0 entao corta plano e se 
		* -1 entao esta no semi plano negativo.
		*/
		virtual int Which_Side(const TRANSFORMATION<Real>* My_Space,const PLANE3<Real>& Plane,const TRANSFORMATION<Real>* Plane_Space)const  = 0;
		virtual int Which_Side(const MATRIX4<Real>* My_Space,const PLANE3<Real>& Plane,const MATRIX4<Real>* Plane_Space)const = 0;
		
		/**
		* Funcao de DEBUG !!
		*/
		virtual void Render_BV(void)const = 0;


		/**
		* Metodo responsavel por transformar um volume envolvente
		* BV_Result sera um ponteiro para o volume a ser usado.Como esta classe
		* e abstrada, entao nao sabemos ainda se e uma esfera, caixa alinhada ou caixa orientada.
		*/
		virtual void Transform_BV(const TRANSFORMATION<Real>* My_Space,BOUNDING_VOLUME* Result_BV)const = 0;
		virtual void Transform_BV(const MATRIX4<Real>* My_Space,BOUNDING_VOLUME* Result_BV)const = 0;

		/**
		* Metodo responsavel por fazer uma copia do volume envolvente.
		*/
		virtual void Copy_BV(const BOUNDING_VOLUME* Source_BV) = 0;

		/**
		* Retorna o volume do volume envolvente
		*/
		Real Get_Volume(void)const
		{
			return(Bounding_Volume_Volume);
		}	

};

typedef BOUNDING_VOLUME<float> BOUNDING_VOLUMEf;

#endif

