/**
* Modulo de declaracao da classe COLLISION_NODE.COLLISION_NODE ,um
* volume envolvente associado e os ponteiros para a construcao da hierarquia
* de volumes envolventes.
* @author Fabio I Nakamura
* @version 1.0b
*/

#ifndef __COL_LIB_COLLISION_NODE_H__
#define __COL_LIB_COLLISION_NODE_H__

#include "../math_library/boundingvolumes/boundingvolumes.h"
#include "../math_library/boundingvolumes/bounding_sphere.h"
#include "../math_library/boundingvolumes/bounding_aabb.h"
#include "../math_library/boundingvolumes/bounding_obb.h"
#include "../math_library/math_includes.h"
#include "../array/array.h"
#include "collision_contact_pair.h"

#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>

class COLLISION_NODE
{
	public:

		typedef enum bv_types
		{
			BV_AABB,
			BV_SPHERE,
			BV_OBB

		}BV_TYPES;

		typedef enum Collision_Options
		{
			ONLY_BV,
			ONLY_OBB_TREE,
			TRI_TRI,
			
		}COLLISION_OPTIONS;

	protected:

		/**
		* Enumeracoes da biblioteca
		*/
		typedef enum Collision_Node_Type
		{
			COL_NODE_LEAF,
			COL_NODE_INTERNAL,
			COL_NODE_SPECIAL

		}COLLISION_NODE_TYPE;

				
		/**
		* Identificador para o tipo de no que este Collision_Node vai ser
		*/
		COLLISION_NODE_TYPE Col_Type;

		/**
		* Todo no possui um volume envolvente associado.
		*/
		BOUNDING_VOLUME<float>* Bounding_Volume;

		/**
		* A matriz de transformacao aplicada a este no.
		* Esta matriz so pode possuir transformacoes de corpo rigido
		* (Rotacoes + translacoes).
		*/
		MATRIX4<float> Matrix;

		/**
		* O tipo do volume envolvente utilizado por este no.
		*/
		BV_TYPES BV_Type;


		/**
		* Determina o estado deste colision_node.Se Is_Up_to_Date == true
		* entao o no esta atualizado caso contrario deve-se fazer a 
		* atualizacao do volume envolvente.
		*/
		bool Is_Up_to_Date;

				
		/**
		* Testa se ha colisao entre o no atual e o no requesitado.
		* @param Self_Matrix A matriz correspondente ao no que chamou o metodo
		* @param Node O no que se deseja testar colisao
		* @param Node_Matrix A matriz correspondente ao no Node.
		* @param Options Determina o nivel de precisao que o usuario deseja na deteccao de colisao.
		*				 ONLY_BV:  Somente colisao entre volumes envolventes.
		*				 COLLISION_OBB_TREE: Somente colisao entre OBB-Trees se houverem (e tambem Volumes envolventes).
		*				 TRI_TRI:  Colisao a nivel de triangulo por triangulo
		* @result true se houve colisao, false caso contrario.
		*/
		bool Test_Collision(const MATRIX4<float>& Self_Matrix,COLLISION_NODE* Node,const MATRIX4<float>& Node_Matrix,COLLISION_OPTIONS Options);

		/**
		* Testa se ha colisao entre o no atual e o no requesitado.
		* @param Self_Matrix A matriz correspondente ao no que chamou o metodo
		* @param Node O no que se deseja testar colisao
		* @param Node_Matrix A matriz correspondente ao no Node.
		* @param Contacts. Onde sera retornado a lista de contatos
		* @result true se houve colisao, false caso contrario.
		*/
		bool Test_Collision_Contacts(const MATRIX4<float>& Self_Matrix,COLLISION_NODE* Node,const MATRIX4<float>& Node_Matrix,COLLISION_CONTACT_PAIR& Contacts);


		/**
		* Testa se ha colisao entre o volume envolvente do no que chamou atual e o no requesitado.Antes de iniciar
		* o teste de colisao, faz-se o update do no' que chamou o metodo e do no Node.
		* Nao se desce na hierarquia do no que chamou o metodo.
		* @param Self_Matrix A matriz correspondente ao no que chamou o metodo
		* @param Node O no que se deseja testar colisao
		* @param Node_Matrix A matriz correspondente ao no Node.
		* @param Options Determina o nivel de precisao que o usuario deseja na deteccao de colisao.
		*				 ONLY_BV:  Somente colisao entre volumes envolventes.
		*				 COLLISION_OBB_TREE: Somente colisao entre OBB-Trees se houverem (e tambem Volumes envolventes).
		*				 TRI_TRI:  Colisao a nivel de triangulo por triangulo
		* @result true se houve colisao, false caso contrario.
		*/
		bool Test_BV_Collision(const MATRIX4<float>& Self_Matrix,COLLISION_NODE* Node,const MATRIX4<float>& Node_Matrix,COLLISION_OPTIONS Options);

        /**
		* Testa se ha colisao entre o volume envolvente do no que chamou atual e o no requesitado.Antes de iniciar
		* o teste de colisao, faz-se o update do no' que chamou o metodo e do no Node.
		* Nao se desce na hierarquia do no que chamou o metodo.
		* @param Self_Matrix A matriz correspondente ao no que chamou o metodo
		* @param Node O no que se deseja testar colisao
		* @param Node_Matrix A matriz correspondente ao no Node.
		* @param Contacts. Onde sera retornado a lista de contatos
		* @result true se houve colisao, false caso contrario.
		*/
		bool Test_BV_Collision_Contacts(const MATRIX4<float>& Self_Matrix,COLLISION_NODE* Node,const MATRIX4<float>& Node_Matrix,COLLISION_CONTACT_PAIR& Contacts);


		/**
		* Testa se ha colisao entre o no atual e o no requesitado.
		* @param Self_Matrix A matriz correspondente ao no que chamou o metodo
		* @param Node O no que se deseja testar colisao
		* @param Node_Matrix A matriz correspondente ao no Node.
		* @param Point Endereco de INTERSECTION_POINT para retornar a normal do plano
					   e a profundidade de colisao.
		* @param Options Determina o nivel de precisao que o usuario deseja na deteccao de colisao.
		*				 ONLY_BV:  Somente colisao entre volumes envolventes.
		*				 COLLISION_OBB_TREE: Somente colisao entre OBB-Trees se houverem (e tambem Volumes envolventes).
		*				 TRI_TRI:  Colisao a nivel de triangulo por triangulo
		* @result true se houve colisao, false caso contrario.
		*/
//		bool Find_Intersection_Point(const MATRIX4<float>& Self_Matrix,COLLISION_NODE* Node,const MATRIX4<float>& Node_Matrix,INTERSECTION_POINT* Point,COLLISION_OPTIONS Options);

		/**
		* Testa se ha colisao entre a hierarquia e um plano dado por (a,b,c,d).
		*/
		bool PLANE_Collision_Test(const MATRIX4<float>& Self_Matrix,const PLANE3<float>& Plane,COLLISION_OPTIONS Options);


		/**
		* Testa se ha colisao entre um raio dado por ( O + td) e a hierarquia de colisao.
		* Se houver colisao entao retorna um valor maior do que 0, caso contrario nao ha colisao.
		*/
		float RAY_Collision_Test(const MATRIX4<float>& Self_Matrix,const RAY3D<float>& Ray,COLLISION_OPTIONS Options);

		/**
		* Testa se ha colisao entre um raio dado por ( O + td) e a hierarquia de colisao.
		* Se houver colisao entao retorna um valor maior do que 0, caso contrario nao ha colisao.
		*/
		float RAY_Collision_Test_Contacts(const MATRIX4<float>& Self_Matrix,const RAY3D<float>& Ray,COLLISION_CONTACT_PAIR& Contact);

		
			
		/**
		* Re calcula o volume envolvente deste no, baseado nos
		* volumes envolventes dos nos filho.
		* O resultado e guardado no proprio no.
		*/
		virtual void Re_Compute_BV(void)
		{
			return;
		}
		

		/**
		* Esta classe e abstrata
		* Faz a inicializacao dos atributos da classe
		*/
		COLLISION_NODE(void):Parent_Node(NULL),Bounding_Volume(NULL),Is_Up_to_Date(false),Is_Leaf(false)
		{
			this->Matrix.Set_Identity();
		};

		/**
		* Para acelerar o teste de colisao, guarda no no' se este e folha ou nao
		*/
		bool Is_Leaf;
			
	public:

		/**
		* Destrutor
		*/
		virtual ~COLLISION_NODE(void)
		{
			this->Destroy();
		};

		/**
		* Faz o update da hierarquia dependendo do tipo de no
		* Nos internos fazem merge do volume envolvente, nos folhas nao fazem nada.
		* Apesar de ser publico este metodo, nao deve ser chamado pelo usuario. E de uso
		* exclusivo interno.
		*/
		virtual int Update(void) = 0;
		

		/**
		* Ponteiro para o pai da classe na hierarquia.
		*/
		COLLISION_NODE* Parent_Node;		
						

		/**
		* Testa se ha colisao entre o no atual e o no requesitado.Antes de fazer
		* o teste de colisao, faz-se o update do no' que chamou o metodo e do no  Node.
		* @param Self_Matrix A matriz correspondente ao no que chamou o metodo
		* @param Node O no que se deseja testar colisao
		* @param Node_Matrix A matriz correspondente ao no Node.
		* @param Options Determina o nivel de precisao que o usuario deseja na deteccao de colisao.
		*				 ONLY_BV:  Somente colisao entre volumes envolventes.
		*				 COLLISION_OBB_TREE: Somente colisao entre OBB-Trees se houverem (e tambem Volumes envolventes).
		*				 TRI_TRI:  Colisao a nivel de triangulo por triangulo
		* @result true se houve colisao, false caso contrario.
		*/
		bool Start_Collision_Test(const float* Self_Matrix,COLLISION_NODE* Node,const float* Node_Matrix,COLLISION_OPTIONS Options)
		{
			MATRIX4<float> Self_Transform;
			MATRIX4<float> Node_Transform;
			
			if(Self_Matrix == NULL)
				Self_Transform.Set_Identity();
			else
				Self_Transform.Set(Self_Matrix);

			if(Node_Matrix == NULL)
				Node_Transform.Set_Identity();
			else
				Node_Transform.Set(Node_Matrix);
			
			// Faz o Update deste no e do no Node
			this->Update();
			Node->Update();
			return(this->Test_Collision(Self_Transform,Node,Node_Transform,Options));
		}

		/**
		* Testa se ha colisao entre o no atual e o no requesitado.Antes de fazer
		* o teste de colisao, faz-se o update do no' que chamou o metodo e do no'  Node.Retorna todos
		* os pares de contato.
		* @param Self_Matrix A matriz correspondente ao no' que chamou o metodo
		* @param Node O no' que se deseja testar colisao
		* @param Node_Matrix A matriz correspondente ao no Node.
		* @param Options Determina o nivel de precisao que o usuario deseja na deteccao de colisao.
		*				 ONLY_BV:  Somente colisao entre volumes envolventes.
		*				 COLLISION_OBB_TREE: Somente colisao entre OBB-Trees se houverem (e tambem Volumes envolventes).
		*				 TRI_TRI:  Colisao a nivel de triangulo por triangulo
		* @result true se houve colisao de algum triangulo contra algum triangulo, false caso contrario.
		* Se nao houver OBB_Trees associadas a hierarquia de colisao, entao falso sera retornado.
		 */
		bool Start_All_Pairs_Collision_Test(const float* Self_Matrix,COLLISION_NODE* Node,const float* Node_Matrix,COLLISION_CONTACT_PAIR& Contacts)
		{
			MATRIX4<float> Self_Transform;
			MATRIX4<float> Node_Transform;
			
			if(Self_Matrix == NULL)
				Self_Transform.Set_Identity();
			else
				Self_Transform.Set(Self_Matrix);

			if(Node_Matrix == NULL)
				Node_Transform.Set_Identity();
			else
				Node_Transform.Set(Node_Matrix);
			
			// Faz o Update deste no e do no Node
			this->Update();
			Node->Update();
      Contacts.Contact_Pairs.Remove_All();
			return(this->Test_Collision_Contacts(Self_Transform,Node,Node_Transform,Contacts));
		}


		/**
		* Testa se ha colisao entre o volume envolvente do no que chamou atual e o no requesitado.Antes de iniciar
		* o teste de colisao, faz-se o update do no' que chamou o metodo e do no Node.
		* Note que neste teste nao se desce na hierarquia do no que chamou o metodo.
		* @param Self_Matrix A matriz correspondente ao no que chamou o metodo
		* @param Node O no que se deseja testar colisao
		* @param Node_Matrix A matriz correspondente ao no Node.
		* @param Options Determina o nivel de precisao que o usuario deseja na deteccao de colisao.
		*				 ONLY_BV:  Somente colisao entre volumes envolventes.
		*				 COLLISION_OBB_TREE: Somente colisao entre OBB-Trees se houverem (e tambem Volumes envolventes).
		*				 TRI_TRI:  Colisao a nivel de triangulo por triangulo
		* @result true se houve colisao, false caso contrario.
		*/
		bool Start_BV_Collision_Test(const float* Self_Matrix,COLLISION_NODE* Node,const float* Node_Matrix,COLLISION_OPTIONS Options)
		{
			MATRIX4<float> Self_Transform;
			MATRIX4<float> Node_Transform;
            
			if(Self_Matrix == NULL)
				Self_Transform.Set_Identity();
			else
				Self_Transform.Set(Self_Matrix);

			if(Node_Matrix == NULL)
				Node_Transform.Set_Identity();
			else
				Node_Transform.Set(Node_Matrix);

			
			
			// Faz o Update deste no e do no Node
			this->Update();
			Node->Update();
			return(this->Test_BV_Collision(Self_Transform,Node,Node_Transform,Options));
		}

        /**
		* Testa se ha colisao entre o no atual e o no requesitado.Antes de fazer
		* o teste de colisao, faz-se o update do no' que chamou o metodo e do no'  Node.Retorna todos
		* os pares de contato.
		* @param Self_Matrix A matriz correspondente ao no' que chamou o metodo
		* @param Node O no' que se deseja testar colisao
		* @param Node_Matrix A matriz correspondente ao no Node.
		* @param Options Determina o nivel de precisao que o usuario deseja na deteccao de colisao.
		*				 ONLY_BV:  Somente colisao entre volumes envolventes.
		*				 COLLISION_OBB_TREE: Somente colisao entre OBB-Trees se houverem (e tambem Volumes envolventes).
		*				 TRI_TRI:  Colisao a nivel de triangulo por triangulo
		* @result true se houve colisao de algum triangulo contra algum triangulo, false caso contrario.
		* Se nao houver OBB_Trees associadas a hierarquia de colisao, entao falso sera retornado.
		 */
		bool Start_All_Pairs_BV_Collision_Test(const float* Self_Matrix,COLLISION_NODE* Node,const float* Node_Matrix,COLLISION_CONTACT_PAIR& Contacts)
		{
			MATRIX4<float> Self_Transform;
			MATRIX4<float> Node_Transform;
			
			if(Self_Matrix == NULL)
				Self_Transform.Set_Identity();
			else
				Self_Transform.Set(Self_Matrix);

			if(Node_Matrix == NULL)
				Node_Transform.Set_Identity();
			else
				Node_Transform.Set(Node_Matrix);
			
			// Faz o Update deste no e do no Node
			this->Update();
			Node->Update();
            Contacts.Contact_Pairs.Remove_All();
			return(this->Test_BV_Collision_Contacts(Self_Transform,Node,Node_Transform,Contacts));
		}


		/**
		* Testa se ha colisao entre o no atual e o no requesitado.Antes de comecar
		* o teste de colisao faz-se o update do no' que chamou o metodo e do no' Node.
		* @param Self_Matrix A matriz correspondente ao no que chamou o metodo
		* @param Node O no que se deseja testar colisao
		* @param Node_Matrix A matriz correspondente ao no Node.
		* @param Collision_Point Um vetor de float onde sera retornado a informacao de colisao.A ordem que segue e a seguinte.
		*				Collision_Point_Depth = a profundidade de colisao.
		*				Collision_Point[0] = A coordenada x do vetor que corresponde a direcao da colisao.
		*				Collision_Point[1] = A coordenada y do vetor que corresponde a direcao da colisao.
		*				Collision_Point[2] = A coordenada z do vetor que corresponde a direcao da colisao.
		*				OBS: Somente atribui os valores acima se houver colisao.Se nao houver colisao entao
		*				nada e escrito no vetor.
		*			   
		* @param Options Determina o nivel de precisao que o usuario deseja na deteccao de colisao.
		*				 ONLY_BV:  Somente colisao entre volumes envolventes.
		*				 COLLISION_OBB_TREE: Somente colisao entre OBB-Trees se houverem (e tambem Volumes envolventes).
		*				 TRI_TRI:  Colisao a nivel de triangulo por triangulo
		* @result true se houve colisao, false caso contrario.
		*/
		//bool Start_Find_Intersection_Point(const float* Self_Matrix,COLLISION_NODE* Node,const float* Node_Matrix,float* Collision_Point_Depth,
		//								   float* Collision_Point,COLLISION_OPTIONS Options);

		/**
		* Testa se ha colisao entre a hierarquia e um plano dado por (a,b,c,d).
		*/
		bool Start_PLANE_Collision_Test(const float* Self_Matrix,const float A,const float B,const float C,
										const float D,COLLISION_OPTIONS Options)
		{
			MATRIX4<float> Self;
			PLANE3<float> Plane(A,B,C,D);

			if(Self_Matrix == NULL)
				Self.Set_Identity();
			else
				Self.Set(Self_Matrix);
			
						
			// Faz o Update deste no e do no Node
			this->Update();
			return(this->PLANE_Collision_Test(Self,Plane,Options));
		}


		/**
		* Testa se ha colisao entre um raio dado por ( O + td) e a hierarquia de colisao.
		*/
		float Start_RAY_Collision_Test(const float* Self_Matrix,const float* Ray_Origin,const float* Ray_Direction,COLLISION_OPTIONS Options)
		{
			MATRIX4<float> Self;
			RAY3D<float> Ray(Ray_Origin,Ray_Direction);
			
			if(Self_Matrix == NULL)
				Self.Set_Identity();
			else
				Self.Set(Self_Matrix);

			this->Update();
			return(this->RAY_Collision_Test(Self,Ray,Options));
		}

		/**
		* Testa se ha colisao entre um raio dado por ( O + td) e a hierarquia de colisao.
		*/
		float Start_RAY_Collision_Test_Contacts(const float* Self_Matrix,const float* Ray_Origin,const float* Ray_Direction,COLLISION_CONTACT_PAIR& Contacts)
		{
			MATRIX4<float> Self;
			RAY3D<float> Ray(Ray_Origin,Ray_Direction);
			
			if(Self_Matrix == NULL)
				Self.Set_Identity();
			else
				Self.Set(Self_Matrix);

			this->Update();
			return(this->RAY_Collision_Test_Contacts(Self,Ray,Contacts));
		}

		
		/**
		* Determina se o volume envolvente deste no' ja foi 
		* criado e se e valido.
		* @return true se for folha, false caso contrario.
		*/
		bool Is_Created(void)const
		{
			if(this->Bounding_Volume)
			{
				return(this->Bounding_Volume->Is_BV_Created());
			}
			else
				return(false);
    }

		/**
		* Retorna o volume envolvente deste no
		*/
		const BOUNDING_VOLUME<float>* Get_Bounding_Volume(void)const
		{
			return(this->Bounding_Volume);
		}
		
		
		/**
		* Retorna o tipo de volume envolvente deste no'
		*/
		BV_TYPES Get_Type(void)const
		{
			return(this->BV_Type);
		}
		

		/** 
		* Faz a atualizacao da matriz correspondete a este no.
		* Toda vez que um no tiver sua matriz atualizada, todos os seus
		* ancestrais sao considerados desatualizados.
		* Matriz e um vetor de float de dimensao 16. O formato da matriz segue o 
		* padrao Opengl ou seja Column Major Order.
		* @param Matriz A nova matriz deste no
		*/
		void Set_Matrix(const float* Matrix);
				
			
		/**
		* Retorna a transformacao deste no' em relacao ao seu pai
		* @return O endereco da matriz do no' que chamou o metodo
		*/
		const MATRIX4<float>* Get_Matrix(void)const
		{
			return(&this->Matrix);
		}
		
				
		/**
		* Desenha Volume Envolvente correspondente ao no.
		* Funcao de teste visual por enquanto
		*/
		virtual void Render_BV(void) = 0;
		
		/** 
		* Destroi se existir o volume envolvente deste no'
		*/
		void Destroy_Bounding_Volume(void)
		{
			if(this->Bounding_Volume)
			{
				delete this->Bounding_Volume;
				this->Bounding_Volume = NULL;
			}
			return;
		}
		
		/** 
		* Destroi tudo alocado pelo no'
		*/
		virtual void Destroy(void)
		{
			this->Destroy_Bounding_Volume();
			return;
		}
		
};
#endif

